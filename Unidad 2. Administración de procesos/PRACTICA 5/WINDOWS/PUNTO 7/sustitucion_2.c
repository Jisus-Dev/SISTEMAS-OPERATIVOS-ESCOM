#include <windows.h> 
#include <stdio.h> 

int main(int argc, char *argv[]) 
{
    STARTUPINFO si;             /* Estructura de información inicial para Windows */
    PROCESS_INFORMATION pi;     /* Estructura de información del adm. de procesos */
    int i; 

    // Inicializa la memoria de las estructuras con ceros
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Creación proceso hijo
    if(!CreateProcess(NULL, argv[1], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
    { 
        printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
        return 1; 
    }

    // Proceso padre
    printf("\n\t ** ARBOL DE PROCESOS **\n");
    printf("\n\t ---> Soy el padre, Mi PID es: %d\n", GetCurrentProcessId());

    // Espera a que el proceso hijo termine
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Terminación controlada del proceso e hilo asociado de ejecución
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0; 
}