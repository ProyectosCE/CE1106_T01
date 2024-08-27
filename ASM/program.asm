org 100h

section .data
    default_ms db 'Otras cosas', 0x0D, 0x0A, '$'  ; Mensaje por defecto
    initial_msg db 'Bienvenido a GeometryTEC', 0x0D, 0x0A, '$'  ; Mensaje inicial que pregunta si se desea iniciar
    askn_msg db 0x0A, 'Escoge una figura:', 0x0D, 0x0A, '$'  ; Mensaje que pide al usuario que escoja una figura

    square db 0x0A, '1. Cuadrado', 0x0D, 0x0A, '$'  ; Opción para cuadrado
    circle db '2. Circulo', 0x0D, 0x0A, '$'  ; Opción para círculo
    triangle db '3. Triangulo', 0x0D, 0x0A, '$'  ; Opción para triángulo
    diamond db '4. Diamante', 0x0D, 0x0A, '$'  ; Opción para diamante
    pentagon db '5. Pentagono', 0x0D, 0x0A, '$'  ; Opción para pentágono
    hexagon db '6. Hexagono', 0x0D, 0x0A, '$'  ; Opción para hexágono
    trapeze db '7. Trapecio', 0x0D, 0x0A, '$'  ; Opción para trapecio
    parallelogram db '8. Paralelogramo', 0x0D, 0x0A, '$'  ; Opción para paralelogramo

    ask_lado db 0x0A, 'Cuanto mide el lado?', 0x0D, 0x0A, '$'  ; Pregunta cuanto mide el lado
    result_peri db 0x0A, 'El perametro es: ', '$'  ; Mensaje para el resultado del perímetro
    result_area db 0x0A, 'El área es: ', '$'  ; Mensaje para el resultado del área

    repetir_msg db 0x0A, 'Por favor presione:', 0x0A, '$'  ; Mensaje que pide al usuario repetir o no
    repsi db '1. Hacer otra operación', 0x0D, 0x0A, '$'  ; Opción para repetir la operación
    repno db '2. Salir', 0x0D, 0x0A, '$'  ; Opción para salir

    salida_msg db 0x0A, 'Gracias por usar GeometryTEC:', 0x0D, 0x0A, '$'  ; Mensaje de salida

section .bss   
    ;buffer general de entrada de texto (reutilizable)
    buffer_text resb 10 ; maxima entrada del input (7 máx y 2 bytes de control)
    ;buffer para datos numericos (hasta 3 para las figuras que lo ocupan)
    dato_01 resb 3 ;dato Numerico para input 1
    dato_02 resb 3 ;dato Numerico para input 2
    dato_03 resb 3 ;dato Numerico para input 3
    
    ;Buffer a usar en operaciones matematicas (guardar direcciones de los buffers)
    operando1 resb 2
    operando2 resb 2
    respuesta resb 2

    buftemp resb 3

    ;Buffers para respuestas, de 5 bytes
    ; 4 bytes max para la parte entera
    ; 1 byte para la parte decimal
    peri_r resb 5 ;para cualquier figura maximo FFFF FFFF
    area_r resb 5 ;para cualquier valor, maximo el circulo 0F FFFF FFFF FFFF
    temp_r resb 5
    
section .text
    global _start  ; Declaración global del punto de entrada

_start:
    jmp initial_case  ; Salta a la sección que pregunta si desea iniciar

initial_case:
    ; Imprime el mensaje inicial preguntando si quiere iniciar
    mov ah, 09h  
    lea dx, [initial_msg]  
    int 21h  
    jmp case_show_figures

case_show_figures:
    call reinciar_buf
    ; Pregunta qué figura quiere el usuario
    lea dx, [askn_msg]  
    mov ah, 09h  
    int 21h 
    ; Imprime las opciones de figuras disponibles
    lea dx, [square]
    int 21h 

    lea dx, [circle]  
    int 21h 

    lea dx, [triangle]  
    int 21h  

    lea dx, [diamond]  
    int 21h  

    lea dx, [pentagon] 
    int 21h  

    lea dx, [hexagon]  
    int 21h  

    lea dx, [trapeze]  
    int 21h  

    lea dx, [parallelogram]  
    int 21h  

    ; Leer elección del usuario (1-8)
    mov ah, 01h  
    int 21h 
    cmp al, '1'  
    je case_square  
    cmp al, '2'  
    je case_circle 
    cmp al, '5'  
    je case_pentagon 
    jmp case_show_figures 


default_case:
    ; Mensaje por defecto en caso de entrada inválida
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [default_ms]  ; Carga la dirección del mensaje por defecto en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena
    jmp initial_case  ; Salta a terminar el programa

repetir:
    ; Mensaje por defecto en caso de entrada inválida
    lea dx, [repetir_msg]  
    mov ah, 09h  
    int 21h 
    ; Imprime las opciones de figuras disponibles
    lea dx, [repsi]
    int 21h 

    lea dx, [repno]  
    int 21h 
    
    mov ah, 01h  
    int 21h 
    cmp al, '1'  
    je case_show_figures  
    cmp al, '2'  
    je done 
    jmp repetir

reinciar_buf:
    mov si, buffer_text+1
    mov cx, 9
    call clear_loop
    
    mov si, dato_01
    mov cx, 3
    call clear_loop
    
    mov si, dato_02
    mov cx, 3
    call clear_loop

    mov si, dato_03
    mov cx, 3
    call clear_loop
    
    mov si, buftemp
    mov cx, 3
    call clear_loop

    mov si, peri_r
    mov cx, 5
    call clear_loop

    mov si, area_r
    mov cx, 5
    call clear_loop

    mov si, temp_r
    mov cx, 5
    call clear_loop

    mov si, operando1
    mov cx, 2
    call clear_loop
    mov si, operando2
    mov cx, 2
    call clear_loop
    mov si, respuesta
    mov cx, 2
    call clear_loop

    ret

clear_loop:
    xor al, al
    mov [si], al            ; Escribir 0 en la posición actual del buffer
    inc si                  ; Avanzar al siguiente byte en el buffer
    loop clear_loop         ; Repetir hasta que CX sea 0

    ret                     ; Retornar de la subrutina


done:
    lea dx, [salida_msg]  
    mov ah, 09h  
    int 21h 
    mov ah, 4Ch  ; Función de MS-DOS para terminar el programa
    int 21h  ; Interrupción de MS-DOS para salir


%include 'io.inc'
%include 'calc.inc'
%include 'figuras/square.inc'
%include 'figuras/circle.inc'
%include 'figuras/pentagon.inc'