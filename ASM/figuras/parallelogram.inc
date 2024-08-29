; MIT License
; Copyright (c) 2024 José Bernardo Barquero Bonilla,
;                    Jose Eduardo Campos Salazar,
;                    Jimmy Feng Feng,
;                    Alexander Montero Vargas
; Consulta el archivo LICENSE para más detalles.


;Seccion con constantes necesarias para el cálculo del área y perimetro del paralelogramo
section .data
    ask_diagonal db 0x0A, 'Cuanto mide el diagonal?',0x0A, '$' 

case_parallelogram:
    ;Lado o base
    ;Metodo para los cálculos propios del paralelogramo

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


    ;Lado diagonal

    ;Imprime la pregunta de cuanto mide la diagonal
    mov bx, ask_diagonal
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

    ;altura

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
    ;BX almacena la direccion del buffer donde se va a guardar el numero leido, buffer dato_3
    ;llama al metodo de procesamiento del número
    mov si,0
    mov cx,[buffer_text+1]
    mov ch,0
    mov bx, dato_03
    call procesar_entero


    ;calculo de perimetro

    ;Se prepara para llamar a suma, cargando el valor de la medida del lado-base, y de la diagonal
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
    ;Se prepara para llamar a multiplicacion, cargando el valor de la medida del lado-base, el valor de la altura
    ; y el buffer donde se va a guardar la respuesta
    mov word [operando1],dato_01
    mov word [operando2],dato_03
    mov word [respuesta],area_r
    call multiplicacion

    ;se imprime el mensaje "el area es"
    mov bx,result_area
    call imp_msg
    ;se convierte e imprime la respuesta obtenida almacenada en area_r
    mov bx,[respuesta]
    call imprimir_resp

    ;se llama a repetir para preguntar si quiere calcular otra figura
    ret
