org 100h  ; Código de inicio para programas .COM

section .data
text db 'Hola mundo','$' ; Cadena de texto a imprimir, terminada con '$'

section .text
    global _start

_start:
    jmp print

print:
    mov ah, 03h         
    int 10h  
    
    mov ah,06h
    mov bh,03h
    mov ch,dh
    mov cl,0
    mov dh,ch
    mov dl,80
    int 10h


    mov ah, 09h
    lea dx,text
    int 21h
    jmp done  ; Repetir hasta el fin de cadena

done:
    mov ah, 4ch    ; Terminar el programa
    int 21h        ; Llamada a DOS para terminar
