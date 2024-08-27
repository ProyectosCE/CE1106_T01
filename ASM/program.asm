[bits 16]

;Seccion de datos predefinidos
section .data
    ;Mensaje general de pruebas
    default_ms db 'Otras cosas', 0x0D, 0x0A, '$' 

    ;Mensaje de bienvenida
    initial_msg db 'Bienvenido a GeometryTEC', 0x0A, '$'
    
    ;Para pregunta se seleccion de figura
    askn_msg db 0x0A, 'Escoge una figura:', '$' 
    square db 0x0A, '1. Cuadrado', '$'  
    circle db 0x0A, '2. Circulo', '$'  
    triangle db 0x0A, '3. Triangulo','$'  
    diamond db 0x0A, '4. Diamante', '$'  
    pentagon db 0x0A, '5. Pentagono', '$'  
    hexagon db 0x0A, '6. Hexagono', '$'  
    trapeze db 0x0A, '7. Trapecio','$'  
    parallelogram db 0x0A, '8. Paralelogramo',0x0A,'$' 

    ;Pregunta de lados
    ask_lado db 0x0A, 'Cuanto mide el lado?',0x0A, '$' 
    
    ;Respuestas de perimetro y área
    result_peri db 0x0A, 'El perametro es: ', '$'
    result_area db 0x0A, 'El area es: ', '$'

    ; Mensaje de para consultar si quiere hacer otro calculo
    repetir_msg db 0x0A, 'Por favor presione:', '$'
    repsi db 0x0A,'1. Hacer otra operacion','$' 
    repno db 0x0A,'2. Salir',0x0A,'$'

    ;Mensaje de agradecimiento
    salida_msg db 0x0A, 'Gracias por usar GeometryTEC:','$'  ; Mensaje de salida

;Seccion de buffer usados en todo el programa para el almacenamiento de valores y datos
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

    ;Buffer numerico de 3 bytes multiproposito
    buftemp resb 3

    ;Buffers para respuestas, de 5 bytes
    ; 4 bytes max para la parte entera
    ; 1 byte para la parte decimal
    peri_r resb 5 
    area_r resb 5
    temp_r resb 5
    
; Seccion de texto propia de asm 8086
section .text
    ;ORG 100h facilita al compilador saber que el codigo es ASM 8086 para DOS
    org 100h
    ; Declaración global del punto de entrada
    global _start 

_start:
    ; Salta a la sección que imprime el mensaje de bienvenida
    jmp initial_case  

initial_case:
    ; Imprime el mensaje inicial de bienvenida
    mov bx, initial_msg
    call imp_msg
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
    cmp al, '4'
    je case_diamond
    cmp al, '5'
    je case_pentagon

    ; PRUEBA
    cmp al, '9'
    je case_suma

    ;si el digito ingresado no es válido vuelve a preguntar que figura quiere calcular
    jmp case_show_figures 


default_case:
    ; Mensaje por defecto en caso de entrada inválida
    mov bx, default_ms
    call imp_msg
    ; Salta a imprimir el listado de figuras
    jmp case_show_figures

repetir:
    ; Mensaje pora preguntar si quiere repetir o no
    mov bx, repetir_msg
    call imp_msg
    
    mov bx, repsi
    call imp_msg

    mov bx, repno
    call imp_msg
    
    ;comprueba la entrada del usuario (1 o 2)
    ;1 para continuar con otro calculo
    ;2 para salir
    mov ah, 01h  
    int 21h 
    cmp al, '1'  
    je case_show_figures  
    cmp al, '2'  
    je done 

    ; en caso de una entrada diferente se vuelve a preguntar si desea repetir
    jmp repetir

reinciar_buf:
    ; Este metodo se llama para limpiar todo los buffers disponibles en una sola llamada
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
    
    ;retorno
    ret

clear_loop:
    ; Entradas: Recibe en si el valor de la dirección del buffer que se desea limpiar, además en CX recibe el tamaño del buffer
    ; Salidas: Limpia el buffer indicado y coloca 0 en todos sus registros
    ; Restricciones: Se necesita especificar tanto la dirección del buffer como su tamaño. Puede limpiar buffers de tamaño n
    
    ; Escribir 0 en la posición actual del buffer
    xor al, al
    mov [si], al            
    
    ; Incrementa si para avanzar al siguiente byte en el buffer
    inc si    
    ; Se repite hasta que CX sea 0              
    loop clear_loop         
    ; Retorna
    ret


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
%include 'figuras/diamond.inc'
%include 'figuras/pentagon.inc'
%include 'pruebasum.inc'