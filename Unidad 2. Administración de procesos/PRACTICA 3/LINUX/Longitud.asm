; Programe una aplicacion en ensamblador que muestre
; en pantalla la longitud de una cadena que haya sido
; ingresada por teclado.

; Seccion de datos para variables globales
section .data
    ; Mensaje para digitar cadena
    mensaje_cadena db "Cadena de entrada >", 0

    ; Mensaje para la cantidad de caracteres
    mensaje_salida db "Cantidad de caracteres>",0
    
; Seccion para variables no inicializadas
section .bss
    ; Variable para cada una de las cadenas
    cadena resb 100
    espDigito resb 100
    posDigito resb 8

; Seccion de texto (codigo)
section .text

; Punto de entrada del programa
global _start

; Inicio de la funcion principal
_start:
    ; Mensaje pera el usuario
    mov edx, 20
    mov ecx, mensaje_cadena
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    ; Lectura de la cadena
    mov edx, 100
    mov ecx, cadena
    mov ebx, 0
    mov eax, 3
    int 0x80

    ; Mensaje para el usuario
    mov edx, 23
    mov ecx, mensaje_salida
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    ; Calcular la longitud de la cadena
    mov rdi, cadena
    call longitud
    sub rax, 1
    call imprimir

    ; Finaliza el programa
    mov rax, 60
    mov rdi, 0
    syscall

; Inicializa espDigito que indica la longitud de la cadena
imprimir:
    ; Inicializa el arreglo espDigito con el valor 10
    mov rcx, espDigito
    mov rbx, 10
    mov [rcx], rbx
    inc rcx
    mov [posDigito], rcx

; Bucle para dividir el numero y convertir los digitos a ASCII
bucle:
    mov rdx, 0
    mov rbx, 10
    div rbx
    push rax
    add rdx, 48

    mov rcx, [posDigito]
    mov [rcx], dl
    inc rcx
    mov [posDigito], rcx

    pop rax
    cmp rax, 0
    jne bucle

; Bucle para imprimir la longitud en consola
bucle2:
    ; Muestra la longitud de la cadena
    mov rcx, [posDigito]
    mov rax, 1
    mov rdi, 1
    mov rsi, rcx
    mov rdx, 1
    syscall

    mov rcx, [posDigito]
    dec rcx
    mov [posDigito], rcx
    cmp rcx, espDigito
    jge bucle2
    ret

; Calcula la longitud de la cadena
longitud:
    xor rcx, rcx

; Itera sobre la cadena
siguiente:
    cmp [rdi], byte 0
    jz salir
    inc rcx
    inc rdi
    jmp siguiente

; Retorna la longitud de la cadena antes de salir
salir:
    mov rax, rcx
    ret