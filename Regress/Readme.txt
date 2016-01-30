
Files:
    regress/
      exp/		- expected output
	buildexp.cmd	- to build expected output
      src/		- source files
      lib/		- used to build binaries in the test
      tmp/		- result (created by buildexp.cmd)
      owbuild.cmd	- Open Watcom build and test
      runtest.cmd	- main test
      vcbuild.cmd	- Visual C build and test
      fcmp.exe		- file compare used by runtest.cmd
      readme.txt	- this file

To build expected output you need a version that passed the test

buildexp.cmd:

    SET MLBASE=\JWASM\jwasm.exe

  Not defined:

    REM SET OWLINK=\JWASM\jwlink.exe
    REM SET MSLINK=\VC80\bin\link.exe

runtest.cmd:

    SET ASMX=\HJWASM\hjwasm.exe

  Not defined:

    REM SET OWLINK=\JWASM\jwlink.exe
    REM SET MSLINK=\VC80\bin\link.exe
