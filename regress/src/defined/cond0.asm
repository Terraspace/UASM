IFDEF _MSC_KER
ECHO defined
ELSE
ECHO not defined
ENDIF

defined macro x
    
ifdef x
      
exitm <-1>
    
else
      
exitm <0>
    
endif
  
endm

IF defined(_MSC_KER) and (_MSC_KER ge 1020)
.ERR <MSCKER defined and ge than 1020>

ENDIF



; if _MSC_KER is not defined, the block should skip ..

; if _MSC_KER is less than 1020 it should skip ..


.code

end
