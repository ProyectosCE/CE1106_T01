section .data
    ask_B db 0x0A,'Cuanto mide Base Mayor?',0x09,'', 0x0D, 0x0A, '$'  
    ask_b db 0x0A, 'Cuanto mide base menor?',0x09,'', 0x0D, 0x0A, '$'

case_trapeze:

    ;Base mayor
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [ask_B]  ; Carga la dirección del mensaje de consulta del 
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


    ;Base menor
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [ask_b]  ; Carga la dirección del mensaje de consulta del 
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


    ;Lado 1
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [ask_l1]  ; Carga la dirección del mensaje de consulta del 
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


    ;Lado 2
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [ask_l2]  ; Carga la dirección del mensaje de consulta del 
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
    mov bx, dato_04
    call procesar_entero

    ;Altura
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [ask_h]  ; Carga la dirección del mensaje de consulta del 
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
    mov bx, dato_05
    call procesar_entero


    ;calculo de perimetro
    mov word [operando1],dato_01
    mov word [operando2],dato_02
    mov word [respuesta],buftemp
    
    call suma

    mov word [operando1],dato_03
    mov word [operando2],buftemp
    mov word [respuesta],buftemp2
    
    call suma

    mov word [operando1],dato_04
    mov word [operando2],buftemp2
    mov word [respuesta],buftemp
    
    call suma

    mov bx,result_peri

    call imp_msg
    mov bx,[respuesta]
    call tres_to_cinco
    mov bx,temp_r
    call imprimir_resp


    ;Calculo de area
    mov word [operando1],dato_01
    mov word [operando2],dato_02
    mov word [respuesta],buftemp

    call suma

    mov word [operando1],buftemp
    mov word [operando2],un_medio_val
    mov word [respuesta],temp_r

    call multiplicacion
    mov bx,[respuesta]
    call cinco_to_tres

    mov word [operando1],dato_05
    mov word [operando2],buftemp
    mov word [respuesta],area_r

    call multiplicacion

    mov bx,result_area
    call imp_msg
    mov bx,[respuesta]
    call imprimir_resp
    jmp repetir
