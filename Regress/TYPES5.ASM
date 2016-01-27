
;--- symbol type conflict error in v2.04-v2.06
;--- this example is from dinput.inc
;--- problem: the redefinition of LPCS1 uses a type alias

    option casemap:none

s1A struct
    DWORD ?
x   BYTE  2 dup (?)
s1A ends

LPCS1A typedef ptr s1A
s1     typedef s1A      ;define a type alias
LPCS1  typedef LPCS1A
LPCS1  typedef ptr s1

LPP1   typedef ptr s2   ;pointer to undefined type
s2 struct
s2 ends
LPP1   typedef ptr s2   ;redefine pointer

_DATA segment
    LPCS1 0
_DATA ends

end
