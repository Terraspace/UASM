
;--- test diverse orders of PROC, PROTO and EXTERNDEF

	.386
	.model small, pascal
	option proc:private

	.code

;--- 1. single proc 

p1 proc c a1:word
	ret
p1 endp

;--- 2. single proto

p2 proto c :word

;--- 3. proto, then proc

p3 proto a1:word
p3 proc a1:word
	ret
p3 endp

;--- 4. externdef, then proc

externdef c p4: near
p4 proc c a1:word
	ret
p4 endp

;--- 5. externdef, proto, then proc

externdef c p5: near
p5 proto c a1:word
p5 proc c a1:word
	ret
p5 endp

;--- 6. proc, then proto

p6 proc c a1:word
	ret
p6 endp

p6 proto c :word

;--- 7. proto, then externdef (with different language)

p7 proto :word
externdef c p7: proc

;--- 8. proc, then externdef (with different language)

p8 proc a1:word
	ret
p8 endp

externdef c p8: near

;--- 9. 2 externdefs (with different language)

externdef pascal p9: proc
externdef c p9: proc

	end
