
;--- GPF if buffer isn't defined ( or forward referenced? )
;--- bug in expreval.c, function get_operand, case T_ID, var opnd is NULL:
;---   if ( sym == opnd->type || opnd->type->isdefined == FALSE || ModuleInfo.oldstructs )
;--- fixed in v2.12

	.386
	.MODEL FLAT, stdcall
	option casemap:none

LARGE_INTEGER union
struct
LowPart  DWORD ?
HighPart SDWORD ?
ends
QuadPart QWORD ?
LARGE_INTEGER ends

MEDIA_TYPE typedef DWORD

DISK_GEOMETRY struct 
Cylinders           LARGE_INTEGER <>
MediaType           MEDIA_TYPE ?
TracksPerCylinder   DWORD ?
SectorsPerTrack     DWORD ?
BytesPerSector      DWORD ?
DISK_GEOMETRY ends

DISK_GEOMETRY_EX struct 8
Geometry    DISK_GEOMETRY <>
DiskSize    LARGE_INTEGER <>
Data        BYTE 1 dup (?)
DISK_GEOMETRY_EX ends

	.DATA

;buffer db 120 dup (?)

	.CODE

	mov ebx,dword ptr buffer.DISK_GEOMETRY_EX.Data

	end

