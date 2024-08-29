; MIT License
; Copyright (c) 2024 José Bernardo Barquero Bonilla,
;                    Jose Eduardo Campos Salazar,
;                    Jimmy Feng Feng,
;                    Alexander Montero Vargas
; Consulta el archivo LICENSE para más detalles.


[bits 16]

;Seccion de datos predefinidos
section .data
    ;Mensaje general de pruebas
    default_ms db 'Otras cosas', 0x0D, 0x0A, '$' 

    ;Mensaje de bienvenida

    imsg1 db ' +----------------------------------------------------------------------------+', 0x0A, '$'
    imsg2 db ' |                       This program is under MIT License                    |', 0x0A, '$'
    imsg3 db ' |                              Copyright(c) 2024                             |', 0x0A, '$'
    imsg4 db ' |                         Bienvenido a GeometryTEC                           |', 0x0A, '$'
    imsg5 db ' +----------------------------------------------------------------------------+', 0x0A, 0x0A, '$'

    gui_ask db ' Seleccione el modo de interfaz (A o B)',0x0A,0x0A,0x0A,'$'
    esc_ask db ' Presione escape para salir',0x0A,0x0A,0x0A,'$'


    ;selector de interfaz
    line0 db '        Clasica CLI (Presione A)             Nueva Interfaz (Presione B)  ', 0x0A, 0x0A, '$'
    line1 db '          +-------------------+                 +-------------------+', 0x0A, '$'
    line2 db '          |                   |                 | +------+          |', 0x0A, '$'
    line3 db '          |  Opcion 1         |                 | | - F  |          |', 0x0A, '$'
    line4 db '          |  Opcion 2         |                 | | - C  |          |', 0x0A, '$'
    line5 db '          |  Opcion 3         |                 | | - T  |          |', 0x0A, '$'
    line6 db '          |  _                |                 | +------+          |', 0x0A, '$'
    line7 db '          |                   |                 |                   |', 0x0A, '$'
    line8 db '          +-------------------+                 +-------------------+', 0x0A, '$'


    ;Para pregunta se seleccion de figura
    askn_msg db 'Escoge una figura:',0X0A, '$' 
    square db '1. Cuadrado', 0x0A, '$'  
    circle db '2. Circulo', 0x0A, '$'  
    triangle db '3. Triangulo', 0x0A, '$'  
    diamond db '4. Diamante', 0x0A, '$'  
    pentagon db '5. Pentagono', 0x0A, '$'  
    hexagon db '6. Hexagono', 0x0A, '$'  
    trapeze db '7. Trapecio', 0x0A, '$'  
    parallelogram db '8. Paralelogramo', 0x0A, '$' 
    rectangle db '9. Rectangulo', 0x0A, '$'  
    exit_msg db  '0. Cerrar programa',0x0A,'$'

    fig_selec db  'Se selecciono la figura: ',0x0A,'$'

    ;Pregunta de lados
    ask_lado db 0x0A, 'Cuanto mide el lado?',0x0A, '$' 
    ask_l1 db 0x0A, 'Cuanto mide el lado 1?',0x0A, '$'
    ask_l2 db 0x0A, 'Cuanto mide el lado 2?',0x0A, '$'
    ask_h db 0x0A, 'Cuanto mide la altura?',0x0A, '$'
    
    ;Respuestas de perimetro y área
    result_peri db 0x0A,0x0A,'El perimetro es: ',0x0A, '$'
    result_area db 0x0A,'El area es: ',0x0A, '$'

    ; Mensaje de para consultar si quiere hacer otro calculo
    repetir_msg db 0x0A, 'Por favor presione:', '$'
    repsi db 0x0A,'1. Hacer otra operacion','$' 
    repno db 0x0A,'2. Salir',0x0A,'$'

    ;Mensaje de agradecimiento
    salida_msg db 0x0A, 'Gracias por usar GeometryTEC',0x0A,'$'  ; Mensaje de salida

    ;MENSAJES DE LICENCIA
    licencia db 'This program is under MIT License, Copyright(c) 2024','$' 

    colorline db ' ','$'
    newline db 0x0A,'$'  

;Seccion de buffer usados en todo el programa para el almacenamiento de valores y datos
section .bss   
    ;buffer general de entrada de texto (reutilizable)
    buffer_text resb 10 ; maxima entrada del input (7 máx y 2 bytes de control)
    
    ;buffer para datos numericos (hasta 3 para las figuras que lo ocupan)
    dato_01 resb 3 ;dato Numerico para input 1
    dato_02 resb 3 ;dato Numerico para input 2
    dato_03 resb 3 ;dato Numerico para input 3
    dato_04 resb 3 ;dato Numerico para input 4
    dato_05 resb 3 ;dato Numerico para input 5
    
    ;Buffer a usar en operaciones matematicas (guardar direcciones de los buffers)
    operando1 resb 2
    operando2 resb 2
    respuesta resb 2

    ;Buffer numerico de 3 bytes multiproposito
    buftemp resb 3
    buftemp2 resb 3
    buftemp3 resb 3

    ;Buffers para respuestas, de 5 bytes
    ; 4 bytes max para la parte entera
    ; 1 byte para la parte decimal
    peri_r resb 5 
    area_r resb 5
    temp_r resb 5

    intselect resb 1
    
; Seccion de texto propia de asm 8086
section .text
    ;ORG 100h facilita al compilador saber que el codigo es ASM 8086 para DOS
    org 100h
    ; Declaración global del punto de entrada
    global _start 

_start:
    call init_pantalla
    call color_screen
    jmp initial_case 

initial_case:
    ;Imprime noticia de Licencia

    mov bx,licencia
    call imp_msg

    ; Imprime el mensaje inicial de bienvenida
    mov bx,imsg1
    mov cl,0x1F
    call color_msg

    mov bx,imsg2
    mov cl,0x1F
    call color_msg

    mov bx,imsg3
    mov cl,0x1F
    call color_msg

    mov bx,imsg4
    mov cl,0x1F
    call color_msg

    mov bx,imsg5
    mov cl,0x1F
    call color_msg

    mov bx,gui_ask
    mov cl,0x71
    call color_msg

; Imprimir cada línea de la del selector de la interfaz
    mov bx, line0
    mov cl, 0x70
    call color_msg

    mov bx, line1
    mov cl, 0x70
    call color_msg

    mov bx, line2
    mov cl, 0x70
    call color_msg

    mov bx, line3
    mov cl, 0x70
    call color_msg

    mov bx, line4
    mov cl, 0x70
    call color_msg

    mov bx, line5
    mov cl, 0x70
    call color_msg

    mov bx, line6
    mov cl, 0x70
    call color_msg

    mov bx, line7
    mov cl, 0x70
    call color_msg

    mov bx, line8
    mov cl, 0x70
    call color_msg
    jmp new_gui_ask
 

new_gui_ask:
    mov al,0
    mov ah, 01h  
    int 21h
    cmp al, 'B'  
    je maingui 
    cmp al, 'b'  
    je maingui  
    cmp al, 'A'  
    je case_show_figures 
    cmp al, 'a'  
    je case_show_figures 
    cmp al, 0x1B
    je force_exit 
    jmp new_gui_ask



default_case:
    ; Mensaje por defecto en caso de entrada inválida
    mov bx, default_ms
    call color_msg
    ; Salta a imprimir el listado de figuras
    jmp case_show_figures


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

    mov si, dato_04
    mov cx, 3
    call clear_loop

    mov si, dato_05
    mov cx, 3
    call clear_loop
    
    mov si, buftemp
    mov cx, 3
    call clear_loop

    mov si, buftemp2
    mov cx, 3
    call clear_loop

    mov si, buftemp3
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
    mov bx, salida_msg
    call imp_msg

    mov ah, 4Ch  ; Función de MS-DOS para terminar el programa
    int 21h  ; Interrupción de MS-DOS para salir

force_exit:
    mov ah, 4Ch  ; Función de MS-DOS para terminar el programa
    int 21h 

init_pantalla:
    mov ah, 06h       
    mov al, 0         
    mov bh, 07h       
    mov cx, 0        
    mov dx, 184Fh     
    int 10h           

    ; Mover el cursor a la posición inicial (0, 0)
    mov ah, 02h       
    mov bh, 0         
    mov dh, 0         
    mov dl, 0         
    int 10h 
    ret     

color_screen:
    mov ah,06h
    mov bh,0x77
    mov ch,0
    mov cl,0
    mov dh,25
    mov dl,80
    int 10h
    ret

%include 'gui.inc'
%include 'cli.inc'
%include 'io.inc'
%include 'calc.inc'
%include 'figuras/square.inc'
%include 'figuras/circle.inc'
%include 'figuras/diamond.inc'
%include 'figuras/pentagon.inc'
%include 'figuras/trapeze.inc'
%include 'figuras/rectangle.inc'
%include 'figuras/parallelogram.inc'
%include 'figuras/hexagon.inc'
%include 'figuras/triangle.inc'
