
;--- test OMF case mapping for option -Cu 
;--- communals and exported names work since v2.11.

extern ext1:near
extern ext2:near

comm c1:dword
comm c2:word

e1 equ 1
e2 equ 2
public e1, e2

s1 segment 's1_code'
p1 proc far export
p1 endp
s1 ends
s2 segment 's2_code'
p2 proc far export
p2 endp
s2 ends

g1 group s1,s2

end
