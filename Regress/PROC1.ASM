
	.386
	.model small, pascal
	option proc:private

	.code

externdef c p1: far

;--- proto accepts undefined symbols, procs, protos and externdefs

p1 proto far c :word
p1 proto far c :word
p1 proc far c public a1:word
	ret
p1 endp

;externdef p1: far

	end
