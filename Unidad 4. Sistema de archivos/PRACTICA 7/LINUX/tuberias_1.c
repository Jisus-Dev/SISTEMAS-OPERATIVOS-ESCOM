#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define VALOR 1

int main(void) {
    int desc_arch[2];
    char bufer[100];

    // Crear el pipe
    if (pipe(desc_arch) != 0)
    {
        exit(1);
    }

    // Crear un proceso hijo
    if (fork() == 0)
    {
        // Código del proceso hijo
        while (VALOR)
        {
            read(desc_arch[0], bufer, sizeof(bufer));
            printf("Se recibió: %s\n", bufer);
        }
    } 
    else
    {
        // Código del proceso padre
        while (VALOR)
        {
            printf("Escriba un mensaje: ");
            fgets(bufer, sizeof(bufer), stdin);
            write(desc_arch[1], bufer, strlen(bufer) + 1);
        }
    }
    
    return 0;
}
