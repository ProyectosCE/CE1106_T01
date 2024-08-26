section .data
    pi_val db 0x00, 0x03, 0x0E
    ask_radio db 0x0A,'Cuando mide el radio?',0x09,'', 0x0D, 0x0A, '$'  ; Pregunta para el cuadrado

case_circle:
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [ask_radio]  ; Carga la dirección del mensaje de consulta del lado del cuadrado en dx
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
       
    mov word [operando1],dato_01
    mov word [operando2],pi_val
    mov word [respuesta],peri_r
    
    Call multiplicacion

    mov bx,result_peri
    call imp_msg
    mov bx,[respuesta]
    call imprimir_resp
    jmp done
