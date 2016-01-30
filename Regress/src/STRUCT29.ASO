
;--- checked since v2.09:
;--- a member with TYPEDEF type and a literal as initializer.
;--- Masm complains only if the struct is instanced or -Fl is set
;--- JWasm emits a warning at -W3

	.286

TD1 typedef WORD

S1 struct
	TD1 <1>
S1 ends

	end
