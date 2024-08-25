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
    result_peri db 0x0A, 'el perimetro es: ',0x09,'', 0x0D, 0x0A, '$' 

    ;aqui va la cantidad de lados de cada figura lo necesario para calcular el perimetro

    square_sides db 0x04
    triangle_sides db 0x03
    diamond_sides db 0x04
    pentagon_sides db 0x05
    hexagon_sides dw 0x06

    ;CONSTANTES
    pi_val db 0x013A
    raiz_tres db 0xAD
    


section .bss
    input_buffer resb 2  ; Reserva 2 bytes para la primera entrada del usuario
    second_input resb 2  ; Reserva 2 bytes para la segunda entrada, donde se elige la figura
    
    
    
    buffer_text resb 10 ; maxima entrada del input (7 máx y 2 bytes de control)
    
 
    dato_01 resb 3 ;dato Numerico para input 1
    dato_02 resb 3 ;dato Numerico para input 2
    dato_03 resb 3 ;dato Numerico para input 3
    dato_lista resw 3  ;buffer lista de las direcciones de los buffer de datos

    lados resb 2

    peri_r resb 4 ;para cualquier figura maximo FFFF FFFF
    area_r resb 7 ;para cualquier valor, maximo el circulo 0F FFFF FFFF FFFF
    
section .text
    global _start  ; Declaración global del punto de entrada

_start:
    jmp initial_case  ; Salta a la sección que pregunta si desea iniciar

initial_case:
    ;inicializar las direcciones de la lista
    mov byte [dato_01],0x0000
    mov word [dato_lista],dato_01
    mov word [dato_lista+2],dato_02
    mov word [dato_lista+2],dato_03

    ; Imprime el mensaje inicial preguntando si quiere iniciar
    mov ah, 09h  
    lea dx, [initial_msg]  
    int 21h  
    ; Leer respuesta del usuario (Y/N)
    mov ah, 01h  
    int 21h  
    cmp al, 'Y'  ; Compara la entrada con 'Y' (mayúscula)
    je case_show_figures  ; Si es 'Y', salta a mostrar las figuras
    cmp al, 'N'  ; Compara la entrada con 'N' (mayúscula)
    je done  ; Si es 'N', termina el programa
    jmp default_case  ; Si no es ni 'Y' ni 'N', salta al caso por defecto

case_show_figures:
    ; Imprime las opciones de figuras disponibles
    mov ah, 09h 
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

    ; Pregunta qué figura quiere el usuario
    lea dx, [askn_msg]  
    mov ah, 09h  
    int 21h 

    ; Leer elección del usuario (1-8)
    mov ah, 01h  
    int 21h 
    cmp al, '1'  
    je case_square  
    cmp al, '2'  
    je case_circle 
    jmp done 

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
    INT 3
    int 21h  ; Interrupción de MS-DOS para salir


print_digitos:
    mov ah , 02h
    pop dx
    int 21h
    loop print_digitos

;basado el el codigo del usuario de stackoverflow @rcgldr 
;recuperado de https://stackoverflow.com/a/41501934/26912080
convert_entero:
    ; Cargar la parte más significativa 
    mov ax, [peri_r]              ; Cargar los primeros 2 bytes (parte más significativa)
    mov bx, [peri_r+2]
    int 3            ; Cargar los últimos 2 bytes (parte menos significativa)
    or ax, bx                 ; Realizar una operación lógica OR para verificar si ambos son 0
    jz print_loop         ; Si ambos son 0, saltar a imprimir los resultados

    ; Si no son 0, continuar la división
    mov ax, [peri_r]
    xor dx, dx                ; Limpiar DX antes de la división
    mov cx, 10                ; Divisor (decimal)
    div cx                    ; Dividir DX:AX por 10, AX = cociente, DX = residuo

    ; Almacenar el cociente y residuo
    mov [peri_r], ax              ; Guardar el cociente en los primeros 2 bytes de peri_r                   ; Guardar el residuo en la pila

    ; Repetir con la parte menos significativa
    mov ax, [peri_r+2]            ; Cargar los bytes menos significativos en AX                ; Limpiar DX antes de la división
    div cx                    ; Dividir DX:AX por 10

    ; Almacenar el cociente y residuo
    mov [peri_r+2], ax            ; Guardar el cociente en los últimos 2 bytes de peri_r
    push dx                   ; Guardar el residuo en la pila

    jmp convert_entero         ; Repetir el ciclo

print_loop:
    pop dx
    int 3                    ; Sacar el residuo de la pila
    add dl, '0'               ; Convertir el residuo a carácter ASCII
    mov ah, 02h               ; Función DOS para imprimir un carácter
    int 21h                   ; Imprimir el carácter
    cmp sp, 0xFFFE            ; Verificar si la pila está vacía (valor inicial de SP en DOS)
    jne print_loop            ; Repetir si aún hay valores en la pila

%include 'input.inc'
%include 'calc.inc'
%include 'figuras/square.inc'