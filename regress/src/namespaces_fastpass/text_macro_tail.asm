.686
.model flat
option casemap:none
namespace LongMacroNamespace
operation TEXTEQU <mov>
statement TEXTEQU <operation eax,12345678h>
.code
statement
another TEXTEQU <statement>
another
@CatStr(operation eax, <,12345678h>)
endnamespace
; Macro identifiers resolve at the expansion site.
operation TEXTEQU <mov>
::LongMacroNamespace::statement
end
