#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define TAM_MEM_QUINTUPLE (5 * N * N * sizeof(int))
#define TAM_MEM_DOUBLE (2 * N * N * sizeof(double))

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
 * Abre la memoria compartida de enteros.
 * 
 * @param nombre El nombre de la memoria compartida.
 * @param hMemCom El identificador del mapeo de archivo de la memoria compartida.
 * @return Un puntero a los datos de la memoria compartida.
 */
int* AbrirMemoriaCompartidaEnteros(const char* nombre, HANDLE hMemCom)
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
            TAM_MEM_QUINTUPLE
        )) == NULL) {
        printf("No se enlazó la memoria compartida: (%i)\n", GetLastError());
        CloseHandle(hMemCom);
        exit(-1);
    }

    return apDatos;
}

/**
 * Abre la memoria compartida de doubles.
 * 
 * @param nombre El nombre de la memoria compartida.
 * @param hMemCom El identificador del mapeo de archivo de la memoria compartida.
 * @return Un puntero a los datos de la memoria compartida.
 */
int* AbrirMemoriaCompartidaDoubles(const char* nombre, HANDLE hMemCom)
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
            TAM_MEM_DOUBLE
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
void LeerMemoriaCompartidaEntera(int matriz[N][N], int* punteroDatos)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = *punteroDatos++;
        }
    }
}

/**
 * Lee los datos de una memoria compartida quintuple.
 * 
 * Esta función lee los datos de dos matrices de tamaño N x N desde una memoria compartida,
 * utilizando un puntero a los datos de la memoria compartida.
 * 
 * @param matrizuno La primera matriz donde se almacenarán los datos leídos.
 * @param matrizdos La segunda matriz donde se almacenarán los datos leídos.
 * @param punteroDatos El puntero a los datos de la memoria compartida.
 */
void LeerMemoriaCompartidaQuintuple(int matrizuno[N][N], int matrizdos[N][N], int matriztres[N][N], int matrizcuatro[N][N], int matrizcinco[N][N], int* punteroDatos)
{
    LeerMemoriaCompartidaEntera(matrizuno, punteroDatos);
    LeerMemoriaCompartidaEntera(matrizdos, punteroDatos + (N * N));
    LeerMemoriaCompartidaEntera(matriztres, punteroDatos + (2 * N * N));
    LeerMemoriaCompartidaEntera(matrizcuatro, punteroDatos + (3 * N * N));
    LeerMemoriaCompartidaEntera(matrizcinco, punteroDatos + (4 * N * N));
}

// Función para leer una matriz de la memoria compartida
void LeerMemoriaCompartidaDouble(double matriz[N][N], double* punteroDatos)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = *punteroDatos++;
        }
    }
}

// Función para leer una matriz de la memoria compartida
void LeerMemoriaCompartidaDoble(double matrizuno[N][N], double matrizdos[N][N], double* punteroDatos)
{
    LeerMemoriaCompartidaDouble(matrizuno, punteroDatos);
    LeerMemoriaCompartidaDouble(matrizdos, punteroDatos + (N * N));
}

/**
 * Función principal del programa.
 * 
 * @return Valor entero que indica el estado de finalización del programa.
 */
int main(void)
{
    // *********** Seccion : Lectura de las matrices de resultado enteras ***********

    // Matrices para almacenar los resultados enteros
    int Res_suma[N][N];
    int Res_resta[N][N];
    int Res_multiplicacion[N][N];
    int Res_traspuesta_uno[N][N];
    int Res_traspuesta_dos[N][N];

    // Manejadores y punteros para la memoria compartida de resultados enteros
    HANDLE hMemComRes;
    int* apDatosRes;

    // Abre el mapeo de archivo de la memoria compartida para las matrices de resultado enteras
    AbrirMemoriaCompartidaEnteros("Memoria_Compartida_Resultados", hMemComRes);

    // Lee las matrices de enteros de la memoria compartida
    LeerMemoriaCompartidaQuintuple(Res_suma, Res_resta, Res_multiplicacion, Res_traspuesta_uno, Res_traspuesta_dos, apDatosRes);

    // *********** Seccion : Lectura de las matrices de resultado double ***********

    // Matrices para almacenar los resultados doubles
    double Res_inversa_uno[N][N];
    double Res_inversa_dos[N][N];

    // Manejadores y punteros para la memoria compartida de resultados doubles
    HANDLE hMemComResD;
    double* apDatosResD;

    // Abre el mapeo de archivo de la memoria compartida para las matrices de resultado double
    AbrirMemoriaCompartidaDoubles("Memoria_Compartida_Resultados_Double", hMemComResD);

    // Lee las matrices de doubles de la memoria compartida
    LeerMemoriaCompartidaDoble(Res_inversa_uno, Res_inversa_dos, apDatosResD);

    // Imprimir las matrices de resultado
    printf("\nResultado suma: \n");
    ImprimirMatriz(Res_suma);
    printf("\nResultado resta: \n");
    ImprimirMatriz(Res_resta);
    printf("\nResultado multiplicacion: \n");
    ImprimirMatriz(Res_multiplicacion);
    printf("\nResultado traspuesta uno: \n");
    ImprimirMatriz(Res_traspuesta_uno);
    printf("\nResultado traspuesta dos: \n");
    ImprimirMatriz(Res_traspuesta_dos);
    printf("\nResultado inversa uno: \n");
    ImprimirInversa(Res_inversa_uno);
    printf("\nResultado inversa dos: \n");
    ImprimirInversa(Res_inversa_dos);
    
    // *********** Seccion : liberacion de semaforo para cada proceso hermano (indicar a los hermanos que se termino de leer) ***********
    HANDLE hSemaforo_resultados;

    // Abrir el semáforo de resultado para la suma
    if ((hSemaforo_resultados = OpenSemaphore(SEMAPHORE_ALL_ACCESS , FALSE, "Sem_Resultados_Sum")) == NULL) {
        printf("Falla al invocar OpenSemaphore: %d\n", GetLastError());
        return -1;
    }

    // Liberación del semáforo de la suma
    if (!ReleaseSemaphore(hSemaforo_resultados, 1, NULL)) {
        printf("Falla al invocar ReleaseSemaphore: %d\n", GetLastError());
    }

    // Abrir el semáforo de resultado para la resta
    if ((hSemaforo_resultados = OpenSemaphore(SEMAPHORE_ALL_ACCESS , FALSE, "Sem_Resultados_Rest")) == NULL) {
        printf("Falla al invocar OpenSemaphore: %d\n", GetLastError());
        return -1;
    }

    // Liberación del semáforo de la resta
    if (!ReleaseSemaphore(hSemaforo_resultados, 1, NULL)) {
        printf("Falla al invocar ReleaseSemaphore: %d\n", GetLastError());
    }

    // Abrir el semáforo de resultado para la multiplicacion
    if ((hSemaforo_resultados = OpenSemaphore(SEMAPHORE_ALL_ACCESS , FALSE, "Sem_Resultados_Mult")) == NULL) {
        printf("Falla al invocar OpenSemaphore: %d\n", GetLastError());
        return -1;
    }

    // Liberación del semáforo de la multiplicacion
    if (!ReleaseSemaphore(hSemaforo_resultados, 1, NULL)) {
        printf("Falla al invocar ReleaseSemaphore: %d\n", GetLastError());
    }

    // Abrir el semáforo de resultado para las traspuestas
    if ((hSemaforo_resultados = OpenSemaphore(SEMAPHORE_ALL_ACCESS , FALSE, "Sem_Traspuestas")) == NULL) {
        printf("Falla al invocar OpenSemaphore: %d\n", GetLastError());
        return -1;
    }

    // Liberación del semáforo de las traspuestas
    if (!ReleaseSemaphore(hSemaforo_resultados, 1, NULL)) {
        printf("Falla al invocar ReleaseSemaphore: %d\n", GetLastError());
    }

    // Abrir el semáforo de resultado para las inversas
    if ((hSemaforo_resultados = OpenSemaphore(SEMAPHORE_ALL_ACCESS , FALSE, "Sem_Inversas")) == NULL) {
        printf("Falla al invocar OpenSemaphore: %d\n", GetLastError());
        return -1;
    }

    // Liberación del semáforo de las inversas
    if (!ReleaseSemaphore(hSemaforo_resultados, 1, NULL)) {
        printf("Falla al invocar ReleaseSemaphore: %d\n", GetLastError());
    }

    // Desmapear la vista del archivo de la memoria del proceso para las matrices de resultado enteras
    UnmapViewOfFile(apDatosRes);
    // Cerrar el manejador de la memoria compartida para las matrices de resultado enteras
    CloseHandle(hMemComRes);

    // Desmapear la vista del archivo de la memoria del proceso para las matrices de resultado double
    UnmapViewOfFile(apDatosResD);
    // Cerrar el manejador de la memoria compartida para las matrices de resultado double
    CloseHandle(hMemComResD);

    return 0;
}