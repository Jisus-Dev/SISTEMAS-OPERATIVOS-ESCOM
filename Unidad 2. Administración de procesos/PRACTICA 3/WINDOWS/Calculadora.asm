; Programe una aplicación en ensamblador que implemente 
; una calculadora con las cuatro operaciones básicas. 
; A través de un menú, dé la posibilidad de seleccionar 
; la operación a realizar.

; Segmento de datos para variables globales
segment .data
    ; Mensajes para el menu
    opc1 db '1 > Operacion Suma',0xa
    opc2 db '2 > Operacion Resta',0xa
    opc3 db '3 > Operacion Division',0xa
    opc4 db '4 > Operacion Multiplicacion',0xa
    
    ; Mensaje para digitar la opción
    opc db 'Opcion >',0
    
    ; Mensaje para digitar cada operando
    soln1 db 'Numero 1 >',0
    soln2 db 'Numero 2 >',0
    nega db '-'
    negal equ ($-nega)
    suma db 'Suma',10
    sumal equ ($-suma)
    
    ; Mensaje para mostrar el resultado
    resu db 'Resultado >',0

; Segmento para variables no inicializadas
segment .bss
    ; Variables para manejo de consola
    handleConsola   resd 1
    caractEscritos  resd 1
    longitudCadena  resd 1
    ultimoArgumento resd 1
    ; Variables para cada una de las cadenas
    opcion resb 3
    num1 resb 50
    num2 resb 50
    espDigito resb 100
    posDigito resb 8

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
    ; Mostrar el menú inicial

    ; Opción Suma
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
    push dword opc1
    push dword [handleConsola]
    call _WriteConsoleA@20
    
    ; Opción Resta
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 20
    push dword opc2
    push dword [handleConsola]
    call _WriteConsoleA@20;
    
    ; Opción División
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 23
    push dword opc3
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Opción Multiplicación
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 29
    push dword opc4
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Mensaje de la opción
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
    push dword opc
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Lectura de la opción digitada por el usuario
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
    push dword 3
    push dword opcion
    push dword [handleConsola]
    call _ReadConsoleA@20

    ; Mensaje para el operando uno
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 11
    push dword soln1
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Lectura del operando uno
    push dword -10
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,50
    mov[longitudCadena],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 50
    push dword num1
    push dword [handleConsola]
    call _ReadConsoleA@20

    ; Mensaje para el operando dos
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 11
    push dword soln2
    push dword [handleConsola]
    call _WriteConsoleA@20;
    
    ; Lectura del operando dos
    push dword -10
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,50
    mov[longitudCadena],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 50
    push dword num2
    push dword [handleConsola]
    call _ReadConsoleA@20

    ; Determinar la opción seleccionada
    sub byte [opcion],'0'
    cmp byte [opcion],byte 1
    je sum
    cmp byte [opcion],byte 2
    je res
    cmp byte [opcion],byte 3
    je divi
    cmp byte [opcion],byte 4
    je multi


; Funcion para realizar la suma
sum:
    ; Mensaje de resultado
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 11
    push dword resu
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Opera con cada uno de los operandos
    mov eax, num1
    call atoi
    push eax
    mov eax, num2
    call atoi
    pop edx
    add eax,edx

    ; Comienza el proceso de impresión del resultado
    call imprimir

    ; Finaliza el programa
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    call _ExitProcess@4

; Función para realizar la resta
res:
    ; Mensaje de resultado
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 11
    push dword resu
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Opera con cada uno de los operandos
    mov eax, num1
    call atoi
    push eax
    mov eax, num2
    call atoi
    pop edx
    cmp eax,edx
    jg cambio
    sub edx,eax
    mov eax, edx

    ; Comienza el proceso de impresión del resultado
    call imprimir

    ; Finaliza el programa
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    call _ExitProcess@4

; Función en caso de valor negativo
cambio:
    push eax
    push edx

    ; Muestra el símbolo de negativo (-)
    push dword-11
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword negal
    push dword nega
    push dword [handleConsola]
    call _WriteConsoleA@20;
    pop edx
    pop eax
    sub eax,edx

    ; Comienza el proceso de impresión del resultado
    call imprimir

    ; Finaliza el programa
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    call _ExitProcess@4

; Función para realizar la división
divi:
    ; Mensaje de resultado
    push dword-11
    xor eax,eax
    call _GetStdHandle@4
    mov [handleConsola],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    push dword caractEscritos
    push dword 11
    push dword resu
    push dword [handleConsola]
    call _WriteConsoleA@20;

    ; Opera con cada uno de los operandos
    mov eax, num1
    call atoi
    push eax
    mov eax, num2
    call atoi
    mov ebx,eax
    pop eax
    div ebx

    ; Comienza el proceso de impresión del resultado
    call imprimir

    ; Finaliza el programa
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    call _ExitProcess@4

; Función para realizar la multiplicación
multi:
    ; Mensaje de resultado
    push dword-11
    xor eax,eax;
    call _GetStdHandle@4;
    mov [handleConsola],eax;
    xor eax,eax;
    mov eax,0d;
    mov [ultimoArgumento],eax;
    push dword [ultimoArgumento];
    push dword caractEscritos;
    push dword 11;
    push dword resu
    push dword [handleConsola];
    call _WriteConsoleA@20;

    ; Opera con cada uno de los operandos
    mov eax, num1
    call atoi
    push eax
    mov eax, num2
    call atoi
    mov ebx,eax
    pop eax
    mul ebx

    ; Comienza el proceso de impresión del resultado
    call imprimir

    ; Finaliza el programa
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    call _ExitProcess@4;

; Convierte una cadena en ASCII
atoi:
    mov     esi, eax
    mov     eax, 0
    mov     ecx, 0

; Convierte una cadena en un numero
.potencia10:
    xor     ebx, ebx
    mov     bl, [esi+ecx]
    cmp     bl, 48
    jl      .finatoi
    cmp     bl, 57
    jg      .finatoi
    cmp     bl, 10
    je      .finatoi
    cmp     bl, 0
    jz      .finatoi
    sub     bl, 48
    add     eax, ebx
    mov     ebx, 10
    mul     ebx
    inc     ecx
    jmp     .potencia10

; Divide entre 10 ya que sobro una potencia de 10
.finatoi:
    mov     ebx, 10 
    div     ebx
    ret

; Inicializa espDigito que indica el resultado de la operacion
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

; Bucle para imprimir el resultado en consola
bucle2:
    mov ecx, [posDigito]

    push dword-11
    xor eax,eax
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