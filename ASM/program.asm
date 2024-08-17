org 100h

section .data
    default_ms db 'Otras cosas', 0x09,'',0x0D, 0x0A, '$'  ; Mensaje por defecto
    initial_msg db 'Quieres iniciar [Y/N]',0x09,'', 0x0D, 0x0A, '$'  ; Mensaje inicial que pregunta si se desea iniciar
    askn_msg db 0x0A,'Escoge una figura:',0x09,'', 0x0D, 0x0A, '$'  ; Mensaje que pide al usuario que escoja una figura
    square db 0x0A,'1. Square',0x09,'', 0x0D, 0x0A, '$'  ; Opción para cuadrado
    circle db '2. Circle',0x09,'', 0x0D, 0x0A, '$'  ; Opción para círculo
    triangle db '3. Triangle',0x09,'', 0x0D, 0x0A, '$'  ; Opción para triángulo
    diamond db '4. Diamond',0x09,'', 0x0D, 0x0A, '$'  ; Opción para diamante
    pentagon db '5. Pentagon',0x09,'', 0x0D, 0x0A, '$'  ; Opción para pentágono
    hexagon db '6. Hexagon',0x09,'', 0x0D, 0x0A, '$'  ; Opción para hexágono
    trapeze db '7. Trapeze',0x09,'', 0x0D, 0x0A, '$'  ; Opción para trapecio
    parallelogram db '8. Parallelogram',0x09,'', 0x0D, 0x0A, '$'  ; Opción para paralelogramo
    square_msg db 0x0A,'Cuando mide el lado?',0x09,'', 0x0D, 0x0A, '$'  ; Pregunta para el cuadrado

    ;aqui va la cantidad de lados de cada figura lo necesario para calcular el perimetro

    square_sides dw 4
    triangle_sides dw 3
    diamond_sides dw 4
    pentagon_sides dw 5
    hexagon_sides dw 6
    


section .bss
    input_buffer resb 2  ; Reserva 2 bytes para la primera entrada del usuario
    second_input resb 2  ; Reserva 2 bytes para la segunda entrada, donde se elige la figura
    buffer_lado_square resb 100 ; maxima entrada del input


section .text
    global _start  ; Declaración global del punto de entrada

_start:
    jmp initial_case  ; Salta a la sección que pregunta si desea iniciar

initial_case:
    ; Imprime el mensaje inicial preguntando si quiere iniciar
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [initial_msg]  ; Carga la dirección del mensaje inicial en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    ; Leer respuesta del usuario (Y/N)
    mov ah, 01h  ; Función de MS-DOS para leer un solo carácter del teclado
    int 21h  ; Interrupción de MS-DOS para leer entrada
    cmp al, 'Y'  ; Compara la entrada con 'Y' (mayúscula)
    je case_show_figures  ; Si es 'Y', salta a mostrar las figuras
    cmp al, 'N'  ; Compara la entrada con 'N' (mayúscula)
    je done  ; Si es 'N', termina el programa
    jmp default_case  ; Si no es ni 'Y' ni 'N', salta al caso por defecto

case_show_figures:
    ; Imprime las opciones de figuras disponibles
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [square]  ; Carga la dirección del mensaje de cuadrado en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    lea dx, [circle]  ; Carga la dirección del mensaje de círculo en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    lea dx, [triangle]  ; Carga la dirección del mensaje de triángulo en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    lea dx, [diamond]  ; Carga la dirección del mensaje de diamante en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    lea dx, [pentagon]  ; Carga la dirección del mensaje de pentágono en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    lea dx, [hexagon]  ; Carga la dirección del mensaje de hexágono en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    lea dx, [trapeze]  ; Carga la dirección del mensaje de trapecio en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    lea dx, [parallelogram]  ; Carga la dirección del mensaje de paralelogramo en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    ; Pregunta qué figura quiere el usuario
    lea dx, [askn_msg]  ; Carga la dirección del mensaje que pide seleccionar figura en dx
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    ; Leer elección del usuario (1-8)
    mov ah, 01h  ; Función de MS-DOS para leer un solo carácter del teclado
    int 21h  ; Interrupción de MS-DOS para leer entrada
    cmp al, '1'  ; Compara la entrada con '1'
    je case_square  ; Si es '1', salta al caso del cuadrado
    cmp al, '2'  ; Compara la entrada con '2'
    je case_circle  ; Si es '2', salta al caso del círculo
    jmp done  ; Si no es ninguna de las opciones válidas, termina el programa

case_square:
    ; Pregunta sobre el lado del cuadrado
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [square_msg]  ; Carga la dirección del mensaje de consulta del lado del cuadrado en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena
    
    mov byte [buffer_lado_square],100
    mov byte [buffer_lado_square+1],0

    ; Leer el lado del cuadrado (suponiendo una entrada numérica)
    mov ah, 0Ah  ; Función de MS-DOS para leer cadena
    lea dx, [buffer_lado_square]  ; Carga la dirección del buffer donde se almacenará la entrada del lado del cuadrado
    int 21h  ; Interrupción de MS-DOS para leer cadena

    jmp input_to_ax


case_circle:
    ; Imprime mensaje de círculo y sale
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [circle]  ; Carga la dirección del mensaje de círculo en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena
    jmp done  ; Salta a terminar el programa

default_case:
    ; Mensaje por defecto en caso de entrada inválida
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [default_ms]  ; Carga la dirección del mensaje por defecto en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena
    jmp initial_case  ; Salta a terminar el programa

done:
    ; Termina el programa y vuelve a MS-DOS
    mov ah, 4Ch  ; Función de MS-DOS para terminar el programa
    int 21h  ; Interrupción de MS-DOS para salir

input_to_ax: ;basicamente vamo a mover la entrada del buffer al registro ax para imprimirlo
    movzx cx, byte [buffer_lado_square+1] ;aqui va a tomar el bite que contiene el tamaño del input
    lea si, [buffer_lado_square+2] ;aqui vamos a apuntar al primer caracter del input 
    xor ax, ax ;limpiamos ax donde vamos almacenar el numero
    jmp convertir_input

convertir_input: ;aqui vamos a convertir los caracteres
    movzx dx, byte [si] ;cargamos el contenido al que esta apuntando si
    sub dx, '0' ; con esto se convierte ASCII a valor numerico
    mov bx, 10
    mul bx
    add ax, dx

    inc si
    loop convertir_input ;se va a repetir hasta que cx sea del mismo tamaño que el input

    jmp multiplicar_input
    

multiplicar_input: ;toma el input en el ax y lo multiplica por un numero
    mov cx, 4 ;multiplica por la cantidad de lados
    mul cx 
    

    


; conver_ax_para_mostrar ;aqui tomamos el valor de ax ya multiplicado y lo convertimos para ensenar
;     lea di, [buffer_lado_square+2] ;se apunta a la cadena
;     mov cx, 10 ;usamos base 10
;     xor dx,dx ;limpiamos


; conversion_loop:
;     xor dx, dx
;     div cx ;dividimos ax
;     add dl, '0'  ; con esto se convierte ASCII a valor numerico
;     dec di ;se decrementa el puntero
;     mov [di],dl ;se guarda el caracter
;     cmp ax, 0
;     jne conversion_loop

;     mov byte [di-1], '$' ;marca el final de la cadena
;     mov ah, 09h
;     lea dx, [di-1]
;     int 21h

;     jmp done