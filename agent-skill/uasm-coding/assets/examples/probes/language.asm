; Assemble with -win64. Syntax probe, not an executable entry point.
option casemap:none
option stackbase:rsp
option win64:15
option frame:auto
option proc:private
namespace Model
Pair STRUCT
 first DWORD ?
 second DWORD ?
Pair ENDS
PPair TYPEDEF PTR Pair
endnamespace
.data
pairData Model::Pair <5,7>
.code
ReadPair PROC USES rbx p:Model::PPair
 LOCAL temp:Model::Pair
 mov rbx,p
 ASSUME rbx:PTR Model::Pair
 mov eax,[rbx].Model::Pair.first
 mov temp.first,eax
 mov eax,(Model::Pair PTR [rbx]).second
 mov temp.second,eax
 ASSUME rbx:NOTHING
 .if eax
  dec eax
 .endif
 .while eax
  dec eax
 .endw
 ret
ReadPair ENDP
end

