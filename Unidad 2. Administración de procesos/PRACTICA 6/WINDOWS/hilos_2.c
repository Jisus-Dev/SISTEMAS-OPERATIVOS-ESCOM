#include <windows.h> 
#include <stdio.h> 

int main(int argc, char *argv[]) 
{
    STARTUPINFO si; // Estructura de información inicial para Windows
    PROCESS_INFORMATION pi; // Estructura de información del administrador de procesos
    int i; 

    // Inicializa la estructura STARTUPINFO con ceros
    ZeroMemory(&si, sizeof(si)); 
    si.cb = sizeof(si); // Establece el tamaño de la estructura
    // Inicializa la estructura PROCESS_INFORMATION con ceros
    ZeroMemory(&pi, sizeof(pi)); 

    // Verifica que se haya proporcionado exactamente un argumento
    if(argc != 2) 
    {
        printf("Usar: %s Nombre_programa_hijo\n", argv[0]); 
        return 1; 
    }

    // Creación del proceso hijo
    if(!CreateProcess(NULL, argv[1], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
    { 
        // Si falla la creación del proceso, muestra un mensaje de error con el código de error
        printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
        return 1; 
    } 

    // Espera a que el proceso hijo termine
    WaitForSingleObject(pi.hProcess, INFINITE); 

    // Cierra los handles del proceso e hilo asociados
    CloseHandle(pi.hProcess); 
    CloseHandle(pi.hThread); 

    return 0; 
}