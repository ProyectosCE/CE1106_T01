;Seccion con constantes necesarias para el cálculo del área y perimetro del diamante, como el valor de 1/2
section .data
    un_medio_val db 0x00, 0x00, 0x32
    cuatro_lados db 0x00, 0x04, 0x00
    ask_D db 0x0A,'Cuando mide Diagonal Mayor?',0x09,'', 0x0D, 0x0A, '$'  
    ask_d db 0x0A, 'Cuando mide diagonal menor?',0x09,'', 0x0D, 0x0A, '$'


case_diamond:
    ;Metodo para los cálculos propios del diamante

    ;Imprime la pregunta de cuanto mide la Diagonal mayor
    mov bx, [ask_D]
    call imp_msg
   
    ;Limpia el buffer del texto
    mov si, buffer_text+1
    mov cx, 9
    call clear_loop

    ;Se prepara para leer la entrada del usuario
    call lectura ;para leer la entrada del usuario
    
    ;Se prepara para procesar la cadena ingresada a un numero
    ;CX tiene la cantidad de caracteres ingresados en el buffer
    ;BX almacena la direccion del buffer donde se va a guardar el numero leido, buffer dato_1
    ;llama al metodo de procesamiento del número
    mov si,0
    mov cx,[buffer_text+1]
    mov ch,0
    mov bx, dato_01
    call procesar_entero

    ;Imprime la pregunta de cuanto mide la Diagonal menor
    mov bx, [ask_D]
    call imp_msg

    ;Limpia el buffer del texto
    mov si, buffer_text+1
    mov cx, 9
    call clear_loop

    ;Se prepara para leer la entrada del usuario
    call lectura ;para leer la entrada del usuario
    
    ;Se prepara para procesar la cadena ingresada a un numero
    ;CX tiene la cantidad de caracteres ingresados en el buffer
    ;BX almacena la direccion del buffer donde se va a guardar el numero leido, buffer dato_2
    ;llama al metodo de procesamiento del número
    mov si,0
    mov cx,[buffer_text+1]
    mov ch,0
    mov bx, dato_02
    call procesar_entero

    ;Imprime la pregunta de cuanto mide la Diagonal menor
    mov bx, [ask_lado]
    call imp_msg

    ;Limpia el buffer del texto
    mov si, buffer_text+1
    mov cx, 9
    call clear_loop

    ;Se prepara para leer la entrada del usuario
    call lectura

    ;Se prepara para procesar la cadena ingresada a un numero
    ;CX tiene la cantidad de caracteres ingresados en el buffer
    ;BX almacena la direccion del buffer donde se va a guardar el numero leido, buffer dato_3
    ;llama al metodo de procesamiento del número
    mov si,0
    mov cx,[buffer_text+1]
    mov ch,0
    mov bx, dato_03
    call procesar_entero


    ;calculo de perimetro
    ;Se prepara para llamar a multiplicacion, cargando el valor del lado, el valor 4
    ; y el buffer donde se va a guardar la respuesta
    mov word [operando1],dato_03
    mov word [operando2],cuatro_lados
    mov word [respuesta],peri_r
    call multiplicacion
    
    ;se imprime el texto "el perimetro es"
    mov bx,result_peri
    call imp_msg
    ;se convierte e imprime la respuesta obtenida en peri_r
    mov bx,[respuesta]
    call imprimir_resp


    ;Calculo de area
    ;Se prepara para llamar a multiplicacion, cargando el valor de la Diagonal Mayor, el valor de 1/2
    ; y el buffer donde se va a guardar la respuesta                                                                                    
    mov word [operando1],dato_01
    mov word [operando2],un_medio_val
    mov word [respuesta],temp_r
    call multiplicacion

    ;Se convierte la respuesta de 5 bytes a 3 bytes para eliminar los dos bytes iniciales vacios
    mov bx,[respuesta]
    call cinco_to_tres

    ;Se prepara para otra multiplicacion, ahora para multiplicar por la diagonal menor el valor obtenido de la respuesta anterior y procesado a 3 bytes
    ; la respuesta se almacena en area_r
    mov word [operando1],dato_02
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
