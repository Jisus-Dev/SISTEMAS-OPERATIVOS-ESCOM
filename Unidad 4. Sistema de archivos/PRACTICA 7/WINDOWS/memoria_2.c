#include <windows.h> /* Servidor de la memoria compartida */
#include <stdio.h>   /* (ejecutar el servidor antes de ejecutar el cliente)*/
#define TAM_MEM 27    /* Tamaño de la memoria compartida en bytes */

int main(void) {
    HANDLE hMemCom;
    char *idMemCompartida = "MemoriaCompartida";
    char *apDatos, *apTrabajo, c;

    // Crea un mapeo de archivo para la memoria compartida
    if ((hMemCom = CreateFileMapping(
            INVALID_HANDLE_VALUE, // Usa memoria compartida
            NULL,                 // Seguridad por defecto
            PAGE_READWRITE,       // Acceso lectura/escritura a la memoria
            0,                    // Tamaño máximo parte alta de un DWORD
            TAM_MEM,              // Tamaño máximo parte baja de un DWORD
            idMemCompartida       // Identificador de la memoria compartida
        )) == NULL) {
        printf("No se creó la memoria compartida: (%i)\n", GetLastError());
        exit(-1);
    }

    // Mapea la vista del archivo a la memoria del proceso
    if ((apDatos = (char *)MapViewOfFile(
            hMemCom,            // Manejador del mapeo
            FILE_MAP_ALL_ACCESS, // Permiso de lectura/escritura en la memoria
            0,
            0,
            TAM_MEM
        )) == NULL) {
        printf("No se enlazó la memoria compartida: (%i)\n", GetLastError());
        CloseHandle(hMemCom);
        exit(-1);
    }

    // Escribe datos en la memoria compartida
    apTrabajo = apDatos;
    for (c = 'a'; c <= 'z'; c++) {
        *apTrabajo++ = c;
    }
    *apTrabajo = '\0';

    // Espera hasta que el cliente modifique el primer byte de la memoria compartida
    while (*apDatos != '*') {
        Sleep(1);
    }
    
    // Desmapea la vista del archivo de la memoria del proceso
    UnmapViewOfFile(apDatos);
    // Cierra el manejador de la memoria compartida
    CloseHandle(hMemCom);

    return 0;
}
