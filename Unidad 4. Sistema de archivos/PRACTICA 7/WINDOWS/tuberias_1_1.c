/* Programa hijo.c */
#include <windows.h>
#include <stdio.h>

int main()
{
    char mensaje[20];
    DWORD leidos;
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);

    // Lectura desde la tubería sin nombre
    ReadFile(hStdIn, mensaje, sizeof(mensaje), &leidos, NULL);
    printf("Mensaje recibido del proceso padre: %s\n", mensaje);

    // Cierre del manejador de entrada estándar
    CloseHandle(hStdIn);

    printf("Termina el proceso hijo, continua el proceso padre\n");
    return 0;
}