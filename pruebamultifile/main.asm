[BITS 16]

section .bss
    num1 resb 1   ; Reserva 1 byte para el primer número
    num2 resb 1   ; Reserva 1 byte para el segundo número
    resultado resb 1 ; Reserva 1 byte para el resultado

section .data
    msg_num1 db "Ingrese el primer numero (0-9): $"
    msg_num2 db "Ingrese el segundo numero (0-9): $"
    msg_result db "La suma es: $"

section .text
    org 0x100  ; Configurar el punto de entrada para formato COM

    extern sumar_numeros  ; Declarar la función externa para sumar

start:
    ; Solicitar el primer número
    mov ah, 09h
    mov dx, msg_num1
    int 21h

    call leer_digito  ; Leer el primer número
    mov [num1], al    ; Guardar el número ingresado en num1

    ; Solicitar el segundo número
    mov ah, 09h
    mov dx, msg_num2
    int 21h

    call leer_digito  ; Leer el segundo número
    mov [num2], al    ; Guardar el número ingresado en num2

    ; Llamar al procedimiento de suma
    mov al, [num1]
    mov bl, [num2]
    call sumar_numeros
    mov [resultado], al  ; Guardar el resultado en "resultado"

    ; Imprimir el resultado de la suma
    mov ah, 09h
    mov dx, msg_result
    int 21h

    call imprimir_digito  ; Imprimir el valor de la suma

    ; Salir del programa
    mov ah, 4Ch
    int 21h

leer_digito:
    ; Leer un dígito del teclado
    mov ah, 01h
    int 21h             ; Leer un carácter
    sub al, '0'         ; Convertir el carácter en su valor numérico
    ret

imprimir_digito:
    ; Imprimir el valor en AL como dígito
    add al, '0'         ; Convertir el número a su valor ASCII
    mov ah, 02h
    mov dl, al
    int 21h
    ret

%include "sumar.inc"
