# Pack validation — 2026-11-27

Validated against UASM master `e693c8c2555c04980308910cac0dad834202ae39`, using the local x64 Release UASM 2.60 executable.

- Skill-creator quick_validate.py: passed.
- All fourteen bundled ASM files (with WinInc configured for the header-based starter): assembled successfully with their appropriate Win64/CV8, ELF64/DWARF or binary flags.
- Namespace scope probe: all twelve emitted bytes match the independently specified expected sequence.
- Standalone Windows namespace project: built, linked and ran; PASS.
- Standalone Windows nested-call project: built, linked and ran; PASS.
- Standalone OO tour: built, linked and ran under RSP and RBP; both PASS.
- Standalone Direct2D project: assembled and linked; GUI not launched in this validation pass.
- Linux sample: ELF64 objects assembled on Windows; Linux linking, runtime, GTK and GDB checks were NOT repeated for this documentation/package task. The copied project retains its check targets for running those on Linux.
- Manual Visual Studio/RAD debugging was NOT repeated. Do not infer debugger success solely from assembly or runtime PASS.

No assembler sources, regression baselines or global skill installation were modified. Copied examples retain their repository source license. The release ZIP excludes binaries, PDBs, generated objects and per-machine validation logs.

## 1.0.1 starter feedback

Defaults now explicitly select x64 for new code (including a generic "Win32 API" request), ARCH:AVX, typed PROTO/plain PROC and `&` in C-style calls, subject to explicit user/project constraints. PROC type-before-FRAME assembled successfully; type-after-FRAME and FRAME PUBLIC were independently rejected. Comma-continued prototype lines assembled successfully. The original generated starter was not standalone because its three includes were absent. With controlled minimal header declarations and corrected PROC/PUBLIC syntax, its C-style OR-expression still failed; an EQU constant fixed that. ADDR calls remained accepted.

The new self-contained window starter assembled and linked in both normal and SMOKE_TEST configurations. The hidden-window smoke executable completed within a ten-second timeout with exit zero, exercising creation, WM_CLOSE/WM_DESTROY and the GetMessage loop. The normal interactive executable was built but not manually inspected in this pass. No assembler implementation changes were made.

## 1.0.2 Windows header defaults

Added .x64, EVEX:1 and the requested global WinInc include block to the new-code defaults; windows.inc supplies API declarations without kernel32.inc/user32.inc. Added INCLUDELIB kernel32.lib/user32.lib. Header/library locations remain configurable, not embedded personal paths. The original self-contained starter remains an explicit alternative.

All fourteen ASM files assembled with the include directory supplied externally. Both normal and SMOKE_TEST WinInc starters linked using only their INCLUDELIB directives (no library names on the link command). The hidden-window smoke test exited zero within ten seconds. The C-style OR-expression issue is recorded as a confirmed token-boundary bug, not a supported-language restriction. No assembler implementation changes were made.

## 1.0.3 packing feedback

The user's new GUI source omitted -Zp8. Independent object-data probes measured MSG at 40 bytes (wParam=12, lParam=20, pt=32) without it, versus the correct 48 bytes (16/24/36) with it. The generated local buffer at RSP+0x70 in a 0x98-byte frame allowed a 48-byte OS write to reach the saved return address. The same user source, rebuilt with -Zp8, passed an automated WM_CLOSE test and exited zero. Default skill build commands now require -Zp8 for WinInc x64. The WinInc starter has layout assertions for SIZEOF and member offsets, and omission is checked as an expected assembly failure. No assembler implementation changes were made.
