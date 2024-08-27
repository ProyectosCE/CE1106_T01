section .data
    ask_diagonal db 0x0A, 'Cuanto mide el diagonal?',0x0A, '$' 

case_parallelogram:
    ;Lado o base
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


    ;Lado diagonal
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [ask_diagonal]  ; Carga la dirección del mensaje de consulta del Diagonal Mayor en dx
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
    mov bx, dato_02
    call procesar_entero

    ;altura
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [ask_diagonal]  ; Carga la dirección del mensaje de consulta del Diagonal Mayor en dx
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
    mov bx, dato_03
    call procesar_entero


    ;calculo de perimetro

    mov word [operando1],dato_01
    mov word [operando2],dato_02
    mov word [respuesta],buftemp
    
    call suma

    mov word [operando1],buftemp
    mov word [operando2],dos
    mov word [respuesta],peri_r

    call multiplicacion


    mov bx,result_peri
    call imp_msg
    mov bx,[respuesta]
    call imprimir_resp

    ;Calculo de area
    mov word [operando1],dato_01
    mov word [operando2],dato_03
    mov word [respuesta],area_r

    call multiplicacion

    mov bx,result_area
    call imp_msg
    mov bx,[respuesta]
    call imprimir_resp

    jmp repetir
