case_square:
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [ask_lado]  ; Carga la dirección del mensaje de consulta del lado del cuadrado en dx
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

    mov ah,[dato_01]
    mov al,[dato_01+1]
    mov bh,[dato_01+2]
    INT 3
    ;OPERACIONES PROPIAS DEL CUADRADO:
    mov ax,4h
    mov [buftemp],ax
    mov byte [buftemp+2],00

    mov word [operando1],dato_01
    mov word [operando2],buftemp
    mov word [respuesta],peri_r
    
    call multiplicacion
    mov bx,result_peri
    call imp_msg
    mov bx,[respuesta]
    call imprimir_resp

    JMP done