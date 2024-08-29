case_square:
    ;Metodo para los cálculos propios del Cuadrado

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
    mov word [operando2],cuatro
    mov word [respuesta],peri_r
    call multiplicacion
    
    ;se imprime el texto "el perimetro es"
    mov bx,result_peri
    call imp_msg
    ;se convierte e imprime la respuesta obtenida en peri_r
    mov bx,[respuesta]
    call imprimir_resp

    ;Calculo de area
    ;Se prepara para llamar a multiplicacion, cargando el valor de la medida del lado
    ; y el buffer donde se va a guardar la respuesta
    mov word [operando1],dato_01
    mov word [operando2],dato_01
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