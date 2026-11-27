"use strict";
// Optional local-project smoke check; no private paths are stored in the repo.
const { loadProject } = require("../src/project");
const { parse } = require("../src/core");
(async () => {
  if (!process.argv[2])
    throw new Error(
      "Usage: node scripts/check-project.js path/to/main.asm [include-directory ...]",
    );
  const started = performance.now();
  const p = await loadProject(process.argv[2], {
    includePaths: process.argv.slice(3),
  });
  const m = parse(p.entry, {
    read: (u) => p.sources.get(u),
    resolve: (u, n) => p.links.get(u + "\0" + n),
  });
  if (!m.files.size) throw new Error("Entry source could not be read");
  console.log(
    `${m.files.size} files, ${m.symbols.length} symbols, ${Math.round(performance.now() - started)} ms`,
  );
  for (const issue of [...p.issues, ...m.issues]) console.log(issue);
})().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
