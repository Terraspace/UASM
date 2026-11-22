.386
.model flat
option literals:on
.data
named dw "éΩ"
 dw "éΩ"
 dw "é","A",0,"😀"
 dw 2 dup("éΩ","Z")
.errnz TYPE named - 2
.errnz SIZEOF named - 4
end
