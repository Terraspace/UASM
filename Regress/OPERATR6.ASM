
;--- forward references in argument of TYPE/SIZEOF/LENGTHOF/SIZE/LENGTH
;--- was a problem if the operator's result was used as divisor
;--- fixed in v2.10

    .386
    .model flat, stdcall

    .DATA

E1 = size_xarray / type xarray
E1 = size_xarray / sizeof xarray
E1 = size_xarray / lengthof xarray
E1 = size_xarray / size xarray
E1 = size_xarray / length xarray   ;actually, LENGTH operator was ok

xarray label word
    dw 1,2
size_xarray equ $ - xarray

    END
