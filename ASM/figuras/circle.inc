;Seccion con constantes necesarias para el cálculo del área y perimetro del circulo, como el valor 2 o el valor de pi
section .data
    pi_val db 0x00, 0x03, 0x0E
    dos_val db 0x00, 0x02, 0x00
    ask_radio db 0x0A,'Cuando mide el radio?',0x09,'', 0x0D, 0x0A, '$'  ; Pregunta para el radio

case_circle:

    ;Metodo para los cálculos propios del círculo

    ;Imprime la pregunta de cuanto mide el radio
    mov bx, [ask_radio]
    call imp_msg
   
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

    ;para uso de las funciones de calc.inc

    ;Calculo del perimetro
    ;Se prepara para llamar a multiplicacion, cargando el valor del radios, el valor de pi
    ; y el buffer donde se va a guardar la respuesta
    mov word [operando1],dato_01
    mov word [operando2],pi_val
    mov word [respuesta],temp_r
    Call multiplicacion

    ;Se convierte la respuesta de 5 bytes a 3 bytes para eliminar los dos bytes iniciales vacios
    mov bx,[respuesta]
    call cinco_to_tres

    ;Se prepara para otra multiplicacion, ahora para multiplicar por 2 el valor obtenido de la respuesta anterior y procesado a 3 bytes
    ; la respuesta se almacena en peri_r
    mov word [operando1],dos_val
    mov word [operando2],buftemp
    mov word [respuesta],peri_r
    call multiplicacion

    ;se imprime el texto "el perimetro es"
    mov bx,result_peri
    call imp_msg
    ;se convierte e imprime la respuesta obtenida en peri_r
    mov bx,[respuesta]
    call imprimir_resp
    
    ;Calculo del area
    ;se prepara para otra multiplicación, ahora del valor almacenado en buftemp (r*pi) por el radio, se almacena la respuesta en area_r
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
