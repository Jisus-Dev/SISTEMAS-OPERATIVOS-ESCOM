; Programe una aplicación en ensamblador que copie 5 
; cadenas dadas (cadena1 a cadena5) a una nueva cadena
; (cadena6). La copia de las cadenas deberá ser intercalando 
; los caracteres de cada cadena.

; Segmento de datos para variables globales
segment .data
    ; Mensajes para digitar cadenas
    mensaje_cadena1 db 'Cadena 1 >', 0
    mensaje_cadena2 db 'Cadena 2 >', 0
    mensaje_cadena3 db 'Cadena 3 >', 0
    mensaje_cadena4 db 'Cadena 4 >', 0
    mensaje_cadena5 db 'Cadena 5 >', 0

    ; Mensaje para la cadena de salida
    mensaje_cadena6 db 'Cadena 6 (concatenada)>', 0

    ; Definición de la longitud de cada cadena
    longitud_cadena1 dd 1
    longitud_cadena2 dd 1
    longitud_cadena3 dd 1
    longitud_cadena4 dd 1
    longitud_cadena5 dd 1

    ; Definición de longitud de la cadena concatenada
    longitud_total dd 1

    ; Definición de salto de línea en consola
    salto_de_linea db 0xa

; Segmento para variables no inicializadas
segment .bss
    ; Variables para manejo de consola
    handleConsola resd 1
    caractEscritos resd 1
    longitudCadena resd 1
    ultimoArgumento resd 1
    ; Variables para cada una de las cadenas
    cadena1 resb 50
    cadena2 resb 50
    cadena3 resb 50
    cadena4 resb 50
    cadena5 resb 50
    cadena_concatenada resb 150

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
    ; Cadena 1

    ; Mensaje para el usuario
    push dword-11
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 11
    push dword mensaje_cadena1
    push dword [handleConsola]
    call _WriteConsoleA@20

    ; Lectura de la cadena
    push dword -10
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,50d
    mov[longitudCadena],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword [longitudCadena]
    push dword cadena1
    push dword [handleConsola]
    call _ReadConsoleA@20

    ; Cadena 2

    ; Mensaje para el usuario
    push dword-11
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 11
    push dword mensaje_cadena2
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Lectura de la cadena
    push dword -10
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,50d
    mov[longitudCadena],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword [longitudCadena]
    push dword cadena2
    push dword [handleConsola]
    call _ReadConsoleA@20

    ; Cadena 3

    ; Mensaje para el usuario
    push dword-11
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 11
    push dword mensaje_cadena3
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Lectura de la cadena
    push dword -10
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,50d
    mov[longitudCadena],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword [longitudCadena]
    push dword cadena3
    push dword [handleConsola]
    call _ReadConsoleA@20

    ; Cadena 4

    ; Mensaje para el usuario
    push dword-11
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 11
    push dword mensaje_cadena4
    push dword [handleConsola]
    call _WriteConsoleA@20

    ; Lectura de la cadena
    push dword -10
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,50d
    mov[longitudCadena],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword [longitudCadena]
    push dword cadena4
    push dword [handleConsola]
    call _ReadConsoleA@20

    ; Cadena 5

    ; Mensaje para el usuario
    push dword-11
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 11
    push dword mensaje_cadena5
    push dword [handleConsola]
    call _WriteConsoleA@20

    ; Lectura de la cadena
    push dword -10
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,50d
    mov[longitudCadena],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword [longitudCadena]
    push dword cadena5
    push dword [handleConsola]
    call _ReadConsoleA@20

    ; Obtener las longitudes de las cadenas

    ; Obtener longitud cadena 1
    mov edi, cadena1
    call _strlen
    mov [longitud_cadena1], eax
    mov [longitud_total], eax

    ; Obtener longitud cadena 2
    mov edi, cadena2
    call _strlen
    mov [longitud_cadena2], eax
    add [longitud_total], eax

    ; Obtener longitud cadena 3
    mov edi, cadena3
    call _strlen
    mov [longitud_cadena3], eax
    add [longitud_total], eax

    ; Obtener longitud cadena 4
    mov edi, cadena4
    call _strlen
    mov [longitud_cadena4], eax
    add [longitud_total], eax

    ; Obtener longitud cadena 5
    mov edi, cadena5
    call _strlen
    mov [longitud_cadena5], eax
    add [longitud_total], eax

    ; Inicializar puntero para concatenar
    mov eax, 0
    xor edi, edi
    mov edi, cadena_concatenada
    jmp concatenar1

; Funciones para la concatenación de las cadenas

concatenar1:
    cmp eax, [longitud_cadena1]
    jge concatenar2

    mov esi, cadena1
    add esi, eax
    mov ecx, 1
    rep movsb

concatenar2:
    cmp eax, [longitud_cadena2]
    jge concatenar3

    mov esi, cadena2
    add esi, eax
    mov ecx, 1
    rep movsb

concatenar3:
    cmp eax, [longitud_cadena3]
    jge concatenar4

    mov esi, cadena3
    add esi, eax
    mov ecx, 1
    rep movsb

concatenar4:
    cmp eax, [longitud_cadena4]
    jge concatenar5

    mov esi, cadena4
    add esi, eax
    mov ecx, 1
    rep movsb

concatenar5:
    cmp eax, [longitud_cadena5]
    jge longitud_maxima

    mov esi, cadena5
    add esi, eax
    mov ecx, 1
    rep movsb

    jmp longitud_maxima

; Verifica que la concatenación haya terminado
longitud_maxima:
    add eax, 1
    cmp eax, [longitud_total]
    jle concatenar1
    jmp final

; Finaliza el programa
final:
    ; Mensaje para el usuario
    push dword-11
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 24
    push dword mensaje_cadena6
    push dword [handleConsola]
    call _WriteConsoleA@20

    ; Se muestra la cadena concatenada
    push dword-11
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword [longitud_total]
    push dword cadena_concatenada
    push dword [handleConsola]
    call _WriteConsoleA@20

    ; Finaliza el programa
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    call _ExitProcess@4

; Calcula la longitud de las cadenas digitadas
_strlen:
    mov ebx, edi
    xor al, al
    mov ecx, 0xffffffff
    repne scasb
    sub edi, ebx
    sub edi, 2
    mov eax, edi
    ret