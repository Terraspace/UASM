Nested-call runtime tests
=========================
These complement the normal byte-for-byte regression suite: hostile callees
clobber volatile registers, and the linked program checks the received values.
No external SDK includes, third-party packages or test frameworks are needed.

Windows x64 Native Tools Command Prompt:
  nested-win64.cmd [path-to-UASM.exe]
Windows x86 Native Tools Command Prompt:
  nested-win32.cmd [path-to-UASM.exe]
Linux (GCC for linking):
  sh nested-linux.sh [path-to-uasm]

Windows defaults to ../../x64/Release/UASM.exe; Linux to ../../GccUnixR/uasm.
The optional assembler path is relative to the directory you invoke the script
from. Generated test executables and objects are placed in runtime/results/.
Each executable returns zero on success and one on a value mismatch. Scripts
stop on an assembly/link failure or nonzero runtime status.

Covered: integer/float sibling results, no-argument children, depth-three
Win32 nesting, RBP/RSP, re-entry, outer/inner stack arguments, prior misalignment,
explicit INVOKE children, and OO static/instance nesting. The ordinary regression
suite also checks diagnostics, vector stores, all return widths, argument ten,
12 siblings, namespace macros, typed VOID, depth limits and CodeView output.
