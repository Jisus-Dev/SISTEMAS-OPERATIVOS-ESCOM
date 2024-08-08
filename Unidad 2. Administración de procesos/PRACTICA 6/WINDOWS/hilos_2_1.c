#include <windows.h>
#include <stdio.h>

// Identificador del hilo
DWORD idHilo;
// Manejador del hilo
HANDLE manHilo;

// Función que será ejecutada por el hilo de nivel 3
DWORD WINAPI hilo3(LPVOID lpParam)
{
    printf("\t\t\tPractica 6 hilo terminal\n");
    return 0;
}

// Función que será ejecutada por el hilo de nivel 2
DWORD WINAPI hilo2(LPVOID lpParam)
{
    printf("\t2- %d\n", GetCurrentThreadId());

    // Crear 10 hilos de nivel 3
    for (int i = 0; i < 10; i++)
    {
        manHilo = CreateThread(NULL, 0, hilo3, NULL, 0, &idHilo);
    }

    return 0;
}

// Función que será ejecutada por el hilo de nivel 1
DWORD WINAPI hilo(LPVOID lpParam)
{
    printf("1- %d\n", GetCurrentThreadId());

    // Crear 15 hilos de nivel 2
    for (int i = 0; i < 15; i++)
    {
        manHilo = CreateThread(NULL, 0, hilo2, NULL, 0, &idHilo);
    }

    return 0;
}

int main(void)
{
    // Crear 20 hilos de nivel 1
    for (int i = 0; i < 20; i++)
    {
        manHilo = CreateThread(NULL, 0, hilo, NULL, 0, &idHilo);
    }

    // Esperar a que el último hilo de nivel 1 termine
    WaitForSingleObject(manHilo, INFINITE);
    // Cerrar el manejador del hilo
    CloseHandle(manHilo);

    return 0;
}