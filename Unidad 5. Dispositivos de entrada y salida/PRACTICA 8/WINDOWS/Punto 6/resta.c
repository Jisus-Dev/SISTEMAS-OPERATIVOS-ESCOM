#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Definiciones de constantes para el tamaño de memoria.
 * 
 * N: Tamaño de la matriz.
 * TAM_MEM_DOBLE: Tamaño de dos matrices en bytes.
 * TAM_MEM_QUINTUPLE: Tamaño de cinco matrices en bytes.
 */
#define N 10
#define TAM_MEM_DOBLE (2 * N * N * sizeof(int))

/**
 * Resta dos matrices cuadradas y guarda el resultado en una tercera matriz.
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
 * Escribe los elementos de una matriz en una memoria compartida.
 * 
 * @param matriz La matriz de entrada.
 * @param punteroDatos El puntero a la memoria compartida donde se escribirán los datos.
 */
void EscribirMemoriaCompartida(int matriz[N][N], int* punteroDatos)
{
    // Avanzar al inicio de la segunda sección de la memoria compartida
    punteroDatos += N * N;

    // Escribir el resultado de la suma en la memoria compartida
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            *punteroDatos++ = matriz[i][j];
        }
    }
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

    // *********** Seccion : Calcular la resta de matrices en el hijo *********
    // Crear la matriz de resultado
    int Resultado[N][N];
    // Calcular la resta de las matrices
    RestarMatrices(Matrizuno, Matrizdos, Resultado);

    // *********** Seccion : Creacion de la memoria compartida para las matrices de resultado *********
    HANDLE hMemComResultados;
    int* apDatosResultados;

    // Abre el mapeo de archivo de la memoria compartida para las matrices
    apDatosResultados = AbrirMemoriaCompartida("Memoria_Compartida_Resultados", hMemComResultados);
    
    // Escribir el resultado de la resta en la memoria compartida (segunda seccion de la memoria)
    EscribirMemoriaCompartida(Resultado, apDatosResultados);

    // *********** Seccion : Creacion de semáforo (esperar a que recoleccion lea las matrices de resultados) ***********
    HANDLE hSemaforo_resultados;

    // Creación del semáforo para esperar a que recoleccion lea el resultado de la resta
    if ((hSemaforo_resultados = CreateSemaphore(NULL, 0, 1, "Sem_Resultados_Rest")) == NULL) {
        printf("Falla al invocar CreateSemaphore: %d\n", GetLastError());
        return -1;
    }

    // Esperar a que recoleccion lea el resultado de la resta
    WaitForSingleObject(hSemaforo_resultados, INFINITE);

    // Desmapear la vista del archivo de la memoria del proceso para los resultados
    UnmapViewOfFile(apDatosResultados);
    // Cerrar el manejador de la memoria compartida para los resultados
    CloseHandle(hMemComResultados);

    return 0;
}