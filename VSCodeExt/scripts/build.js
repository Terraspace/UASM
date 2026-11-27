"use strict";
const fs = require("node:fs"),
  path = require("node:path"),
  { spawnSync } = require("node:child_process");
const root = path.resolve(__dirname, "..");
process.chdir(root);
for (const file of fs.readdirSync("src").filter((n) => n.endsWith(".js"))) {
  const r = spawnSync(process.execPath, ["--check", path.join("src", file)], {
    stdio: "inherit",
  });
  if (r.status) process.exit(r.status);
}
const repo = process.env.UASM_SOURCE_ROOT || path.resolve(root, "..");
const vocabulary = new Set([
  "namespace",
  "endnamespace",
  "struct",
  "struc",
  "union",
  "ends",
  "proc",
  "endp",
  "proto",
  "typedef",
  "local",
  "invoke",
  "assume",
  "include",
  "class",
  "endclass",
  "method",
  "staticmethod",
  "vecmethod",
  "staticvecmethod",
  "endmethod",
  "cmethod",
  "cstatic",
  "cvirtual",
  "endmethods",
  "ointerface",
  "endointerface",
  "cominterface",
  "endcominterface",
  "rawinterface",
  "endrawinterface",
  "stdfunc",
  "equ",
  "textequ",
  "record",
  "macro",
  "endm",
  "public",
  "extern",
  "externdef",
]);
let generated = false;
for (const file of [
  "instruct.h",
  "instr64.h",
  "instravx.h",
  "InstrTableV2.h",
  "InstrTableFP16.h",
  "directve.h",
]) {
  const name = path.join(repo, "H", file);
  if (!fs.existsSync(name)) continue;
  generated = true;
  const text = fs
    .readFileSync(name, "utf8")
    .replace(/\/\*[\s\S]*?\*\//g, "")
    .replace(/\/\/[^\n]*/g, "");
  for (const m of text.matchAll(
    /^\s*(?:insx?|avxins|res)\s*\(\s*\w+\s*,\s*([.\w]+)\s*,/gm,
  ))
    vocabulary.add(m[1].toLowerCase());
  for (const m of text.matchAll(/\{\s*"([a-z][a-z0-9]+)"\s*,/g))
    vocabulary.add(m[1]);
}
if (generated || !fs.existsSync("src/vocabulary.json"))
  fs.writeFileSync(
    "src/vocabulary.json",
    JSON.stringify([...vocabulary].sort(), null, 2) + "\n",
  );
for (const file of [
  "package.json",
  "language-configuration.json",
  "syntaxes/uasm.tmLanguage.json",
])
  JSON.parse(fs.readFileSync(file, "utf8"));
fs.mkdirSync("dist", { recursive: true });
const test = spawnSync(process.execPath, ["--test", "test/core.test.js"], {
  stdio: "inherit",
});
if (test.status) process.exit(test.status);
console.log(
  "Build verified. Vocabulary: " +
    JSON.parse(fs.readFileSync("src/vocabulary.json", "utf8")).length +
    " entries.",
);
