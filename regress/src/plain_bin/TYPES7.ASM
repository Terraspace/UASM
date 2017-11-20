
;--- comparison of pointer types
;--- did only partially work prior to v2.10

_DATA segment

T1  typedef ptr DWORD
T2  typedef ptr SDWORD
T11 typedef ptr T1
T21 typedef ptr T2

v1	T1 0
v2	T2 0
v11	T11 0
v21	T21 0

	db (type T1) EQ (type T2)
	db T1        EQ T2			; the simpler variant ( no TYPE operator needed to compare types )
	db (type v1) EQ (type v2)

;--- increase level of indirection

	db (type T11) EQ (type T21)
	db T11        EQ T21
	db (type v11) EQ (type v21)


;--- target is equal, but different level of indirection

	db (type T11) EQ (type T1)
	db T11        EQ T1
	db (type v11) EQ (type v1)

;--- compare types that ARE equal

T3 typedef ptr DWORD
T4 typedef ptr DWORD
T31 typedef ptr T3
T41 typedef ptr T4

v3	T3 0
v4	T4 0
v31	T31 0
v41	T41 0

	db (type T3) EQ (type T4)
	db T3        EQ T4
	db (type v3) EQ (type v4)

	db (type T31) EQ (type T41)
	db T31        EQ T41
	db (type v31) EQ (type v41)

_DATA ends

end
