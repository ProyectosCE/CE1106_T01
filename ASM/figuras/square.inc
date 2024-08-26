case_square:
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [square_msg]  ; Carga la dirección del mensaje de consulta del lado del cuadrado en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    call lectura ;para leer la entrada del usuario
    ;contador para los bytes del buffer
    mov si,0
    ;cantidad de caracteres ingresados en el buffer
    mov cx,[buffer_text+1]
    mov ch,0
    ;buffer donde se va a guardar el numero leido
    mov bx, dato_01
    call procesar_entero

    ;OPERACIONES PROPIAS DEL CUADRADO:
    mov ax,4h
    mov [buftest],ax
    mov byte [buftest+2],00

    mov word [operando1],dato_01
    mov word [operando2],buftest
    mov word [respuesta],peri_r
    
    call multiplicacion
    
    ; //  DEBUG  //
    MOV AH,[peri_r]
    MOV AL,[peri_r+1]
    MOV BH,[peri_r+2]
    MOV BL,[peri_r+3]
    MOV CH,[peri_r+4]
    INT 3

    JMP done