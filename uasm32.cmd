@SET Path=D:\msvc2005ddk\bin
@SET MSVC1=D:\msvc2005ddk
@SET INCLUDE=%MSVC1%\include
@SET LIB=%MSVC1%\lib
SET SRC=..\HJWasm-master
@REM 	for %%c in (%SRC%\*.c) do %CC% %%c
@REM cl -c -Zl -Zp8 -GS- -Gs- -Ox /TC /analyze- /W2 /Gm- /Zc:inline /fp:precise /WX- /Zc:forScope /Gd /Ot /MT -I H *.c
cl /GS /TC /analyze- /W2 /Zc:wchar_t /I H /Gm- /Ox /Zc:inline /fp:precise /D "WINDOWSDDK" /D "WIN32" /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /WX- /Zc:forScope /Gd /Oy- /MT *.c

cl main.obj apiemu.obj orgfixup.obj assemble.obj assume.obj atofloat.obj backptch.obj bin.obj branch.obj cmdline.obj codegen.obj coff.obj condasm.obj context.obj cpumodel.obj data.obj dbgcv.obj directiv.obj elf.obj end.obj equate.obj errmsg.obj expans.obj expreval.obj extern.obj fastpass.obj fixup.obj fpfixup.obj hll.obj input.obj invoke.obj label.obj linnum.obj listing.obj loop.obj lqueue.obj macro.obj mangle.obj memalloc.obj msgtext.obj omf.obj omffixup.obj omfint.obj option.obj parser.obj posndir.obj preproc.obj proc.obj queue.obj reswords.obj safeseh.obj segment.obj simsegm.obj string.obj symbols.obj tbyte.obj tokenize.obj trmem.obj types.obj libc.lib macrolib.obj bufferoverflowu.lib -Feuasm32.exe
@DEL *.obj
pause