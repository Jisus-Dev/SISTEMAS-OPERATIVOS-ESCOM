#include <windows.h> /* Cliente de la memoria compartida */
#include <stdio.h>
#define TAM_MEM 27 /* Tamaño de la memoria compartida en bytes */

int main(void)
{
    HANDLE hMemCom;
    char *idMemCompartida = "MemoriaCompartida";
    char *apDatos, *apTrabajo;

    // Abre el mapeo de archivo de la memoria compartida
    if ((hMemCom = OpenFileMapping(
            FILE_MAP_ALL_ACCESS, // Acceso lectura/escritura de la memoria compartida
            FALSE,               // No se hereda el nombre
            idMemCompartida      // Identificador de la memoria compartida
        )) == NULL) {
        printf("No se accedió a la memoria compartida: (%i)\n", GetLastError());
        exit(-1);
    }

    // Mapea la vista del archivo a la memoria del proceso
    if ((apDatos = (char *)MapViewOfFile(
            hMemCom,           // Manejador del mapeo
            FILE_MAP_ALL_ACCESS, // Permiso de lectura/escritura en la memoria
            0,
            0,
            TAM_MEM
        )) == NULL) {
        printf("No se enlazó la memoria compartida: (%i)\n", GetLastError());
        CloseHandle(hMemCom);
        exit(-1);
    }

    // Lee datos de la memoria compartida y los imprime
    for (apTrabajo = apDatos; *apTrabajo != '\0'; apTrabajo++) {
        putchar(*apTrabajo);
    }
    putchar('\n');

    // Modifica el primer byte de la memoria compartida
    *apDatos = '*';

    // Desmapea la vista del archivo de la memoria del proceso
    UnmapViewOfFile(apDatos);
    // Cierra el manejador de la memoria compartida
    CloseHandle(hMemCom);

    return 0;
}