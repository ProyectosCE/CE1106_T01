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
    jne check_comma                ; Si no es un punto, es un error
    ret                      ; Retornar de la subrutina
    
check_comma:
    cmp dl, ','
    jne error
    ret   
    
; Llamar a la rutina de manejo de errores
error:
    JMP done 

;basado el el codigo del usuario de stackoverflow @rcgldr 
;recuperado de https://stackoverflow.com/a/41501934/26912080

imprimir_resp:
    xor dx,dx
    mov dl,'$'
    push dx
    mov dl, 10
    push dx
    jmp decimal_pila
    
decimal_pila:
    mov ah,0
    mov al,[bx+4]
    mov cl, 10
    div cl
    xor dx,dx
    mov dl, ah
    add dl,'0'
    push dx
    mov dl, al
    add dl, '0'
    push dx
    mov al,','
    mov dl,al
    push dx
    jmp convert_entero

convert_entero:
    ; Cargar la parte más significativa 
    mov ax, [bx]              ; Cargar los primeros 2 bytes (parte más significativa)
    mov cx, [bx+2]           ; Cargar los últimos 2 bytes (parte menos significativa)
    or ax, cx                ; Realizar una operación lógica OR para verificar si ambos son 0
    jz print_loop         ; Si ambos son 0, saltar a imprimir los resultados
    ; Si no son 0, continuar la división
    mov ah, [bx]
    mov al, [bx+1]
    xor dx, dx                ; Limpiar DX antes de la división
    mov cx, 10                ; Divisor (decimal)
    div cx           ; Dividir DX:AX por 10, AX = cociente, DX = residuo
    ; Almacenar el cociente y residuo
    mov [bx], ah              ; Guardar el cociente en los primeros 2 bytes de               
    mov [bx+1], al
    ; Repetir con la parte menos significativa
    mov ah, [bx+2]
    mov al, [bx+3]       ; Cargar los bytes menos significativos en AX
    div cx                    ; Dividir DX:AX por 10

    ; Almacenar el cociente y residuo
    mov [bx+2], ah   ; Guardar el cociente en los últimos 2 bytes
    mov [bx+3], al
    add dl,'0'          
    push dx                   ; Guardar el residuo en la pila

    jmp convert_entero         ; Repetir el ciclo

print_loop:
    pop dx
    cmp dl, '$'            ; Verificar si la pila está vacía (valor inicial de SP en DOS)
    je done_imp                ; Sacar el residuo de la pila               ; Convertir el residuo a carácter ASCII
    mov ah, 02h               ; Función DOS para imprimir un carácter
    int 21h                   ; Imprimir el carácter
    jmp print_loop  
                ; Repetir si aún hay valores en la pila
done_imp:
    ret