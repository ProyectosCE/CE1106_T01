
section .data
    square db 'Escogiste, cuadrado', 0 
    circle db 'Escogiste, circulo', 0

section .bss
    input_buffer resb 100  ; Reserva 100 bytes para almacenar la entrada del usuario

section .text
    global _start

_start:
    ; sys_read (stdin = 0, buffer = input_buffer, length = 100)
    mov eax, 3                 ; Número de syscall para sys_read
    mov ebx, 0                 ; File descriptor 0 (stdin)
    mov ecx, input_buffer      ; Dirección del buffer
    mov edx, 100               ; Tamaño del buffer
    int 0x80                   ; Llamada al kernel

    ; sys_write (stdout = 1, buffer = input_buffer, length = number_of_bytes_read)
    mov eax, 4                 ; Número de syscall para sys_write
    mov ebx, 1                 ; File descriptor 1 (stdout)
    mov ecx, input_buffer      ; Dirección del buffer
    mov edx, 100               ; Longitud de la entrada a imprimir
    int 0x80                   ; Llamada al kernel

    ; sys_exit (status = 0)
    mov eax, 1                 ; Número de syscall para sys_exit
    xor ebx, ebx               ; Código de salida 0
    int 0x80                   ; Llamada al kernel

case_Squre: ;funcion si el input corresponde a un cuadrado

