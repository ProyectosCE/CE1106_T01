; MIT License
; Copyright (c) 2024 José Bernardo Barquero Bonilla,
;                    Jose Eduardo Campos Salazar,
;                    Jimmy Feng Feng,
;                    Alexander Montero Vargas
; Consulta el archivo LICENSE para más detalles.

multiplicacion:
    ; Entradas: direccion del Operando1 (3 bytes), direccion del Operando2 (3 bytes), direccion del buffer de respuesta (5 bytes)
    ; Salidas: Almacena en el buffer de respuesta el resultado (max 5 bytes)
    ; Restricciones: Los operandos tienen que ser de 3 bytes y la respuesta tiene que ser de 5 bytes
    
    ; // PASO 01. MULTIPLICACION DE PARTE ENTERA-ENTERA
    ; se carga los operandos en los registros, AX-Operando1 y CX-Operando2
    mov bx,[operando1] 
    mov AH,[bx]
    mov AL,[bx+1]
    xor bx,bx
    mov bx, [operando2]
    mov CH,[bx]
    mov CL,[bx+1]
    
    ;Multiplica AX*CX, el resultado se almacena en DX:AX
    mul CX
    ;Guarda el resultado, DX en los primeros 2 bytes del buffer de respuesta y AX en los siguientes 2 bytes
    mov bx,[respuesta]
    MOV [bx+3],AL
    MOV [bx+2],AH
    MOV [bX+1],dl
    MOV [bx],dh

    ; // PASO 02. MULTIPLICACION DE PARTE ENTERA-DECIMAL
    ; se carga los operandos en los registros, AX-Operando1 y CL-Operando2(Decimal)
    mov bx,[operando1] 
    mov AH,[bx]
    mov AL,[bx+1]
    xor bx,bx
    mov bx, [operando2]
    mov CH,0
    mov CL,[bx+2]

    ;Multiplica AX*CX, resultado se almacena en DX:AX
    mul CX

    ;prepara BX=100 para dividir el resultado, En DX se almacena el residuo y en AX el cociente
    mov BX,100
    div BX

    ;Guarda resultado en la parte decimal de la respuesta 
    mov bx,[respuesta]
    add [bx+4],dl
    
    ;se guarda ax en la pila para no perder el valor
    PUSH AX
    ;se limpia ax
    XOR AX,AX

    ;se carga el decimal de la respuesta en AL, para verificar que no se exceda de 99, de ser así pase el exceso al número entero
    ;se preparan los datos para la division entre 100
    mov al,[bx+4]
    MOV CH,0
    MOV CL,100
    
    ;se divide entre 100, en AL se almacena el cociente y en AH el residuo
    DIV CL
    ;se guarda el residuo en el buffer de respuesta decimal
    MOV byte [bx+4],ah
    
    ;Se guarda el cociente en ch para no perderlo, por si tiene algún valor necesario
    mov ch,al
    ;se recupera el valor original de ax y se le suma al valor recién guardado en ch
    POP AX
    ADD CH,AL
    
    ;Se limpia DX, sirve para almacenar datos de Carry
    XOR DX,DX
    
    ;Se guarda toda la parte entera en los primeros 4 bytes del buffer de respuesta, se comprueba el carry
    ADD BYTE [bx+3],CH
    ADC AH,0
    ADD [bx+2],AH
    ADC DL,0
    ADD [bX+1],dl
    ADC DH,0
    ADD [bx],dh
    
    
    ; // PASO 03. MULTIPLICACION DE PARTE DECIMAL-ENTERA
    ; se carga los operandos en los registros, AL-Operando1(Decimal) y CX-Operando2
    mov bx,[operando1]
    MOV AH,0 
    mov AL,[bx+2]
    xor bx,bx
    mov bx, [operando2]
    mov CH,[bx]
    mov CL,[bx+1]
    
    ;Multiplica AX*CX, el resultado se almacena en DX:AX
    mul CX

    ;prepara BX=100 para dividir el resultado, En DX se almacena el residuo y en AX el cociente
    mov BX,100
    div BX

    ;Guarda resultado en la parte decimal de la respuesta, sumandolo al dato que ya tiene almacenado
    mov bx,[respuesta]
    add BYTE [bx+4],dl

    ;se guarda AX en la pila,para no perder el valor, y se limpia el registro
    PUSH AX
    XOR AX,AX
    ;se carga el decimal de la respuesta en AL, para verificar que no se exceda de 99, de ser así pase el exceso al número entero
    ;se preparan los datos para la division entre 100
    mov al,[bx+4]
    MOV CX,0
    MOV CL,100
    
    ;se divide entre 100, en AL se almacena el cociente y en AH el residuo
    ;se guarda el residuo en el buffer de respuesta decimal
    div CL
    mov byte [bx+4],ah
    
    ; se guarda el valor de al en ch para no perderlo
    mov ch,al
    
    ;se recupera el valor original de ax y se le suma el valor recién guardado en ch
    POP AX
    add al,ch

    ;se limpia ch para usarlo en datos de carry
    mov ch,0
    ;se guarda la parte entera de los calculos en los primeros 4 bytes del buffer de respuesta, se comprueba el carry
    ADD BYTE [bx+3],AL
    ADC AH,0
    ADD BYTE [bx+2],AH
    adc CH,0
    ADD BYTE [bx+1],ch
    adc byte [bx],0

    
    ; // PASO 04. MULTIPLICACION DE PARTE DECIMAL-DECIMAL
    ; se cargan los operandos en los registros, AL-Operando1(Decimal) y CL-Operando2(Decimal)
    mov bx,[operando1] 
    MOV AH,0
    mov al,[bx+2]
    xor bx,bx
    mov bx, [operando2]
    MOV ch,0
    mov CL,[bx+2]

    ;Multiplica AL*CL, resultado se almacena en AH:AL
    mul CL
    
    ;Prepara BX para dividir entre 100, el resultado se guarda en AH:AL
    ;En AL el cociente y el residuo en AH
    mov BX,100
    div BL

    ;Guarda resultado en la parte decimal de la respuesta, sumandolo al dato que ya tiene almacenado
    mov bx,[respuesta]
    add BYTE [bx+4],al

    ;se limpia ax y se carga el decimal de la respuesta en AL, para verificar que no se exceda de 99, de ser así pase el exceso al número entero
    ;se preparan los datos para la division entre 100
    XOR AX,AX
    mov al,[bx+4]
    MOV CX,0
    MOV CL,100

    ;se divide entre 100, en AL se almacena el cociente y en AH el residuo
    ;se guarda el residuo en el buffer de respuesta decimal
    DIV CL
    mov byte [bx+4],ah
    
    ;se guarda la parte entera de los calculos en los primeros 4 bytes del buffer de respuesta, se comprueba el carry
    MOV AH,0
    add BYTE [bx+3],AL
    ADC ah,0
    ADD BYTE [bx+2],ah
    MOV AX,0
    adc AL,0
    ADD BYTE [bx+1],al
    ADC AH,0
    adc byte [bx],AH
    
    ;Retorno
    ret

suma:
    ; Entradas: direccion del Operando1 (3 bytes), direccion del Operando2 (3 bytes), direccion del buffer de respuesta (3 bytes)
    ; Salidas: Almacena en el buffer de respuesta el resultado (max 3 bytes)
    ; Restricciones: Los operandos y la respuesta tiene que ser de 3 bytes

    ;cargar a los registros los operandos para decimales, AL para Operando1 y CL para Operando2
    mov bx,[operando1] 
    mov AH,0
    mov AL,[bx+2]
    xor bx,bx
    mov bx, [operando2]
    mov CH,0
    mov CL,[bx+2]

    ;suma los dos decimales, valor máximo a obtener 198
    ADD AL,CL
    ;prepa cl para dividir el valor de AL entre 100, lo que quede en AH se guarda en la respuesta decimal, lo que quede en AL se pasa al numero entero
    MOV CL,100
    DIV CL

    ;Guarda la respuesta decimal
    MOV BX, [respuesta]
    MOV BYTE [BX+2],AH
    ;guarda en DL el carry (1 o 0)
    MOV DH,0
    MOV DL,AL

    ;Carga los operandos, ahora en AX el operando1 y en CX el operando2
    mov bx,[operando1] 
    mov AH,[BX]
    mov AL,[bx+1]
    mov bx, [operando2]
    mov CH,[bx]
    mov CL,[bx+1]
    mov CL,[bx+1]

    ;suma ax,dx, resultado en AX, valor máximo de suma 65535
    ADD AX,CX
    ADD AX,DX

    ;Guarda la rspuesta en los primeros 2 bytes del buffer de respuesta
    MOV BX,[respuesta]
    MOV BYTE [BX+1],AL
    MOV BYTE [BX],AH
    ;Retorno
    ret


cinco_to_tres:
    ; Entradas: direccion del Buffer de 5 Bytes que se quiere convertir a 3 Bytes
    ; Salidas: Almacena en buftemp el resultado (max 3 bytes)
    ; Restricciones: El buffer de entrada debe tener datos en la posición 3 y 4 para valores enteros
    ; y en la posición 5 para valores decimales; y la respuesta tiene de salida es de 3 bytes

    ;Almacena en los 3 primeros bytes de buftemp los valores de las posiciones 3,4 y 5 del buffer de entrada respectivamente.
    mov ah,[bx+2]
    mov byte [buftemp],ah
    mov ah,[bx+3]
    mov byte [buftemp+1],ah
    mov ah,[bx+4]
    mov byte [buftemp+2],ah
    
    ;Retorno
    ret

tres_to_cinco:
    ; Entradas: direccion del Buffer de 3 Bytes que se quiere convertir a 5 Bytes (para impresión)
    ; Salidas: Almacena en temp_r el resultado (max 5 bytes)
    ; Restricciones: El buffer de entrada debe tener datos en la posición 1 y 2 para valores enteros
    ; y en la posición 3 para valores decimales; y la respuesta tiene de salida es de 5 bytes

    ;Almacena en los 3 ultimos bytes de temp_r los valores de las posiciones 1,2 y 3 del buffer de entrada respectivamente.
    
    ;primeros dos bytes en 0
    mov byte [temp_r],0
    mov byte [temp_r+1],0
    
    ;ultimos 3 bytes con datos del buffer de entrada
    mov ah,[bx]
    mov byte [temp_r+2],ah
    mov ah,[bx+1]
    mov byte [temp_r+3],ah
    mov ah,[bx+2]
    mov byte [temp_r+4],ah
    
    ;Retorno
    ret
