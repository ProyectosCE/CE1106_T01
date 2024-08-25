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
    add BYTE [bx+3],al
    adc ah,0
    ADD BYTE [bx+2],ah
    ADC [bx],dx
    ;VERIFICADO

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
    add byte [bx+4],dl
    PUSH AX
    XOR AX,AX
    mov al,[bx+4]
    div Cl
    MOV byte [bx+4],ah
    mov ch,al
    POP AX
    add al,ch
    ADD BYTE [bx+3],al
    adc ah,0
    add byte [bx+2],ah
    adc byte [bx],0
    ;VERIFICADO
    
    
    ;parte decimal del input parte entera de lados
    mov bx,[operando1] 
    mov ax,[bx+2]
    xor bx,bx
    MOV AH,0
    mov bx, [operando2]
    mov bx,[bx]
    mul bx
    mov cx,100
    div Cl
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
    add [bx+2],AX
    adc CH,0
    ADD BYTE [bx+1],ch
    adc byte [bx],0
    ;VERIFICADO
    
    
    ;para ambos decimales
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
    adc word [bx],0
    ;VERIFICADO
    ;retorna
    ret