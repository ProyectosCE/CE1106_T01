section .data
    pi_v db 0x00, 0x03, 0x0E
    dos_v db 0x27, 0x0F, 0x63
    result_suma db 0x0A, 'La suma es ', '$'

case_suma:
    ;para uso de las funciones de calc.inc
    mov word [operando1],dos_v
    mov word [operando2],pi_v
    mov word [respuesta],buftemp

    call suma
    
    mov bx,result_suma
    call imp_msg

    mov bx,[respuesta]
    call tres_to_cinco
    mov bx,temp_r
    call imprimir_resp