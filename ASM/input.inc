lectura: ;lee cualquier entrada segun se requiera en el buffer_text de máximo 8 caracteres (7 de entrada y el enter)
    mov byte [buffer_text],8
    mov ah, 0Ah
    lea dx,[buffer_text]
    int 21h
    ret

procesar_entero:
    mov dx,0
    mov dl, [buffer_text+si+2]
    mov ax,0
    call check_digit
    inc si
    cmp dl,'.'
    je fin_procesar_entero
    sub dl, '0'
    call add_digit_entero
    loop procesar_entero
    ret

procesar_decimal:
    mov dl, [buffer_text+si+2]
    call check_digit
    sub dl, '0'
    inc si
    call add_digit_decimal
    loop procesar_decimal
    ret

fin_procesar_entero:
    dec cx
    call procesar_decimal
    ret

add_digit_entero:
    ; Multiplicar bufnum por 10 usando bucle
    PUSH CX
    PUSH DX
    mov CX, 10
    mov AX, [bx]
    mul CX
    POP DX
    add ax,dx
    cmp ax,9999
    ja error
    mov [bx], AX
    POP CX
    ret

add_digit_decimal:
    ; Multiplicar bufnum por 10 usando bucle
    PUSH CX
    mov CL, 10
    mov al, [bx+2]
    mul cl
    add al,dl
    mov [bx+2], al
    POP CX
    ret
; Subrutina check_digit
check_digit:
    cmp dl, '0'             ; Comparar DL con 0 (ya que restaste '0')
    jb check_point                  ; Si es menor que 0, es un error (no es un número)
    cmp dl, '9'                ; Comparar DL con 9
    ja error                ; Si es mayor que 9, verificar si es un punto
    ret                      ; Retornar de la subrutina

check_point:
    cmp dl, '.'             ; Comparar con el carácter punto '.'
    jne error                ; Si no es un punto, es un error
    ret                      ; Retornar de la subrutina
       ; Llamar a la rutina de manejo de errores
error:
    JMP done 
