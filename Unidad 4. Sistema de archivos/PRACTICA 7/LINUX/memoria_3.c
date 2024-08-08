#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

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

/**
 * Escribe los valores de una matriz en memoria compartida.
 * 
 * @param matriz La matriz cuyos valores se desean escribir.
 * @param shm Un puntero a la memoria compartida.
 */
void EscribirenMemoria(int (*matriz)[N], int *shm)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            *shm = matriz[i][j];
            shm++;
        }
    }
}

/**
 * Lee los valores de una matriz desde memoria compartida.
 * 
 * @param matriz La matriz donde se almacenarán los valores leídos.
 * @param shm Un puntero a la memoria compartida.
 */
void LeerDeMemoria(int (*matriz)[N], int *shm)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matriz[i][j] = *shm;
            shm++;
        }
    }
}

int main()
{
    srand(time(NULL));

    // Declaracion de las matrices
    int matrizuno[N][N];
    int matrizdos[N][N];
    int resultado_multi[N][N];
    int resultado_sum[N][N];

    // Manejo de memoria compartida

    // Clave para los segmentos de memoria compartida
    key_t llave1 = 1670;
    key_t llave2 = 1671;
    key_t llave3 = 1672;
    key_t llave4 = 1673;

    // Obtener identificadores para los segmentos de memoria compartida
    int shmid1 = shmget(llave1, sizeof(int[N][N]), IPC_CREAT | 0666);
    int shmid2 = shmget(llave2, sizeof(int[N][N]), IPC_CREAT | 0666);
    int shmid3 = shmget(llave3, sizeof(int[N][N]), IPC_CREAT | 0666);
    int shmid4 = shmget(llave4, sizeof(int[N][N]), IPC_CREAT | 0666);
    
    // Asociar los segmentos de memoria compartida a punteros
    int (*shm_matrizuno)[N] = shmat(shmid1, NULL, 0);
    int (*shm_matrizdos)[N] = shmat(shmid2, NULL, 0);
    int (*shm_resultado_multi)[N] = shmat(shmid3, NULL, 0);
    int (*shm_resultado_sum)[N] = shmat(shmid4, NULL, 0);

    // Crear un proceso hijo
    if (fork() == 0)
    {
        // Proceso hijo (Multiplicación de matrices)

        // Leer matrices desde la memoria compartida
        LeerDeMemoria(matrizuno, (int *)shm_matrizuno);
        LeerDeMemoria(matrizdos, (int *)shm_matrizdos);

        // Multiplicar matrices
        MultiplicarMatrices(matrizuno, matrizdos, resultado_multi);

        // Escribir resultado en memoria compartida
        EscribirenMemoria(resultado_multi, (int *)shm_resultado_multi);
        
        EscribirenMemoria(matrizuno, (int *)shm_matrizuno);
        EscribirenMemoria(matrizdos, (int *)shm_matrizdos);

        // Crear un proceso nieto
        if (fork() == 0)
        {
            // Proceso nieto (Suma de matrices)

            // Leer matrices desde la memoria compartida
            LeerDeMemoria(matrizuno, (int *)shm_matrizuno);
            LeerDeMemoria(matrizdos, (int *)shm_matrizdos);

            // Sumar matrices
            SumarMatrices(matrizuno, matrizdos, resultado_sum);

            // Escribir resultado en memoria compartida
            EscribirenMemoria(resultado_sum, (int *)shm_resultado_sum);

            exit(0);
        }

        // Esperar al proceso nieto
        wait(NULL);

        exit(0);
    }
    else
    {
        // Proceso padre
        
        // Generar dos matrices aleatorias de 10 x 10
        LlenarMatriz(matrizuno);
        LlenarMatriz(matrizdos);

        // Mostrar las matrices generadas
        printf("Matriz uno:\n");
        ImprimirMatriz(matrizuno);
        printf("\nMatriz dos:\n");
        ImprimirMatriz(matrizdos);

        // Crear segmento de memoria compartida para la primera matriz
        if (shmid1 < 0) {
            perror("Error al obtener memoria compartida para la primera matriz: shmget");
            exit(1);
        }

        // Crear segmento de memoria compartida para la segunda matriz
        if (shmid2 < 0) {
            perror("Error al obtener memoria compartida para la segunda matriz: shmget");
            exit(1);
        }

        // Crear segmento de memoria compartida para el resultado de la multiplicación
        if (shmid3 < 0) {
            perror("Error al obtener memoria compartida para el resultado de la multiplicación: shmget");
            exit(1);
        }

        // Crear segmento de memoria compartida para el resultado de la suma
        if (shmid4 < 0) {
            perror("Error al obtener memoria compartida para el resultado de la suma: shmget");
            exit(1);
        }

        // Adjuntar segmento de memoria compartida para la primera matriz
        if (shm_matrizuno == (void *)-1) {
            perror("Error al enlazar la memoria compartida para la primera matriz: shmat");
            exit(1);
        }

        // Adjuntar segmento de memoria compartida para la segunda matriz
        if (shm_matrizdos == (void *)-1) {
            perror("Error al enlazar la memoria compartida para la segunda matriz: shmat");
            exit(1);
        }

        // Adjuntar segmento de memoria compartida para el resultado de la multiplicación
        if (shm_resultado_multi == (void *)-1) {
            perror("Error al enlazar la memoria compartida para el resultado de la multiplicación: shmat");
            exit(1);
        }

        // Adjuntar segmento de memoria compartida para el resultado de la suma
        if (shm_resultado_sum == (void *)-1) {
            perror("Error al enlazar la memoria compartida para el resultado de la suma: shmat");
            exit(1);
        }

        // Escribir matrices en memoria compartida
        EscribirenMemoria(matrizuno, (int *)shm_matrizuno);
        EscribirenMemoria(matrizdos, (int *)shm_matrizdos);

        // Esperar al proceso hijo
        wait(NULL);

        // Leer resultados desde la memoria compartida
        LeerDeMemoria(resultado_multi, (int *)shm_resultado_multi);
        LeerDeMemoria(resultado_sum, (int *)shm_resultado_sum);

        // Imprimir resultados
        printf("\nResultado de la multiplicación:\n");
        ImprimirMatriz(resultado_multi);

        printf("\nResultado de la suma:\n");
        ImprimirMatriz(resultado_sum);

        // Realizar el cálculo de la inversa de la multiplicación y la suma recibidas
        double inversa_multi[N][N];
        double inversa_sum[N][N];

        InversaMatriz(resultado_multi, inversa_multi);
        InversaMatriz(resultado_sum, inversa_sum);

        // Mostrar los resultados de las inversas
        printf("\nInversa de la multiplicación:\n");
        ImprimirInversa(inversa_multi);
        printf("\nInversa de la suma:\n");
        ImprimirInversa(inversa_sum);
    }

    return 0;
}