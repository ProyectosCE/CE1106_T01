; MIT License
; Copyright (c) 2024 José Bernardo Barquero Bonilla,
;                    Jose Eduardo Campos Salazar,
;                    Jimmy Feng Feng,
;                    Alexander Montero Vargas
; Consulta el archivo LICENSE para más detalles.

;Seccion con constantes necesarias para el cálculo del área y perimetro del hexagono, como el valor 2.60
section .data
    hexagon_var db 0x00, 0x02, 0x3C ; 2,60
    seis_lados db 0x00, 0x06, 0x00

case_hexagon:
    ;Metodo para los cálculos propios del hexagono

    ;Imprime la pregunta de cuanto mide el lado
    mov bx, ask_l1
    call imp_msg
   

   ;Limpia el buffer del texto
    mov si, buffer_text+1
    mov cx, 9
    call clear_loop

   ;Se prepara para leer la entrada del usuario
    call lectura
    
    ;Se prepara para procesar la cadena ingresada a un numero
    ;CX tiene la cantidad de caracteres ingresados en el buffer
    ;BX almacena la direccion del buffer donde se va a guardar el numero leido, buffer dato_1
    ;llama al metodo de procesamiento del número
    mov si,0
    mov cx,[buffer_text+1]
    mov ch,0
    mov bx, dato_01
    call procesar_entero



     ;calculo de perimetro
    
    ;Se prepara para llamar a multiplicacion, cargando el valor de la medida del lado, el valor de 5
    ; y el buffer donde se va a guardar la respuesta

    mov word [operando1],dato_01
    mov word [operando2],seis_lados
    mov word [respuesta],peri_r
    call multiplicacion

    ;se imprime el texto "el perimetro es"
    mov bx,result_peri
    call imp_msg
    ;se convierte e imprime la respuesta obtenida en peri_r
    mov bx,[respuesta]
    call imprimir_resp

    ;Calculo de area
    ;Se prepara para llamar a multiplicacion, cargando el valor de la medida del lado, el valor de hexagon_var
    ; y el buffer donde se va a guardar la respuesta
    mov word [operando1],dato_01
    mov word [operando2],hexagon_var
    mov word [respuesta],temp_r
    call multiplicacion

    ;Se convierte la respuesta de 5 bytes a 3 bytes para eliminar los dos bytes iniciales vacios
    mov bx,[respuesta]
    call cinco_to_tres

    ;Se prepara para otra multiplicacion, ahora para multiplicar por la medida del lado el valor obtenido de la respuesta anterior y procesado a 3 bytes
    ; la respuesta se almacena en area_r 
    mov word [operando1],dato_01
    mov word [operando2],buftemp
    mov word [respuesta],area_r
    call multiplicacion

    ;se imprime el mensaje "el area es"
    mov bx,result_area
    call imp_msg
    ;se convierte e imprime la respuesta obtenida almacenada en area_r
    mov bx,[respuesta]
    call imprimir_resp

    ;se llama a repetir para preguntar si quiere calcular otra figura
    jmp repetir