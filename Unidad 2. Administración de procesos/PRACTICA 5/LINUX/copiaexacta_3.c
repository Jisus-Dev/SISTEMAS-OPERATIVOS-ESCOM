#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    int id_proc;

    // Bucle para crear 5 procesos hijos
    for(int a = 1 ; a <= 5; a++)
    {
        id_proc = fork(); // Crear un nuevo proceso

        // Si estamos en el proceso hijo
        if(id_proc == 0)
        {
            // Si es el primer hijo
            if(a == 1)
            {
                printf("Soy el proceso main, PID: %d\n", getppid());
                printf("Soy el primer hijo, PID: %d, PID del padre: %d\n", getpid(), getppid());

                // Crear 2 procesos nietos
                for(int b = 1; b <= 2; b++)
                {
                    id_proc = fork();

                    if(id_proc == 0)
                    {
                        if(b == 1)
                        {
                            printf("\tSoy el primer nieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                        }
                        if(b == 2)
                        {
                            printf("\tSoy el segundo nieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                        }
                        exit(0); // Salir de cada proceso nieto
                    }
                    else
                    {
                        wait(NULL); // Esperar a que cada proceso nieto termine
                    }                
                }
                exit(0); // Salir del primer proceso hijo
            }

            // Si es el segundo hijo
            if(a == 2)
            {
                printf("Soy el segundo hijo, PID: %d, PID del padre: %d\n", getpid(), getppid());

                id_proc = fork(); // Crear un proceso nieto

                if(id_proc == 0)
                {
                    printf("\tSoy el tercer nieto, PID: %d, PID del padre: %d\n", getpid(), getppid());

                    // Crear 3 procesos bisnietos
                    for(int c = 1; c <= 3; c++)
                    {
                        id_proc = fork();

                        if(id_proc == 0)
                        {
                            if(c == 1)
                            {
                                printf("\t\tSoy el primer bisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                            }
                            if(c == 2)
                            {
                                printf("\t\tSoy el segundo bisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                            }
                            if(c == 3)
                            {
                                printf("\t\tSoy el tercer bisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                            }
                            exit(0); // Salir de cada proceso bisnieto
                        }
                        else
                        {
                            wait(NULL); // Esperar a que cada proceso bisnieto termine
                        }
                    }
                    exit(0); // Salir de cada proceso nieto
                }
                else
                {
                    wait(NULL); // Esperar a que cada proceso nieto termine
                }
                exit(0); // Salir del segundo proceso hijo
            }

            // Si es el tercer hijo
            if(a == 3)
            {
                printf("Soy el tercer hijo, PID: %d, PID del padre: %d\n", getpid(), getppid());

                // Crear 2 procesos un nieto y un bisnieto
                for(int d = 1; d <= 2; d++)
                {
                    id_proc = fork();

                    if(id_proc == 0)
                    {
                        if(d == 1)
                        {
                            printf("\tSoy el cuarto nieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                        }
                        if(d == 2)
                        {
                            printf("\t\tSoy el cuarto bisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());

                            // Crear 4 procesos trisnietos
                            for(int e = 1; e <= 4; e++)
                            {
                                id_proc = fork();

                                if(id_proc == 0)
                                {
                                    if(e == 1)
                                    {
                                        printf("\t\t\tSoy el primer trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    if(e == 2)
                                    {
                                        printf("\t\t\tSoy el segundo trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    if(e == 3)
                                    {
                                        printf("\t\t\tSoy el tercer trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    if(e == 4)
                                    {
                                        printf("\t\t\tSoy el cuarto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    exit(0); // Salir de cada proceso trisnieto
                                }
                                else
                                {
                                    wait(NULL); // Esperar a que cada proceso trisnieto termine
                                }
                            }
                        }
                    }
                    else
                    {
                        wait(NULL); // Esperar a que el proceso nieto y bisnieto termine
                        exit(0); // Salir del proceso nieto y bisnieto
                    }
                }
                exit(0); // Salir del tercer proceso hijo
            }

            // Si es el cuarto hijo
            if(a == 4)
            {
                printf("Soy el cuarto hijo, PID: %d, PID del padre: %d\n", getpid(), getppid());

                // Crear 3 procesos un nieto, un bisnieto y un trisnieto
                for(int f = 1; f <= 3; f++)
                {
                    id_proc = fork();

                    if(id_proc == 0)
                    {
                        if(f == 1)
                        {
                            printf("\tSoy el quinto nieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                        }

                        if(f == 2)
                        {
                            printf("\t\tSoy el quinto bisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                        }

                        if(f == 3)
                        {
                            printf("\t\t\tSoy el quinto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());

                            // Crear 5 procesos hijos del trisnieto
                            for(int g = 1; g <= 5; g++)
                            {
                                id_proc = fork();

                                if(id_proc == 0)
                                {
                                    if(g == 1)
                                    {
                                        printf("\t\t\t\tSoy el primer hijo del quinto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    if(g == 2)
                                    {
                                        printf("\t\t\t\tSoy el segundo hijo del quinto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    if(g == 3)
                                    {
                                        printf("\t\t\t\tSoy el tercer hijo del quinto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    if(g == 4)
                                    {
                                        printf("\t\t\t\tSoy el cuarto hijo del quinto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    if(g == 5)
                                    {
                                        printf("\t\t\t\tSoy el quinto hijo del quinto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    exit(0); // Salir de cada proceso hijo del trisnieto
                                }
                                else
                                {
                                    wait(NULL); // Esperar a que cada proceso hijo del trisnieto termine
                                }
                            }
                        }
                    }
                    else
                    {
                        wait(NULL); // Esperar a que el proceso nieto, bisnieto y trisnieto termine
                        exit(0); // Salir del proceso nieto, bisnieto y trisnieto
                    }
                }
                exit(0); // Salir del cuarto proceso hijo
            }

            // Si es el quinto hijo
            if(a == 5)
            {
                printf("Soy el quinto hijo, PID: %d, PID del padre: %d\n", getpid(), getppid());

                // Crear 4 procesos un nieto, un bisnieto, un trisnieto y un hijo del trisnieto
                for(int h = 1; h <= 4; h++)
                {
                    id_proc = fork();

                    if(id_proc == 0)
                    {
                        if(h == 1)
                        {
                            printf("\tSoy el sexto nieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                        }
                        if(h == 2)
                        {
                            printf("\t\tSoy el sexto bisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                        }
                        if(h == 3)
                        {
                            printf("\t\t\tSoy el sexto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                        }
                        if(h == 4)
                        {
                            printf("\t\t\t\tSoy el hijo del sexto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());

                            // Crear 6 procesos hijos del hijo del trisnieto
                            for(int i = 1; i <= 6; i++)
                            {
                                id_proc = fork();

                                if(id_proc == 0)
                                {
                                    if(i == 1)
                                    {
                                        printf("\t\t\t\t\tSoy el primer hijo del hijo del sexto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    if(i == 2)
                                    {
                                        printf("\t\t\t\t\tSoy el segundo hijo del hijo del sexto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    if(i == 3)
                                    {
                                        printf("\t\t\t\t\tSoy el tercer hijo del hijo del sexto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    if(i == 4)
                                    {
                                        printf("\t\t\t\t\tSoy el cuarto hijo del hijo del sexto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    if(i == 5)
                                    {
                                        printf("\t\t\t\t\tSoy el quinto hijo del hijo del sexto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    if(i == 6)
                                    {
                                        printf("\t\t\t\t\tSoy el sexto hijo del hijo del sexto trisnieto, PID: %d, PID del padre: %d\n", getpid(), getppid());
                                    }
                                    exit(0); // Salir de cada proceso hijo del hijo del trisnieto
                                }
                                else
                                {
                                    wait(NULL); // Esperar a que cada proceso hijo del hijo del trisnieto termine
                                }
                            }
                        }
                    }
                    else
                    {
                        wait(NULL); // Esperar a que el proceso nieto, bisnieto, trisnieto y hijo del trisnieto termine
                        exit(0); // Salir del proceso nieto, bisnieto, trisnieto y hijo del trisnieto
                    }
                }
            }
            exit(0); // Salir del quinto proceso hijo
        }
        else
        {
            wait(NULL); // Esperar a que el proceso hijo termine
        }
    }
    return 0; // Salir del proceso principal
}