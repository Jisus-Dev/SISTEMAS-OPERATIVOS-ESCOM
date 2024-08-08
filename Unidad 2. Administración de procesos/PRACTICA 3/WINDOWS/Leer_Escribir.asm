segment .bss
    handleConsola resd 1         ; Primer argumento para la llamada al sistema _ReadConsoleA()
    cadLeer resb 30              ; Segundo argumento para la llamada al sistema _ReadConsoleA()
    longitudCadena resd 1        ; Tercer argumento para la llamada al sistema _ReadConsoleA()
    caractLeidos resd 1          ; Cuarto argumento para la llamada al sistema _ReadConsoleA()
    ultimoArgumento resd 1       ; Quinto argumento para la llamada al sistema _ReadConsoleA()

segment .text
    global _main
    extern _GetStdHandle@4       ; Acceso externo a la llamada al sistema _GetStdHandle()
    extern _WriteConsoleA@20     ; Acceso externo a la llamada al sistema _WriteConsoleA()
    extern _ReadConsoleA@20      ; Acceso externo a la llamada al sistema _ReadConsoleA()
    extern _ExitProcess@4        ; Acceso externo a la llamada al sistema _ExitProcess()

_main:
    push dword -10               ; Argumento pasado por la pila y usado en _GetStdHandle() para la entrada estándar
    call _GetStdHandle@4         ; Invocación de _GetStdHandle()
    mov [handleConsola], eax     ; Devolución del manejador de consola para lectura en el registro eax

    xor eax, eax                 ; Limpieza del registro eax (eax=0)
    mov eax, 30d                 ; eax=30 caracteres de longitud de la cadena a leer
    mov [longitudCadena], eax    ; Se guarda la longitud en memoria
    xor eax, eax                 ; Limpieza del registro eax (eax=0)
    mov eax, 0d                  ; eax=0 valor del último argumento de _ReadConsoleA()
    mov [ultimoArgumento], eax   ; Se guarda el valor del último argumento en memoria

    push dword [ultimoArgumento] ; Quinto argumento de _ReadConsoleA() pasado por la pila
    push dword caractLeidos      ; Cuarto argumento de _ReadConsoleA() pasado por la pila
    push dword [longitudCadena]  ; Tercer argumento de _ReadConsoleA() pasado por la pila
    push dword cadLeer           ; Segundo argumento de _ReadConsoleA() pasado por la pila
    push dword [handleConsola]   ; Primer argumento de _ReadConsoleA() pasado por la pila
    call _ReadConsoleA@20        ; Invocación de _ReadConsoleA()

    xor eax, eax
    push dword -11               ; Argumento pasado por la pila y usado en _GetStdHandle() para la salida estándar
    call _GetStdHandle@4         ; Invocación de _GetStdHandle()
    mov [handleConsola], eax     ; Devolución del manejador de consola para escritura en el registro eax

    xor eax, eax                 ; Limpieza del registro eax (eax=0)
    mov eax, 30d                 ; eax=30 caracteres de longitud de la cadena a imprimir
    mov [longitudCadena], eax    ; Se guarda la longitud en memoria
    xor eax, eax                 ; Limpieza del registro eax (eax=0)
    mov eax, 0d                  ; eax=0 valor del último argumento de _WriteConsoleA()
    mov [ultimoArgumento], eax   ; Se guarda el valor del último argumento en memoria

    push dword [ultimoArgumento] ; Quinto argumento de _WriteConsoleA() pasado por la pila
    push dword caractLeidos      ; Cuarto argumento de _WriteConsoleA() pasado por la pila
    push dword [longitudCadena]  ; Tercer argumento de _WriteConsoleA() pasado por la pila
    push dword cadLeer           ; Segundo argumento de _WriteConsoleA() pasado por la pila
    push dword [handleConsola]   ; Primer argumento de _WriteConsoleA() pasado por la pila
    call _WriteConsoleA@20       ; Invocación de _WriteConsoleA()

    xor eax, eax                 ; Limpieza del registro eax (eax=0)
    mov eax, 0d                  ; eax=0 valor del argumento de _ExitProcess()
    mov [ultimoArgumento], eax   ; Se guarda el valor del argumento en memoria
    push dword [ultimoArgumento] ; Argumento de _ExitProcess() pasado por la pila
    call _ExitProcess@4          ; Invocación de _ExitProcess()