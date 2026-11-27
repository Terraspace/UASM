; Shared ABI: the executable and library include this file.
option casemap:none
option elfpic:1
option frame:auto
option sysvhome:1
; Explicitly sized null pointer for INVOKE pointer parameters.
NULLPTR textequ <qword ptr 0>
SampleState struct
 count dword ?
 padding dword ?
 total real8 ?
 last real8 ?
SampleState ends
IFNDEF BUILD_LIBRARY
extern sample_model:SampleState
extern sample_events:qword
ENDIF
sample_reset proto SYSTEMV state:ptr SampleState
sample_add proto SYSTEMV state:ptr SampleState, amount:real8
puts proto SYSTEMV text:ptr byte
