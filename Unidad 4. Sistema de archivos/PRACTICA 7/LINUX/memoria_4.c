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


/**
 * Escribe los valores de una matriz double desde memoria compartida.
 * 
 * @param matriz La matriz cuyos valores se escribirán.
 * @param shm Un puntero a la memoria compartida.
 */
void EscribirenMemoriaDouble(double (*matriz)[N], double *shm)
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
 * Lee los valores de una matriz double desde memoria compartida.
 * 
 * @param matriz La matriz donde se almacenarán los valores leídos.
 * @param shm Un puntero a la memoria compartida.
 */
void LeerDeMemoriaDouble(double (*matriz)[N], double *shm) 
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
    int Matrizuno[N][N];
    int Matrizdos[N][N];
    int Resultado[N][N];
    int Traspuestauno[N][N];
    int Traspuestados[N][N];
    double Inversauno[N][N];
    double Inversados[N][N];

    // Manejo de memoria compartida

    // Clave para los segmentos de memoria compartida
    key_t llave1 = 1674;
    key_t llave2 = 1675;
    key_t llave3 = 1676;
    key_t llave4 = 1677;
    key_t llave5 = 1678;
    key_t llave6 = 1679;
    key_t llave7 = 1680;

    // Crear segmentos de memoria compartida
    int shmid1 = shmget(llave1, sizeof(int[N][N]), IPC_CREAT | 0666);
    int shmid2 = shmget(llave2, sizeof(int[N][N]), IPC_CREAT | 0666);
    int shmid3 = shmget(llave3, sizeof(int[N][N]), IPC_CREAT | 0666);
    int shmid4 = shmget(llave4, sizeof(int[N][N]), IPC_CREAT | 0666);
    int shmid5 = shmget(llave5, sizeof(int[N][N]), IPC_CREAT | 0666);
    int shmid6 = shmget(llave6, sizeof(int[N][N]), IPC_CREAT | 0666);
    int shmid7 = shmget(llave7, sizeof(int[N][N]), IPC_CREAT | 0666);
    
    // Enlazar segmentos de memoria compartida
    int (*shm_suma)[N]   = shmat(shmid1, NULL, 0);
    int (*shm_resta)[N]  = shmat(shmid2, NULL, 0);
    int (*shm_multi)[N]  = shmat(shmid3, NULL, 0);
    int (*shm_traspu)[N] = shmat(shmid4, NULL, 0);
    int (*shm_traspd)[N] = shmat(shmid5, NULL, 0);
    double (*shm_inveru)[N] = shmat(shmid6, NULL, 0);
    double (*shm_inverd)[N] = shmat(shmid7, NULL, 0);

    // Verificar si los segmentos de memoria compartida se crearon correctamente
    if (shmid1 < 0) {
        perror("Error al obtener memoria compartida para la matriz resultado de suma: shmget");
        exit(1);
    }
    
    if (shmid2 < 0) {
        perror("Error al obtener memoria compartida para la matriz resultado de resta: shmget");
        exit(1);
    }

    if (shmid3 < 0) {
        perror("Error al obtener memoria compartida para la matriz resultado de multiplicación: shmget");
        exit(1);
    }

    if (shmid4 < 0) {
        perror("Error al obtener memoria compartida para la matriz resultado de traspuesta uno: shmget");
        exit(1);
    }

    if (shmid5 < 0) {
        perror("Error al obtener memoria compartida para la matriz resultado de traspuesta dos: shmget");
        exit(1);
    }

    if (shmid6 < 0) {
        perror("Error al obtener memoria compartida para la matriz resultado de inversa uno: shmget");
        exit(1);
    }

    if (shmid7 < 0) {
        perror("Error al obtener memoria compartida para la matriz resultado de inversa dos: shmget");
        exit(1);
    }

    // Verificar si los segmentos de memoria compartida se enlazaron correctamente
    if (shm_suma == (void *)-1) {
        perror("Error al enlazar la memoria compartida para la matriz resultado de suma: shmat");
        exit(1);
    }

    if (shm_resta == (void *)-1) {
        perror("Error al enlazar la memoria compartida para la matriz resultado de resta: shmat");
        exit(1);
    }

    if (shm_multi == (void *)-1) {
        perror("Error al enlazar la memoria compartida para la matriz resultado de multiplicación: shmat");
        exit(1);
    }

    if (shm_traspu == (void *)-1) {
        perror("Error al enlazar la memoria compartida para la matriz resultado de traspuesta uno: shmat");
        exit(1);
    }

    if (shm_traspd == (void *)-1) {
        perror("Error al enlazar la memoria compartida para la matriz resultado de traspuesta dos: shmat");
        exit(1);
    }

    if (shm_inveru == (void *)-1) {
        perror("Error al enlazar la memoria compartida para la matriz resultado de inversa uno: shmat");
        exit(1);
    }

    if (shm_inverd == (void *)-1) {
        perror("Error al enlazar la memoria compartida para la matriz resultado de inversa dos: shmat");
        exit(1);
    }

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

    // Ciclo para generar los procesos hijos y realizar operaciones de matrices
    for (int i = 1; i <= 6; i++) 
    {
        int id_proc = fork();

        if (id_proc < 0)
        {
            perror("Fork fallido");
            exit(1);
        } 
        else if (id_proc == 0) 
        { // Proceso hijo
            printf("\nSoy el proceso hijo %d con PID: %d, mi padre es el proceso raíz con PID: %d\n", i, getpid(), pid_raiz);
            switch (i) 
            {
                case 1:
                    printf("\tRealizo la suma de matrices\n");
                    SumarMatrices(Matrizuno, Matrizdos, Resultado);
                    // Enviar el resultado de la suma a través de la memoria compartida
                    EscribirenMemoria(Resultado, (int *)shm_suma);
                    break;
                case 2:
                    printf("\tRealizo la resta de matrices\n");
                    RestarMatrices(Matrizuno, Matrizdos, Resultado);
                    // Enviar el resultado de la resta a través de la memoria compartida
                    EscribirenMemoria(Resultado, (int *)shm_resta);
                    break;
                case 3:
                    printf("\tRealizo la multiplicación de matrices\n");
                    MultiplicarMatrices(Matrizuno, Matrizdos, Resultado);
                    // Enviar el resultado de la multiplicación a través de la memoria compartida
                    EscribirenMemoria(Resultado, (int *)shm_multi);
                    break;
                case 4:
                    printf("\tRealizo la traspuesta de matrices\n");
                    TransponerMatriz(Matrizuno, Traspuestauno);
                    TransponerMatriz(Matrizdos, Traspuestados);
                    // Enviar la traspuesta de la matriz uno a través de la memoria compartida
                    EscribirenMemoria(Traspuestauno, (int *)shm_traspu);
                    // Enviar la traspuesta de la matriz dos a través de la memoria compartida
                    EscribirenMemoria(Traspuestados, (int *)shm_traspd);
                    break;
                case 5:
                    printf("\tRealizo la inversa de matrices\n");
                    InversaMatriz(Matrizuno, Inversauno);
                    InversaMatriz(Matrizdos, Inversados);
                    // Enviar la inversa de la matriz uno a través de la memoria compartida
                    EscribirenMemoriaDouble(Inversauno, (double *)shm_inveru);
                    // Enviar la inversa de la matriz dos a través de la memoria compartida
                    EscribirenMemoriaDouble(Inversados, (double *)shm_inverd);
                    break;
                case 6:
                    printf("\nSuma de las matrices:\n");
                    LeerDeMemoria(Resultado, (int *)shm_suma);
                    ImprimirMatriz(Resultado);

                    printf("\nResta de las matrices:\n");
                    LeerDeMemoria(Resultado, (int *)shm_resta);
                    ImprimirMatriz(Resultado);

                    printf("\nMultiplicación de las matrices:\n");
                    LeerDeMemoria(Resultado, (int *)shm_multi);
                    ImprimirMatriz(Resultado);

                    printf("\nTraspuesta de la matriz uno:\n");
                    LeerDeMemoria(Traspuestauno, (int *)shm_traspu);
                    ImprimirMatriz(Traspuestauno);

                    printf("\nTraspuesta de la matriz dos:\n");
                    LeerDeMemoria(Traspuestados, (int *)shm_traspd);
                    ImprimirMatriz(Traspuestados);

                    printf("\nInversa de la matriz uno:\n");
                    LeerDeMemoriaDouble(Inversauno, (double *)shm_inveru);
                    ImprimirInversa(Inversauno);

                    printf("\nInversa de la matriz dos:\n");
                    LeerDeMemoriaDouble(Inversados, (double *)shm_inverd);
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
    for (int i = 1; i <= 6; i++) {
        wait(NULL);
    }

    return 0;
}