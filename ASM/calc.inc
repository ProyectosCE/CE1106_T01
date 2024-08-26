multiplicacion:

    ; ESTE METODO RECIBE UN BUFFER DE MAXIMO DE 3 BYTES (2 para enteros y 1 para decimales)
    ; DEVUELVE UNA SALIDA DE 5 BYTES

    ; // MULTIPLICACION DE PARTE ENTERA-ENTERA
    mov bx,[operando1] 
    mov ax,[bx]
    xor bx,bx
    mov bx, [operando2]
    mov bx,[bx]
    mul bx
    ;guardar resultado
    mov bx,[respuesta]
    MOV [bx+3],AL
    MOV [bx+2],AH
    MOV [bX+1],dl
    MOV [bx],dh
    ;VERIFICADO 24-08-24 23:53

    ; // MULTIPLICACION DE PARTE ENTERA-DECIMAL
    mov bx,[operando1] 
    mov ax,[bx]
    xor bx,bx
    mov bx, [operando2]
    mov bx,[bx+2]
    mul bx
    mov cx,100
    div cx
    ;guardar resultado
    mov bx,[respuesta]
    add [bx+4],dl
    PUSH AX
    XOR AX,AX
    mov al,[bx+4]
    div Cl
    MOV byte [bx+4],ah
    mov ch,al
    POP AX
    XOR DX,DX
    add al,ch
    MOV CL,[bx+3]
    ADD CL,AL
    MOV [BX+3],CL
    ADC AH,0
    ADD [bx+2],AH
    ADC DL,0
    ADD [bX+1],dl
    ADC DH,0
    ADD [bx],dh
    ;VERIFICADO 25-08-24 03:28
    
    
    ; // MULTIPLICACION DE PARTE DECIMAL-ENTERA
    mov bx,[operando1] 
    mov ax,[bx+2]
    xor bx,bx
    MOV AH,0
    mov bx, [operando2]
    mov bx,[bx]
    mul bx
    mov cx,100
    div CX
    mov bx,[respuesta]
    add BYTE [bx+4],dl
    PUSH AX
    XOR AX,AX
    mov al,[bx+4]
    div CL
    mov byte [bx+4],ah
    mov ch,al
    POP AX
    MOV CH,0
    ADD BYTE [bx+3],AL
    ADC AH,0
    ADD BYTE [bx+2],AH
    adc CH,0
    ADD BYTE [bx+1],ch
    adc byte [bx],0
    ;VERIFICADO 25-08-24 03:28
    
    ; // MULTIPLICACION DE PARTE DECIMAL-DECIMAL
    mov bx,[operando1] 
    mov al,[bx+2]
    xor bx,bx
    MOV AH,0
    mov bx, [operando2]
    mov bl,[bx+2]
    mul bl
    mov cx,100
    div cl
    ;guardar resultado
    mov bx,[respuesta]
    add BYTE [bx+4],al
    XOR AX,AX
    mov al,[bx+4]
    div cL
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
    ;retorna
    ret

division:
    jmp done
    
cinco_to_tres:
    mov byte [buftemp],[bx+2]
    mov byte [buftemp+1],[bx+3]
    ret