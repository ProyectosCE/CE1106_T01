section .data
    error_dig db 0x0A,'Favor ingrese un numero valido (0-9999.99)', 0x0D, 0x0A, '$'

lectura: 
    ; Entradas: Carga directamente el buffer_text a leer
    ; Salidas: Guarda en buffer_text la cadena de texto ingresada por el usuario
    ; Restricciones: Se define el tamaño máximo de la entrada en 8 caracteres (7 numéricos y el enter)

    ;Establece la cantidad máxima de caracteres a leer
    mov byte [buffer_text],8
    
    ;Instrucción de ASM 8086 DOS para leer una cadena de texto, guarda en el buffer que apunte DX
    mov ah, 0Ah
    lea dx,[buffer_text]
    int 21h
    
    ;retorno
    ret

procesar_entero:
    ; Entradas: Carga directamente el buffer_text a procesar, 
    ; además espera en BX la direccion del buffer dato_n donde se guarda el valor procesado,
    ; en CX se carga la cantidad de digitos del buffer y si sirve para el desplazamiento en el buffer.
    ; Salidas: Guarda en dato_n especificado el valor procesado y convertido a un valor numerico de 3 bytes,
    ; los primeros dos bytes para la parte entera y el 3 bytes para la parte decimal
    ; Restricciones: Propias del método, solo procesa digitos numéricos, comas y puntos, el valor procesado se almacena en 
    ; los primeros 2 bytes de dato_n

    ; Mueve a dl el digito a leer
    mov dx,0
    mov dl, [buffer_text+si+2]

    ;Llama al metodo de verificación de digitos validos
    call check_digit
    ;incrementa el contador
    inc si

    ;compara el digito con un punto o coma para detener el proceso de enteros
    cmp dl,'.'
    je fin_procesar_entero
    cmp dl,','
    je fin_procesar_entero
    sub dl, '0'

    ;si la comprobación es negativa, entonces se añade el digito al buffer numerico
    call add_digit_entero
    ;se mantiene en loop hasta que CX llegue a 0
    loop procesar_entero

    ;RETORNO
    ret

procesar_decimal:
    ; Entradas: Carga directamente el buffer_text a leer,
    ; además espera en BX la direccion del buffer dato_n donde se guarda el valor procesado,
    ; en CX se recibe el valor de 2 y si sirve para el desplazamiento en el buffer continuacion del metodo de procesar entero.
    ; Salidas: Guarda la parte decimal de la entrada del usuario en el ultimo byte de dato_n
    ; Restricciones: Propias del método, solo acepta caracteres numéricos. Comas o puntos no son validos en este caso.
    ; Ahora si acepta entradas de un solo digito decimal. 

    ; Mueve a dl el digito a leer
    mov dl, [buffer_text+si+2]

    ;comprobar si encontró retorno de carro, ya que sería un decimal de solo un dígito como 1.1
    cmp dl, 0x0D
    je decimal_deuno
    ;verifica que el dígito es un caracter válido
    call check_digit
    
    ;Verifica que el dígito no sea una coma o punto
    cmp dl,'.'
    je error
    cmp dl,','
    je error
    sub dl, '0'
    ;incrementa si
    inc si

    ;llama al metodo para añadir el dígito a la parte decimal del buffer
    call add_digit_decimal
    ;loop hasta CX=0
    loop procesar_decimal

    ;Retorno
    ret

decimal_deuno:
    ;Corrige el ingreso de decimales de solo 1 digito, añadiendo el 0 como ultimo decimal
    mov dl,0
    jmp add_digit_decimal

fin_procesar_entero:
    ;Se llama cuando en procesar_entero se encuentra un punto o coma
    ;Establece CX en un valor fijo de 2
    ;Llama a procesar decimal para seguir procesando la entrada del usuario

    
    MOV cx, 2
    
    ;llama a procesar decimal para procesar los valores faltantes
    call procesar_decimal
    ;Retorno
    ret

add_digit_entero:
    ; Entradas: Recibe en dl el dígito a guardar, y en BX la dirección de dato_n
    ; Salidas: Guarda en dato_n el valor correcto de la entrada.
    ; Restricciones: El valor no puede supererar a 9999
    
    ;Se guarda CX y DX porque se necesitan después
    PUSH CX
    PUSH DX

    ;Prepara para multiplicar el dato ya existente en dato_n (parte entera) por 10 para poder sumar el nuevo digito leido
    mov CX, 10
    mov AH, [bx]
    mov Al, [bx+1]
    mul CX

    ;se recupera DX donde está el digito leido
    POP DX
    ;se suma el dígito
    add ax,dx

    ;se comprueba que el numero almacenado no sea mayor que 9999, de ser así salta a error
    cmp ax,9999
    ja error

    ;guarda el resultado de la suma en los 2 primeros bytes de dato_n
    mov BYTE [bx], AH
    mov BYTE [bX+1], AL

    ;se regresa el valor de cx, ya que ahí está el contador
    POP CX
    ;RETORNA
    ret

add_digit_decimal:
    ; Entradas: Recibe en dl el dígito a guardar, y en BX la dirección de dato_n
    ; Salidas: Guarda en el tercer byte de dato_n el valor correcto de la entrada decimal.
    ; Restricciones: No
    
    ;se guarda el valor de cx
    PUSH CX

    ; se multiplica el valor almacenado en el ultimo byte de dato_n por 10 para sumar el nuevo digito
    mov CL, 10
    mov al, [bx+2]
    mul cl
    
    ;se suma el resultado más el digito leído
    add al,dl
    ; se guarda el valor decimal en el 3 byte de dato_n
    mov [bx+2], al
    
    ;se recupera el valor de cx
    POP CX
    ;Retorna
    ret

; Subrutina check_digit
check_digit:
    ;Verifica que si el digito es menor a '0', de ser así comprueba si es un punto o coma
    cmp dl, '0'             
    jb check_point  

    ;Comprueba que el digito no sea mayor a '9', ya que no hay un valor válido mayor a '9', si es así salta a error               
    cmp dl, '9'              
    ja error  

    ;retorna              
    ret               

check_point:
    ;Verifica si el digito es un punto, si es así retorna, si no salta a comprobar si es una coma.
    cmp dl, '.'             
    jne check_comma 
    ;retorna               
    ret                    
    
check_comma:
    ;Verifica si el digito es una coma, si es así retorna, si no salta a error.
    cmp dl, ','
    jne error
    ret   
    
; Rutina de manejo de errores
error:
    ;Imprime un mensaje de error
    mov bx, error_dig 
    call imp_msg
    mov al, [intselect]

    cmp al, 1 
    je repetir 
    cmp al, 2
    je input

    ;Salta a repetir para preguntar si quiere hacer otro calculo
    ret 


;SUBRUTINA DE IMPRMIR RESPUESTA
;basado el el codigo del usuario de stackoverflow @rcgldr 
;recuperado de https://stackoverflow.com/a/41501934/26912080

; Entradas: Recibe en BX el buffer numérico a imprimir, de 5 bytes
; Salidas: Imprime el valor calculado
; Restricciones: La entrada tiene que ser de 5 bytes

imprimir_resp:
    ;Limpia DX
    xor dx,dx

    ;Guarda en la pila el caracter final '$' y un salto de linea 0x0A
    mov dl,'$'
    push dx
    mov dl, 10
    push dx

    ;salta a añadir la parte decimal a la pila
    jmp decimal_pila
    
decimal_pila:
    ;carga el valor decimal del buffer de entrada en AX
    mov ah,0
    mov al,[bx+4]

    ;Lo divide entre 10, para obtener en AH el ultimo deciaml y en AL el primer decimal
    mov cl, 10
    div cl

    ;limpia DX para guardar AL y AH en la pila através de DL
    xor dx,dx
    mov dl, ah
    add dl,'0'
    push dx
    mov dl, al
    add dl, '0'
    push dx

    ; Adiciona una coma a la pila como caracter separador
    mov al,','
    mov dl,al
    push dx

    ;salta a convertir y añadir en pila el digito entero
    jmp convert_entero

convert_entero:
    ; Carga todo el dato entero (los primeros 4 bytes)
    ; no importa el orden aquí porque se busca comprobar que ambos buffers no están vacios
    mov ax, [bx]              
    mov cx, [bx+2]           
    or ax, cx        
    ; si los buffers están en 0 se pasa a imprimir el dato        
    jz print_loop

    ; Sino se procede a la division de todo el buffer entre 10 para obtener la unidad
    ; se carga la parte más significativa (primeros 2 bytes) y se divide entre 10, el resultado se guarda en DX:AX
    mov ah, [bx]
    mov al, [bx+1]
    xor dx, dx                
    mov cx, 10                
    div cx           
    ; Se almacena el cociente en los primeros 2 bytes del buffer de entrada
    mov [bx], ah                  
    mov [bx+1], al
    
    ;Ahora vamos a dividir DX:AX entre CX, en DX está el reiduo de la división anterior, 
    ;y en AX se debe cargar el 3 y 4 byte del buffer de entrada, CX sigue teniendo valor de 10
    mov ah, [bx+2]
    mov al, [bx+3]       
    div cx                   

    ; Almacena el cociente en los 2 ultimos bytes del buffer de entrada
    mov [bx+2], ah 
    mov [bx+3], al

    ;En DX queda el residuo, específicamente en dl
    ;se le suma el valor de '0' para que se convierta en un caracter ASCII
    add dl,'0'          
    ;guarda en pila
    push dx
    ;vuelve a llamar convert_entero para mantener el ciclo hasta que todo el buffer sea 0
    jmp convert_entero

print_loop:
    ;regresa el valor de dx de la pila, que se ingresaron en los métodos anteriores
    pop dx
    ;compara si es el simbolo de dolar '$', ya que este es el caracter de finalización, si lo encuentra para de imprimir
    cmp dl, '$'
    je done_imp 
    
    ; Esta es la instrucción de ASM 8086 para imprimir un solo caracter              
    mov ah, 02h               
    int 21h     

    ; se mantiene en loop hasta que encuentre el caracter '$'              
    jmp print_loop  

done_imp:
    ; Este es el retorno a donde se haya llamado imprimir_resp
    ret

new_line:
    ;Método para imprimir una nueva linea de ser necesario
    lea dx, newline
    mov ah, 09h
    int 21h
    ret

color_msg:
    ; Entradas: En BX recibe el valor de la direccion de un buffer de texto, recibe el color en CL
    ; Salidas: Imprime el buffer de texto a colores
    ; Restricciones: El buffer debe terminar con el caracter de finalización "$"
    
    ;:guardamos los valores de bx y cx
    push bx
    push cx

    ;Encontramos la posición del carro
    mov ah, 03h
    mov bx, 0         
    int 10h
    int 3 
    
    ;definimos el color de la linea donde se va a imprimir el texto
    pop cx
    mov ah,06h
    mov bh,cl
    mov ch,dh
    mov cl,0
    mov dh,ch
    mov dl,80
    int 10h

    ;impresión normal de la cadena
    pop bx
    mov ah, 09h
    lea dx,[bx]
    int 21h

    ;retorna
    ret

imp_msg:
    mov ah, 09h
    lea dx,[bx]
    int 21h

    ;retorna
    ret
