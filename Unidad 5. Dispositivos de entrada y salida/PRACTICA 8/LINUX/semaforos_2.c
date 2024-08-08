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



int main(void)
{
    // Semilla para los números aleatorios
    srand(time(NULL));

    // **** MEMORIA COMPARTIDA PARA LAS MATRICES ALEATORIAS PADRE-HIJO ****
    key_t llave1 = 1670;
    int shmid1 = shmget(llave1, sizeof(int) * N * N * 2, IPC_CREAT | 0666);
    int (*shm_mu_md_ph)[N] = shmat(shmid1, NULL, 0);

    // Crear segmento de memoria compartida para la matriz uno y dos
    if (shmid1 < 0) {
        perror("Error al obtener memoria compartida para la matriz uno y dos: shmget");
        exit(1);
    }
    
    // Enlazar la memoria compartida para la matriz uno y dos
    if (shm_mu_md_ph == (int (*)[N]) -1) {
        perror("Error al enlazar la memoria compartida para la matriz uno y dos: shmat");
        exit(1);
    }

    // **** MEMORIA COMPARTIDA PARA LAS MATRICES HIJO-NIETO ****
    key_t llave2 = 1671;
    int shmid2 = shmget(llave2, sizeof(int) * N * N * 2, IPC_CREAT | 0666);
    int (*shm_mu_md_hn)[N] = shmat(shmid2, NULL, 0);

    // Crear segmento de memoria compartida para la matriz uno y dos
    if (shmid2 < 0) {
        perror("Error al obtener memoria compartida para la matriz uno y dos: shmget");
        exit(1);
    }
    
    // Enlazar la memoria compartida para la matriz uno y dos
    if (shm_mu_md_hn == (int (*)[N]) -1) {
        perror("Error al enlazar la memoria compartida para la matriz uno y dos: shmat");
        exit(1);
    }

    // **** MEMORIA COMPARTIDA PARA LOS RESULTADOS ****
    key_t llave3 = 1672;
    int shmid3 = shmget(llave3, sizeof(int) * N * N * 2, IPC_CREAT | 0666);
    int (*shm_resultados)[N] = shmat(shmid3, NULL, 0);

    // Crear segmento de memoria compartida para las matrices de resultados
    if (shmid3 < 0) {
        perror("Error al obtener memoria compartida para la matriz de resultados: shmget");
        exit(1);
    }

    // Enlazar la memoria compartida para las matrices de resultados
    if (shm_resultados == (int (*)[N]) -1) {
        perror("Error al enlazar la memoria compartida para la matriz de resultados: shmat");
        exit(1);
    }
    
    // **** SEMÁFOROS PARA LA COMUNICACIÓN ENTRE PROCESOS ****

    // Identificadores de los semáforos
    int semid_PH, semid_HN, semid_resultados;

    // LLaves para los semáforos
    key_t llave_PH = 1234;
    key_t llave_HN = 1235;
    key_t llave_resultados = 1236;
    int semban = IPC_CREAT | 0666;


    // Crear los semáforos
    if ((semid_PH = semget(llave_PH, 1, semban)) == -1)
    {
        perror("semget: error al crear semaforo de comunicacion entre padre e hijo");
        exit(1);
    }

    if ((semid_HN = semget(llave_HN, 1, semban)) == -1)
    {
        perror("semget: error al crear semaforo de comunicacion entre hijo y nieto");
        exit(1);
    }

    if ((semid_resultados = semget(llave_resultados, 1, semban)) == -1)
    {
        perror("semget: error al crear semaforo resultados");
        exit(1);
    }

    // Variables para procesos
    int pid;

    if ((pid = fork()) == 0) // Proceso hijo
    {
        // **** PROCESO HIJO TOMA EL CONTROL (Después de que el padre libere el semaforo) ****

        // Tomar el semaforo de comunicacion entre padre e hijo
        sem_tomar(semid_PH);

        // Crear dos matrices de tamaño N x N
        int matrizuno[N][N];
        int matrizdos[N][N];

        // Leer las matrices de la memoria compartida
        LeerDosMatricesMemoria(matrizuno, matrizdos, shm_mu_md_ph);
        
        // Realizar la multiplicación de las matrices
        int matrizresultado[N][N];
        MultiplicarMatrices(matrizuno, matrizdos, matrizresultado);

        // Escribir la matriz resultado en la memoria compartida
        EscribirMatrizMemoria(matrizresultado, (int *)shm_resultados);

        // Liberar el semaforo de comunicacion entre padre e hijo
        sem_liberar(semid_PH);
        

        // **** PROCESO HIJO ESCRIBE LAS MATRICES EN LA MEMORIA COMPARTIDA ****

        // Tomar el semaforo de comunicacion entre hijo y nieto
        sem_tomar(semid_HN);
        
        // Escribir las matrices en la memoria compartida
        EscribirDosMatricesMemoria(matrizuno, matrizdos, shm_mu_md_hn);

        // Liberar el semaforo de comunicacion entre hijo y nieto
        sem_liberar(semid_HN);

        if ((pid = fork()) == 0) // Proceso nieto
        {
            // **** PROCESO NIETO TOMA EL CONTROL (Después de que el hijo libere el semaforo) ****

            // Tomar el semaforo de comunicacion entre hijo y nieto
            sem_tomar(semid_HN);
            
            // Crear dos matrices de tamaño N x N
            int matrizuno[N][N];
            int matrizdos[N][N];

            // Leer las matrices de la memoria compartida
            LeerDosMatricesMemoria(matrizuno, matrizdos, shm_mu_md_hn);
            
            // Realizar la suma de las matrices
            int matrizresultado[N][N];
            SumarMatrices(matrizuno, matrizdos, matrizresultado);

            // Escribir la matriz resultado en la memoria compartida segunda seccion
            EscribirMatrizMemoria(matrizresultado, (int *)shm_resultados + (N * N));

            // Liberar el semaforo de comunicacion entre hijo y nieto
            sem_liberar(semid_HN);

            // Liberar el semaforo de comunicacion de resultados
            sem_liberar(semid_resultados);
            
            // Finalización del proceso nieto
            exit(0);
        }
        // Finalización del proceso hijo
        exit(0);
    }
    else // Proceso padre
    {
        // **** PROCESO PADRE ESCRIBE LAS MATRICES EN LA MEMORIA COMPARTIDA ****
        // Tomar el semaforo de comunicacion entre padre e hijo
        sem_tomar(semid_PH);

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
        EscribirDosMatricesMemoria(matrizuno, matrizdos, shm_mu_md_ph);

        // Liberar el semaforo de comunicacion entre padre e hijo (hijo toma el control)
        sem_liberar(semid_PH);


        // **** PROCESO PADRE (Espera a que el nieto libere el semaforo de resultados) ****

        /**
         * Lógica: No podemos tomar dos semáforos de forma consecutiva, tenemos que esperar a que alguien 
         * libere el semáforo antes de tomarlo de nuevo.
         * Por lo tanto, el primer semáforo toma el control bloqueando el proceso y el segundo espera a que alguien lo libere.
         */
        sem_tomar(semid_resultados); // Bloquear el padre hasta que el nieto libere el semáforo
        sem_tomar(semid_resultados); // Esperar a que el nieto libere el semáforo
        
        // Leer las matrices de resultados de la memoria compartida
        int matrizresultado_mult[N][N];
        int matrizresultado_suma[N][N];

        // Leer las matrices de resultados de la memoria compartida
        LeerDosMatricesMemoria(matrizresultado_mult, matrizresultado_suma, shm_resultados);

        // Imprimir las matrices de resultados
        printf("\nMatriz resultado de la multiplicacion (final - desde padre):\n");
        ImprimirMatriz(matrizresultado_mult);
        printf("\nMatriz resultado de la suma (final - desde padre):\n");
        ImprimirMatriz(matrizresultado_suma);

        // Calcular la inversa de la matriz resultado de la multiplicación
        double matrizinversa_multi[N][N];
        InversaMatriz(matrizresultado_mult, matrizinversa_multi);

        // Imprimir la matriz inversa
        printf("\nMatriz inversa de la multiplicacion:\n");
        ImprimirInversa(matrizinversa_multi);

        // Calcular la inversa de la matriz resultado de la suma
        double matrizinversa_suma[N][N];
        InversaMatriz(matrizresultado_suma, matrizinversa_suma);
        
        // Imprimir la matriz inversa
        printf("\nMatriz inversa de la suma:\n");
        ImprimirInversa(matrizinversa_suma);

        // Liberar el semaforo de resultados
        sem_liberar(semid_resultados);
    }

    // Liberar la memoria compartida
    shmdt(shm_mu_md_ph);
    shmdt(shm_mu_md_hn);
    shmdt(shm_resultados);

    // Liberar los semáforos
    semctl(semid_PH, 0, IPC_RMID);
    semctl(semid_HN, 0, IPC_RMID);
    semctl(semid_resultados, 0, IPC_RMID);
    
    // Finalización del proceso padre
    return 0;
}