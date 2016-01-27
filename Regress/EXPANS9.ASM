
;--- CATSTR, SUBSTR string macro usages

	.model small

	.data

FName textequ <ABCDEFG>
GName textequ <HIJKLMN>

TE1 catstr FName, GName
TE2 catstr <ABCDEFG>, <HIJKLMN>

TE3	substr FName, 4
TE4	substr <ABCDEFG>, 4

FX	textequ <99+1>

E1	sizestr <abcdefg>
E2	sizestr FName
E3	sizestr <%FName>
%E4	sizestr <FName>
E5	sizestr %FX

TE5	substr FName, 4, @SizeStr(FName)-3	;result "DE"
TE6	substr FName, 4, @SizeStr(%FName)-3	;result "DEFG"

	db @CatStr(!",TE1,!")	;res: "TE1"
%	db @CatStr(!",TE4,!")	;res: "TE4" (JWasm prior to v2.08 made "DEFG")
	db @CatStr(!",%TE4,!")	;res: "DEFG"

	db @CatStr(!",@SubStr(TE1,2),!")	;res: "E1"
%	db @CatStr(!",@SubStr(TE1,2),!")	;res: "E1"
	db @CatStr(!",%@SubStr(TE1,2),!")	;res: "E1"
	db @CatStr(!",@SubStr(%TE1,2),!")	;res: "BCDEFGHIJKLMN"

	db E1, E2, E3, E4, E5

END
