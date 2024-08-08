#include <windows.h> 
#include <stdio.h> 
#include <time.h>

/**
 * Definiciones de constantes para el tamaño de la matriz
 * 
 * N: Tamaño de la matriz.
 * TAM_MEM: Tamaño de la memoria compartida.
 */
#define N 10
#define TAM_MEM (N * N * sizeof(int))

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
            matriz[i][j] = rand() % 101; // Genera un número aleatorio entre 0 y 100
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
        {
            printf("%d\t", matriz[i][j]); // Imprime cada elemento de la matriz con tabulación
        }
        printf("\n"); // Nueva línea al final de cada fila
    }
}

/**
 * Crea memoria compartida con un nombre específico.
 *
 * @param nombre El nombre de la memoria compartida.
 * @param punteroDatos Un puntero a un puntero de enteros donde se almacenará la dirección de la memoria compartida.
 * @return El manejador de la memoria compartida.
 */
HANDLE CrearMemoriaCompartida(const char* nombre, int** punteroDatos)
{
    HANDLE hMemoria;
    if ((hMemoria = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            TAM_MEM,
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
            TAM_MEM
        )) == NULL) {
        printf("No se enlazó la memoria compartida: (%i)\n", GetLastError());
        CloseHandle(hMemoria);
        exit(-1);
    }

    return hMemoria;
}

/**
 * Escribe los datos de una matriz en la memoria compartida.
 *
 * @param matriz La matriz a escribir.
 * @param punteroDatos El puntero a la memoria compartida donde se escribirá la matriz.
 */
void EscribirMemoriaCompartida(int matriz[N][N], int* punteroDatos)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            *punteroDatos++ = matriz[i][j]; // Escribe cada elemento de la matriz en la memoria compartida.
        }
    }
}

int main(int argc, char *argv[]) 
{ 
    // *********** Sección : Llenar Matrices Aleatorias ***********
    srand(time(NULL));

    int Matrizuno[N][N];
    int Matrizdos[N][N];

    // Llenar las matrices con valores aleatorios
    LlenarMatriz(Matrizuno);
    LlenarMatriz(Matrizdos);
    
    // Mostrar las matrices creadas
    printf("Matriz 1:\n");
    ImprimirMatriz(Matrizuno);
    printf("\nMatriz 2:\n");
    ImprimirMatriz(Matrizdos);

    // *********** Sección : Creación de 6 procesos hijos ***********
    STARTUPINFO si[6]; 
    PROCESS_INFORMATION pi[6]; 
    

    // Variables para mantener el manejo de los procesos
    HANDLE handles[6];

    for (int j = 1; j <= 6; j++)
    {
        ZeroMemory(&si[j-1], sizeof(si[j-1]));
        si[j-1].cb = sizeof(si[j-1]);
        ZeroMemory(&pi[j-1], sizeof(pi[j-1]));

        int* apDatosUno;
        int* apDatosDos;

        // Crear memoria compartida para las matrices
        HANDLE hMemComUno = CrearMemoriaCompartida("Memoria_Compartida_MU_PH", &apDatosUno);
        HANDLE hMemComDos = CrearMemoriaCompartida("Memoria_Compartida_MD_PH", &apDatosDos);
        
        // Escribir las matrices en la memoria compartida
        EscribirMemoriaCompartida(Matrizuno, apDatosUno);
        EscribirMemoriaCompartida(Matrizdos, apDatosDos);

        switch (j)
        {
            case 1:
                // Crear proceso hijo para la suma
                if(!CreateProcess(NULL, "suma", NULL, NULL, FALSE, 0, NULL, NULL, &si[j-1], &pi[j-1])) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                // Esperar hasta que el hijo haya leído las matrices
                while (apDatosUno[0] != -1 && apDatosDos[0] != -1)
                {
                    Sleep(1);
                }
                break;
            
            case 2:
                // Crear proceso hijo para la resta
                if(!CreateProcess(NULL, "resta", NULL, NULL, FALSE, 0, NULL, NULL, &si[j-1], &pi[j-1])) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                // Esperar hasta que el hijo haya leído las matrices
                while (apDatosUno[0] != -1 && apDatosDos[0] != -1)
                {
                    Sleep(1);
                }
                break;
            
            case 3:
                // Crear proceso hijo para la multiplicación
                if(!CreateProcess(NULL, "multiplicacion", NULL, NULL, FALSE, 0, NULL, NULL, &si[j-1], &pi[j-1])) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                // Esperar hasta que el hijo haya leído las matrices
                while (apDatosUno[0] != -1 && apDatosDos[0] != -1)
                {
                    Sleep(1);
                }
                break;
            
            case 4:
                // Crear proceso hijo para la traspuesta
                if(!CreateProcess(NULL, "traspuesta", NULL, NULL, FALSE, 0, NULL, NULL, &si[j-1], &pi[j-1])) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                // Esperar hasta que el hijo haya leído las matrices
                while (apDatosUno[0] != -1 && apDatosDos[0] != -1)
                {
                    Sleep(1);
                }
                break;

            case 5:
                // Crear proceso hijo para la inversa
                if(!CreateProcess(NULL, "inversa", NULL, NULL, FALSE, 0, NULL, NULL, &si[j-1], &pi[j-1])) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                // Esperar hasta que el hijo haya leído las matrices
                while (apDatosUno[0] != -1 && apDatosDos[0] != -1)
                {
                    Sleep(1);
                }
                break;

            case 6:
                // Crear proceso hijo para la recolección de resultados
                if(!CreateProcess(NULL, "recoleccion", NULL, NULL, FALSE, 0, NULL, NULL, &si[j-1], &pi[j-1])) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                break;
            
        }

        // Guardar el manejador del proceso
        handles[j-1] = pi[j-1].hProcess;

        // No cerrar los manejadores de proceso

        // Desmapear la vista del archivo de la memoria del proceso para matriz uno y matriz dos
        UnmapViewOfFile(apDatosUno);
        UnmapViewOfFile(apDatosDos);

        // Cerrar el manejador de la memoria compartida para matriz uno y matriz dos
        CloseHandle(hMemComUno);
        CloseHandle(hMemComDos);
    }
    
    // Esperar hasta que todos los procesos hijos hayan terminado
    WaitForMultipleObjects(6, handles, TRUE, INFINITE);

    // Cerrar los manejadores de los procesos hijos
    for (int j = 0; j < 6; j++) {
        CloseHandle(pi[j].hProcess);
        CloseHandle(pi[j].hThread);
    }

    return 0; 
}