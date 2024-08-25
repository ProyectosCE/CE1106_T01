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

;basado el el codigo del usuario de stackoverflow @rcgldr 
;recuperado de https://stackoverflow.com/a/41501934/26912080
convert_entero:
    ; Cargar la parte más significativa 
    mov ax, [peri_r]              ; Cargar los primeros 2 bytes (parte más significativa)
    mov bx, [peri_r+2]
    int 3            ; Cargar los últimos 2 bytes (parte menos significativa)
    or ax, bx                 ; Realizar una operación lógica OR para verificar si ambos son 0
    jz print_loop         ; Si ambos son 0, saltar a imprimir los resultados

    ; Si no son 0, continuar la división
    mov ax, [peri_r]
    xor dx, dx                ; Limpiar DX antes de la división
    mov cx, 10                ; Divisor (decimal)
    div cx                    ; Dividir DX:AX por 10, AX = cociente, DX = residuo

    ; Almacenar el cociente y residuo
    mov [peri_r], ax              ; Guardar el cociente en los primeros 2 bytes de peri_r                   ; Guardar el residuo en la pila

    ; Repetir con la parte menos significativa
    mov ax, [peri_r+2]            ; Cargar los bytes menos significativos en AX                ; Limpiar DX antes de la división
    div cx                    ; Dividir DX:AX por 10

    ; Almacenar el cociente y residuo
    mov [peri_r+2], ax            ; Guardar el cociente en los últimos 2 bytes de peri_r
    push dx                   ; Guardar el residuo en la pila

    jmp convert_entero         ; Repetir el ciclo

print_loop:
    pop dx
    int 3                    ; Sacar el residuo de la pila
    add dl, '0'               ; Convertir el residuo a carácter ASCII
    mov ah, 02h               ; Función DOS para imprimir un carácter
    int 21h                   ; Imprimir el carácter
    cmp sp, 0xFFFE            ; Verificar si la pila está vacía (valor inicial de SP en DOS)
    jne print_loop            ; Repetir si aún hay valores en la pila
