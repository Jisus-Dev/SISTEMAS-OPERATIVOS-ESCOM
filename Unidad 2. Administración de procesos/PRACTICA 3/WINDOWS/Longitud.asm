; Programe una aplicación en ensamblador que muestre en 
; pantalla la longitud de una cadena que haya sido 
; ingresada por teclado.

; Segmento de datos para variables globales
segment .data
    ; Mensaje para digitar cadena
    mensaje_cadena db 'Cadena de entrada >', 0
    
    ; Mensaje para la cantidad de caracteres
    mensaje_salida db 'Cantidad de caracteres>',0

; Segmento para variables no inicializadas
segment .bss
    ; Variables para manejo de consola
    handleConsola   resd 1
    caractEscritos  resd 1
    longitudCadena  resd 1
    ultimoArgumento resd 1
    ; Variables para cada una de las cadenas
    cadena      resd 100
    espDigito   resd 100
    posDigito   resd 8

; Segmento de texto (código)
segment .text

; Punto de entrada del programa
global _main
    ; Declaración de las llamadas al sistema
    extern _GetStdHandle@4
    extern _ReadConsoleA@20
    extern _WriteConsoleA@20
    extern _ExitProcess@4

; Inicio de la función principal
_main:
    ; Mensaje para el usuario
    push dword-11
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 20
    push dword mensaje_cadena
    push dword [handleConsola]
    call _WriteConsoleA@20

    ; Lectura de la cadena
    push dword -10
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,100d
    mov[longitudCadena],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword [longitudCadena]
    push dword cadena
    push dword [handleConsola]
    call _ReadConsoleA@20

    ; Mensaje para el usuario
    push dword-11
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 23
    push dword mensaje_salida
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Calcular la longitud de la cadena
    mov edi,cadena
    call longitud
    sub eax,2
    call imprimir

    ; Finaliza el programa
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    call _ExitProcess@4

; Inicializa espDigito que indica la longitud de la cadena
imprimir:
    mov ecx, espDigito
    mov ebx, 10
    mov [ecx], ebx
    inc ecx
    mov [posDigito], ecx

; Bucle para dividir el número y convertir los dígitos a ASCII
bucle:
    mov edx, 0
    mov ebx, 10
    div ebx
    add edx, 48

    mov ecx, [posDigito]
    mov [ecx], dl
    inc ecx
    mov [posDigito], ecx

    cmp eax, 0
    jne bucle

; Bucle para imprimir la longitud en consola
bucle2:
    mov ecx, [posDigito]

    ; Muestra la longitud de la cadena
    push dword-11
    xor eax,eax;
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 1
    push dword ecx
    push dword [handleConsola]
    call _WriteConsoleA@20;

    mov ecx, [posDigito]
    dec ecx
    mov [posDigito], ecx

    cmp ecx, espDigito
    jge bucle2
    ret

; Calcula la longitud de la cadena
longitud:
    xor ecx, ecx

; Itera sobre la cadena
siguiente:
    cmp   [edi],byte 0
    je    salir
    inc   ecx
    inc   edi
    jmp   siguiente

; Retorna la longitud de la cadena antes de salir
salir:
    mov   eax, ecx
    ret