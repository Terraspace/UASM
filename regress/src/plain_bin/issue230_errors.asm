.386
.model flat
DBW RECORD hibyte:8,lobyte:8
extern target:byte
.code
mov ax,DBW <target,1>
mov ax,DBW <1,2,3>
mov ax,DBW <1+,2>
end
