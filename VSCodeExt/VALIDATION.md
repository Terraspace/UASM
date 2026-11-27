# Validation — UASM IntelliSense 0.1.1

- Semantic engine: 14/14 tests pass on Node.js 25.6.1.
- Package: VSCE 4.1.1 successfully creates the VSIX, with no runtime npm dependencies.
- Vocabulary: 1,890 instruction/directive names derived from the current UASM source tables.
- Stress fixture: 20,000 namespace symbols; tests verify prefix gating, bounded results and incomplete-list reporting. Parse plus 1,000 prefix queries completed in approximately 0.23 seconds on the development machine; not a cross-machine performance guarantee.
- Real-source smoke checks: repository OO tour and Direct2D namespace sample resolve their members; external UEFI project resolves RAW interface methods. A larger game project resolves structure fields across 76 files and 33,204 indexed symbols (approximately 0.85 seconds for loading/parsing).
- Extension-host test harness is included, but could not run successfully inside the Codex Windows sandbox: VS Code 1.148.0 aborts before loading extensions with an AppContainer installation ACL error; a separate 1.85.2 test executable exits before producing test results. Therefore actual interactive provider behaviour still needs a normal-user VS Code test. No claim of passed UI integration tests is made.

Run `npm run test:host` from a normal terminal to exercise real provider calls and unsaved include invalidation with an isolated VS Code profile. It downloads VS Code unless VSCODE_EXECUTABLE is supplied; VSCODE_TEST_VERSION can select a version. Run `install.cmd` to try the package normally, then open `examples/tour.asm` and request completion at the example access expressions.

The assembler sources and assembler regression baselines are unchanged. No Marketplace publication or normal-profile installation was performed.


0.1.1 fixes the installed-host DataCloneError: object-valued VS Code settings are detached from their Proxy wrappers before transfer to the index worker. A Proxy-based worker regression test reproduces the old failure and verifies the fix. Interactive confirmation after reinstall remains outstanding.

