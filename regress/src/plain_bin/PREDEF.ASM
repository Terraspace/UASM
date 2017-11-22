
;--- predefined text macros 
;--- @FileName, @Line, @CodeSize, @DataSize, @Interface

	.286
	.MODEL small, stdcall
	option casemap:none

	.DATA

	db @CatStr(!",%@FileName,!")
	db @CatStr(!",%@Line,!")
	db @CatStr(!",%@CodeSize,!")
	db @CatStr(!",%@DataSize,!")
	db @CatStr(!",%@Interface,!")

	END


