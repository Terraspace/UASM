"use strict";
const { parentPort, workerData } = require("node:worker_threads");
const { parse } = require("./core");
try {
  const { entry, sources, links, options, issues } = workerData;
  const model = parse(
    entry,
    { read: (u) => sources.get(u), resolve: (u, n) => links.get(u + "\0" + n) },
    options,
  );
  model.issues.unshift(...issues);
  parentPort.postMessage({ model });
} catch (error) {
  parentPort.postMessage({ error: error.stack || String(error) });
}
