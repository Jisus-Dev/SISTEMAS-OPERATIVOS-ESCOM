; Programe una aplicación en ensamblador que genere un 
; contador de 0 a 9 mostrando en pantalla el conteo.

; Segmento de datos para variables globales
segment .data
    ; Inicia el contador en 0
    contador            db '0'

    ; Definición de salto de línea en consola
    salto_de_linea      db 0xA

; Segmento para variables no inicializadas
segment .bss
    ; Variables para manejo de consola
    manejador_consola   resd 1
    longitud_cadena     resd 1
    caracteres_escritos resd 1
    ultimo_argumento    resd 1

; Segmento de texto (código)
segment .text

; Punto de entrada del programa
global _main
    ; Declaración de las llamadas al sistema
    extern _GetStdHandle@4
    extern _WriteConsoleA@20
    extern _ExitProcess@4

; Inicio de la función principal
_main:
    jmp bucle_principal

; Bucle contador de 0 a 9
bucle_principal:
    cmp byte [contador], ':'
    jne incrementar
    jmp finalizar

; Muestra cada número contado
incrementar:
    push dword -11
    call _GetStdHandle@4
    mov [manejador_consola], eax
    mov eax, 2d
    mov [longitud_cadena], eax
    mov eax, 0d
    mov [ultimo_argumento], eax
    push dword [ultimo_argumento]
    push dword caracteres_escritos
    push dword [longitud_cadena]
    push dword contador
    push dword [manejador_consola]
    call _WriteConsoleA@20

    inc byte [contador]
    jmp bucle_principal

; Finaliza el programa
finalizar:
    xor eax, eax
    push eax
    call _ExitProcess@4