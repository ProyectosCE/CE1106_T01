; ## ARCHIVO DE EJEMPLO DE COMO HACER UNA SUMA E IMPRIMIRLA

section .data
    pri_v db 0x00, 0x01, 0x0A
    seg_v db 0x00, 0x02, 0x03
    result_suma db 0x0A, 'La suma es ', '$'

case_suma:
    ;para uso de las funciones de calc.inc
    mov word [operando1],seg_v
    mov word [operando2],pri_v
    mov word [respuesta],buftemp

    ;llama al metodo suma
    call suma
    
    ;imprime "la suma es:"
    mov bx,result_suma
    call imp_msg

    ;convierte el buffer de 3 a 5 bytes
    mov bx,[respuesta]
    call tres_to_cinco

    ;imprime el buffer de respuesta
    mov bx,temp_r
    call imprimir_resp