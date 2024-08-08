#include <windows.h> 
#include <stdio.h> 
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
 * @param argc Cantidad de argumentos pasados por línea de comandos.
 * @param argv Arreglo de cadenas que contienen los argumentos pasados por línea de comandos.
 * @return Valor entero que indica el estado de finalización del programa.
 */
int main(int argc, char *argv[])
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

    // *********** Seccion : Creacion de la memoria compartida para la matriz uno y dos (enviadas a los hijo) ***********
    int* apDatos;
    HANDLE hMemCom = CrearMemoriaCompartidaDoble("Memoria_Compartida_Matrices_PH", &apDatos);
    EscribirMemoriaCompartidaDoble(Matrizuno, Matrizdos, apDatos);

    // *********** Seccion : Creacion de semaforo (esperar todos los resultados) ***********
    HANDLE hSemaforo_resultados_espera;

    // Creación del semaforo
    if ((hSemaforo_resultados_espera = CreateSemaphore(NULL, 0, 1 , "Sem_Resultados_Espera")) == NULL) {
        printf("Falla al invocar CreateSemaphore: %d\n", GetLastError());
        return -1;
    }

    // *********** Seccion : Creacion de 6 procesos hijos ***********
    STARTUPINFO si[6]; 
    PROCESS_INFORMATION pi[6]; 

    // Variables para mantener el manejo de los procesos
    HANDLE handles[6];

    for (int j = 1; j <= 6; j++)
    {
        ZeroMemory(&si[j-1], sizeof(si[j-1]));
        si[j-1].cb = sizeof(si[j-1]);
        ZeroMemory(&pi[j-1], sizeof(pi[j-1]));

        // Escribir las matrices en la memoria compartida
        EscribirMemoriaCompartidaDoble(Matrizuno, Matrizdos, apDatos);

        switch (j)
        {
            case 1:
                if(!CreateProcess(NULL, "suma", NULL, NULL, FALSE, 0, NULL, NULL, &si[j-1], &pi[j-1])) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                break;
            
            case 2:
                if(!CreateProcess(NULL, "resta", NULL, NULL, FALSE, 0, NULL, NULL, &si[j-1], &pi[j-1])) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                break;
            
            case 3:
                if(!CreateProcess(NULL, "multiplicacion", NULL, NULL, FALSE, 0, NULL, NULL, &si[j-1], &pi[j-1])) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                break;
            
            case 4:
                if(!CreateProcess(NULL, "traspuesta", NULL, NULL, FALSE, 0, NULL, NULL, &si[j-1], &pi[j-1])) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                break;

            case 5:
                if(!CreateProcess(NULL, "inversa", NULL, NULL, FALSE, 0, NULL, NULL, &si[j-1], &pi[j-1])) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                break;

            case 6:
                // Esperar a que el ultimo resultado sea escrito
                WaitForSingleObject(hSemaforo_resultados_espera, INFINITE);
                if(!CreateProcess(NULL, "recoleccion", NULL, NULL, FALSE, 0, NULL, NULL, &si[j-1], &pi[j-1])) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                break;
            
        }
        
        // Crear semaforo para los primeros 5 procesos
        if (j < 6)
        {
            // Creacion de semáforo (esperar a que cada hijo lea la matriz uno y dos)
            HANDLE hSemaforomatrices_PH;

            // Creación del semaforo
            if ((hSemaforomatrices_PH = CreateSemaphore(NULL, 0, 1, "Sem_Matrices_PH")) == NULL) {
                printf("Falla al invocar CreateSemaphore: %d\n", GetLastError());
                return -1;
            }
            // Esperar a que el hijo lea las matrices
            WaitForSingleObject(hSemaforomatrices_PH, INFINITE);
            // Cerrar el semáforo
            CloseHandle(hSemaforomatrices_PH);
        }

        // Guardar el manejador del proceso
        handles[j-1] = pi[j-1].hProcess;
    }

    // Desmapear la vista del archivo de la memoria del proceso para matriz uno y matriz dos
    UnmapViewOfFile(apDatos);
    // Cerrar el manejador de la memoria compartida para matriz uno y matriz dos
    CloseHandle(hMemCom);
    
    // Esperar a que todos los procesos hijos terminen
    WaitForMultipleObjects(6, handles, TRUE, INFINITE);

    // Cerrar los manejadores de los procesos hijos
    for (int j = 0; j < 6; j++) {
        CloseHandle(pi[j].hProcess);
        CloseHandle(pi[j].hThread);
    }

    return 0; 
}