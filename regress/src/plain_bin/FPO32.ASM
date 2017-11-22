
;--- test option:stackbase in 32-bit

    .686
    .model flat,stdcall
    option casemap:none
    option proc:private

    includelib <kernel32.lib>

    option stackbase:esp
    option renamekeyword: <push>=@@push
    option renamekeyword: <pushd>=@@pushd
    option renamekeyword: <pushw>=@@pushw
    option renamekeyword: <pop>=@@pop
    option renamekeyword: <invoke>=@@invoke
    option renamekeyword: <sub>=@@sub
    option renamekeyword: <add>=@@add
    option renamekeyword: <endp>=@@endp

;--- start FPO redefinitions

push macro x:vararg
    @@push x
  if (@ProcStatus and 7) eq 4  ;outside prologue/epilogue and fpo?
    if type (x)
        @StackBase = @StackBase + type (x)
    else
        @StackBase = @StackBase + @WordSize
    endif
  endif
endm

pushd macro x:vararg
    @@pushd x
  if ( @ProcStatus and 7) eq 4 ;outside prologue/epilogue and fpo?
    @StackBase = @StackBase + 4
  endif
endm

pushw macro x:vararg
    @@pushw x
  if (@ProcStatus and 7) eq 4 ;outside prologue/epilogue and fpo?
    @StackBase = @StackBase + 2
  endif
endm

pop macro x:vararg
  if (@ProcStatus and 7) eq 4 ;outside prologue/epilogue and fpo?
    if type (x)
        @StackBase = @StackBase - type (x)
    else
        @StackBase = @StackBase - @WordSize
    endif
    .errnz @StackBase lt 0, <@StackBase below 0!!>
  endif
    @@pop x
endm

invoke macro args:varargml
  if @ProcStatus and 4
    SavedBase = @StackBase
    @@invoke args
    @StackBase = SavedBase
  else
    @@invoke args
  endif
endm


sub macro dst:req, opnd:req
    @@sub dst, opnd
  if (@ProcStatus and 7) eq 4 ;outside prologue/epilogue and fpo?
    ifidni <dst>,<esp>
      if ( opattr opnd ) and 4 
        @StackBase = @StackBase + (opnd)
      endif
    endif
  endif
endm

add macro dst:req, opnd:req
    @@add dst, opnd
  if (@ProcStatus and 7) eq 4 ;outside prologue/epilogue and fpo?
    ifidni <dst>,<esp>
      if ( opattr opnd ) and 4 
        @StackBase = @StackBase - (opnd)
      endif
    endif
  endif
endm

endp macro name_:label
  if (@ProcStatus and 4) ;fpo on?
    .errnz @StackBase, <@StackBase not zero!!>
  endif
    name_ @@endp
endm

;--- end FPO redefinitions

    .code

xxx proc uses ebx esi a1:dword

local x1:qword
local x2:dword

    mov eax, a1
    mov x2, eax
    add eax, eax
    ret
xxx endp

WinMain proc uses ebx esi hInst:ptr, hPrevInst:ptr, CmdLine:ptr, CmdShow:DWORD

    mov eax, hInst
    invoke xxx, 1
    ret
WinMain endp

start:
    invoke WinMain, 0, 0, 0, 0
    ret

end start
