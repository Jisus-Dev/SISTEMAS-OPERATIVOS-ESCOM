#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Definiciones de constantes para el tamaño de memoria y matriz.
 * 
 * N: Tamaño de la matriz.
 * TAM_MEM_DOBLE: Tamaño de dos matrices en bytes.
 */
#define N 10
#define TAM_MEM_DOBLE (2 * N * N * sizeof(int))

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

     // *********** Seccion : Lectura de matrices de la memoria compartida (provenientes del hijo) ***********
    // Manejadores y punteros para la memoria compartida de las matrices
    HANDLE hMemComMatrices;
    int* apDatosMatrices;

    // Abre el mapeo de archivo de la memoria compartida para las matrices
    apDatosMatrices = AbrirMemoriaCompartida("Memoria_Compartida_Matrices_HN", hMemComMatrices);
    
    // Lee las matrices de la memoria compartida
    LeerMemoriaCompartidaDoble(Matrizuno, Matrizdos, apDatosMatrices);

    // Desmapear la vista del archivo de la memoria del proceso para las matrices
    UnmapViewOfFile(apDatosMatrices);
    // Cerrar el manejador de la memoria compartida para las matrices
    CloseHandle(hMemComMatrices);

    // *********** Seccion : liberacion de semáforo (indicar al hijo que nieto termino de leer) ***********
    HANDLE hSemaforomatrices_HN;

    // Apertura del semáforo
    if ((hSemaforomatrices_HN = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Sem_Matrices_HN")) == NULL) {
        printf("Falla al invocar OpenSemaphore: %d\n", GetLastError());
        return -1;
    }

    // Liberación del semáforo
    if (!ReleaseSemaphore(hSemaforomatrices_HN, 1, NULL)) {
        printf("Falla al invocar ReleaseSemaphore: %d\n", GetLastError());
    }
    
    // *********** Seccion : Calcular la multiplicación de las matrices en el nieto *********
    // Crear la matriz de resultado de la suma
     int Resultado[N][N];
    // Realizar la suma de las matrices
    SumarMatrices(Matrizuno, Matrizdos,Resultado);
    
    // *********** Seccion : Creacion de la memoria compartida para las matrices de resultados multiplicacion y suma *********
    // Manejadores y punteros para la memoria compartida de las matrices de resultados
    HANDLE hMemComResultados;
    int* apDatosResultados;

    // Abre el mapeo de archivo de la memoria compartida para las matrices
    apDatosResultados = AbrirMemoriaCompartida("Memoria_Compartida_Resultados",hMemComResultados);
    // Escribir el resultado de la suma en la memoria compartida (segunda seccion de la memoria)
    EscribirMemoriaCompartida(Resultado, apDatosResultados);

    // Desmapear la vista del archivo de la memoria del proceso para matriz de resultado de la multiplicacion
    UnmapViewOfFile(apDatosResultados);
    // Cerrar el manejador de la memoria compartida para matriz de resultado de la multiplicacion
    CloseHandle(hMemComResultados);

    // *********** Seccion : liberacion de semáforo (indicar al padre que nieto termino la escritura) ***********
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
    
    // *********** Seccion : Creacion de semáforo (esperar a que el padre lea las matrices de resultados) ***********
    HANDLE hSemaforo_resultados;

    // Creación del semáforo
    if ((hSemaforo_resultados = CreateSemaphore(NULL, 0, 1, "Sem_Resultados")) == NULL) {
        printf("Falla al invocar CreateSemaphore: %d\n", GetLastError());
        return -1;
    }

    // Esperar a que el padre lea los resultados
    WaitForSingleObject(hSemaforo_resultados, INFINITE);

    return 0;
}
