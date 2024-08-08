#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

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
            matriz[i][j] = rand() % 101; // Genera números aleatorios entre 0 y 100
        }
    }
}

/**
 * Imprime una matriz de enteros.
 * 
 * @param matriz La matriz de enteros a imprimir.
 */
void ImprimirMatriz(int matriz[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d\t", matriz[i][j]); // Imprime cada elemento seguido de una tabulación.
        printf("\n"); // Nueva línea al final de cada fila.
    }
}

/**
 * Imprime una matriz de doubles (decimales).
 * 
 * @param matriz La matriz a imprimir.
 */
void ImprimirInversa(double matriz[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%lf  ", matriz[i][j]); // Imprime cada elemento seguido de dos espacios.
        printf("\n"); // Nueva línea al final de cada fila.
    }
}

/**
 * Suma dos matrices cuadradas y guarda el resultado en una tercera matriz.
 * 
 * @param matrizuno La primera matriz de entrada.
 * @param matrizdos La segunda matriz de entrada.
 * @param resultado La matriz de salida donde se guarda el resultado de la suma.
 */
void SumarMatrices(int matrizuno[N][N], int matrizdos[N][N], int resultado[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            resultado[i][j] = matrizuno[i][j] + matrizdos[i][j]; // Suma elemento a elemento.
        }
    }
}

/**
 * Resta dos matrices y guarda el resultado en una tercera matriz.
 * 
 * @param matrizuno La primera matriz de entrada.
 * @param matrizdos La segunda matriz de entrada.
 * @param resultado La matriz de salida donde se guarda el resultado de la resta.
 */
void RestarMatrices(int matrizuno[N][N], int matrizdos[N][N], int resultado[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            resultado[i][j] = matrizuno[i][j] - matrizdos[i][j]; // Resta elemento a elemento.
        }
    }
}

/**
 * Multiplica dos matrices cuadradas y guarda el resultado en una tercera matriz.
 * 
 * @param matrizuno La primera matriz de entrada.
 * @param matrizdos La segunda matriz de entrada.
 * @param resultado La matriz de salida donde se guarda el resultado de la multiplicación.
 */
void MultiplicarMatrices(int matrizuno[N][N], int matrizdos[N][N], int resultado[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            resultado[i][j] = 0; // Inicializa el elemento en 0 antes de la suma.
            for (int k = 0; k < N; k++)
            {
                resultado[i][j] += matrizuno[i][k] * matrizdos[k][j]; // Multiplicación y suma.
            }
        }
    }
}

/**
 * Transpone una matriz cuadrada.
 * 
 * Esta función toma una matriz cuadrada y calcula su matriz traspuesta.
 * La matriz traspuesta se obtiene intercambiando las filas por las columnas.
 * 
 * @param matriz La matriz original.
 * @param resultado La matriz traspuesta resultante.
 */
void TransponerMatriz(int matriz[N][N], int resultado[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            resultado[j][i] = matriz[i][j]; // Intercambia filas y columnas.
        }
    }
}

// ***** PROCESO PARA CALCULAR LA INVERSA DE UNA MATRIZ *****

/**
 * Calcula el cofactor de una matriz cuadrada.
 *
 * Esta función toma una matriz cuadrada de tamaño N y calcula el cofactor
 * correspondiente a la posición (p, q). El cofactor se calcula eliminando la
 * fila p y la columna q de la matriz original y almacenando el resultado en
 * la matriz temporal.
 *
 * @param matriz La matriz original de tamaño N x N.
 * @param temp La matriz temporal de tamaño (N-1) x (N-1) donde se almacenará el cofactor.
 * @param p La fila de la matriz a eliminar.
 * @param q La columna de la matriz a eliminar.
 * @param n El tamaño de la matriz.
 */
void Cofactor(int matriz[N][N], int temp[N][N], int p, int q, int n) {
    int i = 0, j = 0;
    for (int fila = 0; fila < n; fila++)
    {
        for (int col = 0; col < n; col++)
        {
            if (fila != p && col != q) // Verifica si no es la fila o columna a eliminar.
            {
                temp[i][j++] = matriz[fila][col]; // Copia el elemento a la matriz temporal.
                if (j == n - 1) 
                {
                    j = 0; // Reinicia la columna.
                    i++; // Avanza a la siguiente fila.
                }
            }
        }
    }
}

/**
 * Calcula el determinante de una matriz cuadrada utilizando el enfoque recursivo.
 * 
 * @param matriz La matriz cuadrada de la que se desea calcular el determinante.
 * @param n El tamaño de la matriz.
 * @return El determinante de la matriz.
 */
int DeterminanteMatriz(int matriz[N][N], int n)
{
    int determinante = 0;

    if (n == 1) // Caso base para matrices de 1x1.
        return matriz[0][0];
    
    int temp[N][N];
    int signo = 1; // Alterna el signo en la expansión.
    for (int f = 0; f < n; f++)
    {
        Cofactor(matriz, temp, 0, f, n); // Calcula el cofactor.
        determinante += signo * matriz[0][f] * DeterminanteMatriz(temp, n - 1); // Suma el producto.
        signo = -signo; // Alterna el signo.
    }
    return determinante; // Retorna el determinante calculado.
}

/**
 * Calcula la matriz adjunta de una matriz dada.
 * 
 * @param matriz La matriz de entrada.
 * @param adjunta La matriz adjunta resultante.
 * @param n El tamaño de la matriz.
 */
void AdjuntaMatriz(int matriz[N][N], double adjunta[N][N], int n) {
    if (n == 1)
    {
        adjunta[0][0] = 1; // La adjunta de una matriz 1x1 es 1.
        return;
    }

    int temp[N][N];
    int signo = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Cofactor(matriz, temp, i, j, n); // Calcula el cofactor.
            signo = ((i + j) % 2 == 0) ? 1 : -1; // Determina el signo.
            adjunta[j][i] = (signo) * (DeterminanteMatriz(temp, n - 1)); // Calcula la adjunta.
        }
    }
}

/**
 * Calcula la inversa de una matriz cuadrada.
 * 
 * @param matriz La matriz de entrada.
 * @param inversa La matriz donde se almacenará la inversa.
 */
void InversaMatriz(int matriz[N][N], double inversa[N][N])
{
    double determinante = (double)DeterminanteMatriz(matriz, N); // Calcula el determinante.

    if (determinante == 0) // Verifica si la matriz es singular.
    {
        printf("La matriz es singular, no se puede calcular la inversa.\n");
        return;
    }

    double adjunta[N][N];
    AdjuntaMatriz(matriz, adjunta, N); // Calcula la matriz adjunta.

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inversa[i][j] = adjunta[i][j] / determinante; // Calcula la inversa dividiendo la adjunta por el determinante.
}

int main()
{
    srand(time(NULL));

    int pipe_suma[2];
    int pipe_resta[2];
    int pipe_multi[2];
    int pipe_trasp[2];
    int pipe_inver[2];

    // Crear las pipes para la comunicación entre procesos
    if (pipe(pipe_suma) != 0 || pipe(pipe_resta) != 0 || pipe(pipe_multi) != 0 || pipe(pipe_trasp) != 0 || pipe(pipe_inver) != 0) 
    {
        exit(1);
    }

    // Declarar matrices para las operaciones
    int Matrizuno[N][N];
    int Matrizdos[N][N];
    int Resultado[N][N];
    int Traspuestauno[N][N];
    int Traspuestados[N][N];
    double Inversauno[N][N];
    double Inversados[N][N];

    // Llenar matrices con valores aleatorios
    LlenarMatriz(Matrizuno);
    LlenarMatriz(Matrizdos);

    // Mostrar en pantalla las matrices generadas
    printf("Matriz 1:\n");
    ImprimirMatriz(Matrizuno);
    printf("\nMatriz 2:\n");
    ImprimirMatriz(Matrizdos);

    // Imprimir el proceso raíz con su PID
    printf("\n\nSoy el proceso raíz. PID: %d\n", getpid());

    int pid_raiz = getpid();
    int id_proc;

    // Ciclo para crear procesos hijos y realizar operaciones con matrices
    for (int i = 1; i <= 6; i++)
    {
        id_proc = fork();

        if (id_proc < 0)
        {
            perror("fork fallido");
            exit(1);
        } 
        else if (id_proc == 0)  // Proceso hijo
        { 
            printf("\nSoy el proceso hijo %d con PID: %d, mi padre es el proceso raíz con PID: %d\n", i, getpid(), pid_raiz);
            switch (i)
            {
                case 1:
                    printf("\tRealizo la suma de matrices\n");
                    SumarMatrices(Matrizuno, Matrizdos, Resultado);
                    // Enviar el resultado de la suma a través de la pipe
                    write(pipe_suma[1], Resultado, sizeof(Resultado));
                    break;
                case 2:
                    printf("\tRealizo la resta de matrices\n");
                    RestarMatrices(Matrizuno, Matrizdos, Resultado);
                    // Enviar el resultado de la resta a través de la pipe
                    write(pipe_resta[1], Resultado, sizeof(Resultado));
                    break;
                case 3:
                    printf("\tRealizo la multiplicación de matrices\n");
                    MultiplicarMatrices(Matrizuno, Matrizdos, Resultado);
                    // Enviar el resultado de la multiplicación a través de la pipe
                    write(pipe_multi[1], Resultado, sizeof(Resultado));
                    break;
                case 4:
                    printf("\tRealizo la traspuesta de matrices\n");
                    TransponerMatriz(Matrizuno, Traspuestauno);
                    TransponerMatriz(Matrizdos, Traspuestados);
                    // Enviar el resultado de las traspuestas a través de la pipe
                    write(pipe_trasp[1], Traspuestauno, sizeof(Traspuestauno));
                    write(pipe_trasp[1], Traspuestados, sizeof(Traspuestados));
                    break;
                case 5:
                    printf("\tRealizo la inversa de matrices\n");
                    InversaMatriz(Matrizuno, Inversauno);
                    InversaMatriz(Matrizdos, Inversados);
                    // Enviar el resultado de las inversas a través de la pipe
                    write(pipe_inver[1], Inversauno, sizeof(Inversauno));
                    write(pipe_inver[1], Inversados, sizeof(Inversados));
                    break;
                case 6:
                    // Leer los resultados de las operaciones desde las pipes

                    printf("\nSuma de las matrices:\n");
                    read(pipe_suma[0], Resultado, sizeof(Resultado));
                    ImprimirMatriz(Resultado);

                    printf("\nResta de las matrices:\n");
                    read(pipe_resta[0], Resultado, sizeof(Resultado));
                    ImprimirMatriz(Resultado);

                    printf("\nMultiplicación de las matrices:\n");
                    read(pipe_multi[0], Resultado, sizeof(Resultado));
                    ImprimirMatriz(Resultado);

                    printf("\nTraspuesta de la matriz uno:\n");
                    read(pipe_trasp[0], Resultado, sizeof(Resultado));
                    ImprimirMatriz(Resultado);

                    printf("\nTraspuesta de la matriz dos:\n");
                    read(pipe_trasp[0], Resultado, sizeof(Resultado));
                    ImprimirMatriz(Resultado);
                    
                    printf("\nInversa de la matriz uno:\n");
                    read(pipe_inver[0], Inversauno, sizeof(Inversauno));
                    ImprimirInversa(Inversauno);

                    printf("\nInversa de la matriz dos:\n");
                    read(pipe_inver[0], Inversados, sizeof(Inversados));
                    ImprimirInversa(Inversados);

                    break;
            }
            exit(0);
        }
        else
        {
            wait(NULL); // Espera a que el proceso hijo termine antes de continuar
        }
    }

    // Esperar a que todos los procesos hijos terminen
    for (int i = 1; i <= 6; i++)
    {
        wait(NULL);
    }

    return 0;
}