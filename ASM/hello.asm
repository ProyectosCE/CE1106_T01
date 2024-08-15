
section .data
    square db 'cuadrado', 0
    circle db 'circulo', 0
    default_ms db 'otras cosa',0
    initial_msg db 'Quieres iniciar [Y/N]'

section .bss
    input_buffer resb 100  ; Reserva 100 bytes para almacenar la entrada del usuario

section .text
    global _start


_start:
    jmp initial_case ;va a preguntar si quiere calcular algo o no



ask_case:
    mov eax, 3             ; Número de syscall para sys_write
    mov ebx, 0               ; File descriptor 1 (stdout)
    mov ecx, input_buffer   ;mueve la direccion del input
    mov edx, 1              ;longitud de la respuesta
    int 0x80                
    mov al,[input_buffer]    ;mueve el contenido a al 

    cmp al, 'Y' ;compara la respuesta
    je case_show_figures ;si, si se va a preguntar cual pregunta
    cmp al, 'N' ; compara la respuesta 
    je done ; ;si, no di ni modo pipipi
    jmp default_case ;si ninguna, salta a la acepcion 



case_show_figures:
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1                 ; File descriptor 1 (stdout)
    mov ecx, square
    mov edx, 8              ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel
    jmp done               ;termina





initial_case: ;caso donde pregunta si desea iniciar
    mov eax, 4
    mov ebx, 1
    mov ecx, initial_msg
    mov edx, 22               ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel
    jmp ask_case ; con esta funcion se va a comprar el input del usuario


case_Squre: ;funcion si el input corresponde a un cuadrado
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1                 ; File descriptor 1 (stdout)
    mov ecx, square           ; Dirección del buffer
    mov edx, 8              ; Longitud de la entrada a imprimir
    int 0x80                 ; Llamada al kernel
    jmp done ; termina


case_circle: ;funcion si el input corresponde a un circulo
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1                 ; File descriptor 1 (stdout)
    mov ecx, circle           ; Dirección del buffer
    mov edx, 6             ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel

    mov eax, 1
    xor ebx, ebx               ; Código de salida 0
    int 0x80                   ; Llamada al kernel
    jmp done                    ;termina

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