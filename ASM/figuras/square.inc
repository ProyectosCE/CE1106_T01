case_square:
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [square_msg]  ; Carga la dirección del mensaje de consulta del lado del cuadrado en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    call lectura
    mov si,0
    mov cx,[buffer_text+1]
    mov ch,0
    mov bx, [dato_lista]
    call procesar_entero
    mov byte [lados],4
    mov byte [lados+1],00
    call multiplicacion
    ;DEBUG
    MOV AH,[peri_r]
    MOV AL,[peri_r+1]
    MOV BH,[peri_r+2]
    MOV BL,[peri_r+3]
    INT 3