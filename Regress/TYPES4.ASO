
;--- type conflicts

UINT32 typedef DWORD
INT32  typedef SDWORD
LONG   typedef SDWORD
PVOID  typedef ptr

TD1 typedef DWORD
TD1 typedef UINT32	;ok (v2.03 failed)
TD1 typedef DWORD	;ok

TD2 typedef DWORD
TD2 typedef INT32	;is to fail

PSID typedef PVOID	;ok

S1 struct
f1 dq ?
f2 dq ?
S1 ends

S2 struct
f1 dq ?
f2 dq ?
S2 ends

TD3 typedef S1
TD3 typedef S1	;ok
TD3 typedef S2	;is to fail

TD4 typedef ptr
TD4 typedef ptr		;ok
TD4 typedef ptr S1	;is to fail

TD5	typedef ptr S1
TD5	typedef ptr S2	;is to fail

TD6	typedef INT32
TD6	typedef LONG	;ok (v2.03 failed)

TD7	typedef ptr DWORD
TD7	typedef ptr WORD	;is to fail

TD8	typedef ptr DWORD
TD8	typedef ptr UINT32	;ok

TD9 typedef ptr UINT32
TD9 typedef proto c :word	;is to fail

TD10 typedef ptr WORD
TD10 typedef proto c :word	;is to fail

TD11 typedef proto c :dword
TD11 typedef proto c :word	;is to fail

TD12 typedef ptr BYTE
TD12 typedef ptr SBYTE	;is to fail

HANDLE typedef ptr
HINSTANCE typedef HANDLE
HINSTANCE typedef ptr

	end
