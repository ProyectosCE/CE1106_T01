; MIT License
; Copyright (c) 2024 José Bernardo Barquero Bonilla,
;                    Jose Eduardo Campos Salazar,
;                    Jimmy Feng Feng,
;                    Alexander Montero Vargas
; Consulta el archivo LICENSE para más detalles.


case_show_figures:
    mov al,1
    mov byte [intselect],al
    xor ax,ax
    call init_pantalla
    call reinciar_buf
    ; Pregunta qué figura quiere el usuario
    mov bx,askn_msg
    mov cl,0x0B
    call color_msg

    ; Imprime las opciones de figuras disponibles
    mov bx, square
    mov cl, 0x0F
    call color_msg

    mov bx, circle
    mov cl, 0x0F
    call color_msg

    mov bx, triangle
    mov cl, 0x0F
    call color_msg

    mov bx, diamond
    mov cl, 0x0F
    call color_msg

    mov bx, pentagon
    mov cl, 0x0F
    call color_msg

    mov bx, hexagon
    mov cl, 0x0F
    call color_msg

    mov bx, trapeze
    mov cl, 0x0F
    call color_msg

    mov bx, parallelogram
    mov cl, 0x0F
    call color_msg

    mov bx, rectangle
    mov cl, 0x0F
    call color_msg

    mov bx, exit_msg
    mov cl, 0x04
    call color_msg

    mov bx, colorline
    mov cl, 0x02
    call color_msg

    call entrada_fig

    jmp repetir

entrada_fig:
    xor AX,AX
    mov ah, 01h  
    int 21h 
    cmp al, '1'  
    je case_square  
    cmp al, '2'  
    je case_circle 
    cmp al, '3'
    je case_triangle
    cmp al, '4'
    je case_diamond
    cmp al, '5'
    je case_pentagon
    cmp al, '6'
    je case_hexagon
    cmp al, '7'
    je case_trapeze
    cmp al, '8'
    je case_parallelogram
    cmp al, '9'
    je case_rectangle
    cmp al, '0'
    je done


    ;si el digito ingresado no es válido vuelve a preguntar que figura quiere calcular
    jmp entrada_fig 

repetir:
    ; Mensaje pora preguntar si quiere repetir o no
    mov bx, repetir_msg
    call imp_msg
    
    mov bx, repsi
    call imp_msg

    mov bx, repno
    call imp_msg

    xor ax,ax
    mov bx, colorline
    mov cl, 0x00
    call color_msg

    jmp procesar_rep
    
procesar_rep:
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
    jmp procesar_rep
