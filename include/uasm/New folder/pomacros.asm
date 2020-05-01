; ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
;                         POASM Support macros
; ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл


    ; **************************
    ; memory allocation macros *
    ; **************************

    comment * --------------------------------------------------    
            Two macros for allocating and freeing OLE memory.
            stralloc returns the handle/address of the string
            memory in eax. alloc$ acts in the same way but is
            used in the function position. strfree uses the
            handle to free memory after use.
    
            NOTE that you must use the following INCLUDE &
            LIB files with these two macros.
    
            include \MASM32\include\oleaut32.inc
            includelib \MASM32\LIB\oleaut32.lib
            -------------------------------------------------- *

      alloc$ MACRO ln
        invoke SysAllocStringByteLen,0,ln
        mov BYTE PTR [eax], 0
        EXITM <eax>
      ENDM

      free$ MACRO strhandle
        invoke SysFreeString,strhandle
      ENDM

      stralloc MACRO ln
        invoke SysAllocStringByteLen,0,ln
      ENDM

      strfree MACRO strhandle
        invoke SysFreeString,strhandle
      ENDM

comment * ------------------------------------------------
    The following 2 macros are for general purpose memory
    allocation where fine granularity in memory is required
    or where the memory attribute "execute" is useful.
    ------------------------------------------------------ *

      alloc MACRO bytecount
        invoke GlobalAlloc,GMEM_FIXED or GMEM_ZEROINIT,bytecount
        EXITM <eax>
      ENDM

      free MACRO hmemory
        invoke GlobalFree,hmemory
      ENDM

comment * ---------------------------------------------------------
        Heap allocation and deallocation macros. On later versions
        of Windows HeapAlloc() appears to be faster on small
        allocations than GlobalAlloc() using the GMEM_FIXED flag.
        --------------------------------------------------------- *

      halloc MACRO bytecount
        EXITM <rv(HeapAlloc,rv(GetProcessHeap),0,bytecount)>
      ENDM

      hsize MACRO hmem
        invoke HeapSize,rv(GetProcessHeap),0,hmem
        EXITM <eax>
      ENDM

      hfree MACRO memory
        invoke HeapFree,rv(GetProcessHeap),0,memory
      ENDM

    ; ************************************************************
    ;                       File IO macros                       *
    ; NOTE: With the address returned by InputFile that contains *
    ; the data in the file, it must be deallocated using the API *
    ; function GlobalFree().                                     *
    ; EXAMPLE: invoke GlobalFree,pMem                            *
    ; ************************************************************

      InputFile MACRO lpFile
      ;; ----------------------------------------------------------
      ;; The untidy data? names are to avoid duplication in normal
      ;; code. The two values are reused by each call to the macro
      ;; ----------------------------------------------------------
        IFNDEF ipf@@flag            ;; if the flag is not defined
          .data?
            ipf@__@mem@__@Ptr dd ?  ;; write 2 DWORD variables to
            ipf@__file__@len dd ?   ;; the uninitialised data section
          .code
          ipf@@flag equ <1>         ;; define the flag
        ENDIF
        invoke read_disk_file,reparg(lpFile),
               ADDR ipf@__@mem@__@Ptr,
               ADDR ipf@__file__@len
        mov ecx, ipf@__file__@len   ;; file length returned in ECX
        mov eax, ipf@__@mem@__@Ptr  ;; address of memory returned in EAX
        EXITM <eax>
      ENDM

      OutputFile MACRO lpFile,lpMem,lof
        invoke write_disk_file,reparg(lpFile),lpMem,lof
        EXITM <eax>
      ENDM


      len MACRO lpString
        invoke szLen,reparg(lpString)
        EXITM <eax>
      ENDM

      ucase$ MACRO lpString
        invoke szUpper,reparg(lpString)
        EXITM <eax>
      ENDM

      lcase$ MACRO lpString
        invoke szLower,reparg(lpString)
        EXITM <eax>
      ENDM

      left$ MACRO lpString,slen
        invoke szLeft,reparg(lpString),reparg(lpString),slen
        EXITM <eax>
      ENDM

      right$ MACRO lpString,slen
        invoke szRight,reparg(lpString),reparg(lpString),slen
        EXITM <eax>
      ENDM

      rev$ MACRO lpString
        invoke szRev,reparg(lpString),reparg(lpString)
        EXITM <eax>
      ENDM

      ltrim$ MACRO lpString
        invoke szLtrim,reparg(lpString),reparg(lpString)
        mov eax, ecx
        EXITM <eax>
      ENDM

      rtrim$ MACRO lpString
        invoke szRtrim,reparg(lpString),reparg(lpString)
        mov eax, ecx
        EXITM <eax>
      ENDM

      trim$ MACRO lpString
        invoke szTrim,reparg(lpString)
        mov eax, ecx
        EXITM <eax>
      ENDM

      remove$ MACRO src,substrx
        invoke szRemove,reparg(src),reparg(src),reparg(substrx)
        EXITM <eax>
      ENDM


  ; **************
  ; File IO Macros
  ; **************
  ; ---------------------------------------------------------------------
  ; create a new file with read / write access and return the file handle
  ; ---------------------------------------------------------------------
    fcreate MACRO filename
      invoke CreateFile,reparg(filename),GENERIC_READ or GENERIC_WRITE,
                        NULL,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL
      EXITM <eax>       ;; return file handle
    ENDM

  ; ------------------
  ; delete a disk file
  ; ------------------
    fdelete MACRO filename
      invoke DeleteFile,reparg(filename)
      EXITM <eax>
    ENDM

  ; ------------------------------
  ; flush open file buffer to disk
  ; ------------------------------
    fflush MACRO hfile
      invoke FlushFileBuffers,hfile
    ENDM

  ; -------------------------------------------------------------------------
  ; open an existing file with read / write access and return the file handle
  ; -------------------------------------------------------------------------
    fopen MACRO filename
      invoke CreateFile,reparg(filename),GENERIC_READ or GENERIC_WRITE,
                        NULL,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL
      EXITM <eax>       ;; return file handle
    ENDM

  ; ------------------
  ; close an open file
  ; ------------------
    fclose MACRO arg:REQ
      invoke CloseHandle,arg
    ENDM

  ; ------------------------------------------------
  ; read data from an open file into a memory buffer
  ; ------------------------------------------------
    fread MACRO hFile,buffer,bcnt
      LOCAL var
      .data?
        var dd ?
      .code
      invoke ReadFile,hFile,buffer,bcnt,ADDR var,NULL
      mov eax, var
      EXITM <eax>       ;; return bytes read
    ENDM

  ; ----------------------------------------
  ; write data from a buffer to an open file
  ; ----------------------------------------
    fwrite MACRO hFile,buffer,bcnt
      LOCAL var
      .data?
        var dd ?
      .code
      invoke WriteFile,hFile,buffer,bcnt,ADDR var,NULL
      mov eax, var
      EXITM <eax>       ;; return bytes written
    ENDM

  ; ----------------------------------------------------
  ; write a line of zero terminated text to an open file
  ; ----------------------------------------------------
    fprint MACRO hFile:REQ,text:VARARG  ;; zero terminated text
      LOCAL var
      LOCAL pst
      .data?
        var dd ?
        pst dd ?
      .code
      mov pst, repargv(text)
      invoke WriteFile,hFile,pst,len(pst),ADDR var,NULL
      invoke WriteFile,hFile,chr$(13,10),2,ADDR var,NULL
    ENDM

  ; ---------------------------------
  ; write zero terminated text with C
  ; style formatting to an open file.
  ; ---------------------------------
    fprintc MACRO hFile:REQ,text:VARARG  ;; zero terminated text
      LOCAL var
      LOCAL pst
      .data?
        var dd ?
        pst dd ?
      .code
      mov pst, cfm$(text)
      invoke WriteFile,hFile,pst,len(pst),ADDR var,NULL
    ENDM

  ; ------------------------------------
  ; set the position of the file pointer
  ; ------------------------------------
    fseek MACRO hFile,distance,location
      IFIDN <location>,<BEGIN>
        var equ <FILE_BEGIN>
      ELSEIFIDN <location>,<CURRENT>
        var equ <FILE_CURRENT>
      ELSEIFIDN <location>,<END>
        var equ <FILE_END>
      ELSE
        var equ <location>
      ENDIF
      invoke SetFilePointer,hFile,distance,0,var
      EXITM <eax>               ;; return current file offset
    ENDM

  ; ------------------------------------------------
  ; set end of file at current file pointer location
  ; ------------------------------------------------
    fseteof MACRO hFile
      invoke SetEndOfFile,hFile
    ENDM

  ; -------------------------------
  ; return the size of an open file
  ; -------------------------------
    fsize MACRO hFile
      invoke GetFileSize,hFile,NULL
      EXITM <eax>
    ENDM

  ; ---------------------------------------
  ; extended formatting version writes text
  ; to the current file pointer location
  ; ---------------------------------------
    ftext MACRO hFile:REQ,args:VARARG
      push esi                              ;; preserve ESI
      mov esi, alloc(16384)                 ;; allocate 16k of buffer
      catargs ftext,esi,args                ;; write ALL args to a single string
      push eax                              ;; make 4 bytes on the stack
      invoke WriteFile,hFile,esi,len(esi),esp,NULL
      pop eax                               ;; release the 4 bytes
      free esi                              ;; free the memory buffer
      pop esi                               ;; restore ESI
    ENDM

      pth$ MACRO            ;; application path OFFSET returned
        IFNDEF pth__equate__flag
        .data?
          pth__260_BYTE__buffer db MAX_PATH dup (?)
        .code
        pth__equate__flag equ <1>
        ENDIF
        invoke GetAppPath,ADDR pth__260_BYTE__buffer
        EXITM <eax>
      ENDM

      CurDir$ MACRO
        IFNDEF cdir__equate__flag
        .data?
          cdir__260_BYTE__buffer db MAX_PATH dup (?)
        .code
        cdir__equate__flag equ <1>
        ENDIF
        invoke GetCurrentDirectory,MAX_PATH,ADDR cdir__260_BYTE__buffer
        mov eax, OFFSET cdir__260_BYTE__buffer
        EXITM <eax>
      ENDM

      SysDir$ MACRO
        IFNDEF sys__equate__flag
        .data?
          sysdir__260_BYTE__buffer db MAX_PATH dup (?)
        .code
        sys__equate__flag equ <1>
        ENDIF
        invoke GetSystemDirectory,ADDR sysdir__260_BYTE__buffer,MAX_PATH
        mov eax, OFFSET sysdir__260_BYTE__buffer
        EXITM <eax>
      ENDM

      WinDir$ MACRO
        IFNDEF wdir__equate__flag
        .data?
          windir__260_BYTE__buffer db MAX_PATH dup (?)
        .code
        wdir__equate__flag equ <1>
        ENDIF
        invoke GetWindowsDirectory,ADDR windir__260_BYTE__buffer,MAX_PATH
        mov eax, OFFSET windir__260_BYTE__buffer
        EXITM <eax>
      ENDM


  ; ******************************************
  ; DOS style directory manipulation macros  *
  ; The parameters passed to these directory *
  ; macros should be zero terminated string  *
  ; addresses.                               *
  ; ******************************************
      chdir MACRO pathname
        invoke SetCurrentDirectory,reparg(pathname)
      ENDM
      CHDIR equ <chdir>

      mkdir MACRO dirname
        invoke CreateDirectory,reparg(dirname),NULL
      ENDM
      MKDIR equ <mkdir>

      rndir MACRO oldname,newname
        invoke MoveFile,reparg(oldname),reparg(newname)
      ENDM
      RNDIR equ <rndir>

      rmdir MACRO dirname
        invoke RemoveDirectory,reparg(dirname)
      ENDM
      RMDIR equ <rmdir>

  ; --------------------------------------------------
  ; count the number of arguments in a VARARG argument
  ; --------------------------------------------------
    varargcnt MACRO args:VARARG
      LOCAL cntr
      cntr = 0
        FOR arg,<args>
          cntr = cntr + 1
        ENDM
      EXITM <cntr>
    ENDM

    cat$ MACRO pmem,args:VARARG
      LOCAL var
      LOCAL strng
        IF (OPATTR pmem) AND 8000h
          ECHO ---------------------------------------------------------
          ECHO cat$().ERROR First operand must be a valid memory address
          ECHO ---------------------------------------------------------
          .err
        ENDIF
      var = varargcnt(args)
      strng equ <szMultiCat,var,pmem>
        FOR arg,<args>
          strng CATSTR strng,<,>,reparg(arg)
        ENDM
      invoke strng
      EXITM <eax>
    ENDM

    str$ MACRO DDvalue
      LOCAL rvstring
      .data
        rvstring db 20 dup (0)
        align 4
      .code
      invoke dwtoa,DDvalue,ADDR rvstring
      EXITM <ADDR rvstring>
    ENDM

  ; -------------------------------------
  ; variation returns address in register
  ; so it can be assigned to a variable.
  ; -------------------------------------
    repargv MACRO arg            ;; ANSI version
      LOCAL nustr
      IF (OPATTR arg) AND 8000h ;; is it a "string"...?
        .data
          nustr db arg,0        ;; write arg to .DATA section
        .code
        EXITM <ADDR nustr>      ;; append name to ADDR operator
      ELSE
        mov eax, arg
        EXITM <eax>             ;; else return arg
      ENDIF
    ENDM

    reparg MACRO arg            ;; ANSI version
      LOCAL nustr
      IF (OPATTR arg) AND 8000h ;; is it a "string"...?
        .data
          nustr db arg,0        ;; write arg to .DATA section
        .code
        EXITM <ADDR nustr>      ;; append name to ADDR operator
      ELSE
        EXITM <arg>             ;; else return arg
      ENDIF
    ENDM

    repargu MACRO arg           ;; UNICODE version
      LOCAL nustr
      IF (OPATTR arg) AND 8000h ;; is it a "string"...?
        .data
          nustr dw arg,0        ;; write arg to .DATA section
        .code
        EXITM <ADDR nustr>      ;; append name to ADDR operator
      ELSE
        EXITM <arg>             ;; else return arg
      ENDIF
    ENDM

    fn MACRO FuncName:REQ,args:VARARG
      arg equ <invoke FuncName>         ;; construct invoke and function name
      FOR var,<args>                    ;; loop through all arguments
        arg CATSTR arg,<,>,reparg(var)  ;; replace quotes and append arg
      ENDM
      arg                               ;; write the invoke macro
    ENDM

    rv MACRO FuncName:REQ,args:VARARG
      arg equ <invoke FuncName>         ;; construct invoke and function name
      FOR var,<args>                    ;; loop through all arguments
        arg CATSTR arg,<,>,reparg(var)  ;; replace quotes and append arg
      ENDM
      arg                               ;; write the invoke macro
      EXITM <eax>
    ENDM

    ufn MACRO FuncName:REQ,args:VARARG
      arg equ <invoke FuncName>         ;; construct invoke and function name
      FOR var,<args>                    ;; loop through all arguments
        arg CATSTR arg,<,>,repargu(var) ;; replace quotes and append arg
      ENDM
      arg                               ;; write the invoke macro
    ENDM

    urv MACRO FuncName:REQ,args:VARARG
      arg equ <invoke FuncName>         ;; construct invoke and function name
      FOR var,<args>                    ;; loop through all arguments
        arg CATSTR arg,<,>,repargu(var) ;; replace quotes and append arg
      ENDM
      arg                               ;; write the invoke macro
      EXITM <eax>
    ENDM


      inkey MACRO user_text:VARARG
        IFDIF <user_text>,<NULL>                  ;; if user text not "NULL"
          IFNB <user_text>                        ;; if user text not blank
            print user_text                       ;; print user defined text
          ELSE                                    ;; else
            print "Press any key to continue ..." ;; print default text
          ENDIF
        ENDIF
        call wait_key
        print chr$(13,10)
      ENDM

      chr$ MACRO any_text:VARARG
        LOCAL txtname
        .data
          txtname db any_text,0
        .code
        EXITM <OFFSET txtname>
      ENDM

      ptr$ MACRO buffer
        lea eax, buffer
        mov WORD PTR [eax], 0
        EXITM <eax>
      ENDM

      exit MACRO
        invoke ExitProcess, 0
      ENDM

      cls MACRO                       ;; clear screen
        invoke ClearScreen
      ENDM

      ; print MACRO arg1
      ;   invoke StdOut,reparg(arg1)
      ; ENDM

      print MACRO quoted,therest:VARARG
        LOCAL txt
        var = 0
        invoke StdOut,reparg(quoted)
        FOR arg,<therest>
          IFNB arg
          var = 1
          ENDIF
        ENDM
        IF var eq 1
          .data
            txt db therest,0
          .code
        invoke StdOut,OFFSET txt
        ENDIF
      ENDM

      SetXY MACRO wdim,sdim
        mov eax, sdim
        sub eax, wdim
        shr eax, 1
        EXITM <eax>
      ENDM

      szText MACRO Name, Text:VARARG
        LOCAL lbl
          jmp lbl
            Name db Text,0
          lbl:
        ENDM

      m2m MACRO M1, M2
        push M2
        pop  M1
      ENDM

      return MACRO arg
        mov eax, arg
        ret
      ENDM

    ; ------------------------------------------------------------
    ; Macro for nesting function calls in other invoke statements
    ; ------------------------------------------------------------
      FUNC MACRO parameters:VARARG
        invoke parameters
        EXITM <eax>
      ENDM

    ; *******************
    ; DATA DECLARATIONS *
    ; *******************

    ; -------------------------------------
    ; initialised GLOBAL value of any type
    ; -------------------------------------
      GLOBAL MACRO variable:VARARG
      .data
      align 4
        variable
      .code
      ENDM

    ; --------------------------------
    ; initialised GLOBAL string value
    ; --------------------------------
      STRING MACRO variable:REQ,args:VARARG
      .data
        variable db args,0
        align 4
      .code
      ENDM

    ; --------------------------------
    ; initialise floating point vaues
    ; --------------------------------
      FLOAT4 MACRO name,value
        .data
        align 4
          name REAL4 value
        .code
      ENDM

      FLOAT8 MACRO name,value
        .data
        align 4
          name REAL8 value
        .code
      ENDM

      FLOAT10 MACRO name,value
        .data
        align 4
          name REAL10 value
        .code
      ENDM

    ; **********************************
    ; control flow macro by Greg Falen *
    ; **********************************

    ; ----------------------
    ; Switch/Case emulation
    ; ----------------------
    _casflg equ <0>
    _casvar equ 0
    _casstk equ 0
   
    switch macro _var:req, _reg:=<eax>
        mov _reg, _var
        _casstk catstr <_reg>, <#>, _casflg, <#>, _casstk
        _casvar equ _reg
        _casflg equ <0>         ;; 0 = emit an .if, 1 an .elseif
    endm
   
    case macro _args:vararg     ;; like Pascal: case id1. id4 .. id8, lparam, ...
                                ;; does an or (case1 || case2 || case3...)
      _cas textequ <>
      for _v, <_args>         ;; for each case
          t@ instr 1, <_v>, <..> ;; range ?
          if t@               ;; yes
              _LB substr <_v>, 1, t@-1                  ;; lbound = left portion
              _LB catstr <(>, _casvar, <!>=>, _LB, <)>  ;; (_casvar >= lbound)
              _UB substr <_v>, t@+2                     ;; ubound = right portion
              _UB catstr <(>, _casvar, <!<=>, _UB, <)>  ;; (_casvar <= ubound)
              _t catstr <(>, _LB, <&&> , _UB,<)>        ;; ((_casvar >= _lb) && (_casvar <= _ub))
          else    ;; no, it's a value (var/const)
              _t catstr <(>, _casvar, <!==>, <_v>, <)>   ;; (_casvar == value)
          endif
          _cas catstr <|| >, _t, _cas                   ;; or this case w/ others
      endm
      _cas substr _cas, 3 ;; lose the extra "|| " in front
        ifidn _casflg, <0> ;; 0 = 1'st case
            .if _cas ;; emit ".if"
        else ;; all others
            .elseif _cas ;; emit ".elseif"
        endif
        _casflg equ <1> ;; NOT 1'st
    endm
   
    default macro _default:vararg
        .else
        _default
    endm
   
    endsw macro _cmd:vararg
        ifidn _casstk, <>
            .err <Endsw w/o Switch>
        else
            t@ instr _casstk, <#>
            _casvar substr _casstk, 1, t@-1
            _casstk substr _casstk, t@+1
            t@ instr _casstk, <#>
            _casflg substr _casstk, 1, t@-1
            ifidn _casstk, <#>
                _casstk equ <>
            else
                _casstk substr _casstk, t@+1
            endif
            .endif
        endif
    endm
