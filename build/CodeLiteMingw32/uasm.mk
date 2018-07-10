##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=uasm
ConfigurationName      :=Release
WorkspacePath          :=D:/Libraries/eXOAMP/UASM/build/CodeLiteMingw32
ProjectPath            :=D:/Libraries/eXOAMP/UASM/build/CodeLiteMingw32
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=vitor
Date                   :=30/06/2018
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=D:/ExternalCompilers/msys64/mingw64/bin/g++.exe
SharedObjectLinkerName :=D:/ExternalCompilers/msys64/mingw64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)DEBUG_OUT $(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="uasm.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=D:/ExternalCompilers/msys64/mingw64/bin/windres.exe
LinkOptions            :=  
IncludePath            := $(IncludeSwitch)D:/ExternalCompilers/msys64/mingw64/include/c++/7.3.0 $(IncludeSwitch)D:/ExternalCompilers/msys64/mingw64/include/c++/7.3.0/x86_64-w64-mingw32 $(IncludeSwitch)D:/ExternalCompilers/msys64/mingw64/include/c++/7.3.0/backward $(IncludeSwitch)D:/ExternalCompilers/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/7.3.0/include $(IncludeSwitch)D:/ExternalCompilers/msys64/mingw64/include $(IncludeSwitch)D:/ExternalCompilers/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/7.3.0/include-fixed $(IncludeSwitch)D:/ExternalCompilers/msys64/mingw64/x86_64-w64-mingw32/include  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../../H 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                :=$(LibraryPathSwitch)D:/ExternalCompilers/msys64/mingw64/lib/gcc/x86_64-w64-mingw32/7.3.0 $(LibraryPathSwitch)D:/ExternalCompilers/msys64/mingw64/lib $(LibraryPathSwitch)D:/ExternalCompilers/msys64/mingw64/x86_64-w64-mingw32/lib  $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := D:/ExternalCompilers/msys64/mingw64/bin/ar.exe rcu
CXX      := D:/ExternalCompilers/msys64/mingw64/bin/g++.exe
CC       := D:/ExternalCompilers/msys64/mingw64/bin/gcc.exe
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := D:/ExternalCompilers/msys64/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/up_up_assemble.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_assume.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_atofloat.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_codegen.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_coff.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_condasm.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_cpumodel.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_end.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_elf.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_equate.c$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_errmsg.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_extern.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_fixup.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_fpfixup.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_hll.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_input.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_linnum.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_listing.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_loop.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_lqueue.c$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_macho64.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_macrolib.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_mangle.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_omffixup.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_omfint.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_macro.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_posndir.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_proc.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_queue.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_reswords.c$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_branch.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_simd.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_simsegm.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_tbyte.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_tokenize.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_main.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_trmem.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_directiv.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_parser.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_label.c$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_omf.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_data.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_fastpass.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_expreval.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_ltype.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_apiemu.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_invoke.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_backptch.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_expans.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_safeseh.c$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_types.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_cmdline.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_orgfixup.c$(ObjectSuffix) 

Objects1=$(IntermediateDirectory)/up_up_bin.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_dbgcv.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_preproc.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_option.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_context.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_symbols.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_memalloc.c$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_string.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_segment.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_msgtext.c$(ObjectSuffix) 



Objects=$(Objects0) $(Objects1) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	@echo $(Objects1) >> $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Release"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/up_up_assemble.c$(ObjectSuffix): ../../assemble.c $(IntermediateDirectory)/up_up_assemble.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/assemble.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_assemble.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_assemble.c$(DependSuffix): ../../assemble.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_assemble.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_assemble.c$(DependSuffix) -MM ../../assemble.c

$(IntermediateDirectory)/up_up_assemble.c$(PreprocessSuffix): ../../assemble.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_assemble.c$(PreprocessSuffix) ../../assemble.c

$(IntermediateDirectory)/up_up_assume.c$(ObjectSuffix): ../../assume.c $(IntermediateDirectory)/up_up_assume.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/assume.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_assume.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_assume.c$(DependSuffix): ../../assume.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_assume.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_assume.c$(DependSuffix) -MM ../../assume.c

$(IntermediateDirectory)/up_up_assume.c$(PreprocessSuffix): ../../assume.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_assume.c$(PreprocessSuffix) ../../assume.c

$(IntermediateDirectory)/up_up_atofloat.c$(ObjectSuffix): ../../atofloat.c $(IntermediateDirectory)/up_up_atofloat.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/atofloat.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_atofloat.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_atofloat.c$(DependSuffix): ../../atofloat.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_atofloat.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_atofloat.c$(DependSuffix) -MM ../../atofloat.c

$(IntermediateDirectory)/up_up_atofloat.c$(PreprocessSuffix): ../../atofloat.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_atofloat.c$(PreprocessSuffix) ../../atofloat.c

$(IntermediateDirectory)/up_up_codegen.c$(ObjectSuffix): ../../codegen.c $(IntermediateDirectory)/up_up_codegen.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/codegen.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_codegen.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_codegen.c$(DependSuffix): ../../codegen.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_codegen.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_codegen.c$(DependSuffix) -MM ../../codegen.c

$(IntermediateDirectory)/up_up_codegen.c$(PreprocessSuffix): ../../codegen.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_codegen.c$(PreprocessSuffix) ../../codegen.c

$(IntermediateDirectory)/up_up_coff.c$(ObjectSuffix): ../../coff.c $(IntermediateDirectory)/up_up_coff.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/coff.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_coff.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_coff.c$(DependSuffix): ../../coff.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_coff.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_coff.c$(DependSuffix) -MM ../../coff.c

$(IntermediateDirectory)/up_up_coff.c$(PreprocessSuffix): ../../coff.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_coff.c$(PreprocessSuffix) ../../coff.c

$(IntermediateDirectory)/up_up_condasm.c$(ObjectSuffix): ../../condasm.c $(IntermediateDirectory)/up_up_condasm.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/condasm.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_condasm.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_condasm.c$(DependSuffix): ../../condasm.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_condasm.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_condasm.c$(DependSuffix) -MM ../../condasm.c

$(IntermediateDirectory)/up_up_condasm.c$(PreprocessSuffix): ../../condasm.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_condasm.c$(PreprocessSuffix) ../../condasm.c

$(IntermediateDirectory)/up_up_cpumodel.c$(ObjectSuffix): ../../cpumodel.c $(IntermediateDirectory)/up_up_cpumodel.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/cpumodel.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_cpumodel.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_cpumodel.c$(DependSuffix): ../../cpumodel.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_cpumodel.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_cpumodel.c$(DependSuffix) -MM ../../cpumodel.c

$(IntermediateDirectory)/up_up_cpumodel.c$(PreprocessSuffix): ../../cpumodel.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_cpumodel.c$(PreprocessSuffix) ../../cpumodel.c

$(IntermediateDirectory)/up_up_end.c$(ObjectSuffix): ../../end.c $(IntermediateDirectory)/up_up_end.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/end.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_end.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_end.c$(DependSuffix): ../../end.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_end.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_end.c$(DependSuffix) -MM ../../end.c

$(IntermediateDirectory)/up_up_end.c$(PreprocessSuffix): ../../end.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_end.c$(PreprocessSuffix) ../../end.c

$(IntermediateDirectory)/up_up_elf.c$(ObjectSuffix): ../../elf.c $(IntermediateDirectory)/up_up_elf.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/elf.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_elf.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_elf.c$(DependSuffix): ../../elf.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_elf.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_elf.c$(DependSuffix) -MM ../../elf.c

$(IntermediateDirectory)/up_up_elf.c$(PreprocessSuffix): ../../elf.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_elf.c$(PreprocessSuffix) ../../elf.c

$(IntermediateDirectory)/up_up_equate.c$(ObjectSuffix): ../../equate.c $(IntermediateDirectory)/up_up_equate.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/equate.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_equate.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_equate.c$(DependSuffix): ../../equate.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_equate.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_equate.c$(DependSuffix) -MM ../../equate.c

$(IntermediateDirectory)/up_up_equate.c$(PreprocessSuffix): ../../equate.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_equate.c$(PreprocessSuffix) ../../equate.c

$(IntermediateDirectory)/up_up_errmsg.c$(ObjectSuffix): ../../errmsg.c $(IntermediateDirectory)/up_up_errmsg.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/errmsg.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_errmsg.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_errmsg.c$(DependSuffix): ../../errmsg.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_errmsg.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_errmsg.c$(DependSuffix) -MM ../../errmsg.c

$(IntermediateDirectory)/up_up_errmsg.c$(PreprocessSuffix): ../../errmsg.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_errmsg.c$(PreprocessSuffix) ../../errmsg.c

$(IntermediateDirectory)/up_up_extern.c$(ObjectSuffix): ../../extern.c $(IntermediateDirectory)/up_up_extern.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/extern.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_extern.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_extern.c$(DependSuffix): ../../extern.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_extern.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_extern.c$(DependSuffix) -MM ../../extern.c

$(IntermediateDirectory)/up_up_extern.c$(PreprocessSuffix): ../../extern.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_extern.c$(PreprocessSuffix) ../../extern.c

$(IntermediateDirectory)/up_up_fixup.c$(ObjectSuffix): ../../fixup.c $(IntermediateDirectory)/up_up_fixup.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/fixup.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_fixup.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_fixup.c$(DependSuffix): ../../fixup.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_fixup.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_fixup.c$(DependSuffix) -MM ../../fixup.c

$(IntermediateDirectory)/up_up_fixup.c$(PreprocessSuffix): ../../fixup.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_fixup.c$(PreprocessSuffix) ../../fixup.c

$(IntermediateDirectory)/up_up_fpfixup.c$(ObjectSuffix): ../../fpfixup.c $(IntermediateDirectory)/up_up_fpfixup.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/fpfixup.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_fpfixup.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_fpfixup.c$(DependSuffix): ../../fpfixup.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_fpfixup.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_fpfixup.c$(DependSuffix) -MM ../../fpfixup.c

$(IntermediateDirectory)/up_up_fpfixup.c$(PreprocessSuffix): ../../fpfixup.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_fpfixup.c$(PreprocessSuffix) ../../fpfixup.c

$(IntermediateDirectory)/up_up_hll.c$(ObjectSuffix): ../../hll.c $(IntermediateDirectory)/up_up_hll.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/hll.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_hll.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_hll.c$(DependSuffix): ../../hll.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_hll.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_hll.c$(DependSuffix) -MM ../../hll.c

$(IntermediateDirectory)/up_up_hll.c$(PreprocessSuffix): ../../hll.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_hll.c$(PreprocessSuffix) ../../hll.c

$(IntermediateDirectory)/up_up_input.c$(ObjectSuffix): ../../input.c $(IntermediateDirectory)/up_up_input.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/input.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_input.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_input.c$(DependSuffix): ../../input.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_input.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_input.c$(DependSuffix) -MM ../../input.c

$(IntermediateDirectory)/up_up_input.c$(PreprocessSuffix): ../../input.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_input.c$(PreprocessSuffix) ../../input.c

$(IntermediateDirectory)/up_up_linnum.c$(ObjectSuffix): ../../linnum.c $(IntermediateDirectory)/up_up_linnum.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/linnum.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_linnum.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_linnum.c$(DependSuffix): ../../linnum.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_linnum.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_linnum.c$(DependSuffix) -MM ../../linnum.c

$(IntermediateDirectory)/up_up_linnum.c$(PreprocessSuffix): ../../linnum.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_linnum.c$(PreprocessSuffix) ../../linnum.c

$(IntermediateDirectory)/up_up_listing.c$(ObjectSuffix): ../../listing.c $(IntermediateDirectory)/up_up_listing.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/listing.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_listing.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_listing.c$(DependSuffix): ../../listing.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_listing.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_listing.c$(DependSuffix) -MM ../../listing.c

$(IntermediateDirectory)/up_up_listing.c$(PreprocessSuffix): ../../listing.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_listing.c$(PreprocessSuffix) ../../listing.c

$(IntermediateDirectory)/up_up_loop.c$(ObjectSuffix): ../../loop.c $(IntermediateDirectory)/up_up_loop.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/loop.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_loop.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_loop.c$(DependSuffix): ../../loop.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_loop.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_loop.c$(DependSuffix) -MM ../../loop.c

$(IntermediateDirectory)/up_up_loop.c$(PreprocessSuffix): ../../loop.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_loop.c$(PreprocessSuffix) ../../loop.c

$(IntermediateDirectory)/up_up_lqueue.c$(ObjectSuffix): ../../lqueue.c $(IntermediateDirectory)/up_up_lqueue.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/lqueue.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_lqueue.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_lqueue.c$(DependSuffix): ../../lqueue.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_lqueue.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_lqueue.c$(DependSuffix) -MM ../../lqueue.c

$(IntermediateDirectory)/up_up_lqueue.c$(PreprocessSuffix): ../../lqueue.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_lqueue.c$(PreprocessSuffix) ../../lqueue.c

$(IntermediateDirectory)/up_up_macho64.c$(ObjectSuffix): ../../macho64.c $(IntermediateDirectory)/up_up_macho64.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/macho64.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_macho64.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_macho64.c$(DependSuffix): ../../macho64.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_macho64.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_macho64.c$(DependSuffix) -MM ../../macho64.c

$(IntermediateDirectory)/up_up_macho64.c$(PreprocessSuffix): ../../macho64.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_macho64.c$(PreprocessSuffix) ../../macho64.c

$(IntermediateDirectory)/up_up_macrolib.c$(ObjectSuffix): ../../macrolib.c $(IntermediateDirectory)/up_up_macrolib.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/macrolib.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_macrolib.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_macrolib.c$(DependSuffix): ../../macrolib.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_macrolib.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_macrolib.c$(DependSuffix) -MM ../../macrolib.c

$(IntermediateDirectory)/up_up_macrolib.c$(PreprocessSuffix): ../../macrolib.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_macrolib.c$(PreprocessSuffix) ../../macrolib.c

$(IntermediateDirectory)/up_up_mangle.c$(ObjectSuffix): ../../mangle.c $(IntermediateDirectory)/up_up_mangle.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/mangle.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_mangle.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_mangle.c$(DependSuffix): ../../mangle.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_mangle.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_mangle.c$(DependSuffix) -MM ../../mangle.c

$(IntermediateDirectory)/up_up_mangle.c$(PreprocessSuffix): ../../mangle.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_mangle.c$(PreprocessSuffix) ../../mangle.c

$(IntermediateDirectory)/up_up_omffixup.c$(ObjectSuffix): ../../omffixup.c $(IntermediateDirectory)/up_up_omffixup.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/omffixup.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_omffixup.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_omffixup.c$(DependSuffix): ../../omffixup.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_omffixup.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_omffixup.c$(DependSuffix) -MM ../../omffixup.c

$(IntermediateDirectory)/up_up_omffixup.c$(PreprocessSuffix): ../../omffixup.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_omffixup.c$(PreprocessSuffix) ../../omffixup.c

$(IntermediateDirectory)/up_up_omfint.c$(ObjectSuffix): ../../omfint.c $(IntermediateDirectory)/up_up_omfint.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/omfint.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_omfint.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_omfint.c$(DependSuffix): ../../omfint.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_omfint.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_omfint.c$(DependSuffix) -MM ../../omfint.c

$(IntermediateDirectory)/up_up_omfint.c$(PreprocessSuffix): ../../omfint.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_omfint.c$(PreprocessSuffix) ../../omfint.c

$(IntermediateDirectory)/up_up_macro.c$(ObjectSuffix): ../../macro.c $(IntermediateDirectory)/up_up_macro.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/macro.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_macro.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_macro.c$(DependSuffix): ../../macro.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_macro.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_macro.c$(DependSuffix) -MM ../../macro.c

$(IntermediateDirectory)/up_up_macro.c$(PreprocessSuffix): ../../macro.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_macro.c$(PreprocessSuffix) ../../macro.c

$(IntermediateDirectory)/up_up_posndir.c$(ObjectSuffix): ../../posndir.c $(IntermediateDirectory)/up_up_posndir.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/posndir.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_posndir.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_posndir.c$(DependSuffix): ../../posndir.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_posndir.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_posndir.c$(DependSuffix) -MM ../../posndir.c

$(IntermediateDirectory)/up_up_posndir.c$(PreprocessSuffix): ../../posndir.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_posndir.c$(PreprocessSuffix) ../../posndir.c

$(IntermediateDirectory)/up_up_proc.c$(ObjectSuffix): ../../proc.c $(IntermediateDirectory)/up_up_proc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/proc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_proc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_proc.c$(DependSuffix): ../../proc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_proc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_proc.c$(DependSuffix) -MM ../../proc.c

$(IntermediateDirectory)/up_up_proc.c$(PreprocessSuffix): ../../proc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_proc.c$(PreprocessSuffix) ../../proc.c

$(IntermediateDirectory)/up_up_queue.c$(ObjectSuffix): ../../queue.c $(IntermediateDirectory)/up_up_queue.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/queue.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_queue.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_queue.c$(DependSuffix): ../../queue.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_queue.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_queue.c$(DependSuffix) -MM ../../queue.c

$(IntermediateDirectory)/up_up_queue.c$(PreprocessSuffix): ../../queue.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_queue.c$(PreprocessSuffix) ../../queue.c

$(IntermediateDirectory)/up_up_reswords.c$(ObjectSuffix): ../../reswords.c $(IntermediateDirectory)/up_up_reswords.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/reswords.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_reswords.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_reswords.c$(DependSuffix): ../../reswords.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_reswords.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_reswords.c$(DependSuffix) -MM ../../reswords.c

$(IntermediateDirectory)/up_up_reswords.c$(PreprocessSuffix): ../../reswords.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_reswords.c$(PreprocessSuffix) ../../reswords.c

$(IntermediateDirectory)/up_up_branch.c$(ObjectSuffix): ../../branch.c $(IntermediateDirectory)/up_up_branch.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/branch.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_branch.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_branch.c$(DependSuffix): ../../branch.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_branch.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_branch.c$(DependSuffix) -MM ../../branch.c

$(IntermediateDirectory)/up_up_branch.c$(PreprocessSuffix): ../../branch.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_branch.c$(PreprocessSuffix) ../../branch.c

$(IntermediateDirectory)/up_up_simd.c$(ObjectSuffix): ../../simd.c $(IntermediateDirectory)/up_up_simd.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/simd.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_simd.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_simd.c$(DependSuffix): ../../simd.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_simd.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_simd.c$(DependSuffix) -MM ../../simd.c

$(IntermediateDirectory)/up_up_simd.c$(PreprocessSuffix): ../../simd.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_simd.c$(PreprocessSuffix) ../../simd.c

$(IntermediateDirectory)/up_up_simsegm.c$(ObjectSuffix): ../../simsegm.c $(IntermediateDirectory)/up_up_simsegm.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/simsegm.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_simsegm.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_simsegm.c$(DependSuffix): ../../simsegm.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_simsegm.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_simsegm.c$(DependSuffix) -MM ../../simsegm.c

$(IntermediateDirectory)/up_up_simsegm.c$(PreprocessSuffix): ../../simsegm.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_simsegm.c$(PreprocessSuffix) ../../simsegm.c

$(IntermediateDirectory)/up_up_tbyte.c$(ObjectSuffix): ../../tbyte.c $(IntermediateDirectory)/up_up_tbyte.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/tbyte.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_tbyte.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_tbyte.c$(DependSuffix): ../../tbyte.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_tbyte.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_tbyte.c$(DependSuffix) -MM ../../tbyte.c

$(IntermediateDirectory)/up_up_tbyte.c$(PreprocessSuffix): ../../tbyte.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_tbyte.c$(PreprocessSuffix) ../../tbyte.c

$(IntermediateDirectory)/up_up_tokenize.c$(ObjectSuffix): ../../tokenize.c $(IntermediateDirectory)/up_up_tokenize.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/tokenize.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_tokenize.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_tokenize.c$(DependSuffix): ../../tokenize.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_tokenize.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_tokenize.c$(DependSuffix) -MM ../../tokenize.c

$(IntermediateDirectory)/up_up_tokenize.c$(PreprocessSuffix): ../../tokenize.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_tokenize.c$(PreprocessSuffix) ../../tokenize.c

$(IntermediateDirectory)/up_up_main.c$(ObjectSuffix): ../../main.c $(IntermediateDirectory)/up_up_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_main.c$(DependSuffix): ../../main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_main.c$(DependSuffix) -MM ../../main.c

$(IntermediateDirectory)/up_up_main.c$(PreprocessSuffix): ../../main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_main.c$(PreprocessSuffix) ../../main.c

$(IntermediateDirectory)/up_up_trmem.c$(ObjectSuffix): ../../trmem.c $(IntermediateDirectory)/up_up_trmem.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/trmem.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_trmem.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_trmem.c$(DependSuffix): ../../trmem.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_trmem.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_trmem.c$(DependSuffix) -MM ../../trmem.c

$(IntermediateDirectory)/up_up_trmem.c$(PreprocessSuffix): ../../trmem.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_trmem.c$(PreprocessSuffix) ../../trmem.c

$(IntermediateDirectory)/up_up_directiv.c$(ObjectSuffix): ../../directiv.c $(IntermediateDirectory)/up_up_directiv.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/directiv.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_directiv.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_directiv.c$(DependSuffix): ../../directiv.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_directiv.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_directiv.c$(DependSuffix) -MM ../../directiv.c

$(IntermediateDirectory)/up_up_directiv.c$(PreprocessSuffix): ../../directiv.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_directiv.c$(PreprocessSuffix) ../../directiv.c

$(IntermediateDirectory)/up_up_parser.c$(ObjectSuffix): ../../parser.c $(IntermediateDirectory)/up_up_parser.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/parser.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_parser.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_parser.c$(DependSuffix): ../../parser.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_parser.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_parser.c$(DependSuffix) -MM ../../parser.c

$(IntermediateDirectory)/up_up_parser.c$(PreprocessSuffix): ../../parser.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_parser.c$(PreprocessSuffix) ../../parser.c

$(IntermediateDirectory)/up_up_label.c$(ObjectSuffix): ../../label.c $(IntermediateDirectory)/up_up_label.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/label.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_label.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_label.c$(DependSuffix): ../../label.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_label.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_label.c$(DependSuffix) -MM ../../label.c

$(IntermediateDirectory)/up_up_label.c$(PreprocessSuffix): ../../label.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_label.c$(PreprocessSuffix) ../../label.c

$(IntermediateDirectory)/up_up_omf.c$(ObjectSuffix): ../../omf.c $(IntermediateDirectory)/up_up_omf.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/omf.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_omf.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_omf.c$(DependSuffix): ../../omf.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_omf.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_omf.c$(DependSuffix) -MM ../../omf.c

$(IntermediateDirectory)/up_up_omf.c$(PreprocessSuffix): ../../omf.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_omf.c$(PreprocessSuffix) ../../omf.c

$(IntermediateDirectory)/up_up_data.c$(ObjectSuffix): ../../data.c $(IntermediateDirectory)/up_up_data.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/data.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_data.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_data.c$(DependSuffix): ../../data.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_data.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_data.c$(DependSuffix) -MM ../../data.c

$(IntermediateDirectory)/up_up_data.c$(PreprocessSuffix): ../../data.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_data.c$(PreprocessSuffix) ../../data.c

$(IntermediateDirectory)/up_up_fastpass.c$(ObjectSuffix): ../../fastpass.c $(IntermediateDirectory)/up_up_fastpass.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/fastpass.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_fastpass.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_fastpass.c$(DependSuffix): ../../fastpass.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_fastpass.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_fastpass.c$(DependSuffix) -MM ../../fastpass.c

$(IntermediateDirectory)/up_up_fastpass.c$(PreprocessSuffix): ../../fastpass.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_fastpass.c$(PreprocessSuffix) ../../fastpass.c

$(IntermediateDirectory)/up_up_expreval.c$(ObjectSuffix): ../../expreval.c $(IntermediateDirectory)/up_up_expreval.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/expreval.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_expreval.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_expreval.c$(DependSuffix): ../../expreval.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_expreval.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_expreval.c$(DependSuffix) -MM ../../expreval.c

$(IntermediateDirectory)/up_up_expreval.c$(PreprocessSuffix): ../../expreval.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_expreval.c$(PreprocessSuffix) ../../expreval.c

$(IntermediateDirectory)/up_up_ltype.c$(ObjectSuffix): ../../ltype.c $(IntermediateDirectory)/up_up_ltype.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/ltype.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_ltype.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_ltype.c$(DependSuffix): ../../ltype.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_ltype.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_ltype.c$(DependSuffix) -MM ../../ltype.c

$(IntermediateDirectory)/up_up_ltype.c$(PreprocessSuffix): ../../ltype.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_ltype.c$(PreprocessSuffix) ../../ltype.c

$(IntermediateDirectory)/up_up_apiemu.c$(ObjectSuffix): ../../apiemu.c $(IntermediateDirectory)/up_up_apiemu.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/apiemu.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_apiemu.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_apiemu.c$(DependSuffix): ../../apiemu.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_apiemu.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_apiemu.c$(DependSuffix) -MM ../../apiemu.c

$(IntermediateDirectory)/up_up_apiemu.c$(PreprocessSuffix): ../../apiemu.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_apiemu.c$(PreprocessSuffix) ../../apiemu.c

$(IntermediateDirectory)/up_up_invoke.c$(ObjectSuffix): ../../invoke.c $(IntermediateDirectory)/up_up_invoke.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/invoke.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_invoke.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_invoke.c$(DependSuffix): ../../invoke.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_invoke.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_invoke.c$(DependSuffix) -MM ../../invoke.c

$(IntermediateDirectory)/up_up_invoke.c$(PreprocessSuffix): ../../invoke.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_invoke.c$(PreprocessSuffix) ../../invoke.c

$(IntermediateDirectory)/up_up_backptch.c$(ObjectSuffix): ../../backptch.c $(IntermediateDirectory)/up_up_backptch.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/backptch.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_backptch.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_backptch.c$(DependSuffix): ../../backptch.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_backptch.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_backptch.c$(DependSuffix) -MM ../../backptch.c

$(IntermediateDirectory)/up_up_backptch.c$(PreprocessSuffix): ../../backptch.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_backptch.c$(PreprocessSuffix) ../../backptch.c

$(IntermediateDirectory)/up_up_expans.c$(ObjectSuffix): ../../expans.c $(IntermediateDirectory)/up_up_expans.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/expans.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_expans.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_expans.c$(DependSuffix): ../../expans.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_expans.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_expans.c$(DependSuffix) -MM ../../expans.c

$(IntermediateDirectory)/up_up_expans.c$(PreprocessSuffix): ../../expans.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_expans.c$(PreprocessSuffix) ../../expans.c

$(IntermediateDirectory)/up_up_safeseh.c$(ObjectSuffix): ../../safeseh.c $(IntermediateDirectory)/up_up_safeseh.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/safeseh.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_safeseh.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_safeseh.c$(DependSuffix): ../../safeseh.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_safeseh.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_safeseh.c$(DependSuffix) -MM ../../safeseh.c

$(IntermediateDirectory)/up_up_safeseh.c$(PreprocessSuffix): ../../safeseh.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_safeseh.c$(PreprocessSuffix) ../../safeseh.c

$(IntermediateDirectory)/up_up_types.c$(ObjectSuffix): ../../types.c $(IntermediateDirectory)/up_up_types.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/types.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_types.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_types.c$(DependSuffix): ../../types.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_types.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_types.c$(DependSuffix) -MM ../../types.c

$(IntermediateDirectory)/up_up_types.c$(PreprocessSuffix): ../../types.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_types.c$(PreprocessSuffix) ../../types.c

$(IntermediateDirectory)/up_up_cmdline.c$(ObjectSuffix): ../../cmdline.c $(IntermediateDirectory)/up_up_cmdline.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/cmdline.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_cmdline.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_cmdline.c$(DependSuffix): ../../cmdline.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_cmdline.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_cmdline.c$(DependSuffix) -MM ../../cmdline.c

$(IntermediateDirectory)/up_up_cmdline.c$(PreprocessSuffix): ../../cmdline.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_cmdline.c$(PreprocessSuffix) ../../cmdline.c

$(IntermediateDirectory)/up_up_orgfixup.c$(ObjectSuffix): ../../orgfixup.c $(IntermediateDirectory)/up_up_orgfixup.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/orgfixup.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_orgfixup.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_orgfixup.c$(DependSuffix): ../../orgfixup.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_orgfixup.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_orgfixup.c$(DependSuffix) -MM ../../orgfixup.c

$(IntermediateDirectory)/up_up_orgfixup.c$(PreprocessSuffix): ../../orgfixup.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_orgfixup.c$(PreprocessSuffix) ../../orgfixup.c

$(IntermediateDirectory)/up_up_bin.c$(ObjectSuffix): ../../bin.c $(IntermediateDirectory)/up_up_bin.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/bin.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_bin.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_bin.c$(DependSuffix): ../../bin.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_bin.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_bin.c$(DependSuffix) -MM ../../bin.c

$(IntermediateDirectory)/up_up_bin.c$(PreprocessSuffix): ../../bin.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_bin.c$(PreprocessSuffix) ../../bin.c

$(IntermediateDirectory)/up_up_dbgcv.c$(ObjectSuffix): ../../dbgcv.c $(IntermediateDirectory)/up_up_dbgcv.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/dbgcv.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_dbgcv.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_dbgcv.c$(DependSuffix): ../../dbgcv.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_dbgcv.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_dbgcv.c$(DependSuffix) -MM ../../dbgcv.c

$(IntermediateDirectory)/up_up_dbgcv.c$(PreprocessSuffix): ../../dbgcv.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_dbgcv.c$(PreprocessSuffix) ../../dbgcv.c

$(IntermediateDirectory)/up_up_preproc.c$(ObjectSuffix): ../../preproc.c $(IntermediateDirectory)/up_up_preproc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/preproc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_preproc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_preproc.c$(DependSuffix): ../../preproc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_preproc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_preproc.c$(DependSuffix) -MM ../../preproc.c

$(IntermediateDirectory)/up_up_preproc.c$(PreprocessSuffix): ../../preproc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_preproc.c$(PreprocessSuffix) ../../preproc.c

$(IntermediateDirectory)/up_up_option.c$(ObjectSuffix): ../../option.c $(IntermediateDirectory)/up_up_option.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/option.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_option.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_option.c$(DependSuffix): ../../option.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_option.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_option.c$(DependSuffix) -MM ../../option.c

$(IntermediateDirectory)/up_up_option.c$(PreprocessSuffix): ../../option.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_option.c$(PreprocessSuffix) ../../option.c

$(IntermediateDirectory)/up_up_context.c$(ObjectSuffix): ../../context.c $(IntermediateDirectory)/up_up_context.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/context.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_context.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_context.c$(DependSuffix): ../../context.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_context.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_context.c$(DependSuffix) -MM ../../context.c

$(IntermediateDirectory)/up_up_context.c$(PreprocessSuffix): ../../context.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_context.c$(PreprocessSuffix) ../../context.c

$(IntermediateDirectory)/up_up_symbols.c$(ObjectSuffix): ../../symbols.c $(IntermediateDirectory)/up_up_symbols.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/symbols.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_symbols.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_symbols.c$(DependSuffix): ../../symbols.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_symbols.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_symbols.c$(DependSuffix) -MM ../../symbols.c

$(IntermediateDirectory)/up_up_symbols.c$(PreprocessSuffix): ../../symbols.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_symbols.c$(PreprocessSuffix) ../../symbols.c

$(IntermediateDirectory)/up_up_memalloc.c$(ObjectSuffix): ../../memalloc.c $(IntermediateDirectory)/up_up_memalloc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/memalloc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_memalloc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_memalloc.c$(DependSuffix): ../../memalloc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_memalloc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_memalloc.c$(DependSuffix) -MM ../../memalloc.c

$(IntermediateDirectory)/up_up_memalloc.c$(PreprocessSuffix): ../../memalloc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_memalloc.c$(PreprocessSuffix) ../../memalloc.c

$(IntermediateDirectory)/up_up_string.c$(ObjectSuffix): ../../string.c $(IntermediateDirectory)/up_up_string.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/string.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_string.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_string.c$(DependSuffix): ../../string.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_string.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_string.c$(DependSuffix) -MM ../../string.c

$(IntermediateDirectory)/up_up_string.c$(PreprocessSuffix): ../../string.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_string.c$(PreprocessSuffix) ../../string.c

$(IntermediateDirectory)/up_up_segment.c$(ObjectSuffix): ../../segment.c $(IntermediateDirectory)/up_up_segment.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/segment.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_segment.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_segment.c$(DependSuffix): ../../segment.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_segment.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_segment.c$(DependSuffix) -MM ../../segment.c

$(IntermediateDirectory)/up_up_segment.c$(PreprocessSuffix): ../../segment.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_segment.c$(PreprocessSuffix) ../../segment.c

$(IntermediateDirectory)/up_up_msgtext.c$(ObjectSuffix): ../../msgtext.c $(IntermediateDirectory)/up_up_msgtext.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/Libraries/eXOAMP/UASM/msgtext.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_msgtext.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_msgtext.c$(DependSuffix): ../../msgtext.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_msgtext.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_msgtext.c$(DependSuffix) -MM ../../msgtext.c

$(IntermediateDirectory)/up_up_msgtext.c$(PreprocessSuffix): ../../msgtext.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_msgtext.c$(PreprocessSuffix) ../../msgtext.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


