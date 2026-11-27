# Pack validation — 2026-11-27

Validated against UASM master `e693c8c2555c04980308910cac0dad834202ae39`, using the local x64 Release UASM 2.60 executable.

- Skill-creator quick_validate.py: passed.
- All twelve bundled ASM files: assembled successfully with their appropriate Win64/CV8, ELF64/DWARF or binary flags.
- Namespace scope probe: all twelve emitted bytes match the independently specified expected sequence.
- Standalone Windows namespace project: built, linked and ran; PASS.
- Standalone Windows nested-call project: built, linked and ran; PASS.
- Standalone OO tour: built, linked and ran under RSP and RBP; both PASS.
- Standalone Direct2D project: assembled and linked; GUI not launched in this validation pass.
- Linux sample: ELF64 objects assembled on Windows; Linux linking, runtime, GTK and GDB checks were NOT repeated for this documentation/package task. The copied project retains its check targets for running those on Linux.
- Manual Visual Studio/RAD debugging was NOT repeated. Do not infer debugger success solely from assembly or runtime PASS.

No assembler sources, regression baselines or global skill installation were modified. Copied examples retain their repository source license. The release ZIP excludes binaries, PDBs, generated objects and per-machine validation logs.
