#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid; // Almacena el ID del proceso.

    char *argv[4]; // Arreglo para los argumentos de los programas.

    pid = fork(); // Crea un nuevo proceso.

    if (pid == 0) // Código del proceso hijo.
    {
        printf("Soy el proceso hijo\n");

        pid = fork(); // Crea el primer proceso nieto.

        if (pid == 0) // Código del primer proceso nieto.
        {
            printf("\tSoy el primer proceso nieto\n");
            argv[0] = "./expresion";
            argv[1] = "5*8+9";
            argv[2] = NULL;
            execv(argv[0], argv); // Ejecuta el programa "expresion".
        }
        else
        {
            wait(0); // Espera al primer nieto.
            pid = fork(); // Crea el segundo proceso nieto.

            if (pid == 0) // Código del segundo proceso nieto.
            {
                printf("\tSoy el segundo proceso nieto\n");
                argv[0] = "./permisos";
                argv[1] = "Permisos.txt";
                argv[2] = "777";
                argv[3] = NULL;
                execv(argv[0], argv); // Ejecuta el programa "permisos".
            }
            else
            {
                wait(0); // Espera al segundo nieto.
                pid = fork(); // Crea el tercer proceso nieto.

                if (pid == 0) // Código del tercer proceso nieto.
                {
                    printf("\tSoy el tercer proceso nieto\n");
                    argv[0] = "./inversa";
                    argv[1] = NULL;
                    execv(argv[0], argv); // Ejecuta el programa "inversa".
                }
                else
                {
                    wait(0); // Espera al tercer nieto.
                }
            }
        }
    }
    else
    {
        wait(0); // Espera al proceso hijo.
        printf("\nSoy el Padre\n");
    }
}