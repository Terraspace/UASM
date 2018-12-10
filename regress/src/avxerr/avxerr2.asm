
option evex:1
option flat:1

.code

use64

vblendmpd zmm26{k6}, QWORD PTR [r11+8], zmm30
vbroadcastsd zmm23, [r11+8]{1to8}
;reported by GWoltman 27th Nov, 2018.
