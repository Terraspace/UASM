"use strict";
const path = require("node:path"),
  fs = require("node:fs");
const { runTests } = require("@vscode/test-electron");
const root = path.resolve(__dirname, ".."),
  data = path.join(root, ".test-data");
fs.mkdirSync(data, { recursive: true });
runTests({
  version: process.env.VSCODE_TEST_VERSION || "stable",
  vscodeExecutablePath: process.env.VSCODE_EXECUTABLE || undefined,
  extensionDevelopmentPath: root,
  extensionTestsPath: path.join(root, "test", "host.js"),
  cachePath: path.join(data, "vscode"),
  launchArgs: [
    path.join(root, "examples"),
    "--user-data-dir",
    path.join(data, "user"),
    "--extensions-dir",
    path.join(data, "extensions"),
    "--disable-extensions",
    "--skip-welcome",
    "--skip-release-notes",
    "--disable-workspace-trust",
    "--disable-gpu",
  ],
}).catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
