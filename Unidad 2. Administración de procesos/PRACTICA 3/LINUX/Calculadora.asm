; Programe una aplicacion en ensamblador que implemente
; una calculadora con las cuatro operaciones basicas.
; A traves de un menu, de la posibilidad de seleccionar
; la operacion a realizar.

; Seccion de datos para variables globales
section .data 
    ; Mensaje para el menu
    opc1 db '1 > Operacion Suma',0xa
    opc2 db '2 > Operacion Resta',0xa
    opc3 db '3 > Operacion Division',0xa
    opc4 db '4 > Operacion Multiplicacion',0xa
    
    ; Mensaje para digitar la opcion
    opc db 'Opcion >',0
    opcl equ ($-opc)
    
    ; Mensaje para digitar cada operando
    soln1 db 'Numero 1 >',0
    soln2 db 'Numero 2 >',0
    nega db '-'
    negal equ ($-nega)
    suma db 'Suma',10
    sumal equ ($-suma)
    
    ; Mensaje para mostrar el resultado
    resu db 'Resultado >',0
  
; Seccion para variables no inicializadas
section .bss
    ; Variables para cada una de las cadenas
    opcion resb 2
    num1 resb 50
    num2 resb 50
    espDigito resb 100
    posDigito resb 8

; Seccion de texto (codigo)
section .text

; Punto de entrada del programa
global _start

; Inicio de la funcion principal
_start:
    ; Mostrar el menu inicial

    ; Opcion Suma
    mov edx, 19
    mov ecx, opc1
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Opcion Resta
    mov edx, 20
    mov ecx, opc2
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Opcion Division
    mov edx, 23
    mov ecx, opc3
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Opcion Multiplicacion
    mov edx, 29
    mov ecx, opc4
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Mensaje de la opcion
    mov edx, 9
    mov ecx, opc
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Lectura de la opcion digitada por el usuario
    mov edx, 2
    mov ecx, opcion
    mov ebx, 0
    mov eax, 3
    int 0x80

    ; Mensaje para el operando uno
    mov edx, 11
    mov ecx, soln1
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Lectura del operando uno
    mov edx, 50
    mov ecx, num1
    mov ebx, 0
    mov eax, 3
    int 0x80

    ; Mensaje para el operando dos
    mov edx, 11
    mov ecx, soln2
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Lectura del operando dos
    mov edx, 50
    mov ecx, num2
    mov ebx, 0
    mov eax, 3
    int 0x80

    ; Determianr la opcion seleccionada
    sub byte [opcion], '0'
    cmp byte [opcion], byte 1
    je sum
    cmp byte [opcion], byte 2
    je res
    cmp byte [opcion], byte 3
    je divi
    cmp byte [opcion], byte 4
    je multi

; Funcion para realizar la suma
sum:
    ; Mensaje de resultado
    mov edx, 13
    mov ecx, resu
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Opera con cada uno de los operandos
    mov rax, num1
    call atoi
    push rax
    mov rax, num2
    call atoi
    pop rdx
    add rax, rdx

    ; Comienza el proceso de impresion del resultado
    call imprimir

    ; Finaliza el programa
    mov eax, 1
    int 0x80

; Funcion para realizar la resta
res:
    ; Mensaje de resultado
    mov edx, 13
    mov ecx, resu
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Opera con cada uno de los operandos
    mov rax, num1
    call atoi
    push rax
    mov rax, num2
    call atoi
    pop rdx
    cmp rax, rdx
    jg cambio
    sub rdx, rax
    mov rax, rdx

    ; Comienza el proceso de impresion del resultado
    call imprimir

    ; Finaliza el programa
    mov eax, 1
    int 0x80

; Funcion en caso de valor negativo
cambio:
    push rax
    push rdx

    ; Muestra el simbolo de negativo (-)
    mov edx, negal
    mov ecx, nega
    mov ebx, 1
    mov eax, 4
    int 0x80
    pop rdx
    pop rax
    sub rax, rdx

    ; Comienza el proceso de impresion del resultado
    call imprimir

    ; Finaliza el programa
    mov eax, 1
    int 0x80

; Funcion para realizar la division
divi:
    ; Mensaje de resultado
    mov edx, 13
    mov ecx, resu
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; Opera con cada uno de los operandos
    mov rax, num1
    call atoi
    push rax
    mov rax, num2
    call atoi
    mov rbx, rax
    pop rax
    div rbx

    ; Comienza el proceso de impresion del resultado
    call imprimir

    ; Finaliza el programa
    mov eax, 1
    int 0x80

; Funcion para realizar la multiplicacion
multi:
    ; Mensaje de resultado
    mov edx, 13
    mov ecx, resu
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    ; Opera con cada uno de los operandos
    mov rax, num1
    call atoi
    push rax
    mov rax, num2
    call atoi
    mov rbx, rax
    pop rax
    mul rbx

    ; Comienza el proceso de impresion del resultado
    call imprimir

    ; Finaliza el programa
    mov eax, 1
    int 0x80

; Convierte una cadena en ASCII
atoi:
    ; Funcion para convertir ASCII a entero
    mov esi, eax
    mov eax, 0
    mov ecx, 0

; Convierte una cadena en un numero
.potencia10:
    xor ebx, ebx
    mov bl, [esi+ecx]
    cmp bl, 48
    jl .finatoi
    cmp bl, 57
    jg .finatoi
    cmp bl, 10
    je .finatoi
    cmp bl, 0
    jz .finatoi
    sub bl, 48
    add eax, ebx
    mov ebx, 10
    mul ebx
    inc ecx
    jmp .potencia10

; Divide entre 10 ya que sobro una potencia de 10
.finatoi:
    mov ebx, 10
    div ebx
    ret

; Inicializa espDigito que indica el resultado de la operacion
imprimir:
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

; Bucle para imprimir el resultado en consola
bucle2:
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
