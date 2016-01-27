
;--- test expansion and ! operator

	.386
	.model flat, stdcall

	.data

TE1 textequ <!<>,<bx,ax,>
;%	echo TE1
TE1 substr TE1,1,@SizeStr(%TE1)-1
;%	echo TE1
TE1	catstr TE1,<!>>
;%	echo TE1
ifidn TE1,<!<bx,ax!>>
	db 1
else
	db 0
endif

	end
