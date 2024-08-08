#include <windows.h>
#include <stdio.h>

int main()
{
    STARTUPINFO si;             /* Estructura de información inicial para Windows */
    PROCESS_INFORMATION pi;     /* Estructura de información del adm. de procesos */
    int i;
    int j;

    // Indica que este proceso es el hijo
    printf("\n\t\t --> Soy el hijo, Mi PID es: %d\n", GetCurrentProcessId());

    // Bucle para crear 5 procesos hijos
    for(j = 0; j < 5; j++)
    {
        // Inicializa la memoria de las estructuras con ceros
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        // Creación del proceso hijo
        if(!CreateProcess(NULL, "sustitucion_2_2", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
        {
            printf("Fallo al invocar CreateProcess (%d)\n", GetLastError());
            return 1;
        }

        // Espera a que el proceso hijo termine
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Terminación controlada del proceso e hilo asociado de ejecución
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    return 0;
}