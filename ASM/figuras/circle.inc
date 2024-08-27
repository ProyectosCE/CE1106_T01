section .data
    pi_val db 0x00, 0x03, 0x0E
    dos_val db 0x00, 0x02, 0x00
    ask_radio db 0x0A,'Cuanto mide el radio?',0x09,'', 0x0D, 0x0A, '$'  ; Pregunta para el radio

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

    ;para uso de las funciones de calc.inc
    ;calculo de perimetro
    mov word [operando1],dato_01
    mov word [operando2],pi_val
    mov word [respuesta],temp_r
    
    Call multiplicacion

    mov bx,[respuesta]
    call cinco_to_tres
    mov word [operando1],dos_val
    mov word [operando2],buftemp
    mov word [respuesta],peri_r
    
    call multiplicacion
    mov bx,result_peri
    call imp_msg
    mov bx,[respuesta]
    call imprimir_resp

    ;Calculo de area
    mov word [operando1],dato_01
    mov word [operando2],buftemp
    mov word [respuesta],area_r

    call multiplicacion

    mov bx,result_area
    call imp_msg
    mov bx,[respuesta]
    call imprimir_resp
    jmp repetir
