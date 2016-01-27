
;--- test 3DNow

	.586
	.model flat
	.k3d

	.data

v1	dq 0

	.code

	femms
	pfmax mm0, mm1
	pfmax mm0, [v1]
	pfmax mm3, [v1]
	pfmax mm3, [esp+edx*2+1]
	prefetch [v1]
	prefetchw [v1]

	end
