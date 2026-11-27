"use strict";
const fs = require("node:fs"),
  path = require("node:path");
const root = path.resolve(__dirname, "..");
for (const name of ["dist", ".test-data"]) {
  const target = path.resolve(root, name);
  if (path.dirname(target) !== root) throw new Error("Invalid cleanup target");
  if (fs.existsSync(target) && fs.lstatSync(target).isSymbolicLink())
    throw new Error("Refusing to follow cleanup link: " + target);
  fs.rmSync(target, { recursive: true, force: true });
}
console.log(
  "Removed build artifacts and isolated test data. Sources and dependencies preserved.",
);
