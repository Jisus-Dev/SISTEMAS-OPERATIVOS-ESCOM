#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
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
 * Crea una memoria compartida de tamaño doble y la enlaza a un puntero de enteros.
 * 
 * @param nombre El nombre de la memoria compartida.
 * @param punteroDatos Un puntero a un puntero de enteros donde se enlazará la memoria compartida.
 * @return El identificador de la memoria compartida creada.
 */
HANDLE CrearMemoriaCompartidaDoble(const char* nombre, int** punteroDatos)
{
    HANDLE hMemoria;
    if ((hMemoria = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            TAM_MEM_DOBLE,
            nombre
        )) == NULL) {
        printf("No se creó la memoria compartida: (%i)\n", GetLastError());
        exit(-1);
    }

    if ((*punteroDatos = (int*)MapViewOfFile(
            hMemoria,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            TAM_MEM_DOBLE
        )) == NULL) {
        printf("No se enlazó la memoria compartida: (%i)\n", GetLastError());
        CloseHandle(hMemoria);
        exit(-1);
    }

    return hMemoria;
}

/**
 * Escribe los elementos de una matriz en una memoria compartida.
 * 
 * @param matriz La matriz de entrada.
 * @param punteroDatos El puntero a la memoria compartida donde se escribirán los datos.
 */
void EscribirMemoriaCompartida(int matriz[N][N], int* punteroDatos)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            *punteroDatos++ = matriz[i][j];
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
void EscribirMemoriaCompartidaDoble(int matrizuno[N][N], int matrizdos[N][N], int* punteroDatos)
{
    EscribirMemoriaCompartida(matrizuno, punteroDatos);
    EscribirMemoriaCompartida(matrizdos, punteroDatos + (N * N));
}

/**
 * Abre la memoria compartida.
 * 
 * @param nombre El nombre de la memoria compartida.
 * @param hMemCom El identificador del mapeo de archivo de la memoria compartida.
 * @return Un puntero a los datos de la memoria compartida.
 */
int* AbrirMemoriaCompartida(const char* nombre, HANDLE hMemCom)
{
    int* apDatos;
    
    // Abre el mapeo de archivo de la memoria compartida
    if ((hMemCom = OpenFileMapping(
            FILE_MAP_ALL_ACCESS, 
            FALSE,               
            nombre
        )) == NULL) {
        printf("No se accedió a la memoria compartida para %s: (%i)\n", nombre, GetLastError());
        exit(-1);
    }

    // Mapea la vista del archivo a la memoria del proceso
    if ((apDatos = (int *)MapViewOfFile(
            hMemCom,             
            FILE_MAP_ALL_ACCESS, 
            0,
            0,
            TAM_MEM_DOBLE
        )) == NULL) {
        printf("No se enlazó la memoria compartida: (%i)\n", GetLastError());
        CloseHandle(hMemCom);
        exit(-1);
    }

    return apDatos;
}

/**
 * Lee los datos de una memoria compartida y los guarda en una matriz.
 * 
 * @param matriz La matriz en la que se guardarán los datos leídos.
 * @param punteroDatos El puntero a los datos en la memoria compartida.
 */
void LeerMemoriaCompartida(int matriz[N][N], int* punteroDatos)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = *punteroDatos++;
        }
    }
}

/**
 * Lee los datos de una memoria compartida doble.
 * 
 * Esta función lee los datos de dos matrices de tamaño N x N desde una memoria compartida,
 * utilizando un puntero a los datos de la memoria compartida.
 * 
 * @param matrizuno La primera matriz donde se almacenarán los datos leídos.
 * @param matrizdos La segunda matriz donde se almacenarán los datos leídos.
 * @param punteroDatos El puntero a los datos de la memoria compartida.
 */
void LeerMemoriaCompartidaDoble(int matrizuno[N][N], int matrizdos[N][N], int* punteroDatos)
{
    LeerMemoriaCompartida(matrizuno, punteroDatos);
    LeerMemoriaCompartida(matrizdos, punteroDatos + (N * N));
}

/**
 * Función principal del programa.
 * 
 * @param argc Cantidad de argumentos pasados por línea de comandos.
 * @param argv Arreglo de cadenas que contienen los argumentos pasados por línea de comandos.
 * @return Valor entero que indica el estado de finalización del programa.
 */
int main(int argc, char* argv[])
{
    // *********** Seccion : Creacion de matrices y llenado de las mismas ***********
    srand(time(NULL));

    // Crear dos matrices de tamaño N x N
    int Matrizuno[N][N];
    int Matrizdos[N][N];

    // Llenar las matrices con valores aleatorios
    LlenarMatriz(Matrizuno);
    LlenarMatriz(Matrizdos);

    // Imprimir las matrices
    printf("Matriz 1:\n");
    ImprimirMatriz(Matrizuno);
    printf("\nMatriz 2:\n");
    ImprimirMatriz(Matrizdos);

    // *********** Seccion : Creacion de la memoria compartida para la matriz uno y dos (enviadas al hijo) ***********
    int* apDatos;
    HANDLE hMemCom = CrearMemoriaCompartidaDoble("Memoria_Compartida_Matrices_PH", &apDatos);
    EscribirMemoriaCompartidaDoble(Matrizuno, Matrizdos, apDatos);

    // *********** Seccion : Creacion de Proceso hijo ***********
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    
    // Crear el proceso hijo
    if (!CreateProcess(NULL, argv[1], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("Fallo al invocar CreateProcess (%d)\n", GetLastError());
        return 1;
    }

    // *********** Seccion : Creacion de semáforo (esperar a que el hijo lea la matriz uno y dos) ***********
    HANDLE hSemaforomatrices_PH;

    // Creación del semáforo
    if ((hSemaforomatrices_PH = CreateSemaphore(NULL, 0, 1, "Sem_Matrices_PH")) == NULL) {
        printf("Falla al invocar CreateSemaphore: %d\n", GetLastError());
        return -1;
    }
    // Esperar a que el hijo lea las matrices
    WaitForSingleObject(hSemaforomatrices_PH, INFINITE);


    // Desmapear la vista del archivo de la memoria del proceso para matriz uno y matriz dos
    UnmapViewOfFile(apDatos);
    // Cerrar el manejador de la memoria compartida para matriz uno y matriz dos
    CloseHandle(hMemCom);


    // *********** Seccion : Creacion de semáforo (esperar resultado de suma y multiplicacion por parte del nieto) ***********
    HANDLE hSemaforo_resultados_espera;

    // Creación del semáforo
    if ((hSemaforo_resultados_espera = CreateSemaphore(NULL, 0, 1, "Sem_Resultados_Espera")) == NULL) {
        printf("Falla al invocar CreateSemaphore: %d\n", GetLastError());
        return -1;
    }

    // Esperar a que el nieto termine de escribir los resultados
    WaitForSingleObject(hSemaforo_resultados_espera, INFINITE);
    
    // *********** Seccion : Lectura de los resultados de multiplicacion y suma ***********

    // Matrices para almacenar los resultados
    int Resultado_multi[N][N];
    int Resultado_sum[N][N];

    // Manejadores y punteros para la memoria compartida de resultados
    HANDLE hMemComRes;
    int* apDatosRes;

    // Abre el mapeo de archivo de la memoria compartida para los resultados
    apDatosRes = AbrirMemoriaCompartida("Memoria_Compartida_Resultados", hMemComRes);
    
    // Lee los resultados de la memoria compartida
    LeerMemoriaCompartidaDoble(Resultado_multi,Resultado_sum, apDatosRes);

    // Desmapear la vista del archivo de la memoria del proceso para matriz de resultados
    UnmapViewOfFile(apDatosRes);
    // Cerrar el manejador de la memoria compartida para matriz de resultados
    CloseHandle(hMemComRes);
    
    // Imprimir los resultados
    printf("\nResultado de la suma:\n\n");
    ImprimirMatriz(Resultado_sum);
    printf("\nResultado de la multiplicacion:\n\n");
    ImprimirMatriz(Resultado_multi);

    // *********** Seccion : liberacion de semaforo para el proceso nieto (indicar al nieto que padre termino de leer) ***********
    HANDLE hSemaforo_resultados;

    // Apertura del semáforo
    if ((hSemaforo_resultados = OpenSemaphore(SEMAPHORE_ALL_ACCESS , FALSE, "Sem_Resultados")) == NULL) {
        printf("Falla al invocar OpenSemaphore: %d\n", GetLastError());
        return -1;
    }

    // Liberación del semáforo
    if (!ReleaseSemaphore(hSemaforo_resultados, 1, NULL)) {
        printf("Falla al invocar ReleaseSemaphore: %d\n", GetLastError());
    }

    // *********** Seccion : Calcular la inversa de la matriz de resultados de la multiplicacion y la suma ***********
    // Matrices para almacenar las inversas
    double Inversa_multi[N][N];
    double Inversa_sum[N][N];

    // Calcular las matrices inversas
    InversaMatriz(Resultado_multi, Inversa_multi);
    InversaMatriz(Resultado_sum, Inversa_sum);

    // Imprimir las matrices inversas
    printf("\nInversa del resultado de la multiplicacion:\n\n");
    ImprimirInversa(Inversa_multi);
    printf("\nInversa del resultado de la suma:\n\n");
    ImprimirInversa(Inversa_sum);
    
    // Esperar a que el proceso hijo termine
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Terminación controlada del proceso e hilo asociado de ejecución 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}