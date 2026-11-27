"use strict";
// Editor-independent semantic model. No assembler or macro execution.
const ID = "[A-Za-z_@$?][\\w@$?]*";
const QID = "(?:::)?" + ID + "(?:::" + ID + ")*";
const primitive =
  /^(?:byte|sbyte|word|sword|dword|sdword|fword|qword|sqword|tbyte|oword|xmmword|ymmword|zmmword|real[48]|real10|db|dw|dd|df|dq|dt|do|dy|dz|ptr|near|far|void|voidarg)$/i;
const reg =
  /^(?:[re]?(?:ax|bx|cx|dx|si|di|sp|bp)|r(?:[89]|[12]\d|3[01])(?:[dwb])?|[xyz]mm\d+)$/i;
const qualify = (ns, name) =>
  name.startsWith("::") ? name.slice(2) : (ns ? ns + "::" : "") + name;
const parent = (ns) =>
  ns.includes("::") ? ns.slice(0, ns.lastIndexOf("::")) : "";
const unangle = (s) =>
  s
    .trim()
    .replace(/^<(.*)>$/, "$1")
    .trim();
function stripComment(s) {
  let quote = "";
  for (let i = 0; i < s.length; i++) {
    const c = s[i];
    if (quote) {
      if (c === quote) {
        if (s[i + 1] === quote) i++;
        else quote = "";
      }
    } else if (c === '"' || c === "'") quote = c;
    else if (c === ";") return s.slice(0, i);
  }
  return s;
}
function splitTop(s, separator = ",", angles = true) {
  let quote = "",
    depth = 0,
    square = 0,
    angle = 0,
    start = 0;
  const parts = [];
  for (let i = 0; i < s.length; i++) {
    const c = s[i];
    if (quote) {
      if (c === quote) {
        if (s[i + 1] === quote) i++;
        else quote = "";
      }
      continue;
    }
    if (c === '"' || c === "'") {
      quote = c;
      continue;
    }
    if (c === "(") depth++;
    if (c === ")") depth = Math.max(0, depth - 1);
    if (c === "[") square++;
    if (c === "]") square = Math.max(0, square - 1);
    if (angles && c === "<" && s[i + 1] !== "=") angle++;
    if (angles && c === ">" && s[i - 1] !== "-") angle = Math.max(0, angle - 1);
    if (c === separator && !depth && !square && !angle) {
      parts.push(s.slice(start, i).trim());
      start = i + 1;
    }
  }
  parts.push(s.slice(start).trim());
  return parts;
}
function logicalLines(text) {
  const lines = text.split(/\r?\n/),
    out = [];
  let delimiter = "";
  for (let i = 0; i < lines.length; i++) {
    const raw = lines[i],
      line = i;
    if (delimiter) {
      if (raw.includes(delimiter)) delimiter = "";
      out.push({ line, end: i, text: "", comment: "" });
      continue;
    }
    const block = /^\s*COMMENT\s+(\S)(.*)$/i.exec(raw);
    if (block) {
      if (!block[2].includes(block[1])) delimiter = block[1];
      out.push({ line, end: i, text: "", comment: "" });
      continue;
    }
    let code = stripComment(raw);
    while (/\\\s*$/.test(code) && i + 1 < lines.length)
      code = code.replace(/\\\s*$/, " ") + stripComment(lines[++i]);
    out.push({
      line,
      end: i,
      text: code.trim(),
      comment: raw.slice(stripComment(raw).length).replace(/^;\s*/, ""),
    });
  }
  return out;
}
function typeSpec(text) {
  return (
    new RegExp(
      "^\\s*((?:(?:near|far)(?:16|32|64)?\\s+)?(?:ptr\\s+)*(?:" + QID + "))",
      "i",
    )
      .exec(text)?.[1]
      .trim() || ""
  );
}
function parameters(text) {
  return splitTop(text.replace(/^\s*,/, ""))
    .filter(Boolean)
    .map((p, i) => {
      const m = new RegExp(
        "^\\s*(" + ID + ")?(?:\\s*\\[[^\\]]*\\])?\\s*:\\s*(.+)$",
        "i",
      ).exec(p);
      return m
        ? {
            name: m[1] || "arg" + (i + 1),
            type: m[2].trim(),
            optionalName: !m[1],
          }
        : { name: p.replace(/:=.*$/, "").trim(), type: "" };
    });
}
function procedureTail(tail) {
  let returnType = "",
    m = /^\s*\(([^)]*)\)/.exec(tail);
  if (m) {
    returnType = m[1].trim();
    tail = tail.slice(m[0].length);
  }
  const start = new RegExp("(?:" + ID + "\\s*)?:").exec(tail);
  return {
    returnType,
    params: start ? parameters(tail.slice(start.index)) : [],
  };
}
// Sorted name indexes support prefix lookup in O(log n + returned items).
class NameIndex {
  constructor() {
    this.items = [];
    this.sorted = false;
  }
  add(s) {
    this.items.push(s);
    this.sorted = false;
  }
  query(prefix = "", limit = 200) {
    if (!this.sorted) {
      this.items.sort((a, b) =>
        a.name.toLowerCase() < b.name.toLowerCase()
          ? -1
          : a.name.toLowerCase() > b.name.toLowerCase()
            ? 1
            : 0,
      );
      this.sorted = true;
    }
    prefix = prefix.toLowerCase();
    let lo = 0,
      hi = this.items.length;
    while (lo < hi) {
      const mid = (lo + hi) >>> 1;
      if (this.items[mid].name.toLowerCase() < prefix) lo = mid + 1;
      else hi = mid;
    }
    const items = [],
      seen = new Set();
    let more = false;
    for (let i = lo; i < this.items.length; i++) {
      const s = this.items[i],
        key = s.name.toLowerCase();
      if (!key.startsWith(prefix)) break;
      if (seen.has(key)) continue;
      seen.add(key);
      if (items.length === limit) {
        more = true;
        break;
      }
      items.push(s);
    }
    return { items, more };
  }
}
class Model {
  constructor(options = {}) {
    this.options = options;
    this.symbols = [];
    this.globals = new Map();
    this.scopes = new Map();
    this.contexts = new Map();
    this.files = new Set();
    this.issues = [];
    this.includes = [];
    this.count = 0;
    this.complete = true;
  }
  add(s, owner) {
    s.params ||= [];
    s.members ||= [];
    s.qualified ||= qualify(s.ns || "", s.name);
    if (owner) {
      s.owner = owner;
      owner.members.push(s);
    } else {
      const key = s.qualified.toLowerCase(),
        bucket = this.globals.get(key) || [];
      bucket.push(s);
      this.globals.set(key, bucket);
      const idx = this.scopes.get(s.ns || "") || new NameIndex();
      idx.add(s);
      this.scopes.set(s.ns || "", idx);
    }
    this.symbols.push(s);
    return s;
  }
  finalize() {
    for (const idx of this.scopes.values()) idx.query("", 0);
  }
  context(uri, line) {
    const a = this.contexts.get(uri) || [];
    let lo = 0,
      hi = a.length;
    while (lo < hi) {
      const mid = (lo + hi) >>> 1;
      if (a[mid].line <= line) lo = mid + 1;
      else hi = mid;
    }
    return (
      a[Math.max(0, lo - 1)] || {
        ns: "",
        proc: null,
        assumes: {},
        sensitive: !!this.options.caseSensitive,
      }
    );
  }
  lookup(name, ctx = {}, typesOnly = false) {
    const absolute = name.startsWith("::");
    name = name.trim().replace(/^::/, "");
    const eq = (a, b) =>
      ctx.sensitive ? a === b : a.toLowerCase() === b.toLowerCase();
    if (!typesOnly && !absolute && !name.includes("::") && ctx.proc) {
      const local = ctx.proc.members.find((s) => eq(s.name, name));
      if (local) return local;
    }
    let ns = absolute ? "" : ctx.ns || "";
    for (;;) {
      const full = qualify(ns, name),
        bucket = this.globals.get(full.toLowerCase()) || [];
      const matches = bucket.filter(
        (s) =>
          eq(s.qualified, full) &&
          (!typesOnly ||
            [
              "struct",
              "union",
              "class",
              "interface",
              "rawinterface",
              "typedef",
              "namespace",
            ].includes(s.kind)),
      );
      if (matches.length) {
        const def = matches.find((s) => s.definition) || matches[0];
        if (!def.returnType)
          def.returnType = matches.find((s) => s.returnType)?.returnType || "";
        return def;
      }
      if (!ns || absolute) break;
      ns = parent(ns);
    }
    return null;
  }
  resolveType(spec, ctx, seen = new Set()) {
    if (!spec) return null;
    spec = spec
      .trim()
      .replace(/^(?:(?:near|far)(?:16|32|64)?\s+)?(?:ptr\s+)*/i, "");
    const s = this.lookup(spec, ctx, true);
    if (!s || seen.has(s)) return null;
    if (s.kind === "typedef") {
      seen.add(s);
      return this.resolveType(s.type, { ...ctx, ns: s.ns }, seen);
    }
    return ["struct", "union", "class", "interface", "rawinterface"].includes(
      s.kind,
    )
      ? s
      : null;
  }
  members(type) {
    if (!type) return [];
    const out = [],
      seen = new Set();
    for (const m of type.members) {
      const candidates = m.anonymous ? this.members(m) : [m];
      for (const c of candidates)
        if (!seen.has(c.name.toLowerCase())) {
          seen.add(c.name.toLowerCase());
          out.push(c);
        }
    }
    return out;
  }
  member(type, name, ctx) {
    return (
      this.members(type).find((s) =>
        ctx.sensitive
          ? s.name === name
          : s.name.toLowerCase() === name.toLowerCase(),
      ) || null
    );
  }
  visible(ctx, prefix = "", limit = 200) {
    const items = [],
      seen = new Set();
    let more = false;
    const put = (s) => {
      const key = ctx.sensitive ? s.name : s.name.toLowerCase();
      if (
        !seen.has(key) &&
        s.name.toLowerCase().startsWith(prefix.toLowerCase())
      ) {
        seen.add(key);
        if (items.length < limit) items.push(s);
        else more = true;
      }
    };
    if (ctx.proc) ctx.proc.members.forEach(put);
    let ns = ctx.ns || "";
    for (;;) {
      const result = this.scopes.get(ns)?.query(prefix, limit) || {
        items: [],
        more: false,
      };
      result.items.forEach(put);
      more ||= result.more;
      if (!ns) break;
      ns = parent(ns);
    }
    return { items, more };
  }
  resolveExpression(expression, ctx) {
    let s = expression.trim(),
      symbol = null,
      type = null,
      m;
    m = new RegExp(
      "^\\(\\s*(" + QID + ")\\s+PTR\\s+\\[[^\\]]*\\]\\s*\\)",
      "i",
    ).exec(s);
    if (!m)
      m = new RegExp("^(" + QID + ")\\s+PTR\\s+\\[[^\\]]*\\]", "i").exec(s);
    if (m) {
      type = this.resolveType(m[1], ctx);
      symbol = type;
      s = s.slice(m[0].length);
    } else if (s[0] === "[") {
      const end = s.indexOf("]");
      if (end < 0) return null;
      const inside = s.slice(1, end).trim();
      s = s.slice(end + 1);
      const r = new RegExp("^(" + ID + ")\\b").exec(inside)?.[1] || "";
      if (reg.test(r))
        type = this.resolveType(ctx.assumes?.[r.toLowerCase()], ctx);
      else {
        symbol = this.lookup(r, ctx);
        type =
          symbol && this.resolveType(symbol.type, { ...ctx, ns: symbol.ns });
      }
      const typed = new RegExp("^\\.\\s*(" + QID + ")").exec(s);
      if (typed) {
        const explicit = this.resolveType(typed[1], ctx);
        if (explicit) {
          type = explicit;
          symbol = explicit;
          s = s.slice(typed[0].length);
        }
      }
    } else {
      m = new RegExp("^(" + QID + ")").exec(s);
      if (!m) return null;
      const name = m[1];
      s = s.slice(m[0].length);
      symbol = this.lookup(name, ctx);
      if (reg.test(name))
        type = this.resolveType(ctx.assumes?.[name.toLowerCase()], ctx);
      else if (symbol)
        type = this.resolveType(symbol.type || symbol.qualified, {
          ...ctx,
          ns: symbol.ns,
        });
    }
    while (s.trim()) {
      m = new RegExp("^\\s*(\\.|->)\\s*(" + ID + ")").exec(s);
      if (!m || !type) return null;
      if (
        m[1] === "->" &&
        !["class", "interface", "rawinterface"].includes(type.kind)
      )
        return null;
      symbol = this.member(type, m[2], ctx);
      if (!symbol) return null;
      s = s.slice(m[0].length);
      type = ["struct", "union", "class", "interface", "rawinterface"].includes(
        symbol.kind,
      )
        ? symbol
        : this.resolveType(symbol.type || symbol.returnType, {
            ...ctx,
            ns: symbol.ns,
          });
    }
    return { symbol, type };
  }
}
function parse(entry, loader, options = {}) {
  const model = new Model(options);
  const state = {
    ns: "",
    proc: null,
    types: [],
    assumes: {},
    sensitive: !!options.caseSensitive,
    macro: null,
    macroDepth: 0,
    conditions: [],
  };
  const constants = new Map(
    Object.entries(options.defines || {}).map(([k, v]) => [k.toLowerCase(), v]),
  );
  let docComment = [];
  const active = () => !state.conditions.some((c) => c.enabled === false);
  const ctx = () => ({
    ns: state.ns,
    proc: state.proc,
    assumes: state.assumes,
    sensitive: state.sensitive,
  });
  function symbol(name, kind, r, extra = {}, owner = null) {
    const s = {
      name,
      kind,
      ns: state.ns,
      uri: r.uri,
      line: r.line,
      endLine: r.end,
      documentation: docComment.join("\n") || r.comment || "",
      ...extra,
    };
    docComment = [];
    return model.add(s, owner);
  }
  function enterType(name, kind, r, anonymous = false) {
    const owner = state.types.at(-1),
      s = symbol(name, kind, r, { anonymous }, owner);
    state.types.push(s);
    if (["class", "interface", "rawinterface"].includes(kind)) {
      symbol("psr" + name, "typedef", r, {
        type: "PTR " + s.qualified,
        synthetic: true,
      });
      if (kind !== "rawinterface")
        symbol("pVtbl", "field", r, { type: "PTR", synthetic: true }, s);
      if (kind === "interface" && /^COMINTERFACE/i.test(r.text)) {
        for (const [method, ret, args] of [
          ["QueryInterface", "SDWORD", "riid:PTR,ppvObject:PTR PTR"],
          ["AddRef", "DWORD", ""],
          ["Release", "DWORD", ""],
        ])
          symbol(
            method,
            "method",
            r,
            { returnType: ret, params: parameters(args), synthetic: true },
            s,
          );
      }
    }
    return s;
  }
  function parseFile(uri, stack = []) {
    if (stack.includes(uri)) {
      model.issues.push("Include cycle: " + [...stack, uri].join(" -> "));
      return;
    }
    if (stack.length > 64) {
      model.complete = false;
      model.issues.push("Include depth limit: " + uri);
      return;
    }
    const text = loader.read(uri);
    if (text === undefined) return;
    model.files.add(uri);
    let contexts = model.contexts.get(uri);
    const firstVisit = !contexts;
    if (!contexts) {
      contexts = [];
      model.contexts.set(uri, contexts);
    }
    for (const logical of logicalLines(text)) {
      if (++model.count > (options.maxIndexLines || 250000)) {
        model.complete = false;
        model.issues.push("Expanded source line limit reached");
        return;
      }
      const r = { ...logical, uri },
        s = r.text;
      if (firstVisit)
        for (let l = r.line; l <= r.end; l++)
          contexts.push({ line: l, ...ctx() });
      if (!s) {
        if (r.comment) docComment.push(r.comment);
        else docComment = [];
        continue;
      }
      let m;
      if (state.macro) {
        if (/\bMACRO\b|^\s*(?:REPT|REPEAT|IRP|IRPC|FOR|FORC)\b/i.test(s))
          state.macroDepth++;
        if (/^ENDM\b/i.test(s) && --state.macroDepth === 0) {
          state.macro.endLine = r.end;
          state.macro = null;
        }
        continue;
      }
      if ((m = new RegExp("^(" + ID + ")\\s+MACRO\\b(.*)$", "i").exec(s))) {
        state.macro = active()
          ? symbol(m[1], "macro", r, { params: parameters(m[2]) })
          : { endLine: r.end };
        state.macroDepth = 1;
        continue;
      }
      if ((m = /^(IFDEF|IFNDEF|IF)\s+(.+)$/i.exec(s))) {
        let enabled = null,
          key = m[2].trim().toLowerCase();
        if (/^IFN?DEF$/i.test(m[1])) {
          enabled = constants.has(key) || !!model.lookup(m[2].trim(), ctx());
          if (/IFNDEF/i.test(m[1])) enabled = !enabled;
        } else if (/^[01]$/.test(key)) enabled = key === "1";
        else if (constants.has(key)) enabled = !!Number(constants.get(key));
        state.conditions.push({
          enabled,
          original: enabled,
          snapshot: {
            ns: state.ns,
            types: [...state.types],
            proc: state.proc,
            assumes: state.assumes,
            sensitive: state.sensitive,
          },
        });
        if (enabled === null)
          model.issues.push(
            "Unknown conditional indexed conservatively: " +
              s +
              " (" +
              uri +
              ":" +
              (r.line + 1) +
              ")",
          );
        continue;
      }
      if (/^ELSE\b/i.test(s)) {
        const c = state.conditions.at(-1);
        if (c) {
          if (c.original === null)
            Object.assign(state, {
              ...c.snapshot,
              types: [...c.snapshot.types],
            });
          c.enabled = c.original === null ? null : !c.original;
        }
        continue;
      }
      if (/^ELSEIF\b/i.test(s)) {
        const c = state.conditions.at(-1);
        if (c) {
          Object.assign(state, { ...c.snapshot, types: [...c.snapshot.types] });
          c.enabled = null;
        }
        continue;
      }
      if (/^ENDIF\b/i.test(s)) {
        state.conditions.pop();
        continue;
      }
      if (!active()) continue;
      if ((m = /^OPTION\s+CASEMAP\s*:\s*(NONE|ALL|NOTPUBLIC)/i.exec(s))) {
        state.sensitive = m[1].toUpperCase() !== "ALL";
        continue;
      }
      if ((m = /^INCLUDE\s+(.+)$/i.exec(s))) {
        const requested = m[1].trim().replace(/^(?:<|")|(?:>|")$/g, ""),
          target = loader.resolve(uri, requested);
        model.includes.push({ uri, line: r.line, requested, target });
        if (target) parseFile(target, [...stack, uri]);
        else
          model.issues.push("Unresolved INCLUDE " + requested + " in " + uri);
        continue;
      }
      if (
        !state.proc &&
        !state.types.length &&
        (m = new RegExp("^NAMESPACE\\s+(" + ID + ")\\s*$", "i").exec(s))
      ) {
        const full = qualify(state.ns, m[1]);
        if (!model.lookup("::" + full, ctx(), true))
          symbol(m[1], "namespace", r);
        state.ns = full;
        continue;
      }
      if (!state.proc && !state.types.length && /^ENDNAMESPACE\s*$/i.test(s)) {
        state.ns = parent(state.ns);
        continue;
      }
      if (
        (m = /^(CLASS|OINTERFACE|COMINTERFACE|RAWINTERFACE)\s+(\S+)/i.exec(s))
      ) {
        enterType(
          m[2],
          {
            CLASS: "class",
            OINTERFACE: "interface",
            COMINTERFACE: "interface",
            RAWINTERFACE: "rawinterface",
          }[m[1].toUpperCase()],
          r,
        );
        continue;
      }
      if (
        (m = new RegExp(
          "^(" + ID + ")\\s+(STRUCT|STRUC|UNION|CSTRUCT|RAWSTRUCT)\\b",
          "i",
        ).exec(s))
      ) {
        enterType(m[1], /UNION/i.test(m[2]) ? "union" : "struct", r);
        continue;
      }
      if (
        state.types.length &&
        (m = /^(STRUCT|STRUC|UNION)(?:\s+(\w+))?$/i.exec(s))
      ) {
        enterType(
          m[2] || "<anonymous>",
          /UNION/i.test(m[1]) ? "union" : "struct",
          r,
          !m[2],
        );
        continue;
      }
      if (
        /^(?:(?:\S+\s+)?ENDS|ENDCLASS|ENDOINTERFACE|ENDCOMINTERFACE|ENDRAWINTERFACE)\b/i.test(
          s,
        )
      ) {
        const t = state.types.pop();
        if (t) t.endLine = r.end;
        continue;
      }
      if (/^ENDMETHODS\b/i.test(s)) continue;
      if (
        (m = /^(METHOD|VECMETHOD|STATICMETHOD|STATICVECMETHOD)\s+(.+)$/i.exec(
          s,
        ))
      ) {
        const parts = splitTop(m[2]),
          owner = model.resolveType(parts[0], ctx());
        if (!owner || !parts[1]) continue;
        const method =
          model.member(owner, parts[1], ctx()) ||
          symbol(parts[1], "method", r, {}, owner);
        Object.assign(method, {
          returnType: unangle(parts[2] || ""),
          params: parameters(parts.slice(4).join(",")),
          definition: true,
          uri,
          line: r.line,
          static: /STATIC/i.test(m[1]),
          signatureKnown: true,
        });
        state.proc = { ...method, members: [], savedAssumes: state.assumes };
        for (const p of method.params)
          symbol(p.name, "parameter", r, { type: p.type }, state.proc);
        if (!method.static) {
          symbol(
            "thisPtr",
            "parameter",
            r,
            { type: "PTR " + owner.qualified },
            state.proc,
          );
          state.assumes = { ...state.assumes, rcx: "PTR " + owner.qualified };
        }
        continue;
      }
      if (/^(?:\S+\s+ENDP|ENDMETHOD)\b/i.test(s)) {
        if (state.proc) {
          state.proc.endLine = r.end;
          if (state.proc.savedAssumes) state.assumes = state.proc.savedAssumes;
        }
        state.proc = null;
        continue;
      }
      const owner = state.types.at(-1);
      if (
        owner &&
        (m = /^(CMETHOD|CSTATIC|CVIRTUAL|STDFUNC)\s+(.+)$/i.exec(s))
      ) {
        const parts = splitTop(m[2]),
          typed = /CVIRTUAL|STDFUNC/i.test(m[1]);
        symbol(
          parts[0],
          "method",
          r,
          {
            returnType: typed ? unangle(parts[1] || "") : "",
            params: typed ? parameters(parts.slice(2).join(",")) : [],
            static: /^CSTATIC$/i.test(m[1]),
            signatureKnown: typed,
          },
          owner,
        );
        continue;
      }
      if ((m = new RegExp("^(" + ID + ")\\s+TYPEDEF\\s+(.+)$", "i").exec(s))) {
        const proto = /^PROTO\b(.*)$/i.exec(m[2]);
        symbol(
          m[1],
          "typedef",
          r,
          proto
            ? { ...procedureTail(proto[1]), callable: true, type: "PROTO" }
            : { type: typeSpec(m[2]) },
        );
        continue;
      }
      if (
        (m = new RegExp("^(" + ID + ")\\s+(PROC|PROTO)\\b(.*)$", "i").exec(s))
      ) {
        const proc = symbol(m[1], "procedure", r, {
          ...procedureTail(m[3]),
          definition: /^PROC$/i.test(m[2]),
        });
        if (proc.definition) {
          state.proc = proc;
          for (const p of proc.params)
            symbol(p.name, "parameter", r, { type: p.type }, proc);
        }
        continue;
      }
      if ((m = /^LOCAL\s+(.+)$/i.exec(s)) && state.proc) {
        for (const p of parameters(m[1]))
          symbol(p.name, "local", r, { type: p.type }, state.proc);
        continue;
      }
      if ((m = /^ASSUME\s+(.+)$/i.exec(s))) {
        let assumes = { ...state.assumes };
        if (/^NOTHING$/i.test(m[1])) assumes = {};
        else
          for (const part of splitTop(m[1])) {
            const a = /^(\w+)\s*:\s*(.+)$/.exec(part);
            if (!a) continue;
            const key = a[1].toLowerCase();
            if (/^(?:NOTHING|ERROR)$/i.test(a[2])) delete assumes[key];
            else assumes[key] = a[2].trim();
          }
        state.assumes = assumes;
        continue;
      }
      if (
        (m = new RegExp(
          "^(" + ID + ")\\s+(EQU|TEXTEQU|RECORD|=)\\s*(.*)$",
          "i",
        ).exec(s))
      ) {
        symbol(
          m[1],
          /^RECORD$/i.test(m[2])
            ? "record"
            : /^TEXTEQU$/i.test(m[2])
              ? "text"
              : "constant",
          r,
          { value: m[3], type: m[2].toUpperCase() },
        );
        constants.set(m[1].toLowerCase(), m[3]);
        continue;
      }
      if ((m = /^(?:EXTERN|EXTERNDEF)\s+(.+)$/i.exec(s))) {
        for (const p of parameters(m[1]))
          symbol(p.name, /^PROC$/i.test(p.type) ? "procedure" : "variable", r, {
            type: p.type,
            external: true,
          });
        continue;
      }
      if ((m = new RegExp("^(" + ID + ")\\s*::?\\s*").exec(s))) {
        symbol(m[1], "label", r, {}, state.proc);
        continue;
      }
      if (
        (m = new RegExp("^(" + ID + ")\\s+(?:LABEL\\s+)?(.+)$", "i").exec(s))
      ) {
        const t = typeSpec(m[2]);
        if (
          t &&
          (owner ||
            primitive.test(t) ||
            /^ptr\s/i.test(t) ||
            model.lookup(t, ctx(), true))
        ) {
          if (/^(?:OPTION|INVOKE|PUBLIC|ALIGN|ORG|ASSUME)$/i.test(m[1]))
            continue;
          symbol(m[1], owner ? "field" : "variable", r, { type: t }, owner);
        }
      }
    }
  }
  parseFile(entry);
  model.finalize();
  return model;
}
function expressionSuffix(text) {
  const atom =
    "(?:\\(\\s*" +
    QID +
    "\\s+PTR\\s+\\[[^\\]]*\\]\\s*\\)|\\[[^\\]]*\\]|" +
    QID +
    ")";
  return (
    new RegExp(
      "(" + atom + "(?:\\s*(?:\\.|->)\\s*" + ID + ")*)\\s*$",
      "i",
    ).exec(text)?.[1] || ""
  );
}
function completionContext(prefix) {
  const m = /(::|->|\.)([A-Za-z_@$?][\w@$?]*)?$/.exec(prefix);
  if (!m) return { mode: "symbol", prefix: /[\w@$?]*$/.exec(prefix)[0] };
  const before = prefix.slice(0, m.index),
    partial = m[2] || "";
  if (m[1] === "::") {
    const name = new RegExp("((?:::)?" + ID + "(?:::" + ID + ")*)$").exec(
      before,
    )?.[1];
    return { mode: "namespace", target: name || "::", prefix: partial };
  }
  return {
    mode: "member",
    target: expressionSuffix(before),
    operator: m[1],
    prefix: partial,
  };
}
function completions(model, uri, line, prefix, options = {}) {
  const c = completionContext(prefix),
    ctx = model.context(uri, line),
    limit = options.maxCompletions || 200;
  let items = [],
    more = false,
    needsPrefix = false,
    total = 0;
  if (c.mode === "namespace") {
    const ns =
      c.target === "::" ? "" : model.lookup(c.target, ctx, true)?.qualified;
    const idx = ns === undefined ? null : model.scopes.get(ns);
    total = idx?.items.length || 0;
    if (
      total > (options.largeNamespaceThreshold || 1000) &&
      c.prefix.length < (options.namespaceMinPrefix || 2)
    )
      needsPrefix = true;
    else
      ({ items, more } = idx?.query(c.prefix, limit) || {
        items: [],
        more: false,
      });
  } else if (c.mode === "member") {
    const type = model.resolveExpression(c.target, ctx)?.type;
    if (
      type &&
      (c.operator !== "->" ||
        ["class", "interface", "rawinterface"].includes(type.kind))
    ) {
      items = model
        .members(type)
        .filter(
          (s) =>
            (c.operator !== "->" ||
              s.kind === "method" ||
              ["class", "interface", "rawinterface"].includes(
                model.resolveType(s.type, { ...ctx, ns: s.ns })?.kind,
              )) &&
            s.name.toLowerCase().startsWith(c.prefix.toLowerCase()),
        );
      more = items.length > limit;
      items = items.slice(0, limit);
    }
  } else ({ items, more } = model.visible(ctx, c.prefix, limit));
  return { ...c, items, more, needsPrefix, total };
}
function callable(model, expression, ctx) {
  let sym =
    model.resolveExpression(expression, ctx)?.symbol ||
    model.lookup(expression, ctx);
  const seen = new Set();
  while (sym && !seen.has(sym)) {
    seen.add(sym);
    if (["procedure", "method", "macro"].includes(sym.kind) || sym.callable)
      return sym;
    sym = model.lookup(
      (sym.type || "").replace(/^(?:ptr\s+)*/i, ""),
      { ...ctx, ns: sym.ns },
      true,
    );
  }
  return null;
}
function signature(model, uri, line, source) {
  const clean = source
      .split(/\r?\n/)
      .map(stripComment)
      .join("\n")
      .replace(/\\\s*\n/g, " "),
    stack = [];
  let quote = "";
  for (let i = 0; i < clean.length; i++) {
    const c = clean[i];
    if (quote) {
      if (c === quote) {
        if (clean[i + 1] === quote) i++;
        else quote = "";
      }
      continue;
    }
    if (c === '"' || c === "'") quote = c;
    else if (c === "(") stack.push(i);
    else if (c === ")") stack.pop();
  }
  const ctx = model.context(uri, line);
  for (let n = stack.length - 1; n >= 0; n--) {
    const pos = stack[n],
      name = expressionSuffix(clean.slice(0, pos)),
      sym = callable(model, name, ctx);
    if (sym)
      return {
        symbol: sym,
        active: splitTop(clean.slice(pos + 1), ",", false).length - 1,
      };
  }
  const statement = clean.split(/\r?\n/).pop().trim(),
    invoke = /^invoke\s+(.+)$/i.exec(statement);
  if (invoke) {
    const parts = splitTop(invoke[1], ",", false),
      sym = callable(model, parts[0], ctx);
    if (sym) return { symbol: sym, active: Math.max(0, parts.length - 2) };
  }
  const macro = new RegExp("^(" + QID + ")\\s+(.*)$").exec(statement);
  if (macro) {
    const sym = model.lookup(macro[1], ctx);
    if (sym?.kind === "macro")
      return { symbol: sym, active: splitTop(macro[2]).length - 1 };
  }
  return null;
}
function signatureLabel(s) {
  return (
    s.name +
    "(" +
    s.params.map((p) => p.name + (p.type ? ": " + p.type : "")).join(", ") +
    ")" +
    (s.returnType ? " : " + s.returnType : "")
  );
}
function detail(s) {
  if (["procedure", "method", "macro"].includes(s.kind))
    return s.kind + " " + signatureLabel(s);
  return (
    s.kind + (s.type ? " : " + s.type : "") + (s.value ? " = " + s.value : "")
  );
}
module.exports = {
  Model,
  NameIndex,
  parse,
  completions,
  signature,
  callable,
  signatureLabel,
  detail,
  stripComment,
  splitTop,
  logicalLines,
  expressionSuffix,
  completionContext,
};
