
; Declare GLIBC prototypes (with output format -elf64 SYSTEMV ABI is assumed as the default).
;********************************************************************************************

malloc PROTO memSize:QWORD
free   PROTO memPtr:QWORD
printf PROTO pString:PTR, args:VARARG
exit   PROTO exitcode:DWORD
close  PROTO fd:DWORD

__errno_location PROTO SYSTEMV

CLOCK_REALTIME	= 0
CLOCK_MONOTONIC	= 1
TIMER_ABSTIME	= 1

time_t TYPEDEF QWORD

timespec STRUCT
tv_sec  time_t ?
tv_nsec dq ?
timespec ENDS

clock_gettime PROTO clockid_t:DWORD, pTimeSpec:PTR


