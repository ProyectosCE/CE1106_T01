section .data
    hexagon_var db 0x00, 0x02, 0x3C ; 2,30 = \frac{3raiz(3)}{2}

case_hexagon:
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [ask_l1]  ; Carga la dirección del mensaje de consulta del Diagonal Mayor en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    mov si, buffer_text+1
    mov cx, 9
    call clear_loop

    call lectura ;para leer la entrada del usuario
    ;contador para los bytes del buffer
    mov si,0
    ;cantidad de caracteres ingresados en el buffer
    mov cx,[buffer_text+1]
    mov ch,0
    ;buffer donde se va a guardar el numero leido
    mov bx, dato_01
    call procesar_entero


    ;calculo de perimetro
    mov ax,6h
    mov [buftemp],ah
    mov [buftemp+1],al
    mov byte [buftemp+2],00

    mov word [operando1],dato_01
    mov word [operando2],buftemp
    mov word [respuesta],peri_r
    
    call multiplicacion
    mov bx,result_peri
    call imp_msg
    mov bx,[respuesta]
    call imprimir_resp


    ;Calculo de area
    mov word [operando1],dato_01
    mov word [operando2],hexagon_var
    mov word [respuesta],temp_r

    call multiplicacion

    mov bx,[respuesta]

    call cinco_to_tres

    mov word [operando1],dato_01
    mov word [operando2],buftemp
    mov word [respuesta],area_r

    call multiplicacion

    mov bx,result_area
    call imp_msg
    mov bx,[respuesta]
    call imprimir_resp
    jmp repetir
