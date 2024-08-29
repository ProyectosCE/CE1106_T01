org 100h  ; Código de inicio para programas .COM

section .data
text db 'Hola mundo',0x0A,'$' ; Cadena de texto a imprimir, terminada con '$'
texto2 db 'Otro Texto',0x0A,'$' ; Cadena de texto a imprimir, terminada con '$'

line1 db ' +----------------------------------------------------------------------------+', 0x0A, '$'
line2 db ' |                       This program is under MIT License                    |', 0x0A, '$'
line3 db ' |                              Copyright(c) 2024                             |', 0x0A, '$'
line4 db ' |                         Bienvenido a GeometryTEC                           |', 0x0A, '$'
line5 db ' +----------------------------------------------------------------------------+', 0x0A, '$'

section .text
    global _start

_start:
    
    mov bx,line1
    mov cl,0x1F
    call print

    mov bx,line2
    mov cl,0x1F
    call print

    mov bx,line3
    mov cl,0x1F
    call print

    mov bx,line4
    mov cl,0x1F
    call print

    mov bx,line5
    mov cl,0x1F
    call print
    
    jmp done

print:
    push bx
    push cx
    mov ah, 03h
    mov bx, 0         
    int 10h
    int 3 
    
    pop cx
    mov ah,06h
    mov bh,cl
    mov ch,dh
    mov cl,0
    mov dh,ch
    mov dl,80
    int 10h

    pop bx
    mov ah, 09h
    lea dx,[bx]
    int 21h

    ret  ; Repetir hasta el fin de cadena

done:
    mov ah, 4ch    ; Terminar el programa
    int 21h        ; Llamada a DOS para terminar
