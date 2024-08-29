[bits 16]

; Sección de datos predefinidos
section .data
M1 db ' ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '  | >Cuadrado      |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  |  Rectangulo    |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  |  Triangulo     |   ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '$', 0ah, 0dh

M2 db ' ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '  |  Cuadrado      |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  | >Rectangulo    |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  |  Triangulo     |   ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '$', 0ah, 0dh

M3 db ' ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '  |  Cuadrado      |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  |  Rectangulo    |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  | >Triangulo     |   ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '$', 0ah, 0dh

M4 db ' ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '  |  Triangulo     |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  | >Rombo         |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  |  Pentagono     |   ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '$', 0ah, 0dh

M5 db ' ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '  |  Rombo         |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  | >Pentagono     |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  |  Hexagono      |   ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '$', 0ah, 0dh

M6 db ' ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '  |  Pentagono     |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  | >Hexagono      |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  |  Circulo       |   ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '$', 0ah, 0dh

M7 db ' ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '  |  Hexagono      |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  | >Circulo       |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  |  Trapecio      |   ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '$', 0ah, 0dh

M8 db ' ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '  |  Circulo       |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  | >Trapecio      |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  |  Paralelogramo |   ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '$', 0ah, 0dh

M9 db ' ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '  |  Trapecio      |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  | >Paralelogramo |   ', 0ah, 0dh
db '  |                |   ', 0ah, 0dh
db '  |  Cuadrado      |   ', 0ah, 0dh
db '  ---------------  ', 0ah, 0dh
db '$', 0ah, 0dh

msg1: db 'Has seleccionado Cuadrado.', 0ah, 0dh, 0ah, 0dh
    db ' ________', 0ah, 0dh
    db ' |      |', 0ah, 0dh
    db ' |      |', 0ah, 0dh
    db ' |______|', 0ah, 0dh, 
    db '          ', 0ah, 0dh, 24h
msg2: db 'Has seleccionado Rectangulo.', 0ah, 0dh, 0ah, 0dh
    db ' _____', 0ah, 0dh
    db ' |   |', 0ah, 0dh
    db ' |   |', 0ah, 0dh
    db ' |___|', 0ah, 0dh, 
    db '        ', 0ah, 0dh, 24h
msg3: db 'Has seleccionado Triangulo.', 0ah, 0dh, 0ah, 0dh
    db '   /\\  ', 0ah, 0dh
    db '  /  \\ ', 0ah, 0dh
    db ' /____\\', 0ah, 0dh, 24h
msg4: db 'Has seleccionado Rombo.', 0ah, 0dh, 0ah, 0dh
    db '  /\\  ', 0ah, 0dh
    db ' /  \\ ', 0ah, 0dh
    db ' \  // ', 0ah, 0dh
    db '  \// ', 0ah, 0dh, 24h
msg5: db 'Has seleccionado Pentagono.', 0ah, 0dh, 0ah, 0dh
    db '     / \\   ', 0ah, 0dh
    db '    /   \\   ', 0ah, 0dh
    db '   /     \\  ', 0ah, 0dh
    db '   \     //  ', 0ah, 0dh
    db '    \___// ', 0ah, 0dh, 
    db '      ', 0ah, 0dh, 24h


msg6: db 'Has seleccionado Hexagono.', 0ah, 0dh, 0ah, 0dh
    db '    _____   ', 0ah, 0dh
    db '   /     \\  ', 0ah, 0dh
    db '  /       \\ ', 0ah, 0dh
    db '  \       // ', 0ah, 0dh, 
    db '   \_____//  ', 0ah, 0dh, 
    db '      ', 0ah, 0dh, 24h
msg7: db 'Has seleccionado Circulo.', 0ah, 0dh, 0ah, 0dh
    db '     /  /     ', 0ah, 0dh
    db '  /        /  ', 0ah, 0dh
    db ' /          / ', 0ah, 0dh
    db '  /        /  ', 0ah, 0dh, 
    db '     /  /     ', 0ah, 0dh, 
        db '     ', 0ah, 0dh, 24h


msg8: db 'Has seleccionado Trapecio.', 0ah, 0dh, 0ah, 0dh
    db '   _______  ', 0ah, 0dh
    db '  /       \\ ', 0ah, 0dh
    db ' /_________\\ ', 0ah, 0dh
    db '             ', 0ah, 0dh, 24h
msg9: db 'Has seleccionado Paralelogramo.', 0ah, 0dh, 0ah, 0dh
    db '   _______  ', 0ah, 0dh
    db '  /      // ', 0ah, 0dh
    db ' /______//  ', 0ah, 0dh
    db '             ', 0ah, 0dh, 24h

msgTitle: db 'Demo de GUI en MS-DOS', 0ah, 0dh, 24h

current_menu dw 1

section .text
    org 100h
    global _start 

_start:
    jmp print_menu

print_menu:
    call clear_screen
    mov ax, [current_menu]
    cmp ax, 1
    je print_menu_1
    cmp ax, 2
    je print_menu_2
    cmp ax, 3
    je print_menu_3
    cmp ax, 4
    je print_menu_4
    cmp ax, 5
    je print_menu_5
    cmp ax, 6
    je print_menu_6
    cmp ax, 7
    je print_menu_7
    cmp ax, 8
    je print_menu_8
    cmp ax, 9
    je print_menu_9
    jmp input

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

print_menu_4:
    mov dx, M4
    mov ah, 9
    int 21h
    jmp input

print_menu_5:
    mov dx, M5
    mov ah, 9
    int 21h
    jmp input

print_menu_6:
    mov dx, M6
    mov ah, 9
    int 21h
    jmp input

print_menu_7:
    mov dx, M7
    mov ah, 9
    int 21h
    jmp input

print_menu_8:
    mov dx, M8
    mov ah, 9
    int 21h
    jmp input

print_menu_9:
    mov dx, M9
    mov ah, 9
    int 21h
    jmp input

input:
    mov dx, msgTitle
    mov ah, 9
    int 21h
    mov ah, 0
    int 16h
    cmp ah, 50h   ; Tecla abajo
    je down_pressed
    cmp ah, 48h   ; Tecla arriba
    je up_pressed
    cmp ah, 31   ; Tecla Enter
    je handle_buttonclick
    jmp print_menu

down_pressed:
    cmp word [current_menu], 9  ; Verificar si está en el último menú
    je print_menu
    inc word [current_menu]     ; Incrementar menú
    jmp print_menu
 
up_pressed:
    cmp word [current_menu], 1  ; Verificar si está en el primer menú
    je print_menu
    dec word [current_menu]     ; Decrementar menú
    jmp print_menu

handle_buttonclick:
    mov ax, [current_menu]
    cmp ax, 1
    je b1c
    cmp ax, 2
    je b2c
    cmp ax, 3
    je b3c
    cmp ax, 4
    je b4c
    cmp ax, 5
    je b5c
    cmp ax, 6
    je b6c
    cmp ax, 7
    je b7c
    cmp ax, 8
    je b8c
    cmp ax, 9
    je b9c
 
b1c:
    call clear_screen
    mov dx, msg1
    mov ah, 9
    int 21h
    jmp input

b2c:
    call clear_screen
    mov dx, msg2
    mov ah, 9
    int 21h
    jmp input
 
b3c:
    call clear_screen
    mov dx, msg3
    mov ah, 9
    int 21h
    jmp input

b4c:
    call clear_screen
    mov dx, msg4
    mov ah, 9
    int 21h
    jmp input

b5c:
    call clear_screen
    mov dx, msg5
    mov ah, 9
    int 21h
    jmp input

b6c:
    call clear_screen
    mov dx, msg6
    mov ah, 9
    int 21h
    jmp input

b7c:
    call clear_screen
    mov dx, msg7
    mov ah, 9
    int 21h
    jmp input

b8c:
    call clear_screen
    mov dx, msg8
    mov ah, 9
    int 21h
    jmp input

b9c:
    call clear_screen
    mov dx, msg9
    mov ah, 9
    int 21h
    jmp input
 
end:
    mov ah, 4ch
    mov al, 0
    int 21h 
 
clear_screen:
    mov ah, 0
    mov al, 3
    int 10h        
    ret
