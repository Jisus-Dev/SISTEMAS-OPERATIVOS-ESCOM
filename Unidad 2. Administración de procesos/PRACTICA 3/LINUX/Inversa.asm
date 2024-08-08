; Programe una aplicacion en ensamblador que concatene 5
; cadenas (cadena1 a cadena5) ingresadas por teclado,
; mostrando en pantalla lo siguiente: el contenido de la
; cadena concatenada, la cadena concatenada en sentido
; inverso y el numero total de vocales que tiene la
; cadena concatenada.

; Seccion de datos para variables globales
section .data
    ; Mensaje de instruccion
    instruccion db 'Digite 5 cadenas:',0

    ; Mensaje para digitar cada una de las cadenas
    mensaje db "Cadena >",0

    ; Mensaje para los resultados calculados
    concat  db "Cadena concatenada >",0
    inver   db "Cadena inversa >",0
    voca    db "Cantidad vocales >",0
    salto   db 0xa
    d times 100 db ' '  ; Reserva espacio para 100 caracteres

; Seccion para variables no inicializadas
section .bss
    ; Variables para el calculo de vocales
    laux        resb 1
    l4          resb 1
    cadena      resb 50
    reversa     resb 500
    espDigito   resb 100
    posDigito   resb 8
    vocalesStr  resd 1

; Seccion de texto (codigo)
section .text

; Punto de entrada del programa
global _start

; Inicio de la funcion principal
_start:
    ; Mensaje de instruccion
    mov edx, 18
    mov ecx, instruccion
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Salto de linea
    mov edx,1
    mov ecx,salto
    mov ebx,1
    mov eax,4
    int 0x80

    ; Mensaje para solicitar cadena
    mov edx, 9
    mov ecx, mensaje
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    ; Lectura de la cadena
    mov edi,d
    mov edx,50
    mov ecx,cadena
    mov ebx,0
    mov eax,3
    int 0x80
    mov esi, cadena

    ; Busca el final de la cadena
    call buscarfin

    ; Solicitar las 4 cadenas restantes
    times 4 call guardar

    ; Calcula la longitud de la cadena
    mov rdi,d
    call len
    mov [l4],rax
    mov [laux],rax
    push laux

    ; Mensaje que indica cual es la cadena concatenada
    mov edx, 20
    mov ecx, concat
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    ; Muestra la cadena concatenada
    mov edx,[laux]
    mov ecx,d
    mov ebx,1
    mov eax,4
    int 0x80

    ; Salto de linea
    mov edx,1
    mov ecx,salto
    mov ebx,1
    mov eax,4
    int 0x80

    ; Invierte la cadena
    call inverso
    
    ; Mensaje que indica cual es la cadena invertida
    mov edx, 16
    mov ecx, inver
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    ; Muestra la cadena inversa
    mov edx,[laux]
    mov ecx,reversa
    mov ebx,1
    mov eax,4
    int 0x80
	
    ; Mensaje que indica la cantidad de vocales
    mov edx, 19
    mov ecx, voca
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    ; Guarda el conteo de vocales
    mov eax, [vocalesStr]
    mov [espDigito], eax

    ; Imprime el conteo de vocales
    call imprimir

    ; Finaliza el programa
    mov eax,1
    int 0x80

; Solicita las 4 cadenas restantes
guardar:
    ; Mensaje para solicitar la cadena
    mov edx, 9
    mov ecx, mensaje
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    ; Lectura de la cadena
    mov edx,50
    mov ecx,cadena
    mov ebx,0
    mov eax,3
    int 0x80
    mov esi,cadena
    inc edi

; Busca el final de la cadena y cuenta las vocales
buscarfin:
    cmp [esi], byte 0xa
    jz fin
    mov al, [esi]
    cmp al, 'a'
    je incrementa
    cmp al, 'e'
    je incrementa
    cmp al, 'i'
    je incrementa
    cmp al, 'o'
    je incrementa
    cmp al, 'u'
    je incrementa
    jmp sigue

; Incrementa el numero de vocales
incrementa:
    add dword [vocalesStr], 1

; Continua con la iteracion sobre la cadena
sigue:
    mov ecx,1
    rep movsb
    jmp buscarfin

; Calcula la longitud de la cadena
len:
    xor rcx,rcx

; Continua con la iteracion sobre la cadena
siguiente:
    cmp [rdi],byte ' '
    jz salir
    inc rcx
    inc rdi
    jmp siguiente

; Retorna la cantidad de vocales de la cadena antes de salir
salir:
    mov rax,rcx
    ret

; Imprime el conteo de vocales
imprimir:
    mov rcx,espDigito
    mov rbx,10
    mov [rcx],rbx
    inc rcx
    mov [posDigito],rcx

; Bucle para dividir el numero y convertir los digitos a ASCII
bucle:
    mov rdx,0
    mov rbx,10
    div rbx
    push rax
    add rdx,48
    mov rcx, [posDigito]
    mov [rcx], dl
    inc rcx
    mov [posDigito], rcx
    pop rax
    cmp rax, 0
    jne bucle

; Bucle para imprimir el resultado en consola
bucle2:
    mov rcx, [posDigito]
    mov rax,1
    mov rdi,1
    mov rsi,rcx
    mov rdx,1
    syscall
    mov rcx, [posDigito]
    dec rcx
    mov [posDigito], rcx
    cmp rcx, espDigito
    jge bucle2
    ret

; Invierte la cadena
inverso:    
    mov esi,d
    sub esi,1

; Muestra la cadea inversa
invimprimir:
    cmp [esi],byte 0
    jz invfin
    mov edi,reversa
    add edi,[laux]
    mov ecx,1
    rep movsb
    sub byte [laux],1
    jmp invimprimir

; Indica que se termino de mostrar la caden inversa
invfin:
    ret

; Indica el fin del muestro de calculos
fin:
    sub edi,1
    ret