; Issue #236: ALIGN above the segment alignment without a FLAT group.
.model tiny
.code
align 0x80
start_label:
 db 0a5h
align 0x80
aligned_label:
.errnz aligned_label - start_label - 80h
 db 05ah
end
