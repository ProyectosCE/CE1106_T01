multiplicacion:

    ; ESTE METODO RECIBE UN BUFFER DE MAXIMO DE 3 BYTES (2 para enteros y 1 para decimales)
    ; DEVUELVE UNA SALIDA DE 5 BYTES

    ; // MULTIPLICACION DE PARTE ENTERA-ENTERA
    mov bx,[operando1] 
    mov AH,[bx]
    mov AL,[bx+1]
    xor bx,bx
    mov bx, [operando2]
    mov CH,[bx]
    mov CL,[bx+1]
    mul CX
    ;guardar resultado
    mov bx,[respuesta]
    MOV [bx+3],AL
    MOV [bx+2],AH
    MOV [bX+1],dl
    MOV [bx],dh
    ;VERIFICADO 24-08-24 23:53 por @alexmv235
    ;REVERIFICADO 26-08-24 00:13 por @alexmv235

    ; // MULTIPLICACION DE PARTE ENTERA-DECIMAL
    mov bx,[operando1] 
    mov AH,[bx]
    mov AL,[bx+1]
    xor bx,bx
    mov bx, [operando2]
    mov CH,0
    mov CL,[bx+2]
    mul CX
    mov BX,100
    div BX
    ;guardar resultado
    mov bx,[respuesta]
    add [bx+4],dl
    PUSH AX
    XOR AX,AX
    mov al,[bx+4]
    MOV CH,0
    MOV CL,100
    DIV CL
    MOV byte [bx+4],ah
    mov ch,al
    POP AX
    XOR DX,DX
    ADD CH,AL
    ADD BYTE [bx+3],CH
    ADC AH,0
    ADD [bx+2],AH
    ADC DL,0
    ADD [bX+1],dl
    ADC DH,0
    ADD [bx],dh
    ;VERIFICADO 25-08-24 03:28
    ;REVERIFICADO 26-08-24 00:35 por @alexmv235
    
    
    ; // MULTIPLICACION DE PARTE DECIMAL-ENTERA
    mov bx,[operando1]
    MOV AH,0 
    mov AL,[bx+2]
    xor bx,bx
    xor CX,CX
    MOV AH,0
    mov bx, [operando2]
    mov CH,[bx]
    mov CL,[bx+1]
    mul CX
    mov BX,100
    div BX
    mov bx,[respuesta]
    add BYTE [bx+4],dl
    PUSH AX
    XOR AX,AX
    mov al,[bx+4]
    MOV CX,0
    MOV CL,100
    div CL
    mov byte [bx+4],ah
    mov ch,al
    POP AX
    add al,ch
    mov ch,0
    ADD BYTE [bx+3],AL
    ADC AH,0
    ADD BYTE [bx+2],AH
    adc CH,0
    ADD BYTE [bx+1],ch
    adc byte [bx],0
    ;VERIFICADO 25-08-24 03:28
    ;REVERIFICADO 26-08-24 00:39 por @alexmv235
    
    ; // MULTIPLICACION DE PARTE DECIMAL-DECIMAL
    mov bx,[operando1] 
    MOV AH,0
    mov al,[bx+2]
    xor bx,bx
    mov bx, [operando2]
    MOV ch,0
    mov CL,[bx+2]
    mul CL
    mov BX,100
    div BL
    ;guardar resultado
    mov bx,[respuesta]
    add BYTE [bx+4],al
    XOR AX,AX
    mov al,[bx+4]
    MOV CX,0
    MOV CL,100
    DIV CL
    mov byte [bx+4],ah
    MOV AH,0
    add BYTE [bx+3],AL
    ADC ah,0
    ADD BYTE [bx+2],ah
    MOV AX,0
    adc AL,0
    ADD BYTE [bx+1],al
    ADC AH,0
    adc byte [bx],AH
    ;VERIFICADO 25-08-24 03:28
    ;REVERIFICADO 26-08-24 00:46 por @alexmv235
    ;retorna
    ret

division:
    jmp done

cinco_to_tres:
    mov ah,[bx+2]
    mov byte [buftemp],ah
    mov ah,[bx+3]
    mov byte [buftemp+1],ah
    mov ah,[bx+4]
    mov byte [buftemp+2],ah
    ret