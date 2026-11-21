.686p
.listmacroall
recurse macro n
if n
recurse %(n-1)
else
db 90h
endif
endm
foo segment use16
recurse 10
foo ends
end
