#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

/**
 * Definición de constante para el tamaño de la matriz
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
            resultado[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                resultado[i][j] += matrizuno[i][k] * matrizdos[k][j]; // Acumula el producto de los elementos correspondientes.
            }
        }
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
            resultado[i][j] = matrizuno[i][j] + matrizdos[i][j]; // Suma los elementos correspondientes de las dos matrices.
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
    
    int padre_hijo[2]; // Tubo de comunicación entre el proceso padre y el hijo.
    int hijo_nieto[2]; // Tubo de comunicación entre el proceso hijo y el nieto.

    int matrizuno[N][N];
    int matrizdos[N][N];

    if (pipe(padre_hijo) != 0 || pipe(hijo_nieto) != 0)
    {
        exit(1); // Sale si no se pueden crear los tubos.
    }

    if (fork() == 0) // Proceso hijo
    {
        read(padre_hijo[0], matrizuno, sizeof(matrizuno)); // Lee la primera matriz del tubo.
        read(padre_hijo[0], matrizdos, sizeof(matrizdos)); // Lee la segunda matriz del tubo.

        int resultado[N][N];
        MultiplicarMatrices(matrizuno, matrizdos, resultado); // Multiplica las matrices.
        write(padre_hijo[1], resultado, sizeof(resultado)); // Escribe el resultado en el tubo.

        write(hijo_nieto[1], matrizuno, sizeof(matrizuno)); // Escribe la primera matriz en el tubo.
        write(hijo_nieto[1], matrizdos, sizeof(matrizdos)); // Escribe la segunda matriz en el tubo.

        if (fork() == 0) // Proceso nieto
        {
            read(hijo_nieto[0], matrizuno, sizeof(matrizuno)); // Lee la primera matriz del tubo.
            read(hijo_nieto[0], matrizdos, sizeof(matrizdos)); // Lee la segunda matriz del tubo.

            int resultado[N][N];
            SumarMatrices(matrizuno, matrizdos, resultado); // Suma las matrices.
            write(hijo_nieto[1], resultado, sizeof(resultado)); // Escribe el resultado en el tubo.

            exit(0);
        }
        else // Proceso hijo
        {
            wait(NULL); // Espera a que el proceso nieto termine.
        }
    } 
    else // Proceso padre
    {
        LlenarMatriz(matrizuno); // Llena la primera matriz con valores aleatorios.
        LlenarMatriz(matrizdos); // Llena la segunda matriz con valores aleatorios.

        printf("Matriz uno:\n");
        ImprimirMatriz(matrizuno); // Imprime la primera matriz.
        printf("\nMatriz dos:\n");
        ImprimirMatriz(matrizdos); // Imprime la segunda matriz.

        write(padre_hijo[1], matrizuno, sizeof(matrizuno)); // Escribe la primera matriz en el tubo.
        write(padre_hijo[1], matrizdos, sizeof(matrizdos)); // Escribe la segunda matriz en el tubo.

        wait(NULL); // Espera a que el proceso hijo termine.

        int resultado_multi[N][N];
        int resultado_sum[N][N];

        printf("\nResultado de la multiplicacion:\n");
        read(padre_hijo[0], resultado_multi, sizeof(resultado_multi)); // Lee el resultado de la multiplicación del tubo.
        ImprimirMatriz(resultado_multi); // Imprime el resultado de la multiplicación.

        read(hijo_nieto[0], resultado_sum, sizeof(resultado_sum)); // Lee el resultado de la suma del tubo.
        printf("\nResultado de la suma\n");
        ImprimirMatriz(resultado_sum); // Imprime el resultado de la suma.

        double inversa_multi[N][N];
        double inversa_sum[N][N];

        InversaMatriz(resultado_multi, inversa_multi); // Calcula la inversa de la matriz resultante de la multiplicación.
        InversaMatriz(resultado_sum, inversa_sum); // Calcula la inversa de la matriz resultante de la suma.

        printf("\nInversa de la multiplicacion\n");
        ImprimirInversa(inversa_multi); // Imprime la inversa de la multiplicación.
        printf("\nInversa de la suma\n");
        ImprimirInversa(inversa_sum); // Imprime la inversa de la suma.

        exit(0);
    }

    return 0;
}