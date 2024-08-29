;Seccion con constantes necesarias para el cálculo del área y perimetro del rectangulo
section .data
    dos db 0x00, 0x02, 0x00


case_rectangle:
    ;Metodo para los cálculos propios del rectangulo

    ;Imprime la pregunta de cuanto mide el lado 1
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

    ;Imprime la pregunta de cuanto mide el lado 2
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
    ;BX almacena la direccion del buffer donde se va a guardar el numero leido, buffer dato_2
    ;llama al metodo de procesamiento del número
    mov si,0
    mov cx,[buffer_text+1]
    mov ch,0
    mov bx, dato_02
    call procesar_entero



    ;calculo de perimetro

    ;Se prepara para llamar a suma, cargando el valor de la medida de la base, y del lado
    ; y el buffer donde se va a guardar la respuesta
    mov word [operando1],dato_01
    mov word [operando2],dato_02
    mov word [respuesta],buftemp
    call suma

    ;Se prepara para llamar a multiplicacion, cargando el valor de la suma calculada, el valor de 2
    ; y el buffer donde se va a guardar la respuesta
    mov word [operando1],buftemp
    mov word [operando2],dos
    mov word [respuesta],peri_r
    call multiplicacion


    ;se imprime el texto "el perimetro es"
    mov bx,result_peri
    call imp_msg
    ;se convierte e imprime la respuesta obtenida en peri_r
    mov bx,[respuesta]
    call imprimir_resp

    ;Calculo de area
    ;Se prepara para llamar a multiplicacion, cargando el valor de la medida de la base y el valor del lado
    ; y el buffer donde se va a guardar la respuesta
    mov word [operando1],dato_01
    mov word [operando2],dato_02
    mov word [respuesta],area_r
    call multiplicacion

    ;se imprime el mensaje "el area es"
    mov bx,result_area
    call imp_msg
    ;se convierte e imprime la respuesta obtenida almacenada en area_r
    mov bx,[respuesta]
    call imprimir_resp

    ;se llama a repetir para preguntar si quiere calcular otra figura
    jmp input