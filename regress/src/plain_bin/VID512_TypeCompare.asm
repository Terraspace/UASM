 .x64
    .model flat
    .code
HANDLE typedef ptr
MY_STRUCT STRUCT
  hProcess    HANDLE ?
MY_STRUCT ENDS
assume rax:PTR MY_STRUCT
if type( (type [rax].hProcess) ptr [rax].hProcess) NE type([rax].hProcess)
  echo "Error 1"
endif
xor eax,eax
end