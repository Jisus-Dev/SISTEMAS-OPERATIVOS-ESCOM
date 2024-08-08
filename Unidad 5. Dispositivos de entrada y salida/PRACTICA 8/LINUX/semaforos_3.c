#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <time.h>

/**
 * Definiciones de constantes para el tamaño de memoria y matriz.
 * 
 * N: Tamaño de la matriz.
 * TAM_MEM_DOBLE: Tamaño de dos matrices en bytes.
 */

#define N 10
#define TAM_MEM_DOBLE (2 * N * N * sizeof(int))
#define TAM_MEM_QUINTUPLE (5 * N * N * sizeof(int))
#define TAM_MEM_DOUBLE (2 * N * N * sizeof(double))

/**
 * Llena una matriz con valores aleatorios entre 0 y 100.
 * 
 * @param matriz La matriz a llenar.
 */
void LlenarMatriz(int matriz[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matriz[i][j] = rand() % 101;
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
            printf("%d\t", matriz[i][j]);
        printf("\n");
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
            printf("%lf  ", matriz[i][j]);
        printf("\n");
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
            resultado[i][j] = matrizuno[i][j] + matrizdos[i][j];
        }
    }
}

/**
 * RestarMatrices: Resta dos matrices y guarda el resultado en una tercera matriz.
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
            resultado[i][j] = matrizuno[i][j] - matrizdos[i][j];
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
            resultado[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                resultado[i][j] += matrizuno[i][k] * matrizdos[k][j];
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
 * @param traspuesta La matriz traspuesta resultante.
 */
void TransponerMatriz(int matriz[N][N], int traspuesta[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            traspuesta[j][i] = matriz[i][j];
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
            if (fila != p && col != q)
            {
                temp[i][j++] = matriz[fila][col];
                if (j == n - 1) 
                {
                    j = 0;
                    i++;
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

    if (n == 1)
        return matriz[0][0];
    
    int temp[N][N]; // Para almacenar cofactores
    int signo = 1; // Para almacenar el signo del cofactor
    for (int f = 0; f < n; f++)
    {
        Cofactor(matriz, temp, 0, f, n); // Calculando el cofactor
        determinante += signo * matriz[0][f] * DeterminanteMatriz(temp, n - 1);
        signo = -signo;
    }
    return determinante;
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
        adjunta[0][0] = 1;
        return;
    }

    int temp[N][N]; // Para almacenar cofactores
    int signo = 1; // Para almacenar el signo del cofactor
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Cofactor(matriz, temp, i, j, n);
            signo = ((i + j) % 2 == 0) ? 1 : -1;
            adjunta[j][i] = (signo) * (DeterminanteMatriz(temp, n - 1));
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
    double determinante = (double)DeterminanteMatriz(matriz, N);

    if (determinante == 0)
    {
        printf("La matriz es singular, no se puede calcular la inversa.\n");
        return;
    }

    double adjunta[N][N];
    AdjuntaMatriz(matriz, adjunta, N);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inversa[i][j] = adjunta[i][j] / determinante;
}

/**
 * Escribe los elementos de una matriz en una memoria compartida.
 * 
 * @param matriz La matriz de entrada.
 * @param punteroDatos El puntero a la memoria compartida donde se escribirán los datos.
 */
void EscribirMatrizMemoria(int (*matriz)[N], int *shm)
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
 * Escribe las matrices en la memoria compartida de forma consecutiva.
 * 
 * @param matrizuno La primera matriz a escribir en la memoria compartida.
 * @param matrizdos La segunda matriz a escribir en la memoria compartida.
 * @param punteroDatos El puntero a la memoria compartida.
 */
void EscribirDosMatricesMemoria(int (*matrizuno)[N], int (*matrizdos)[N], int (*shm)[N])
{
    EscribirMatrizMemoria(matrizuno, (int *)shm);
    EscribirMatrizMemoria(matrizdos, (int *)shm + (N * N));
}

/**
 * Escribe los elementos de una matriz de doubles en una memoria compartida.
 * 
 * @param matriz La matriz de entrada.
 * @param punteroDatos El puntero a la memoria compartida donde se escribirán los datos.
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
 * Lee los datos de una memoria compartida y los guarda en una matriz.
 * 
 * @param matriz La matriz en la que se guardarán los datos leídos.
 * @param punteroDatos El puntero a los datos en la memoria compartida.
 */
void LeerMatrizMemoria(int (*matriz)[N], int *shm)
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
 * Lee los datos de una memoria compartida de dos secciones y los guarda en dos matrices.
 * 
 * Esta función lee los datos de dos matrices de tamaño N x N desde una memoria compartida,
 * utilizando un puntero a los datos de la memoria compartida.
 * 
 * @param matrizuno La primera matriz donde se almacenarán los datos leídos.
 * @param matrizdos La segunda matriz donde se almacenarán los datos leídos.
 * @param punteroDatos El puntero a los datos de la memoria compartida.
 */
void LeerDosMatricesMemoria(int (*matrizuno)[N], int (*matrizdos)[N], int (*shm)[N])
{
    LeerMatrizMemoria(matrizuno, (int *)shm);
    LeerMatrizMemoria(matrizdos, (int *)shm + (N * N));
}

/**
 * Lee los datos de una memoria compartida de tipo double y los guarda en una matriz.
 * 
 * @param matriz La matriz en la que se guardarán los datos leídos.
 * @param punteroDatos El puntero a los datos en la memoria compartida.
 */
void LeerMatrizMemoriaDouble(double (*matriz)[N], double *shm)
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

// ***** FUNCIONES PARA OPERACIONES DE SEMÁFOROS *****

/**
 * Función para tomar un semáforo.
 * 
 * Toma el semáforo identificado por el ID proporcionado.
 * La función espera a que el semáforo sea 0 y luego lo incrementa en 1.
 * 
 * @param semid El ID del semáforo.
 */
void sem_tomar(int semid)
{
    struct sembuf sops[2];

    sops[0].sem_num = 0;
    sops[0].sem_op = 0;     // Esperar a que el semáforo sea 0
    sops[0].sem_flg = SEM_UNDO;
    sops[1].sem_num = 0;
    sops[1].sem_op = 1;     // Incrementar el semáforo en 1
    sops[1].sem_flg = SEM_UNDO | IPC_NOWAIT;

    // Ejecutar la operación semop() para tomar el semáforo
    if (semop(semid, sops, 2) == -1)
    {
        perror("sem_tomar: error en operacion del semaforo tomar");
        exit(1);
    }
}

/**
 * Libera un semáforo dado su identificador.
 * 
 * @param semid El identificador del semáforo.
 */
void sem_liberar(int semid)
{
    struct sembuf sop;

    sop.sem_num = 0;
    sop.sem_op = -1;
    sop.sem_flg = SEM_UNDO | IPC_NOWAIT;

    // Ejecutar la operación semop() para liberar el semáforo
    if (semop(semid, &sop, 1) == -1)
    {
        perror("sem_liberar: error en operacion del semaforo liberacion");
        exit(1);
    }
}



int main()
{
    // Semilla para la generación de números aleatorios
    srand(time(NULL));

    // **** SEMÁFOROS PARA LA COMUNICACIÓN ENTRE PROCESOS ****

    // Identificadores de los semáforos
    int semid_escritura, semid_resultados, semid_finalizacion;

    // LLaves para los semáforos
    key_t llave_sem1 = 1300;
    key_t llave_sem2 = 1301;
    key_t llave_sem3 = 1302;
    int semban = IPC_CREAT | 0666;

    // Crear los semáforos
    if ((semid_escritura = semget(llave_sem1, 1, semban)) == -1)
    {
        perror("semget: error al crear semaforo de comunicacion 1");
        exit(1);
    }

    if ((semid_resultados = semget(llave_sem2, 1, semban)) == -1)
    {
        perror("semget: error al crear semaforo de comunicacion 2");
        exit(1);
    }

     if ((semid_finalizacion = semget(llave_sem3, 1, semban)) == -1)
    {
        perror("semget: error al crear semaforo de comunicacion 2");
        exit(1);
    }


    // **** MEMORIA COMPARTIDA PARA LAS MATRICES ****
    key_t llave1 = 1700;
    int shmid1 = shmget(llave1, sizeof(int[N][N]), IPC_CREAT | 0666);
    int (*shm_mu_md)[N]   = shmat(shmid1, NULL, 0);

    // Crear segmento de memoria compartida para la matriz uno y dos
    if (shmid1 < 0) {
        perror("Error al obtener memoria compartida para la matriz uno y dos: shmget");
        exit(1);
    }

    // Enlazar la memoria compartida para la matriz uno y dos
    if (shm_mu_md == (void *)-1) {
        perror("Error al adjuntar memoria compartida para la matriz uno y dos: shmat");
        exit(1);
    }

    // **** MEMORIA COMPARTIDA PARA LOS RESULTADOS ENTEROS ****
    key_t llave2 = 1701;
    int shmid2 = shmget(llave2, sizeof(int[N][N]), IPC_CREAT | 0666);
    int (*shm_resultados_enteros)[N]  = shmat(shmid2, NULL, 0);

    // Crear segmento de memoria compartida para los resultados enteros
    if (shmid2 < 0) {
        perror("Error al obtener memoria compartida para los resultados enteros: shmget");
        exit(1);
    }

    // Enlazar la memoria compartida para los resultados enteros
    if (shm_resultados_enteros == (void *)-1) {
        perror("Error al adjuntar memoria compartida para los resultados enteros: shmat");
        exit(1);
    }


    // **** MEMORIA COMPARTIDA PARA LOS RESULTADOS DOUBLES ****
    key_t llave3 = 1702;    
    int shmid3 = shmget(llave3, sizeof(int[N][N]), IPC_CREAT | 0666);
    int (*shm_resultados_doubles)[N]  = shmat(shmid3, NULL, 0);
    
    // Crear segmento de memoria compartida para los resultados doubles
    if (shmid3 < 0) {
        perror("Error al obtener memoria compartida para los resultados doubles: shmget");
        exit(1);
    }

    // Enlazar la memoria compartida para los resultados doubles
    if (shm_resultados_doubles == (void *)-1) {
        perror("Error al adjuntar memoria compartida para los resultados doubles: shmat");
        exit(1);
    }

    // Crear dos matrices de tamaño N x N
    int matrizuno[N][N];
    int matrizdos[N][N];

    // Llenar las matrices con valores aleatorios
    LlenarMatriz(matrizuno);
    LlenarMatriz(matrizdos);

    // Imprimir las matrices
    printf("Matriz 1:\n");
    ImprimirMatriz(matrizuno);
    printf("\nMatriz 2:\n");
    ImprimirMatriz(matrizdos);

    // Escribir las matrices en la memoria compartida
    EscribirDosMatricesMemoria(matrizuno, matrizdos, shm_mu_md);

    /**
    * Lógica: Bloqueamos un ssemáforo hasta que algun proceso lo libere
    * El primer semaforo se bloquea hasta que el proceso 5 lo libere, cuando el ultimo resultado se escribe en la memoria compartida
    * El segundo semaforo se bloquea hasta que el proceso 6 lo libere, cuando todos los resultados se terminan de imprimir
    */
    sem_tomar(semid_resultados);    // Bloquear el semáforo de resultados
    sem_tomar(semid_finalizacion);  // Bloquear el semáforo de finalización
    
    // Crear matrices para los resultados
    int matriz_resultado[N][N];
    int matriz_traspuestau[N][N];
    int matriz_traspuestad[N][N];
    double matriz_inversauno[N][N];
    double matriz_inversados[N][N];

    // Variables para procesos
    int pid;
    
    // Crear 6 procesos hijos
    for (int i = 1; i <= 6; i++)
    {
        if ((pid = fork()) == 0) // Crear un proceso hijo
        {   
            switch (i)
            {
                case 1: // Proceso hijo 1
                    // Proceso 1 tomar semaforo de escritura
                    sem_tomar(semid_escritura);
                    // Leer las matrices de la memoria compartida
                    LeerDosMatricesMemoria(matrizuno, matrizdos, shm_mu_md);
                    // Calcular la suma de las matrices
                    SumarMatrices(matrizuno, matrizdos, matriz_resultado);
                    // Escribir la matriz de resultados de la suma en la primera sección de la memoria compartida
                    EscribirMatrizMemoria(matriz_resultado, (int *)shm_resultados_enteros);
                    // Liberar semaforo de escritura para el siguiente proceso
                    sem_liberar(semid_escritura);
                    break;
                case 2:
                    // Proceso 2 toma semáforo de escritura
                    sem_tomar(semid_escritura);
                    // Leer las matrices de la memoria compartida
                    LeerDosMatricesMemoria(matrizuno, matrizdos, shm_mu_md);
                    // Calcular la resta de las matrices
                    RestarMatrices(matrizuno, matrizdos, matriz_resultado);
                    // Escribir la matriz de resultados de la resta en la segunda sección de la memoria compartida
                    EscribirMatrizMemoria(matriz_resultado, (int *)shm_resultados_enteros + (N * N));
                    // Liberar semáforo de escritura para el siguiente proceso
                    sem_liberar(semid_escritura);
                    break;
                case 3:
                    // Proceso 3 toma semáforo de escritura
                    sem_tomar(semid_escritura);
                    // Leer las matrices de la memoria compartida
                    LeerDosMatricesMemoria(matrizuno, matrizdos, shm_mu_md);
                    // Calcular la multiplicación de las matrices
                    MultiplicarMatrices(matrizuno, matrizdos, matriz_resultado);
                    // Escribir la matriz de resultados de la multiplicación en la tercera sección de la memoria compartida
                    EscribirMatrizMemoria(matriz_resultado, (int *)shm_resultados_enteros + (2 * (N * N)));
                    // Liberar semáforo de escritura para el siguiente proceso
                    sem_liberar(semid_escritura);
                    break;
                case 4:
                    // Proceso 4 toma semáforo de escritura
                    sem_tomar(semid_escritura);
                    // Leer las matrices de la memoria compartida
                    LeerDosMatricesMemoria(matrizuno, matrizdos, shm_mu_md);
                    // Calcular la traspuesta de la matriz uno
                    TransponerMatriz(matrizuno, matriz_traspuestau);
                    // Calcular la traspuesta de la matriz dos
                    TransponerMatriz(matrizdos, matriz_traspuestad);
                    // Escribir la matriz traspuesta de la matriz uno en la cuarta sección de la memoria compartida
                    EscribirMatrizMemoria(matriz_traspuestau, (int *)shm_resultados_enteros + (3 * (N * N)));
                    // Escribir la matriz traspuesta de la matriz dos en la quinta sección de la memoria compartida
                    EscribirMatrizMemoria(matriz_traspuestad, (int *)shm_resultados_enteros + (4 * (N * N)));
                    // Liberar semáforo de escritura para el siguiente proceso
                    sem_liberar(semid_escritura);
                    break;
                case 5:
                    // Proceso 5 toma semáforo de escritura
                    sem_tomar(semid_escritura);
                    // Leer las matrices de la memoria compartida
                    LeerDosMatricesMemoria(matrizuno, matrizdos, shm_mu_md);
                    // Calcular la inversa de la matriz uno
                    InversaMatriz(matrizuno, matriz_inversauno);
                    // Calcular la inversa de la matriz dos
                    InversaMatriz(matrizdos, matriz_inversados);
                    // Escribir la matriz inversa de la matriz uno en la primera sección de la memoria compartida
                    EscribirenMemoriaDouble(matriz_inversauno, (double *)shm_resultados_doubles);
                    // Escribir la matriz inversa de la matriz dos en la segunda sección de la memoria compartida
                    EscribirenMemoriaDouble(matriz_inversados, (double *)shm_resultados_doubles + (N * N));
                    // Liberar semáforo de escritura para el siguiente proceso
                    sem_liberar(semid_escritura);
                    // Liberar semáforo de resultados para que el proceso 6 pueda imprimir los resultados
                    sem_liberar(semid_resultados);
                    break;
                case 6:
                    // Proceso 6 toma semáforo de resultados (no puede tomarlo hasta que el proceso 5 lo libere)
                    sem_tomar(semid_resultados);
                    
                    // Imprimir los resultados de las memorias compartida tanto de enteros como de doubles
                    printf("\nSuma de las matrices:\n");
                    LeerMatrizMemoria(matriz_resultado, (int *)shm_resultados_enteros);
                    ImprimirMatriz(matriz_resultado);

                    printf("\nResta de las matrices:\n");
                    LeerMatrizMemoria(matriz_resultado, (int *)shm_resultados_enteros + (N * N));
                    ImprimirMatriz(matriz_resultado);

                    printf("\nMultiplicacion de las matrices:\n");
                    LeerMatrizMemoria(matriz_resultado, (int *)shm_resultados_enteros + (2 * (N * N)));
                    ImprimirMatriz(matriz_resultado);

                    printf("\nTraspuesta de la matriz uno:\n");
                    LeerMatrizMemoria(matriz_traspuestau, (int *)shm_resultados_enteros + (3 * (N * N)));
                    ImprimirMatriz(matriz_traspuestau);

                    printf("\nTraspuesta de la matriz dos:\n");
                    LeerMatrizMemoria(matriz_traspuestad, (int *)shm_resultados_enteros + (4 * (N * N)));
                    ImprimirMatriz(matriz_traspuestad);

                    printf("\nInversa de la matriz uno:\n");
                    LeerMatrizMemoriaDouble(matriz_inversauno, (double *)shm_resultados_doubles);
                    ImprimirInversa(matriz_inversauno);

                    printf("\nInversa de la matriz dos:\n");
                    LeerMatrizMemoriaDouble(matriz_inversados, (double *)shm_resultados_doubles + (N * N));
                    ImprimirInversa(matriz_inversados);

                    // Liberar semáforo de resultados
                    sem_liberar(semid_resultados);

                    // Liberar semáforo de finalización para que el proceso padre puede terminar
                    sem_liberar(semid_finalizacion);
                    break;
            }
            exit(0);
        }
    }

    // Esperar a que todos los procesos hijos terminen
    sem_tomar(semid_finalizacion);

    // Liberar memoria compartida
    shmdt(shm_mu_md);
    shmdt(shm_resultados_enteros);
    shmdt(shm_resultados_doubles);

    // Liberar semáforos
    semctl(semid_escritura, 0, IPC_RMID);
    semctl(semid_resultados, 0, IPC_RMID);
    semctl(semid_finalizacion, 0, IPC_RMID);

    return 0;
}
