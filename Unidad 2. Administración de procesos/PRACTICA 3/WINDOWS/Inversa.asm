; Programe una aplicación en ensamblador que concatene 5 
; cadenas (cadena1 a cadena5) ingresadas por teclado, 
; mostrando en pantalla lo siguiente: el contenido de la 
; cadena concatenada, la cadena concatenada en sentido 
; inverso y el número total de vocales que tiene la 
; cadena concatenada.

; Segmento de datos para variables globales
segment .data
    ; Mensaje de instruccion
    instruccion db 'Digite 5 cadenas:',0
    
    ; Mensaje para digitar cada una de las cadenas
    mensaje     db 'Cadena >',0
    
    ; Mensaje para los resultados calculados
    concat      db 'Cadena concatenada >',0
    inver       db 'Cadena inversa >',0
    voca        db 'Cantidad vocales >',0
    salto       db 0xD, 0xA
    i db 0
    longitud dd 0
    vocales dd 0

; Segmento para variables no inicializadas
segment .bss
    ; Variables para manejo de consola
    handleConsola   resd 1
    caractEscritos  resd 1
    longitudCadena  resd 1
    ultimoArgumento resd 1

    ; Variables para cada una de las cadenas
    cadena      resb 101
    resultado   resb 1000
    reversa     resb 1000
    longitudStr resb 4
    vocalesStr  resb 4

; Segmento de texto (código)
segment .text

; Punto de entrada del programa
global _main
    ; Declaración de las llamadas al sistema
    extern    _GetStdHandle@4
    extern    _WriteConsoleA@20
    extern    _ReadConsoleA@20
    extern    _ExitProcess@4

; Inicio de la función principal
_main:
    ; Inicializa las variables
    mov edi, resultado
    mov byte[i], 0
    mov dword[longitud], 0
    
    ; Mensaje de instrucción
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 18
    push dword instruccion
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Salto de línea
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 2
    push dword salto
    push dword [handleConsola]
    call _WriteConsoleA@20

; Funcion que solicita las 5 cadenas en un ciclo
pedirCadenas:
    ; Mensaje para solicitar cada cadena
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 9
    push dword mensaje
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Lectura de cada cadena
    push dword -10
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,2
    mov[longitudCadena],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 101
    push dword cadena
    push dword [handleConsola]
    call _ReadConsoleA@20

    ; Ciclo para lectura de cadenas
    mov esi, cadena
    call copiarCadena
    inc byte[i]
    cmp byte[i], 5
    je imprimirResultado
    jne pedirCadenas

; Concatena la cadena digitada con la anterior
copiarCadena:
    mov dl, byte[esi]
    mov byte[edi], dl
    inc edi
    inc esi
    inc dword[longitud]
    call esVocal
    cmp byte[esi], 0xD
    jne copiarCadena
    ret

; Verifica si cada caracter es una vocal
esVocal:
    cmp dl, 'a'
    je incrementarVocales
    cmp dl, 'e'
    je incrementarVocales
    cmp dl, 'i'
    je incrementarVocales
    cmp dl, 'o'
    je incrementarVocales
    cmp dl, 'u'
    je incrementarVocales
    cmp dl, 'A'
    je incrementarVocales
    cmp dl, 'E'
    je incrementarVocales
    cmp dl, 'I'
    je incrementarVocales
    cmp dl, 'O'
    je incrementarVocales
    cmp dl, 'U'
    je incrementarVocales
    ret

; Incrementa el contador de vocales
incrementarVocales:
    inc dword[vocales]
    ret

; Imprime la concatenacion de las cadenas
imprimirResultado:
    ; Mensaje que indica cual es la cadena concatenada
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 21
    push dword concat
    push dword [handleConsola]
    call _WriteConsoleA@20

    ; Muestra la cadena concatenada
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword [longitud]
    push dword resultado
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Salto de linea
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 2
    push dword salto
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Apuntar a la cadena invertida
    mov esi, reversa
    dec edi

; Invertir la cadena concatenada
invertir:
    mov dl, byte[edi]
    mov byte[esi], dl
    dec edi
    inc esi
    cmp edi, resultado
    jl imprimirReversa
    jge invertir
    ret

; Imprime la cadena invertida
imprimirReversa:          
    ; Mensaje que indica cual es la cadena inversa
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 17
    push dword inver
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Muestra la cadena inversa
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword [longitud]
    push dword reversa
    push dword [handleConsola]
    call _WriteConsoleA@20

    ; Salto de linea
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 2
    push dword salto
    push dword [handleConsola]
    call _WriteConsoleA@20

    mov ax, word[vocales]
    mov bx, 10
    mov cx, 0
    mov dx, 0
    mov edi, vocalesStr

; Obtenemos digito por digito
enteroACadena:              
    mov bx, 10
    div bx
    add dx, '0'
    push dx
    inc cx
    mov dx, 0
    cmp ax, 0
    jne enteroACadena

; Guardamos digito por digito
guardarDigitos:
    pop dx
    mov [edi], dx
    inc edi
    dec cx
    cmp cx, 0
    jne guardarDigitos

; Imprime la cantidad de vocales
imprimirVocales:
    ; Mensaje que indica la cantidad de vocales
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 19
    push dword voca
    push dword [handleConsola]
    call _WriteConsoleA@20

    ; Muestra la cantidad de vocales
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 4
    push dword vocalesStr
    push dword [handleConsola]
    call _WriteConsoleA@20

; Finaliza el programa
salida:
    push dword 0
    call _ExitProcess@4