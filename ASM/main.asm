org 100h

section .data
    default_ms db 'Otras cosas', 0x09,'',0x0D, 0x0A, '$'  ; Mensaje por defecto
    initial_msg db 'Quieres iniciar [Y/N]',0x09,'', 0x0D, 0x0A, '$'  ; Mensaje inicial que pregunta si se desea iniciar
    askn_msg db 0x0A,'Escoge una figura:',0x09,'', 0x0D, 0x0A, '$'  ; Mensaje que pide al usuario que escoja una figura
    square db 0x0A,'1. Square',0x09,'', 0x0D, 0x0A, '$'  ; Opción para cuadrado
    circle db '2. Circle',0x09,'', 0x0D, 0x0A, '$'  ; Opción para círculo
    triangle db '3. Triangle',0x09,'', 0x0D, 0x0A, '$'  ; Opción para triángulo
    diamond db '4. Diamond',0x09,'', 0x0D, 0x0A, '$'  ; Opción para diamante
    pentagon db '5. Pentagon',0x09,'', 0x0D, 0x0A, '$'  ; Opción para pentágono
    hexagon db '6. Hexagon',0x09,'', 0x0D, 0x0A, '$'  ; Opción para hexágono
    trapeze db '7. Trapeze',0x09,'', 0x0D, 0x0A, '$'  ; Opción para trapecio
    parallelogram db '8. Parallelogram',0x09,'', 0x0D, 0x0A, '$'  ; Opción para paralelogramo
    square_msg db 0x0A,'Cuando mide el lado?',0x09,'', 0x0D, 0x0A, '$'  ; Pregunta para el cuadrado
    result_peri db 0x0A, 'el perimetro es: ',0x09,'', 0x0D, 0x0A, '$' 

    ;aqui va la cantidad de lados de cada figura lo necesario para calcular el perimetro

    square_sides db 0x04
    triangle_sides db 0x03
    diamond_sides db 0x04
    pentagon_sides db 0x05
    hexagon_sides dw 0x06

    ;CONSTANTES
    pi_val db 0x013A
    raiz_tres db 0xAD
    


section .bss
    input_buffer resb 2  ; Reserva 2 bytes para la primera entrada del usuario
    second_input resb 2  ; Reserva 2 bytes para la segunda entrada, donde se elige la figura
    
    
    
    buffer_text resb 10 ; maxima entrada del input (7 máx y 2 bytes de control)
    
 
    dato_01 resb 3 ;dato Numerico para input 1
    dato_02 resb 3 ;dato Numerico para input 2
    dato_03 resb 3 ;dato Numerico para input 3
    dato_lista resw 3  ;buffer lista de las direcciones de los buffer de datos

    lados resb 2

    peri_r resb 4 ;para cualquier figura maximo FFFF FFFF
    area_r resb 7 ;para cualquier valor, maximo el circulo 0F FFFF FFFF FFFF
    
section .text
    global _start  ; Declaración global del punto de entrada

_start:
    jmp initial_case  ; Salta a la sección que pregunta si desea iniciar

initial_case:
    ;inicializar las direcciones de la lista
    mov byte [dato_01],0x0000
    mov word [dato_lista],dato_01
    mov word [dato_lista+2],dato_02
    mov word [dato_lista+2],dato_03

    ; Imprime el mensaje inicial preguntando si quiere iniciar
    mov ah, 09h  
    lea dx, [initial_msg]  
    int 21h  
    ; Leer respuesta del usuario (Y/N)
    mov ah, 01h  
    int 21h  
    cmp al, 'Y'  ; Compara la entrada con 'Y' (mayúscula)
    je case_show_figures  ; Si es 'Y', salta a mostrar las figuras
    cmp al, 'N'  ; Compara la entrada con 'N' (mayúscula)
    je done  ; Si es 'N', termina el programa
    jmp default_case  ; Si no es ni 'Y' ni 'N', salta al caso por defecto

case_show_figures:
    ; Imprime las opciones de figuras disponibles
    mov ah, 09h 
    lea dx, [square]
    int 21h 

    lea dx, [circle]  
    int 21h 

    lea dx, [triangle]  
    int 21h  

    lea dx, [diamond]  
    int 21h  

    lea dx, [pentagon] 
    int 21h  

    lea dx, [hexagon]  
    int 21h  

    lea dx, [trapeze]  
    int 21h  

    lea dx, [parallelogram]  
    int 21h  

    ; Pregunta qué figura quiere el usuario
    lea dx, [askn_msg]  
    mov ah, 09h  
    int 21h 

    ; Leer elección del usuario (1-8)
    mov ah, 01h  
    int 21h 
    cmp al, '1'  
    je case_square  
    cmp al, '2'  
    je case_circle 
    jmp done 

case_square:
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [square_msg]  ; Carga la dirección del mensaje de consulta del lado del cuadrado en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena

    call lectura
    mov si,0
    mov cx,[buffer_text+1]
    mov ch,0
    mov bx, [dato_lista]
    call procesar_entero
    mov byte [lados],4
    mov byte [lados+1],00
    call perimetro
    ;DEBUG
    MOV AH,[peri_r]
    MOV AL,[peri_r+1]
    MOV BH,[peri_r+2]
    MOV BL,[peri_r+3]
    INT 3
    
    

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

;calculo de perimetro
perimetro:
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

case_circle:
    ; Imprime mensaje de círculo y sale
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [circle]  ; Carga la dirección del mensaje de círculo en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena
    jmp done  ; Salta a terminar el programa

default_case:
    ; Mensaje por defecto en caso de entrada inválida
    mov ah, 09h  ; Función de MS-DOS para imprimir cadena
    lea dx, [default_ms]  ; Carga la dirección del mensaje por defecto en dx
    int 21h  ; Interrupción de MS-DOS para imprimir cadena
    jmp initial_case  ; Salta a terminar el programa

done:
    ; Termina el programa y vuelve a MS-DOS
    mov ah, 4Ch  ; Función de MS-DOS para terminar el programa
    INT 3
    int 21h  ; Interrupción de MS-DOS para salir


print_digitos:
    mov ah , 02h
    pop dx
    int 21h
    loop print_digitos

; Inicializar puntero al buffer
mov si, offset peri_r

; Inicializar registros para la parte entera
xor ax, ax             ; Limpiar AX
xor bx, bx             ; Limpiar BX
xor dx, dx             ; Limpiar DX

; Cargar los 4 bytes de la parte entera en DX:AX:BX
mov dx, [si]           ; Cargar B1 (byte más significativo) en DX
mov ax, [si+2]         ; Cargar B2 y B3 en AX
mov bx, [si+4]         ; Cargar B4 (byte menos significativo) en BX

; Convertir DX:AX:BX de hexadecimal a decimal
mov cx, 10             ; Configurar CX para la división por 10

convert_entero:
    xor dx, dx         ; Limpiar DX antes de la división
    div cx             ; Dividir DX:AX por 10
    push dx            ; Guardar el resto (el siguiente dígito decimal)
    mov bx, ax         ; Mover AX (cociente) a BX
    loop convert_entero; Repetir hasta convertir toda la parte entera

; Imprimir la parte entera en pantalla
print_entero:
    pop dx             ; Obtener el siguiente dígito decimal
    add dl, '0'        ; Convertirlo a carácter ASCII
    mov ah, 02h        ; Función DOS para imprimir un carácter
    int 21h            ; Llamar a DOS para imprimir
    loop print_entero  ; Repetir para todos los dígitos












  

    



    

    


