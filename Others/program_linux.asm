
section .data
    default_ms db 'otras cosa',0x0A,0
    initial_msg db 'Quieres iniciar [Y/N]',0x0A,0  
    askn_msg db 'Escoge una figura',0x0A,0
    square db '1.square',0x0A ,0
    circle db '2.circle',0x0A, 0
    triangle db '3.trianle',0x0A, 0
    diamond db '4.diamond',0x0A, 0
    pentagon db '5.pentagon',0x0A, 0
    hexagon db '6.hexagon',0x0A, 0
    trapeze db '7.trapeze',0x0A, 0
    parallelogram db '8.parallelogram', 0x0A, 0
    square_msg db 'cuando mide el lado?' , 0x0A, 0



    

section .bss
    input_buffer resb 2  ; Reserva 2 bytes para la primera entrada
    second_input resb 2 ; Reserva 2 bytes para la segunda entrada, donde decide que figura quiera
    buffer_lado_square resb 100 ;reserva 100 bytes para la medida de los lados del cuadrado

section .text
    global _start


_start:
    jmp initial_case ;va a preguntar si quiere calcular algo o no




initial_case: ;caso donde pregunta si desea iniciar
    mov eax, 4
    mov ebx, 1
    mov ecx, initial_msg
    mov edx, 22               ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel
    jmp initial_ask_case ; con esta funcion se va a comprar el input del usuario


initial_ask_case:
    mov eax, 3             ; Número de syscall para sys_write
    mov ebx, 0               ; File descriptor 1 (stdout)
    mov ecx, input_buffer   ;mueve la direccion del input
    mov edx, 2              ;longitud de la respuesta
    int 0x80                
    mov al,[input_buffer]    ;mueve el contenido a al 

    cmp al, 'Y' ;compara la respuesta
    je case_show_figures ;si, si se va a preguntar cual pregunta
    cmp al, 'N' ; compara la respuesta 
    je done ; ;si, no di ni modo pipipi
    jmp default_case ;si ninguna, salta a la acepcion 



case_show_figures
    ;aqui va a imprimir cuadrado
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1                 ; File descriptor 1 (stdout)
    mov ecx, square
    mov edx, 9        ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel

    ;aqui va a imprimir circulo
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1
    mov ecx, circle
    mov edx, 9             ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel

    ;aqui va a imprimir triangulo
    mov eax, 4   
    mov ebx, 1              ; Número de syscall para sys_write
    mov ecx, triangle
    mov edx, 11             ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel

    ;aqui va a imprimir diamond
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1
    mov ecx, diamond
    mov edx, 10             ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel
    
    ;aqui va a imprimir pentagon
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1
    mov ecx, pentagon
    mov edx, 11             ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel


    ;aqui va a imprimir hexagon
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1
    mov ecx, hexagon
    mov edx, 10             ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel
    
    ;aqui va a imprimir trapeze
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1
    mov ecx, trapeze
    mov edx, 10             ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel

    ;aqui va a imprimir parallelogram
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1
    mov ecx, parallelogram
    mov edx, 16             ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel
    
    jmp figure_ask_case ; termina


figure_ask_case: ;pregunta que figura quiere y espepera un input
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1
    mov ecx, askn_msg
    mov edx, 18               ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel

    mov eax, 3             ; Número de syscall para sys_write
    mov ebx, 0               ; File descriptor 1 (stdout)
    mov ecx, second_input ;mueve la direccion del input
    mov edx, 2             ;longitud de la respuesta
    int 0x80                 ; Llamada al kernel


    mov al, [second_input]
    cmp al, '1'
    je case_Squre ; si, es un cuadrado
    cmp al, '2'
    je case_circle ; si, es un circulo
    jmp done





case_Squre: ;funcion si el input corresponde a un cuadrado

    ;pregunta cuando mide el lado del cuadrado
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1                 ; File descriptor 1 (stdout)
    mov ecx, square_msg           ; Dirección del buffer
    mov edx, 21           ; Longitud de la entrada a imprimir
    int 0x80                 ; Llamada al kernel

    ;aqui va a extraer el input

    mov eax, 3             ; Número de syscall para sys_read
    mov ebx, 0               ; File descriptor 0 (stdin)
    mov ecx, buffer_lado_square   ;mueve la direccion del input
    mov edx, 23             ;longitud de la entrada
    int 0x80                 ; Llamada al kernel

    jmp done
    


case_circle: ;funcion si el input corresponde a un circulo
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1                 ; File descriptor 1 (stdout)
    mov ecx, circle           ; Dirección del buffer
    mov edx, 9             ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel

    mov eax, 1
    xor ebx, ebx               ; Código de salida 0
    int 0x80                   ; Llamada al kernel
    jmp done                    ;termina

default_case:
    mov eax, 4
    mov ebx, 1
    mov ecx, default_ms
    mov edx, 9               ; Longitud de la entrada a imprimir
    int 0x80
    jmp done

done:
    mov eax, 1
    xor ebx, ebx               ; Código de salida 0
    int 0x80                   ; Llamada al kernel