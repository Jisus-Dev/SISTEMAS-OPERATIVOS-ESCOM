; Programe una aplicacion en ensamblador que copie 5
; cadenas dadas (cadena1 a cadena5) a una nueva cadena
; (cadena6). La copia de las cadenas debera ser intercalando
; los caracteres de cada cadena.

; Seccion de datos para variables globales
section .data
    ; Mensajes para digitar cadenas
    mensaje_cadena1 db "Cadena 1 >", 0
    mensaje_cadena2 db "Cadena 2 >", 0
    mensaje_cadena3 db "Cadena 3 >", 0
    mensaje_cadena4 db "Cadena 4 >", 0
    mensaje_cadena5 db "Cadena 5 >", 0

    ; Mensaje para la cadena de salida
    mensaje_cadena6 db "Cadena 6 (concatenada)>", 0

    ; Definicion de la longitud de cada cadena
    longitud_cadena1 dd 1
    longitud_cadena2 dd 1
    longitud_cadena3 dd 1
    longitud_cadena4 dd 1
    longitud_cadena5 dd 1

    ; Definicion de longitud de la cadena concatenada
    longitud_total dd 1

    ; Definicion de salto de linea en consola
    salto_de_linea db 0xa

; Seccion para variables no inicializadas
section .bss
    ; Variable para cada una de las cadenas
    cadena1 resb 50
    cadena2 resb 50
    cadena3 resb 50
    cadena4 resb 50
    cadena5 resb 50
    cadena_concatenada resb 150

; Seccion de texto (codigo)
section .text

; Punto de entrada del programa
global _start

; Inicio de la funcion principal
_start:
    ; Cadena 1

    ; Mensaje para el usuario
    mov edx, 11
    mov ecx, mensaje_cadena1
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    ; Lectura de la cadena
    mov edx, 50
    mov ecx, cadena1
    mov ebx, 0
    mov eax, 3
    int 0x80

    ; Cadena 2

    ; Mensaje para el usuario
    mov edx, 11
    mov ecx, mensaje_cadena2
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Lectura de la cadena
    mov edx, 50
    mov ecx, cadena2
    mov ebx, 0
    mov eax, 3
    int 0x80

    ; Cadena 3

    ; Mensaje para el usuario
    mov edx, 11
    mov ecx, mensaje_cadena3
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Lectura de la cadena
    mov edx, 50
    mov ecx, cadena3
    mov ebx, 0
    mov eax, 3
    int 0x80

    ; Cadena 4

    ; Mensaje para el usuario
    mov edx, 11
    mov ecx, mensaje_cadena4
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Lectura de la cadena
    mov edx, 50
    mov ecx, cadena4
    mov ebx, 0
    mov eax, 3
    int 0x80

    ; Cadena 5

    ; Mensaje para el usuario
    mov edx, 11
    mov ecx, mensaje_cadena5
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    ; Lectura de la cadena
    mov edx, 50
    mov ecx, cadena5
    mov ebx, 0
    mov eax, 3
    int 0x80

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

; Funciones para la concatenacion de las cadenas

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

; Verifica que la concatenacion haya terminado
longitud_maxima:
    add eax, 1
    cmp eax, [longitud_total]
    jle concatenar1
    jmp final

; Finaliza el programa
final:
    ; Mensaje para el usuario
    mov edx, 24
    mov ecx, mensaje_cadena6
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Se muestra la cdena contacatenada
    mov edx, [longitud_total]
    mov ecx, cadena_concatenada
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Salto de linea
    mov edx, 1
    mov ecx, salto_de_linea
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Finaliza el programa
    mov eax, 1
    int 0x80

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