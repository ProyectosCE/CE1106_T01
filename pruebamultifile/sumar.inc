[BITS 16]

section .text

sumar_numeros:
    ; Suma los valores en AL y BL y retorna el resultado en AL
    add al, bl
    ret
