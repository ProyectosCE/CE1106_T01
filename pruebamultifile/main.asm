section .data
prompt db 'Ingrese texto: $'
newline db 0xA, 0xD, '$'

section .bss
global input
input resb 64 ; buffer para la entrada del usuario

section .text
extern imprime  ; Declarar la función imprime en print.asm
global _start  ; Punto de entrada global

_start:
    ; Mostrar el mensaje de entrada
    mov ah, 9
    mov dx, prompt
    int 0x21

    ; Obtener la entrada del usuario
    mov ah, 0x0A
    mov dx, input
    int 0x21

    ; Llamar a la función 'imprime'
    call imprime

    ; Terminar el programa
    mov ah, 4Ch
    int 21h
