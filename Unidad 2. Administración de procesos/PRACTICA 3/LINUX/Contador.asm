; Programe una aplicacion en ensamblador que genere un
; contador de 0 a 9 mostrando en pantalla el conteo.

; Seccion de datos para variables globales
section .data
    ; Inicia el contador en 0
    contador db 0
    ; Definicion de salto de linea en consola
    salto db 10

; Seccion de texto (codigo)
section .text

; Punto de entrada del programa
global _start

; Inicio de la funcion principal
_start:
    ; Inicializacion de registros
    mov ecx, 10
    mov ebx, 1
    mov edx, 1
    mov eax, 4
    mov esi, contador

; Bucle contador de 0 a 9
bucle_contador:
    ; Suma '0' al valor en [esi] para convertirlo a caracter
    add byte [esi], '0'
    mov ecx, esi
    mov eax, 4
    int 0x80

    ; Restaura el valor original en [esi] y aumenta el contador
    sub byte [esi], '0'
    inc byte [contador]

    ; Salto de linea
    mov eax, 4
    mov ebx, 1
    mov ecx, salto
    mov edx, 1
    int 0x80

    ; Comprueba si el contador llego a 10
    cmp byte [contador], 10
    je fin_programa

    ; Salta al inicio del bucle
    jmp bucle_contador

; Finaliza el programa
fin_programa:    
    mov eax, 1
    xor ebx, ebx
    int 0x80