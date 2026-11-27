"use strict";

// VS Code returns object-valued settings through read-only Proxy wrappers.
// Worker messages must contain plain structured-cloneable data instead.
function plainDefines(value) {
  return Object.fromEntries(
    Object.entries(value || {}).filter(([, item]) =>
      ["string", "number", "boolean"].includes(typeof item),
    ),
  );
}
module.exports = { plainDefines };
