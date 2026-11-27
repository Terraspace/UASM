"use strict";
const vscode = require("vscode"),
  path = require("node:path"),
  assert = require("node:assert/strict"),
  fs = require("node:fs");
async function eventually(action, check) {
  const end = Date.now() + 20000;
  while (Date.now() < end) {
    const result = await action();
    if (check(result)) return result;
    await new Promise((r) => setTimeout(r, 100));
  }
  throw new Error("Timed out waiting for provider result");
}
async function run() {
  const root = path.resolve(__dirname, ".."),
    uri = vscode.Uri.file(path.join(root, "examples", "tour.asm"));
  const ext = vscode.extensions.getExtension("terraspace.uasm-intellisense");
  assert.ok(ext);
  await ext.activate();
  const doc = await vscode.workspace.openTextDocument(uri),
    editor = await vscode.window.showTextDocument(doc);
  assert.equal(doc.languageId, "uasm");
  const original = doc.getText(),
    messages = [];
  async function checkLine(text, expect) {
    await editor.edit((edit) =>
      edit.replace(
        new vscode.Range(0, 0, doc.lineCount, 0),
        original + "\n" + text,
      ),
    );
    const position = new vscode.Position(
      doc.lineCount - 1,
      doc.lineAt(doc.lineCount - 1).text.length,
    );
    const result = await eventually(
      () =>
        vscode.commands.executeCommand(
          "vscode.executeCompletionItemProvider",
          uri,
          position,
        ),
      (r) =>
        r?.items?.some(
          (i) =>
            (typeof i.label === "string" ? i.label : i.label.label) === expect,
        ),
    );
    messages.push("PASS completion " + text + " -> " + expect);
    return result;
  }
  await checkLine("Win32::", "WriteFile");
  await checkLine("point.", "NameSpace");
  await checkLine("(Demo::Point PTR [rax]).", "x");
  await checkLine("counter->", "Add");
  await checkLine("shell->", "QueryInterface");
  await checkLine("boot->", "Open");
  await editor.edit((edit) =>
    edit.replace(
      new vscode.Range(0, 0, doc.lineCount, 0),
      original + "\nINVOKE Win32::WriteFile, 1, ",
    ),
  );
  const pos = new vscode.Position(
    doc.lineCount - 1,
    doc.lineAt(doc.lineCount - 1).text.length,
  );
  const help = await eventually(
    () =>
      vscode.commands.executeCommand(
        "vscode.executeSignatureHelpProvider",
        uri,
        pos,
      ),
    (r) => r?.signatures?.length > 0,
  );
  assert.equal(help.activeParameter, 1);
  assert.equal(help.signatures[0].parameters.length, 5);
  messages.push("PASS INVOKE signature");
  const definition = await vscode.commands.executeCommand(
    "vscode.executeDefinitionProvider",
    uri,
    new vscode.Position(1, 12),
  );
  assert.ok(definition?.length);
  messages.push("PASS INCLUDE definition");
  const inc = await vscode.workspace.openTextDocument(
    vscode.Uri.file(path.join(root, "examples", "types.inc")),
  );
  const edit = new vscode.WorkspaceEdit();
  edit.insert(inc.uri, new vscode.Position(4, 0), "    unsavedField DWORD ?\n");
  await vscode.workspace.applyEdit(edit);
  await checkLine("point.", "unsavedField");
  await vscode.window.showTextDocument(inc);
  await vscode.commands.executeCommand("workbench.action.files.revert");
  await vscode.window.showTextDocument(doc);
  await vscode.commands.executeCommand("workbench.action.files.revert");
  fs.mkdirSync(path.join(root, ".test-data"), { recursive: true });
  fs.writeFileSync(
    path.join(root, ".test-data", "host-results.txt"),
    messages.join("\n") + "\n",
  );
  console.log(messages.join("\n"));
}
module.exports = { run };
