"use strict";
const test = require("node:test"),
  assert = require("node:assert/strict"),
  path = require("node:path"),
  fs = require("node:fs/promises");
const { parse, completions, signature, logicalLines } = require("../src/core");
const { loadProject, normalize } = require("../src/project");
const fixture = [
  "option casemap:none",
  "namespace Win32",
  "; Creates a window.",
  "CreateWindow proto (qword) title:ptr byte,width:dword",
  "FLAG equ 1",
  "Log macro message:REQ",
  " mov eax,1",
  "endm",
  "namespace Detail",
  "Value dd 7",
  "endnamespace",
  "endnamespace",
  "namespace Model",
  "Point STRUCT",
  " x real4 ?",
  " y real4 ?",
  " NameSpace dd ?",
  "Point ENDS",
  "Choice UNION",
  " namespace dword ?",
  " endnamespace qword ?",
  "Choice ENDS",
  "PPoint TYPEDEF PTR Point",
  "Alias TYPEDEF PPoint",
  "Node STRUC",
  " point Point <>",
  " next PTR Node ?",
  "Node ENDS",
  "CLASS Counter",
  " CMETHOD Add",
  " CSTATIC Make",
  "ENDMETHODS",
  " value dword 0",
  " child psrCounter 0",
  "ENDCLASS",
  "METHOD Counter,Add,<dword>,<>,amount:dword,scale:real4",
  " mov eax,amount",
  " ret",
  "ENDMETHOD",
  "STATICMETHOD Counter,Make,<qword>,<>,seed:dword",
  " ret",
  "ENDMETHOD",
  "COMINTERFACE IShell",
  " CVIRTUAL NameSpace,<sdword>,item:ptr byte",
  "ENDCOMINTERFACE",
  "RAWINTERFACE EFI",
  " STDFUNC Open,<qword>,pThis:ptr,path:ptr word",
  " Revision qword ?",
  "ENDRAWINTERFACE",
  "PEFI TYPEDEF PTR EFI",
  "PShell TYPEDEF PTR IShell",
  "endnamespace",
  "point Model::Point <>",
  "node Model::Node <>",
  "pointer Model::Alias 0",
  "object Model::psrCounter 0",
  "shell Model::PShell 0",
  "boot Model::PEFI 0",
  "Callback TYPEDEF PROTO (dword) value:dword",
  "PCallback TYPEDEF PTR Callback",
  "callback PCallback 0",
  ".code",
  "Work proc namespace:ptr Model::Node, count:dword",
  " LOCAL localPoint:Model::Point,localPtr:Model::PPoint",
  " assume rax:ptr Model::Point,rbx:Model::PEFI",
  " mov eax,0 ; anchor",
  " assume rax:nothing",
  " mov eax,0 ; cleared",
  " ret",
  "Work endp",
  "Other proc",
  " LOCAL localPoint:Model::Choice",
  " mov eax,0 ; other",
  " ret",
  "Other endp",
].join("\n");
function model(text = fixture, others = {}) {
  const files = { "main.asm": text, ...others };
  return parse("main.asm", {
    read: (u) => files[u],
    resolve: (u, n) => (files[n] !== undefined ? n : undefined),
  });
}
const anchor = fixture.split("\n").findIndex((s) => s.includes("; anchor"));
const labels = (r) => r.items.map((s) => s.name);
test("structures, unions, aliases, pointers and locals", () => {
  const m = model();
  for (const expr of [
    "point.",
    "pointer.",
    "localPoint.",
    "localPtr.",
    "[rax].",
    "[rax].Model::Point.",
    "(Model::Point PTR [r8 + 16]).",
    "node.point.",
    "namespace.point.",
  ]) {
    assert.deepEqual(
      labels(completions(m, "main.asm", anchor, expr)),
      ["x", "y", "NameSpace"],
      expr,
    );
  }
  assert.deepEqual(labels(completions(m, "main.asm", anchor, "node.next.")), [
    "point",
    "next",
  ]);
  assert.deepEqual(labels(completions(m, "main.asm", anchor, "point->")), []);
});
test("ASSUME reset, procedure scope and CASEMAP", () => {
  const m = model(),
    cleared = anchor + 2,
    other = fixture.split("\n").findIndex((s) => s.includes("; other"));
  assert.deepEqual(labels(completions(m, "main.asm", cleared, "[rax].")), []);
  assert.deepEqual(labels(completions(m, "main.asm", other, "localPoint.")), [
    "namespace",
    "endnamespace",
  ]);
  assert.deepEqual(labels(completions(m, "main.asm", other, "localPtr.")), []);
  assert.deepEqual(labels(completions(m, "main.asm", anchor, "POINT.")), []);
});
test("OO, COM, RAW and chained receivers", () => {
  const m = model();
  assert.ok(
    labels(completions(m, "main.asm", anchor, "object->")).includes("Add"),
  );
  assert.ok(
    !labels(completions(m, "main.asm", anchor, "object->")).includes("value"),
  );
  assert.ok(
    labels(completions(m, "main.asm", anchor, "object->")).includes("child"),
  );
  assert.ok(
    labels(completions(m, "main.asm", anchor, "object->child->")).includes(
      "Add",
    ),
  );
  assert.ok(
    labels(completions(m, "main.asm", anchor, "object.child->")).includes(
      "Add",
    ),
  );
  assert.deepEqual(labels(completions(m, "main.asm", anchor, "boot->")), [
    "Open",
  ]);
  assert.deepEqual(
    labels(completions(m, "main.asm", anchor, "[rbx].Model::EFI->")),
    ["Open"],
  );
  assert.deepEqual(labels(completions(m, "main.asm", anchor, "shell->")), [
    "QueryInterface",
    "AddRef",
    "Release",
    "NameSpace",
  ]);
  const query = signature(m, "main.asm", anchor, "shell->QueryInterface(iid, ");
  assert.equal(query.symbol.params.length, 2);
  assert.equal(query.active, 1);
});
test("namespace completion includes categories and child namespaces", () => {
  const m = model();
  assert.deepEqual(labels(completions(m, "main.asm", anchor, "Win32::")), [
    "CreateWindow",
    "Detail",
    "FLAG",
    "Log",
  ]);
  assert.deepEqual(
    labels(completions(m, "main.asm", anchor, "Win32::Detail::")),
    ["Value"],
  );
  assert.deepEqual(labels(completions(m, "main.asm", anchor, "::Win32::Cr")), [
    "CreateWindow",
  ]);
  assert.equal(
    completions(m, "main.asm", anchor, "Win32::Create").items[0].params.length,
    2,
  );
});
test("signature help handles INVOKE, C calls, nested calls, quoted commas and typed callbacks", () => {
  const m = model();
  let r = signature(
    m,
    "main.asm",
    anchor,
    'invoke Win32::CreateWindow, "a,b", ',
  );
  assert.equal(r.active, 1);
  assert.equal(r.symbol.returnType, "qword");
  r = signature(
    m,
    "main.asm",
    anchor,
    'Win32::CreateWindow("a,b", object->Add(7, ',
  );
  assert.equal(r.symbol.name, "Add");
  assert.equal(r.active, 1);
  assert.equal(r.symbol.params[0].name, "amount");
  r = signature(m, "main.asm", anchor, "Win32::CreateWindow(object->Make(7), ");
  assert.equal(r.symbol.name, "CreateWindow");
  assert.equal(r.active, 1);
  r = signature(m, "main.asm", anchor, "boot->Open(boot, ");
  assert.equal(r.symbol.params.length, 2);
  assert.equal(r.active, 1); // RAW does not hide pThis.
  assert.equal(
    signature(m, "main.asm", anchor, "callback(").symbol.params[0].name,
    "value",
  );
});
test("INCLUDE inherits namespace; guards and cycles are bounded", () => {
  const m = model(
    "namespace Outer\ninclude types.inc\nendnamespace\np Outer::Point <>\nmov eax,0",
    {
      "types.inc":
        "IFNDEF SEEN\nSEEN equ 1\nPoint struct\nx dd ?\nPoint ends\ninclude types.inc\nENDIF",
    },
  );
  assert.deepEqual(labels(completions(m, "main.asm", 4, "p.")), ["x"]);
  assert.ok(m.issues.some((s) => s.startsWith("Include cycle")));
});
test("conditional assembly and macro bodies do not leak declarations", () => {
  const m = model(
    "IFDEF ENABLE\nYes dd 1\nELSE\nNo dd 0\nENDIF\nM macro\nHidden dd 0\nendm\n",
  );
  assert.equal(m.lookup("Yes"), null);
  assert.ok(m.lookup("No"));
  assert.equal(m.lookup("Hidden"), null);
});
test("continuations and comments preserve declaration line positions", () => {
  const m = model("Run proto (dword) first:dword, \\\n second:ptr byte\n");
  assert.equal(m.lookup("Run").params.length, 2);
  assert.equal(logicalLines("COMMENT !\nFake dd 0\n!\nReal dd 1")[3].line, 3);
});
test("anonymous unions, named nested structs and unknown alternative type headers do not leak scope", () => {
  const m = model(
    "IF UNKNOWN EQ 1\nLarge struct\nELSE\nLarge union\nstruct u\nLow dd ?\nends\nENDIF\nQuad dq ?\nLarge ends\nNext struct\nvalue dd ?\nNext ends\nn Next <>\nv Large <>\n",
  );
  assert.equal(m.lookup("Next").owner, undefined);
  assert.deepEqual(labels(completions(m, "main.asm", 16, "n.")), ["value"]);
  const unions = model(
    "T struct\nunion\n a dd ?\n b dq ?\nends\nstruct named\n c db ?\nends\nT ends\nv T <>\n",
  );
  assert.deepEqual(labels(completions(unions, "main.asm", 10, "v.")), [
    "a",
    "b",
    "named",
  ]);
  assert.deepEqual(labels(completions(unions, "main.asm", 10, "v.named.")), [
    "c",
  ]);
});
test("20,000-symbol namespace uses bounded prefix queries", () => {
  const text =
    "namespace Huge\n" +
    Array.from(
      { length: 20000 },
      (_, i) => "Entry" + String(i).padStart(5, "0") + " equ " + i,
    ).join("\n") +
    "\nendnamespace";
  const m = model(text),
    last = 20002;
  const start = performance.now();
  const bare = completions(m, "main.asm", last, "Huge::");
  assert.equal(bare.items.length, 0);
  assert.equal(bare.needsPrefix, true);
  const wide = completions(m, "main.asm", last, "Huge::Entry", {
    maxCompletions: 50,
  });
  assert.equal(wide.items.length, 50);
  assert.equal(wide.more, true);
  for (let i = 0; i < 1000; i++) {
    const r = completions(m, "main.asm", last, "Huge::Entry1999", {
      maxCompletions: 50,
    });
    assert.equal(r.items.length, 10);
    assert.equal(r.more, false);
  }
  assert.ok(
    performance.now() - start < 2000,
    "prefix queries must not scan every symbol",
  );
});
test("real fixture project loads relative INCLUDEs and unsaved overlays", async () => {
  const root = path.resolve(__dirname, "../examples"),
    main = path.join(root, "tour.asm");
  const loaded = await loadProject(
    main,
    {},
    new Map([[normalize(main), "include types.inc\np Demo::PPoint 0\n"]]),
  );
  const m = parse(loaded.entry, {
    read: (u) => loaded.sources.get(u),
    resolve: (u, n) => loaded.links.get(u + "\0" + n),
  });
  assert.ok(m.lookup("Demo::Point"));
  assert.ok(labels(completions(m, loaded.entry, 1, "p.")).includes("x"));
});

test("signature help follows INVOKE continuation lines", () => {
  const found = signature(
    model(),
    "main.asm",
    anchor,
    "invoke Win32::CreateWindow, \\\n    title, ",
  );
  assert.equal(found.symbol.name, "CreateWindow");
  assert.equal(found.active, 1);
});

test("background worker returns a usable semantic index", async () => {
  const { Worker } = require("node:worker_threads");
  const { Model, NameIndex } = require("../src/core");
  const input = await loadProject(path.join(__dirname, "../examples/tour.asm"));
  const result = await new Promise((resolve, reject) => {
    const worker = new Worker(path.join(__dirname, "../src/index-worker.js"), {
      workerData: input,
    });
    worker.once("message", resolve);
    worker.once("error", reject);
    worker.once("exit", (code) => {
      if (code) reject(new Error("Worker exit " + code));
    });
  });
  assert.equal(result.error, undefined);
  Object.setPrototypeOf(result.model, Model.prototype);
  for (const index of result.model.scopes.values())
    Object.setPrototypeOf(index, NameIndex.prototype);
  assert.ok(
    labels(completions(result.model, input.entry, 17, "counter->")).includes(
      "Add",
    ),
  );
  assert.ok(
    labels(completions(result.model, input.entry, 17, "Win32::")).includes(
      "WriteFile",
    ),
  );
});

test("VS Code proxy settings are detached before worker transfer", async () => {
  const { plainDefines } = require("../src/settings");
  const { Worker } = require("node:worker_threads");
  const wrapped = new Proxy({ _WIN64: 1, ENABLED: true, FLAVOUR: "demo" }, {});
  assert.throws(() => structuredClone(wrapped), { name: "DataCloneError" });
  const defines = plainDefines(wrapped);
  assert.deepEqual(structuredClone(defines), {
    _WIN64: 1,
    ENABLED: true,
    FLAVOUR: "demo",
  });
  const input = await loadProject(
    path.join(__dirname, "../examples/tour.asm"),
    { defines },
  );
  const result = await new Promise((resolve, reject) => {
    const worker = new Worker(path.join(__dirname, "../src/index-worker.js"), {
      workerData: input,
    });
    worker.once("message", resolve);
    worker.once("error", reject);
    worker.once("exit", (code) => {
      if (code) reject(new Error("Worker exit " + code));
    });
  });
  assert.equal(result.error, undefined);
  assert.ok(result.model.symbols.some((s) => s.name === "Point"));
});
