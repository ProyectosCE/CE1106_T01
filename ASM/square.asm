org 100h
section .data
    square_msg db 0x0A,'Cuando mide el lado?',0x09,'', 0x0D, 0x0A, '$'  ; Pregunta para el cuadrado
    result_peri db 0x0A, 'el perimetro es: ',0x09,'', 0x0D, 0x0A, '$' 

    ;aqui va la cantidad de lados de cada figura lo necesario para calcular el perimetro
    


section .bss
    input_buffer resb 2  ; Reserva 2 bytes para la primera entrada del usuario
    second_input resb 2  ; Reserva 2 bytes para la segunda entrada, donde se elige la figura
    buffer_lado_square resb 100 ; maxima entrada del input
    buffer_para_entero resb 8
    buffer_peque resb 2


section .text
    global _start  ; Declaración global del punto de entrada

_start:
    jmp case_square  ; Salta a la sección que pregunta si desea iniciar


case_square:
    ; Pregunta sobre el lado del cuadrado
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [square_msg]  ; Carga la dirección del mensaje de consulta del lado del cuadrado en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena
    
    mov byte [buffer_lado_square],100
    mov byte [buffer_lado_square+1],0

    ; Leer el lado del cuadrado (suponiendo una entrada numérica)
    mov ah, 0Ah  ; Función de MS-DOS para leer cadena
    lea dx, [buffer_lado_square]  ; Carga la dirección del buffer donde se almacenará la entrada del lado del cuadrado
    int 21h  ; Interrupción de MS-DOS para leer cadena
    jmp result_msg


result_msg:
    mov ah,09h
    lea dx, [result_peri]
    int 21h
    jmp input_to_ax

done:
    ; Termina el programa y vuelve a MS-DOS
    mov ah, 4Ch  ; Función de MS-DOS para terminar el programa
    int 21h  ; Interrupción de MS-DOS para salir

input_to_ax: ;este paso es para un ciclo 
    xor ax, ax
    xor bx, bx    
    xor cx,cx
    mov cl, [buffer_lado_square+1]
    lea si, [buffer_lado_square+2]  ; Mueve fuera del bucle 
    ;call restricciones
    xor ax, ax
    xor bx, bx    
    xor cx,cx
    mov cl, [buffer_lado_square+1]
    lea si, [buffer_lado_square+2]  ; Mueve fuera del bucle
    jmp loop_convertidor
    
    
restricciones: ;verifica que la entrda solo sean numeros:
    mov dx, 0                       ; Asegura que DX esté en 0
    mov dl, [si]                    ; Lee el valor en DL
    sub dx, '0'
    cmp dl,9
    jg case_square
    cmp dl,0
    jl case_square                     ; Convierte de ASCII a valor numérico                      ; Preparación para multiplicación por 10 
    cmp cx, 1                    ; Añade el dígito convertido al acumulador                           ; Multiplica AX por 10 (AX = AX * 10)
    inc si                     ; Mueve al siguiente carácte
    loop restricciones
    ret 
    

loop_convertidor:
    mov dx, 0                       ; Asegura que DX esté en 
    mov dl, [si]
    cmp dl, 46
    je separacion                    ; Lee el valor en DL
    sub dx, '0'                     ; Convierte de ASCII a valor numérico
    mov bx, 10                      ; Preparación para multiplicación por 10 
    add ax, dx
    cmp cx, 1
    je  calculos
    inc si
    mov dl, [si]
    cmp dl,46
    je separacion                    ; Añade el dígito convertido al acumulador  
    mul bx                          ; Multiplica AX por 10 (AX = AX * 10)
                         ; Mueve al siguiente carácte
    loop loop_convertidor 
    jmp calculos   

calculos:
    mov bx, 4
    mul bx
    mov bx,100
    div bx
    mov [buffer_para_entero+4],dx
    mov [buffer_peque],ax
    mov ax, [buffer_para_entero]
    mov bx, 4
    mul bx
    add ax, [buffer_peque]
    mov [buffer_para_entero],ax
    mov ax, [buffer_para_entero+4]
    jmp from_ax_db
           
           
 
separacion:
    inc si
    dec cx
    dec cx
    mov [buffer_para_entero], ax
    xor ax, ax
    xor dx,dx
    jmp loop_convertidor 


from_ax_db:
    xor dx,dx
    mov bx, 10
    div bx
    add dx, '0'
    push dx
    inc cx
    cmp ax, 0
    jne from_ax_db
    jmp clean_to_dec 
    
clean_to_dec:
    push 46
    xor ax,ax
    mov ax, [buffer_para_entero]
    jmp from_ax_db_dec

from_ax_db_dec:
    xor dx,dx
    mov bx, 10
    div bx
    add dx, '0'
    push dx
    inc cx
    cmp ax, 0
    jne from_ax_db_dec
    jmp imprimir_digitos

   

imprimir_digitos:
    mov ah, 02h
    pop dx
    int 21h
    loop imprimir_digitos
    jmp done