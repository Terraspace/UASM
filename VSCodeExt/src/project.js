"use strict";
const fs = require("node:fs/promises");
const path = require("node:path");
const { logicalLines } = require("./core");
const normalize = (p) => {
  p = path.resolve(p);
  return process.platform === "win32" ? p.toLowerCase() : p;
};

// Asynchronous I/O with explicit file/byte bounds. No glob over the whole drive,
// shell execution, INCBIN reads or environment-dependent build invocation.
async function loadProject(
  entry,
  options = {},
  overlays = new Map(),
  diskCache = new Map(),
) {
  const sources = new Map(),
    links = new Map(),
    issues = [];
  const maxFiles = options.maxIncludeFiles || 1000,
    maxBytes = (options.maxFileSizeKB || 2048) * 1024;
  const search = [path.dirname(entry), ...(options.includePaths || [])];
  const pending = new Set();
  async function read(file) {
    const key = normalize(file);
    if (overlays.has(key)) return overlays.get(key);
    if (diskCache.has(key)) return diskCache.get(key);
    try {
      const stat = await fs.stat(key);
      if (!stat.isFile()) return undefined;
      if (stat.size > maxBytes) {
        issues.push("File too large: " + key);
        return undefined;
      }
      const text = await fs.readFile(key, "utf8");
      diskCache.set(key, text);
      if (diskCache.size > 4000)
        diskCache.delete(diskCache.keys().next().value);
      return text;
    } catch {
      return undefined;
    }
  }
  async function visit(file) {
    const key = normalize(file);
    if (sources.has(key) || pending.has(key)) return key;
    if (sources.size + pending.size >= maxFiles) {
      issues.push("Include file limit reached: " + key);
      return undefined;
    }
    pending.add(key);
    const text = await read(key);
    if (text === undefined) {
      pending.delete(key);
      return undefined;
    }
    sources.set(key, text);
    pending.delete(key);
    for (const line of logicalLines(text)) {
      const m = /^INCLUDE\s+(.+)$/i.exec(line.text);
      if (!m) continue;
      const name = m[1]
        .trim()
        .replace(/^(?:<|")|(?:>|")$/g, "")
        .replace(/[\\/]/g, path.sep);
      const candidates = path.isAbsolute(name)
        ? [name]
        : [
            path.resolve(path.dirname(key), name),
            ...search.map((p) => path.resolve(p, name)),
          ];
      let resolved;
      for (const candidate of [...new Set(candidates)]) {
        resolved = await visit(candidate);
        if (resolved) break;
      }
      links.set(
        key + "\0" + m[1].trim().replace(/^(?:<|")|(?:>|")$/g, ""),
        resolved,
      );
    }
    return key;
  }
  await visit(entry);
  return { entry: normalize(entry), sources, links, issues, options };
}
module.exports = { loadProject, normalize };
