case_circle:

    mov ax,7AA7H
    mov bl,61h
    mov [dato_01],ax
    mov [dato_01+2],bl
    mov ax,270fh
    mov bl, 63h
    mov [dato_02],ax
    mov [dato_02+2],bl

    mov word [operando1],dato_01
    mov word [operando2],dato_02
    mov word [respuesta],peri_r
    
    Call multiplicacion
    
    ; //  DEBUG  //
    MOV AH,[peri_r]
    MOV AL,[peri_r+1]
    MOV BH,[peri_r+2]
    MOV BL,[peri_r+3]
    MOV CH,[peri_r+4]
    INT 3
    ; Imprime mensaje de círculo y sale
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [circle]  ; Carga la dirección del mensaje de círculo en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena
    jmp done  ; Salta a terminar el programa