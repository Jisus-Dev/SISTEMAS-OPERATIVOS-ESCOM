#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    char mensaje[] = "Tuberias en Windows";
    DWORD escritos;
    HANDLE hLecturaPipe, hEscrituraPipe;
    PROCESS_INFORMATION piHijo;
    STARTUPINFO siHijo;
    SECURITY_ATTRIBUTES pipeSeg = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

    // Obtención de información para la inicialización del proceso hijo
    GetStartupInfo(&siHijo);

    // Creación de la tubería sin nombre
    CreatePipe(&hLecturaPipe, &hEscrituraPipe, &pipeSeg, 0);

    // Escritura en la tubería sin nombre
    WriteFile(hEscrituraPipe, mensaje, strlen(mensaje) + 1, &escritos, NULL);

    // Configuración de los manejadores estándar del proceso hijo
    siHijo.hStdInput = hLecturaPipe;
    siHijo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    siHijo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    siHijo.dwFlags = STARTF_USESTDHANDLES;

    // Creación del proceso hijo, heredando los manejadores de la tubería del padre
    CreateProcess(
        NULL, argv[1], NULL, NULL, TRUE, 0, NULL, NULL, &siHijo, &piHijo
    );

    // Espera a que el proceso hijo termine
    WaitForSingleObject(piHijo.hProcess, INFINITE);

    printf("Mensaje recibido en el proceso hijo, termina el proceso padre\n");

    // Cierre de los manejadores
    CloseHandle(hLecturaPipe);
    CloseHandle(hEscrituraPipe);
    CloseHandle(piHijo.hThread);
    CloseHandle(piHijo.hProcess);

    return 0;
}