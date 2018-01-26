;
; SHA
;
    .x64
    .model flat
    .code

    option evex:1

	sha256msg1 xmm1,xmm2
    sha256msg2 xmm1,xmm2
    sha256msg1 xmm1,[rcx]
    sha256msg2 xmm1,[rcx]
    sha1rnds4 xmm1,xmm2,12
    sha1rnds4 xmm1,[rcx],12
    sha1nexte xmm1,xmm2
    sha1nexte xmm1,[rcx]
    sha1msg1 xmm1,xmm2
    sha1msg1 xmm1,[rcx]
    sha1msg2 xmm1,xmm2
    sha1msg2 xmm1,[rcx]
    sha256rnds2 xmm1,xmm2
    sha256rnds2 xmm1,[rcx]

    end
