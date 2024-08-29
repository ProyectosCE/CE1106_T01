; MIT License
; Copyright (c) 2024 José Bernardo Barquero Bonilla,
;                  Jose Eduardo Campos Salazar,
;                  Jimmy Feng Feng,
;                  Alexander Montero Vargas
; Consulta el archivo LICENSE para más detalles.


;Seccion con constantes necesarias para el cálculo del área y perimetro del trapecio
section .data
    ask_B db 0x0A,'Cuanto mide Base Mayor?',0x09,'', 0x0D, 0x0A, '$'  
    ask_b db 0x0A, 'Cuanto mide base menor?',0x09,'', 0x0D, 0x0A, '$'

case_trapeze:
    ;Metodo para los cálculos propios del trapecio
    ;Base mayor
    ;Imprime la pregunta de cuanto mide la Base Mayor
    mov bx, ask_B
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


    ;Base menor
    ;Imprime la pregunta de cuanto mide la base menor
    mov bx, ask_b
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


    ;Lado 1
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
    mov bx, dato_03
    call procesar_entero


    ;Lado 2
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
    ;BX almacena la direccion del buffer donde se va a guardar el numero leido, buffer dato_4
    ;llama al metodo de procesamiento del número
    mov si,0
    mov cx,[buffer_text+1]
    mov ch,0
    mov bx, dato_04
    call procesar_entero

    ;Altura
    ;Imprime la pregunta de cuanto mide la altura
    mov bx, ask_h
    call imp_msg
   
    ;Limpia el buffer del texto
    mov si, buffer_text+1
    mov cx, 9
    call clear_loop

   ;Se prepara para leer la entrada del usuario
    call lectura
    
    ;Se prepara para procesar la cadena ingresada a un numero
    ;CX tiene la cantidad de caracteres ingresados en el buffer
    ;BX almacena la direccion del buffer donde se va a guardar el numero leido, buffer dato_5
    ;llama al metodo de procesamiento del número
    mov si,0
    mov cx,[buffer_text+1]
    mov ch,0
    mov bx, dato_05
    call procesar_entero

    ;calculo de perimetro
    ;Se prepara para llamar a suma, cargando el valor de la medida de la BaseMayor y basemenor
    ; y el buffer donde se va a guardar la respuesta
    mov word [operando1],dato_01
    mov word [operando2],dato_02
    mov word [respuesta],buftemp
    call suma

    ;Se prepara para llamar a suma, cargando el valor de la suma anterior y el lado1
    ; y el buffer donde se va a guardar la respuesta
    mov word [operando1],dato_03
    mov word [operando2],buftemp
    mov word [respuesta],buftemp2
    call suma

    ;Se prepara para llamar a suma, cargando el valor de la suma anterior y el lado2
    ; y el buffer donde se va a guardar la respuesta
    mov word [operando1],dato_04
    mov word [operando2],buftemp2
    mov word [respuesta],buftemp
    call suma

    ;se imprime el texto "el perimetro es"
    mov bx,result_peri
    call imp_msg

    ;Se convierte la suma de 3 a 5 bytes para imprimirlo
    mov bx,[respuesta]
    call tres_to_cinco
    ;se convierte e imprime la respuesta obtenida en peri_r
    mov bx,temp_r
    call imprimir_resp


    ;Calculo de area
    ;Se prepara para llamar a suma, cargando el valor de la medida de la BaseMayor y basemenor
    ; y el buffer donde se va a guardar la respuesta

    mov word [operando1],dato_01
    mov word [operando2],dato_02
    mov word [respuesta],buftemp
    call suma

    ;Se prepara para llamar a multiplicacion, cargando el valor de la suma obtenido anteriormente, el valor 1/2
    ; y el buffer donde se va a guardar la respuesta
    mov word [operando1],buftemp
    mov word [operando2],un_medio
    mov word [respuesta],temp_r
    call multiplicacion

    ;Se convierte la multiplicacion de 5 a 3 bytes para volver a operarlo
    mov bx,[respuesta]
    call cinco_to_tres

    ;Se prepara para llamar a multiplicacion, cargando el valor de la altura, con el valor de la multiplicacion anterior convertido a 3 bytes
    ; y el buffer donde se va a guardar la respuesta
    mov word [operando1],dato_05
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
