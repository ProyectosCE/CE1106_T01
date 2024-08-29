org 100h

%include "program.asm"  ; Incluir el archivo program.asm

jmp start

start:
    mov word [current_menu], 1
    jmp print_menu

print_menu:
    call clear_screen
    call print_title
    mov ax, [current_menu]
    cmp ax, 1
    je print_menu_1
    cmp ax, 2
    je print_menu_2
    cmp ax, 3
    je print_menu_3

input:
    mov dx, msg4
    mov ah, 9
    int 21h
    mov ah, 0
    int 16h  ; Espera a que se presione una tecla
    
    cmp al, 0Dh ; Verifica si es Enter (0Dh es el código ASCII de Enter)
    je handle_buttonclick ; Si es Enter, manejarlo
    
    cmp al, 1Bh ; Verifica si es Esc (1Bh es el código ASCII de Escape)
    je exit ; Si es Esc, salir del programa

    cmp al, 0 ; Verifica si es una tecla especial (tecla de flecha)
    je handle_special_key ; Si es una tecla especial, manejarla
    
    jmp input ; Si no es una tecla reconocida, esperar de nuevo

handle_special_key:
    mov ah, 0 ; Captura la siguiente parte del código de escaneo
    int 16h
    
    ; Manejo de teclas de flecha
    cmp ah, 50h ; Flecha hacia abajo
    je down_pressed
    cmp ah, 48h ; Flecha hacia arriba
    je up_pressed
    jmp input ; Si no es una tecla reconocida, volver al menú
 
inc_menu:
    inc word [current_menu] ; Incrementa el menú actual
    cmp word [current_menu], 4 ; Si es mayor a 3, resetear a 1
    jb print_menu
    mov word [current_menu], 1
    jmp print_menu
 
dec_menu:
    dec word [current_menu] ; Decrementa el menú actual
    cmp word [current_menu], 0 ; Si es menor a 1, resetear a 3
    ja print_menu
    mov word [current_menu], 3
    jmp print_menu
 
up_pressed:
    jmp dec_menu
 
down_pressed:
    jmp inc_menu
 
print_menu_1:
    mov dx, M1
    mov ah, 9
    int 21h
    jmp input
 
print_menu_2:
    mov dx, M2
    mov ah, 9
    int 21h
    jmp input
 
print_menu_3:
    mov dx, M3
    mov ah, 9
    int 21h
    jmp input
 
handle_buttonclick:
    mov ax, [current_menu]
    cmp ax, 1
    je b1c
    cmp ax, 2
    je b2c
    cmp ax, 3
    je b3c

b1c:
    call clear_screen
    call print_title
    call case_show_figures  ; Llama a la función case_show_figures
    jmp print_menu

b2c:
    call clear_screen
    call print_title
    call case_show_figures  ; Llama a la función case_show_figures
    jmp print_menu

b3c:
    call clear_screen
    call print_title
    call case_show_figures  ; Llama a la función case_show_figures
    jmp print_menu

exit:
    call clear_screen
    mov ah, 4Ch
    mov al, 0
    int 21h

clear_screen:
    mov ah, 0
    mov al, 3
    int 10h        
    ret

print_title:
    mov dx, title
    mov ah, 9
    int 21h
    ret

msg3: db 'You clicked button 3.', 0ah, 0dh, '$'
msg2: db 'You clicked button 2.', 0ah, 0dh, '$'
msg1: db 'You clicked button 1.', 0ah, 0dh, '$'
msg4: db 'Use arrow keys to navigate, Enter to select, Esc to exit.', 0ah, 0dh, '$'

title: 
    db 'geotec', 0ah, 0dh, '$'

current_menu dw 1

M1 db '  ---------------  ', 0ah, 0dh
   db '  | >Figuras   |   ', 0ah, 0dh
   db '  ---------------  ', 0ah, 0dh, '$'

M2 db '  ---------------  ', 0ah, 0dh
   db '  | >Option 2  |   ', 0ah, 0dh
   db '  ---------------  ', 0ah, 0dh, '$'

M3 db '  ---------------  ', 0ah, 0dh
   db '  | >Salir     |   ', 0ah, 0dh
   db '  ---------------  ', 0ah, 0dh, '$'
ret
