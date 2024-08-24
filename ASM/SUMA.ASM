org 100h

section .bss
    lados resb 3

    
section .text
    global _start  ; Declaración global del punto de entrada

_start:
    add word [lados+1],0XAAF2
    MOV AH,[lados]
    mov AL,[lados+1]
    mov BH,[lados+2]
    int 3
