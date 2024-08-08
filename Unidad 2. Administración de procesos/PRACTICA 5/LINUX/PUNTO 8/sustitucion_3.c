#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

/**
 * Definiciones de constantes para el tamaño de la matriz
 * 
 * N: Tamaño de la matriz.
 */
#define N 10

/**
 * Llena una matriz con valores aleatorios entre 0 y 100.
 * 
 * @param matriz La matriz a llenar.
 */
void LlenarMatriz(int matriz[N][N])
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            matriz[i][j] = rand() % 101; // Asigna un valor aleatorio entre 0 y 100.
        }
    }
}

/**
 * Imprime una matriz en la consola.
 * 
 * @param matriz La matriz a imprimir.
 */
void ImprimirMatriz(int matriz[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d\t", matriz[i][j]); // Imprime cada elemento seguido de un tabulador.
        printf("\n"); // Nueva línea al final de cada fila.
    }
}

/**
 * Convierte una matriz en una cadena de caracteres.
 * 
 * @param Matrizuno La matriz de entrada.
 * @param str La cadena de caracteres donde se almacenarán los valores de la matriz.
 */
void CrearStringMatriz(int Matrizuno[N][N], char str[N*N*10])
{
    str[0] = '\0'; // Inicializa la cadena como vacía.
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            sprintf(str + strlen(str), " %d", Matrizuno[i][j]); // Agrega el elemento a la cadena.
        }
    }
}

int main()
{
    srand(time(NULL)); // Inicializa la semilla para la generación de números aleatorios.

    // Declaración de las matrices
    int Matrizuno[N][N];
    int Matrizdos[N][N];

    // Se llenan las matrices con valores aleatorios
    LlenarMatriz(Matrizuno);
    LlenarMatriz(Matrizdos);

    // Declaración de la matriz que almacenará algunos de los resultados
    int Resultado[N][N];

    // Muestra en pantalla las dos matrices generadas
    printf("Matriz 1:\n");
    ImprimirMatriz(Matrizuno);
    printf("\nMatriz 2:\n");
    ImprimirMatriz(Matrizdos);

    // Cadena para almacenar las matrices como texto
    char MatrizunoC[N*N*10];
    char MatrizdosC[N*N*10];
    char *argv[4]; // Arreglo para argumentos de los procesos hijos

    // Crear la cadena de la matriz
    CrearStringMatriz(Matrizuno, MatrizunoC);
    CrearStringMatriz(Matrizdos, MatrizdosC);

    // Imprime el proceso raíz con su PID
    int id_proc;
    printf("Soy el proceso raíz. PID: %d\n", getpid());

    int pid_raiz = getpid();
    
    // Crear 6 procesos hijos
    for (int i = 0; i < 6; i++)
    {
        id_proc = fork(); // Crea un nuevo proceso
        
        sleep(1); // Pausa para evitar conflictos de impresión

        if (id_proc < 0)
        {
            perror("fork fallido"); // Manejo de error si fork falla
            exit(1);
        } 
        else if (id_proc == 0) // Proceso hijo
        { 
            printf("Soy el proceso hijo %d con PID: %d, mi padre es el proceso raíz con PID: %d\n", i+1, getpid(), pid_raiz);

            switch (i)
            {
                case 0:
                    argv[0] = "suma"; // Proceso para la suma
                    argv[1] = MatrizunoC;
                    argv[2] = MatrizdosC;
                    argv[3] = NULL;
                    execv(argv[0], argv); // Ejecuta el comando 'suma'
                    break;
                case 1:
                    argv[0] = "resta"; // Proceso para la resta
                    argv[1] = MatrizunoC;
                    argv[2] = MatrizdosC;
                    argv[3] = NULL;
                    execv(argv[0], argv);
                    break;
                case 2:
                    argv[0] = "multiplicacion"; // Proceso para la multiplicación
                    argv[1] = MatrizunoC;
                    argv[2] = MatrizdosC;
                    argv[3] = NULL;
                    execv(argv[0], argv);
                    break;
                case 3: 
                    argv[0] = "traspuesta"; // Proceso para la traspuesta
                    argv[1] = MatrizunoC;
                    argv[2] = MatrizdosC;
                    argv[3] = NULL;
                    execv(argv[0], argv);
                    break;
                case 4: 
                    argv[0] = "inversa"; // Proceso para la inversa
                    argv[1] = MatrizunoC;
                    argv[2] = MatrizdosC;
                    argv[3] = NULL;
                    execv(argv[0], argv);
                    break;
                case 5:
                    argv[0] = "archivo"; // Proceso para manejar el archivo
                    argv[1] = NULL;
                    execv(argv[0], argv);      
                    break;
            }
            exit(0); // Termina el proceso hijo después de ejecutar
        }
        else
        {
            wait(0); // Espera a que el proceso hijo termine
        }
    }
    return 0; // Finaliza el proceso principal
}