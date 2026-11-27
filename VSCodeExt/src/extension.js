"use strict";
const vscode = require("vscode");
const path = require("node:path");
const { Worker } = require("node:worker_threads");
const core = require("./core");
const { plainDefines } = require("./settings");
const { loadProject, normalize } = require("./project");
const selector = ["uasm", "asm", "masm", "assembly"].map((language) => ({
  language,
  scheme: "file",
}));
const kinds = {
  namespace: "Module",
  struct: "Struct",
  union: "Struct",
  class: "Class",
  interface: "Interface",
  rawinterface: "Interface",
  typedef: "TypeParameter",
  procedure: "Function",
  method: "Method",
  macro: "Function",
  variable: "Variable",
  local: "Variable",
  parameter: "Variable",
  field: "Field",
  constant: "Constant",
  text: "Constant",
  record: "Struct",
  label: "Reference",
};

function configuration(document) {
  const config = vscode.workspace.getConfiguration("uasm", document.uri);
  const folder =
    vscode.workspace.getWorkspaceFolder(document.uri)?.uri.fsPath ||
    path.dirname(document.uri.fsPath);
  const expand = (p) =>
    p
      .replace(/\$\{workspaceFolder\}/g, folder)
      .replace(/\$\{env:([^}]+)\}/g, (_, key) => process.env[key] || "");
  return {
    includePaths: config
      .get("includePaths", [])
      .map((p) => path.resolve(folder, expand(p))),
    defines: plainDefines(config.get("defines", {})),
    caseSensitive: config.get("caseSensitive", false),
    maxIncludeFiles: config.get("maxIncludeFiles", 1000),
    maxFileSizeKB: config.get("maxFileSizeKB", 2048),
    maxIndexLines: config.get("maxIndexLines", 250000),
    maxCompletions: config.get("maxCompletions", 200),
    largeNamespaceThreshold: config.get("largeNamespaceThreshold", 1000),
    namespaceMinPrefix: config.get("namespaceMinPrefix", 2),
    suggestInstructions: config.get("suggestInstructions", true),
  };
}
function suppressed(text) {
  let quote = "";
  for (let i = 0; i < text.length; i++) {
    const c = text[i];
    if (quote) {
      if (c === quote) {
        if (text[i + 1] === quote) i++;
        else quote = "";
      }
    } else if (c === ";") return true;
    else if (c === '"' || c === "'") quote = c;
  }
  return !!quote;
}
class IndexService {
  constructor(output) {
    this.output = output;
    this.generation = 0;
    this.cache = new Map();
    this.diskCache = new Map();
    this.workers = new Set();
    this.watchers = new Map();
    this.disposed = false;
  }
  invalidate(file) {
    this.generation++;
    this.cache.clear();
    if (file) this.diskCache.delete(normalize(file));
    for (const worker of this.workers) worker.terminate();
  }
  dispose() {
    this.disposed = true;
    for (const worker of this.workers) worker.terminate();
    for (const w of this.watchers.values()) w.dispose();
  }
  async get(document) {
    const key = normalize(document.uri.fsPath);
    const generation = this.generation;
    if (this.cache.has(key)) {
      const result = await this.cache.get(key);
      return generation === this.generation ? result : null;
    }
    const promise = this.build(document, generation).catch((error) => {
      if (generation === this.generation) {
        this.cache.delete(key);
        this.output.appendLine(error.stack || String(error));
      }
      return null;
    });
    this.cache.set(key, promise);
    if (this.cache.size > 8) this.cache.delete(this.cache.keys().next().value);
    const result = await promise;
    if (this.disposed) return null;
    if (generation !== this.generation) return null; // Never answer from an obsolete edit snapshot.
    return result;
  }
  async build(document, generation) {
    const started = Date.now(),
      options = configuration(document),
      overlays = new Map();
    for (const doc of vscode.workspace.textDocuments)
      if (doc.uri.scheme === "file")
        overlays.set(normalize(doc.uri.fsPath), doc.getText());
    const input = await loadProject(
      document.uri.fsPath,
      options,
      overlays,
      this.diskCache,
    );
    if (this.disposed || generation !== this.generation) return null;
    const model = await new Promise((resolve, reject) => {
      const worker = new Worker(path.join(__dirname, "index-worker.js"), {
        workerData: input,
      });
      this.workers.add(worker);
      const cleanup = () => {
        clearTimeout(timer);
        this.workers.delete(worker);
      };
      const timer = setTimeout(() => {
        worker.terminate();
        cleanup();
        reject(new Error("UASM index timed out; reduce include/index limits."));
      }, 30000);
      worker.once("message", (result) => {
        cleanup();
        result.error ? reject(new Error(result.error)) : resolve(result.model);
      });
      worker.once("error", (error) => {
        cleanup();
        reject(error);
      });
      worker.once("exit", (code) => {
        cleanup();
        if (code) reject(new Error("UASM index worker exited: " + code));
      });
    });
    Object.setPrototypeOf(model, core.Model.prototype);
    for (const index of model.scopes.values())
      Object.setPrototypeOf(index, core.NameIndex.prototype);
    // Watch INCLUDE parents, including explicit absolute paths outside the workspace.
    for (const dir of new Set(
      [...model.files]
        .map((file) => path.dirname(file))
        .concat(options.includePaths),
    )) {
      if (this.watchers.has(dir)) continue;
      const watcher = vscode.workspace.createFileSystemWatcher(
        new vscode.RelativePattern(dir, "*"),
      );
      watcher.onDidChange((uri) => this.invalidate(uri.fsPath));
      watcher.onDidCreate((uri) => this.invalidate(uri.fsPath));
      watcher.onDidDelete((uri) => this.invalidate(uri.fsPath));
      this.watchers.set(dir, watcher);
    }
    this.output.appendLine(
      path.basename(document.uri.fsPath) +
        ": " +
        model.symbols.length +
        " symbols, " +
        model.files.size +
        " files, " +
        (Date.now() - started) +
        " ms; " +
        model.issues.length +
        " index notices.",
    );
    return model;
  }
}
function documentation(s) {
  const md = new vscode.MarkdownString();
  md.isTrusted = false;
  md.appendCodeblock(s.qualified + "\n" + core.detail(s), "uasm");
  if (s.documentation) md.appendText(s.documentation);
  if (s.synthetic) md.appendText("\nBuilt-in macrolib declaration.");
  if (s.kind === "method" && s.signatureKnown === false)
    md.appendText(
      "\nSignature unavailable until the METHOD implementation is included.",
    );
  return md;
}
function symbolAt(model, document, position) {
  const line = document.lineAt(position.line).text,
    range = document.getWordRangeAtPosition(position, /[A-Za-z_@$?][\w@$?]*/);
  if (!range) return null;
  const prefix = line.slice(0, range.end.character),
    ctx = model.context(normalize(document.uri.fsPath), position.line);
  const expression = core.expressionSuffix(prefix);
  return (
    model.resolveExpression(expression, ctx)?.symbol ||
    model.lookup(document.getText(range), ctx)
  );
}
function activate(context) {
  const output = vscode.window.createOutputChannel("UASM IntelliSense"),
    service = new IndexService(output);
  const status = vscode.window.createStatusBarItem(
    vscode.StatusBarAlignment.Right,
    20,
  );
  status.command = "uasm.showIndex";
  status.text = "UASM";
  status.tooltip = "UASM IntelliSense index";
  let debounce;
  const supported = (doc) =>
    doc &&
    selector.some((s) => s.language === doc.languageId) &&
    doc.uri.scheme === "file";
  const schedule = (doc) => {
    clearTimeout(debounce);
    if (supported(doc)) debounce = setTimeout(() => service.get(doc), 200);
  };
  context.subscriptions.push(
    output,
    status,
    {
      dispose: () => {
        clearTimeout(debounce);
        service.dispose();
      },
    },
    vscode.workspace.onDidChangeTextDocument((e) => {
      if (e.contentChanges.length) {
        service.invalidate();
        schedule(e.document);
      }
    }),
    vscode.workspace.onDidSaveTextDocument((doc) => {
      service.invalidate(doc.uri.fsPath);
      schedule(doc);
    }),
    vscode.workspace.onDidCloseTextDocument(() => service.invalidate()),
    vscode.workspace.onDidChangeConfiguration((e) => {
      if (e.affectsConfiguration("uasm")) {
        service.diskCache.clear();
        service.invalidate();
        schedule(vscode.window.activeTextEditor?.document);
      }
    }),
    vscode.window.onDidChangeActiveTextEditor((editor) => {
      if (supported(editor?.document)) {
        status.show();
        schedule(editor.document);
      } else status.hide();
    }),
    vscode.commands.registerCommand("uasm.reindex", async () => {
      service.diskCache.clear();
      service.invalidate();
      const doc = vscode.window.activeTextEditor?.document;
      if (supported(doc)) await service.get(doc);
    }),
    vscode.commands.registerCommand("uasm.showIndex", async () => {
      const doc = vscode.window.activeTextEditor?.document;
      if (!supported(doc)) return;
      const model = await service.get(doc);
      if (!model) return;
      output.appendLine(
        "\n" +
          doc.uri.fsPath +
          "\n" +
          model.files.size +
          " source files; " +
          model.symbols.length +
          " symbols; " +
          model.count +
          " source lines.",
      );
      for (const notice of model.issues.slice(0, 100))
        output.appendLine(notice);
      if (model.issues.length > 100)
        output.appendLine(
          "Additional notices omitted: " + (model.issues.length - 100),
        );
      output.show(true);
    }),
  );
  let vocabulary = [];
  try {
    vocabulary = require("./vocabulary.json");
  } catch {
    /* Development before build. */
  }
  context.subscriptions.push(
    vscode.languages.registerCompletionItemProvider(
      selector,
      {
        async provideCompletionItems(document, position, token) {
          const prefix = document
            .lineAt(position.line)
            .text.slice(0, position.character);
          if (suppressed(prefix)) return;
          const model = await service.get(document);
          if (!model || token.isCancellationRequested) return;
          const opts = configuration(document),
            result = core.completions(
              model,
              normalize(document.uri.fsPath),
              position.line,
              prefix,
              opts,
            );
          const range = new vscode.Range(
            position.translate(0, -result.prefix.length),
            position,
          );
          if (result.needsPrefix) {
            const hint = new vscode.CompletionItem(
              "Type " +
                opts.namespaceMinPrefix +
                " or more characters to filter " +
                result.total.toLocaleString() +
                " symbols",
              vscode.CompletionItemKind.Text,
            );
            hint.insertText = result.prefix;
            hint.filterText = result.prefix;
            hint.range = range;
            hint.detail =
              "Large namespace — results are capped at " + opts.maxCompletions;
            hint.sortText = "~";
            return new vscode.CompletionList([hint], true);
          }
          const items = result.items.map((s) => {
            const item = new vscode.CompletionItem(
              s.name,
              vscode.CompletionItemKind[kinds[s.kind]] ||
                vscode.CompletionItemKind.Variable,
            );
            item.detail = core.detail(s) + (s.ns ? " — " + s.ns : "");
            item.documentation = documentation(s);
            item.range = range;
            item.insertText = s.name;
            item.sortText = "0_" + s.name.toLowerCase();
            return item;
          });
          if (
            opts.suggestInstructions &&
            result.mode === "symbol" &&
            items.length < opts.maxCompletions
          ) {
            // No instruction suggestions in member/namespace lists or argument lists.
            if (/^\s*[.\w@$?]*$/.test(prefix)) {
              for (const name of vocabulary) {
                if (!name.toLowerCase().startsWith(result.prefix.toLowerCase()))
                  continue;
                if (items.length >= opts.maxCompletions) {
                  result.more = true;
                  break;
                }
                const item = new vscode.CompletionItem(
                  name,
                  vscode.CompletionItemKind.Keyword,
                );
                item.range = range;
                item.detail = "UASM instruction / directive";
                item.sortText = "1_" + name;
                items.push(item);
              }
            }
          }
          return new vscode.CompletionList(items, result.more);
        },
      },
      ".",
      ">",
      ":",
    ),
  );
  context.subscriptions.push(
    vscode.languages.registerSignatureHelpProvider(
      selector,
      {
        async provideSignatureHelp(document, position, token) {
          const current = document
            .lineAt(position.line)
            .text.slice(0, position.character);
          if (suppressed(current)) return;
          const model = await service.get(document);
          if (!model || token.isCancellationRequested) return;
          const start = Math.max(0, position.line - 40);
          const text = document.getText(
            new vscode.Range(start, 0, position.line, position.character),
          );
          const found = core.signature(
            model,
            normalize(document.uri.fsPath),
            position.line,
            text,
          );
          if (!found) return;
          const s = found.symbol;
          if (s.signatureKnown === false) return;
          const info = new vscode.SignatureInformation(
            core.signatureLabel(s),
            documentation(s),
          );
          info.parameters = s.params.map(
            (p) =>
              new vscode.ParameterInformation(
                p.name + (p.type ? ": " + p.type : ""),
              ),
          );
          const help = new vscode.SignatureHelp();
          help.signatures = [info];
          help.activeSignature = 0;
          help.activeParameter = Math.min(
            found.active,
            Math.max(0, s.params.length - 1),
          );
          return help;
        },
      },
      "(",
      ",",
      " ",
    ),
  );
  context.subscriptions.push(
    vscode.languages.registerHoverProvider(selector, {
      async provideHover(document, position, token) {
        if (
          suppressed(
            document.lineAt(position.line).text.slice(0, position.character),
          )
        )
          return;
        const model = await service.get(document);
        if (!model || token.isCancellationRequested) return;
        const s = symbolAt(model, document, position);
        if (s) return new vscode.Hover(documentation(s));
      },
    }),
  );
  context.subscriptions.push(
    vscode.languages.registerDefinitionProvider(selector, {
      async provideDefinition(document, position, token) {
        const model = await service.get(document);
        if (!model || token.isCancellationRequested) return;
        const include = model.includes.find(
          (i) =>
            i.uri === normalize(document.uri.fsPath) &&
            i.line === position.line,
        );
        if (include?.target)
          return new vscode.Location(
            vscode.Uri.file(include.target),
            new vscode.Position(0, 0),
          );
        const s = symbolAt(model, document, position);
        if (s)
          return new vscode.Location(
            vscode.Uri.file(s.uri),
            new vscode.Position(s.line, 0),
          );
      },
    }),
  );
  context.subscriptions.push(
    vscode.languages.registerDocumentSymbolProvider(selector, {
      async provideDocumentSymbols(document, token) {
        const model = await service.get(document);
        if (!model || token.isCancellationRequested) return [];
        return model.symbols
          .filter(
            (s) =>
              s.uri === normalize(document.uri.fsPath) &&
              !s.synthetic &&
              !s.owner,
          )
          .map((s) => {
            const start = new vscode.Position(s.line, 0),
              end = new vscode.Position(
                Math.min(s.endLine, document.lineCount - 1),
                document.lineAt(
                  Math.min(s.endLine, document.lineCount - 1),
                ).text.length,
              );
            return new vscode.DocumentSymbol(
              s.name,
              core.detail(s),
              vscode.SymbolKind[kinds[s.kind]] || vscode.SymbolKind.Variable,
              new vscode.Range(start, end),
              new vscode.Range(start, start),
            );
          });
      },
    }),
  );
  if (supported(vscode.window.activeTextEditor?.document)) {
    status.show();
    schedule(vscode.window.activeTextEditor.document);
  }
  return { service };
}
module.exports = { activate };
