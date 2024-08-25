multiplicacion:
    ;partes enteras
    mov ax,[dato_01] ;cambiar para usar con BX buffer dinamico para que la formula sea universal
    ;implementar uso de pila, push BX aqui
    xor bx,bx
    mov bl, [lados]
    mul bx
    ;guardar resultado
    add BYTE [peri_r+2],al
    adc ah,0
    ADD BYTE [peri_r+1],ah
    ADC BYTE [peri_r],dl
    ;VERIFICADO

    ;parte entera del input por parte decimal de lados
    ;pop BX aqui
    mov ax,[dato_01]
    xor bx,bx
    mov bl, [lados+1]
    mul bx
    mov cx,100
    div cx
    ;guardar resultado
    add byte [peri_r+3],dl
    PUSH AX
    XOR AX,AX
    mov al,[peri_r+3]
    div Cl
    MOV byte [peri_r+3],ah
    mov ch,al
    POP AX
    add al,ch
    ADD BYTE [peri_r+2],al
    adc ah,0
    add byte [peri_r+1],ah
    adc byte [peri_r],0
    ;VERIFICADO
    
    
    ;parte decimal del input parte entera de lados
    mov al,[dato_01+2]
    xor bx,bx
    MOV AH,0
    mov bl,[lados]
    mul bl
    mov cx,100
    div Cl
    add BYTE [peri_r+3],ah
    PUSH AX
    XOR AX,AX
    mov al,[peri_r+3]
    div CL
    mov byte [peri_r+3],ah
    mov ch,al
    POP AX
    add al,ch
    MOV CH,0
    add BYTE [peri_r+2],AL
    adc CH,0
    ADD BYTE [peri_r+1],ch
    adc byte [peri_r],0
    ;VERIFICADO
    
    
    ;para ambos decimales
    mov al,[dato_01+2]
    xor bx,bx
    MOV AH,0
    mov bl,[lados+1]
    mul bl
    mov cx,100
    div cl
    ;guardar resultado
    add BYTE [peri_r+3],al
    XOR AX,AX
    mov al,[peri_r+3]
    div cL
    mov byte [peri_r+3],ah
    MOV AH,0
    add BYTE [peri_r+2],AL
    ADC ah,0
    ADD BYTE [peri_r+1],ah
    adc byte [peri_r],0
    ;VERIFICADO
    ;retorna
    ret