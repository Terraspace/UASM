@SET Path=D:\msvc2005ddk\bin\amd64
@SET MSVC1=D:\msvc2005ddk
@SET INCLUDE=%MSVC1%\include
@SET LIB=%MSVC1%\lib\x64
echo @SET SRC=..\HJWasm-master
cl -c -Zl -GS- -Ox -I H *.c

cl main.obj apiemu.obj assemble.obj assume.obj atofloat.obj backptch.obj bin.obj branch.obj cmdline.obj codegen.obj coff.obj condasm.obj context.obj cpumodel.obj data.obj dbgcv.obj directiv.obj elf.obj end.obj equate.obj errmsg.obj expans.obj expreval.obj extern.obj fastpass.obj fixup.obj fpfixup.obj hll.obj input.obj invoke.obj label.obj linnum.obj listing.obj loop.obj lqueue.obj macro.obj mangle.obj memalloc.obj msgtext.obj omf.obj omffixup.obj omfint.obj option.obj parser.obj posndir.obj preproc.obj proc.obj queue.obj reswords.obj safeseh.obj segment.obj simsegm.obj string.obj symbols.obj tbyte.obj tokenize.obj trmem.obj types.obj libc.lib bufferoverflowu.lib -Fehjwasm64.exe
@DEL *.obj
pause
