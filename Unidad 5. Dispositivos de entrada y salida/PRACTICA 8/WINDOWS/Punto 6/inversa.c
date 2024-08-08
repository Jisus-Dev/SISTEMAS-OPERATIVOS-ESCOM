#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Definiciones de constantes para el tamaño de memoria y matriz.
 * 
 * N: Tamaño de la matriz.
 * TAM_MEM_DOBLE: Tamaño de dos matrices enteras en bytes.
 * TAM_MEM_DOUBLE: Tamaño de dos matrices doubles en bytes.
 */
#define N 10
#define TAM_MEM_DOBLE (2 * N * N * sizeof(int))
#define TAM_MEM_DOUBLE (2 * N * N * sizeof(double))

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
 * Crea una memoria compartida de tamaño doble y la enlaza a un puntero de doubles
 * 
 * @param nombre El nombre de la memoria compartida.
 * @param punteroDatos Un puntero a un puntero de doubles donde se enlazará la memoria compartida.
 * @return El identificador de la memoria compartida creada.
 */
HANDLE CrearMemoriaCompartidaDoble(const char* nombre, double** punteroDatos) {
    HANDLE hMemoria;
    if ((hMemoria = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            TAM_MEM_DOUBLE,
            nombre
        )) == NULL) {
        printf("No se creó la memoria compartida: (%i)\n", GetLastError());
        exit(-1);
    }

    if ((*punteroDatos = (double*)MapViewOfFile(
            hMemoria,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            TAM_MEM_DOUBLE
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
void EscribirMemoriaCompartida(double matriz[N][N], double* punteroDatos)
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
void EscribirMemoriaCompartidaDoble(double matrizuno[N][N], double matrizdos[N][N], double* punteroDatos)
{
    EscribirMemoriaCompartida(matrizuno, punteroDatos);
    EscribirMemoriaCompartida(matrizdos, punteroDatos + (N * N));
}

/**
 * Función principal del programa.
 * 
 * @return Valor entero que indica el estado de finalización del programa.
 */
int main(void)
{
    // Crear dos matrices de tamaño N x N
    int Matrizuno[N][N];
    int Matrizdos[N][N];

    // *********** Seccion : Lectura de matrices de la memoria compartida (provenientes del padre) ***********
    // Manejadores y punteros para la memoria compartida de las matrices
    HANDLE hMemComMatrices;
    int* apDatosMatrices;

    // Abre el mapeo de archivo de la memoria compartida para las matrices
    apDatosMatrices = AbrirMemoriaCompartida("Memoria_Compartida_Matrices_PH", hMemComMatrices);
    
    // Lee las matrices de la memoria compartida
    LeerMemoriaCompartidaDoble(Matrizuno, Matrizdos, apDatosMatrices);

    // Desmapear la vista del archivo de la memoria del proceso para las matrices
    UnmapViewOfFile(apDatosMatrices);
    // Cerrar el manejador de la memoria compartida para las matrices
    CloseHandle(hMemComMatrices);


    // *********** Seccion : liberacion de semaforo (indicar al padre que hijo termino de leer) ***********
    HANDLE hSemaforomatrices_PH;

    // Apertura del semáforo
    if ((hSemaforomatrices_PH = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Sem_Matrices_PH")) == NULL) {
        printf("Falla al invocar OpenSemaphore: %d\n", GetLastError());
        return -1;
    }

    // Liberación del semáforo
    if (!ReleaseSemaphore(hSemaforomatrices_PH, 1, NULL)) {
        printf("Falla al invocar ReleaseSemaphore: %d\n", GetLastError());
    }

    // *********** Seccion : Calcular la inversa de las matrices en el hijo *********
    // Crear las matrices de resultado
    double Inversa_uno[N][N];
    double Inversa_dos[N][N];

    // Calcular la inversa de la primera matriz
    InversaMatriz(Matrizuno, Inversa_uno);

    // Calcular la inversa de la segunda matriz
    InversaMatriz(Matrizdos, Inversa_dos);

    // *********** Seccion : Creacion de la memoria compartida para las matrices inversas *********
    double* apDatosResInversas;
    // Crear la memoria compartida para los resultados
    HANDLE hMemComResInversas = CrearMemoriaCompartidaDoble("Memoria_Compartida_Res_Inversa", &apDatosResInversas);
    // Escribir las matrices inversas en la memoria compartida
    EscribirMemoriaCompartidaDoble(Inversa_uno, Inversa_dos, apDatosResInversas);
    
    // *********** Seccion : liberacion de semáforo (indicar a recoleccion que los resultados estan listos) ***********
    HANDLE hSemaforo_resultados_espera;

    // Apertura del semáforo
    if ((hSemaforo_resultados_espera = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Sem_Resultados_Espera")) == NULL) {
        printf("Falla al invocar OpenSemaphore: %d\n", GetLastError());
        return -1;
    }

    // Liberación del semáforo
    if (!ReleaseSemaphore(hSemaforo_resultados_espera, 1, NULL)) {
        printf("Falla al invocar ReleaseSemaphore: %d\n", GetLastError());
    }

    // *********** Seccion : Creacion de semáforo (esperar a que recoleccion lea las matrices inversas) ***********
    HANDLE hSemaforo_inversa;

    // Creación del semáforo para esperar a que inversa lea las matrices inversas
    if ((hSemaforo_inversa = CreateSemaphore(NULL, 0, 1, "Sem_Inversas")) == NULL) {
        printf("Falla al invocar CreateSemaphore: %d\n", GetLastError());
        return -1;
    }

    // Esperar a que inversa lea las matrices inversas
    WaitForSingleObject(hSemaforo_inversa, INFINITE);

    // Desmapear la vista del archivo de la memoria del proceso para el resultado de la matriz de inversa dos
    UnmapViewOfFile(hMemComResInversas);
    // Cerrar el manejador de la memoria compartida para el resultado de la matriz de inversa dos
    CloseHandle(apDatosResInversas);
    
    return 0;
}