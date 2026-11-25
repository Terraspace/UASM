Procedure-local shadowing (experimental v2.60b)

LOCAL variables and named PROC parameters may shadow module symbols.
Declaration checks search only the active procedure's local table. Ordinary
references retain local-first lookup; global symbols and unresolved global
references are not removed or renamed. Duplicate parameters, duplicate locals,
and local/parameter collisions within one procedure remain errors.

This deliberately extends ML/ML64: tested Microsoft tools reject shadowing
when a global is already defined but accept it when the global is defined later.
The comparison covered data, numeric EQU, TYPEDEF, STRUCT, labels, EXTERN,
PROTO, macro names and TEXTEQU in all four parameter positions, 32/64-bit.
TEXTEQU substitution remains preprocessing, not lexical shadowing: an identifier
replacement renames the parameter before declaration, while a numeric
replacement is invalid. No changes are made to text/macro expansion rules.

Regression controls:
scopes32/64: parameter and LOCAL shadowing, PROTO-to-PROC attachment, repeated
local names, data/constants/types/labels/prototypes/record fields, global
resolution restored after ENDP. Baselines independently assembled by release
2.60 after renaming only the conflicting global declarations/references.
forward_text32/64: unresolved/later globals and TEXTEQU behaviour unchanged;
baselines agree between release and fixed assemblers.
smart_unused: WIN64:15 unused parameter remains unhomed; binary agrees with
release control using nonconflicting global names.
duplicate_params/duplicate_locals/param_local: diagnostics match release 2.60.

Declaration lookup must not set used flags: they drive smart homing. Existing
SymFindLocal reference lookup retains its used-flag behaviour; the new
SymFindLocalDeclare helper is side-effect-free apart from its insertion cursor.
