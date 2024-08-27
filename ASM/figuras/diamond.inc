section .data
    un_medio_val db 0x00, 0x00, 0x05
    ask_D db 0x0A,'Cuando mide Diagonal Mayor?',0x09,'', 0x0D, 0x0A, '$'  
    ask_d db 0x0A, 'Cuando mide diagonal menor?',0x09,'', 0x0D, 0x0A, '$'


case_diamond:
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [ask_D]  ; Carga la dirección del mensaje de consulta del Diagonal Mayor en dx
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



    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [ask_d]  ; Carga la dirección del mensaje de consulta del Diagonal Mayor en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    call lectura ;para leer la entrada del usuario
    ;contador para los bytes del buffer
    mov si,0
    ;cantidad de caracteres ingresados en el buffer
    mov cx,[buffer_text+1]
    mov ch,0
    ;buffer donde se va a guardar el numero leido
    mov bx, dato_02
    call procesar_entero



    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [ask_lado]  ; Carga la dirección del mensaje de consulta del Diagonal Mayor en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    call lectura ;para leer la entrada del usuario
    ;contador para los bytes del buffer
    mov si,0
    ;cantidad de caracteres ingresados en el buffer
    mov cx,[buffer_text+1]
    mov ch,0
    ;buffer donde se va a guardar el numero leido
    mov bx, dato_03
    call procesar_entero
    

    ;calculo de perimetro
    mov ax,4h
    mov [buftemp],ah
    mov [buftemp+1],al
    mov byte [buftemp+2],00

    mov word [operando1],dato_03
    mov word [operando2],buftemp
    mov word [respuesta],peri_r
    
    call multiplicacion
    mov bx,result_peri
    call imp_msg
    mov bx,[respuesta]
    call imprimir_resp


    ;Calculo de area
    mov word [operando1],dato_01
    mov word [operando2],dato_02
    mov word [respuesta],temp_r

    call multiplicacion

    mov bx,[respuesta]

    call cinco_to_tres

    mov word [operando1],un_medio_val
    mov word [operando2],buftemp
    mov word [respuesta],area_r

    call multiplicacion

    mov bx,result_area
    call imp_msg
    mov bx,[respuesta]
    call imprimir_resp
    jmp repetir
