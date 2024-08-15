
section .data
    square db 'Escogiste, cuadrado', 0
    circle db 'Escogiste, circulo', 0
    default_ms db 'Escogiste,otra cosa',0

section .bss
    input_buffer resb 100  ; Reserva 100 bytes para almacenar la entrada del usuario

section .text
    global _start


_start:
    mov eax, 3
    mov ebx, 0                 ; File descriptor 1 (stdin)
    mov ecx, input_buffer      ; Dirección del buffer
    mov edx, 1               ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel

    ; mueve el input al AL 
    mov al, [input_buffer]

    ;switch -cases
    cmp al, 'A' ;si el input es A 
    je case_Squre ;ejecuta el cuadrado
    cmp al, 'B' ;si el input es B
    je case_circle ;ejecuta el circulo
    jmp default_case ;si no coincide con ninguno, ejecuta el default





case_Squre: ;funcion si el input corresponde a un cuadrado
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1                 ; File descriptor 1 (stdout)
    mov ecx, square           ; Dirección del buffer
    mov edx, 11               ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel
    jmp done ; si no coincide con


case_circle: ;funcion si el input corresponde a un circulo
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1                 ; File descriptor 1 (stdout)
    mov ecx, circle           ; Dirección del buffer
    mov edx, 12               ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel

    mov eax, 1
    xor ebx, ebx               ; Código de salida 0
    int 0x80                   ; Llamada al kernel
    jmp done

default_case:
    mov eax, 4
    mov ebx, 1
    mov ecx, default_ms
    mov edx, 12               ; Longitud de la entrada a imprimir
    int 0x80

done:
    mov eax, 1
    xor ebx, ebx               ; Código de salida 0
    int 0x80                   ; Llamada al kernel