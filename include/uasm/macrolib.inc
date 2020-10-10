
; / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
; / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
; / /                                                                               / /
; / /                Copyright 2020 (c) UASM macro assembly library                 / /
; / /                                                                               / /
; / /    Licensed under the Apache License, Version 2.0 (the "License");            / /
; / /    you may not use this file except in compliance with the License.           / /
; / /    You may obtain a copy of the License at                                    / /
; / /                                                                               / /
; / /        http://www.apache.org/licenses/LICENSE-2.0                             / /
; / /                                                                               / /
; / /    Unless required by applicable law or agreed to in writing, software        / /
; / /    distributed under the License is distributed on an "AS IS" BASIS,          / /
; / /    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   / /
; / /    See the License for the specific language governing permissions and        / /
; / /    limitations under the License.                                             / /
; / /                                                                               / /
; / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
; / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /

    IFNDEF MACROLIB_INC
    MACROLIB_INC EQU 1

    IFDEF WITHMACROLIB
    ;;Uncomment to remove from inclusion
    ;DEFINES_INC EQU 1
    ;TYPES_INC EQU 1
    ;LIMITS_INC EQU 1
    ;CPUBITS_INC EQU 1
    ;MACROS_INC EQU 1
    ;PARAMS_INC EQU 1

    INCLUDE defines.inc
    INCLUDE types.inc
    INCLUDE limits.inc
    INCLUDE cpubits.inc
    INCLUDE macros.inc
    INCLUDE params.inc

    ENDIF ;WITHMACROLIB

    ENDIF    ; MACROLIB_INC
