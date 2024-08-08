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

    // *********** Seccion : liberacion de semáforo (indicar al padre que hijo termino de leer) ***********
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

    // *********** Seccion : Calcular la multiplicación de las matrices en el hijo *********
    // Crear la matriz de resultado para la multiplicación
    int Resultado[N][N];
    // Realizar la multiplicación de las matrices
    MultiplicarMatrices(Matrizuno, Matrizdos,Resultado);

    // *********** Seccion : Creacion de la memoria compartida para las matrices de resultados multiplicacion y suma *********
    int* apDatosResultados;
    // Crear la memoria compartida para los resultados
    HANDLE hMemComResultados = CrearMemoriaCompartidaDoble("Memoria_Compartida_Resultados", &apDatosResultados);
    // Escribir el resultado de la multiplicación en la memoria compartida (primera seccion de la memoria)
    EscribirMemoriaCompartida(Resultado, apDatosResultados);

    // *********** Seccion : Creacion de la memoria compartida para la matriz uno y dos (enviadas al nieto) ***********
    int* apDatos;
    // Crear la memoria compartida para las matrices
    HANDLE hMemCom = CrearMemoriaCompartidaDoble("Memoria_Compartida_Matrices_HN", &apDatos);
    // Escribir las matrices en la memoria compartida
    EscribirMemoriaCompartidaDoble(Matrizuno, Matrizdos, apDatos);

    // *********** Seccion : Creación del proceso nieto *********
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Crear el proceso nieto
    if (!CreateProcess(NULL,"memoria_3", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("Fallo al invocar CreateProcess (%d)\n", GetLastError());
        return 1;
    }

    // *********** Seccion : Creacion de semáforo (esperar a que el nieto lea la matriz uno y dos) ***********
    HANDLE hSemaforomatrices_HN;

    // Creación del semáforo
    if ((hSemaforomatrices_HN = CreateSemaphore(NULL, 0, 1, "Sem_Matrices_HN")) == NULL) {
        printf("Falla al invocar CreateSemaphore: %d\n", GetLastError());
        return -1;
    }

    // Esperar a que el nieto lea las matrices
    WaitForSingleObject(hSemaforomatrices_HN, INFINITE);

    // Desmapear la vista del archivo de la memoria del proceso para matriz uno y matriz dos
    UnmapViewOfFile(apDatos);
    // Cerrar el manejador de la memoria compartida para matriz uno y matriz dos
    CloseHandle(hMemCom);

    // Esperar a que el proceso hijo termine
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Desmapear la vista del archivo de la memoria del proceso para los resultados
    UnmapViewOfFile(apDatosResultados);
    // Cerrar el manejador de la memoria compartida para los resultados
    CloseHandle(hMemComResultados);
    
    // Terminación controlada del proceso e hilo asociado de ejecución 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}