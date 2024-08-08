#include <windows.h> 
#include <stdio.h> 
#include <time.h>

/**
 * Definiciones de constantes para el tamaño de la matriz
 * 
 * N: Tamaño de la matriz.
 */
#define N 10

/**
 * Llena una matriz con números aleatorios entre 0 y 100.
 * 
 * @param matriz La matriz a llenar.
 */
void LlenarMatriz(int matriz[N][N])
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            matriz[i][j] = rand() % 101; // Genera números aleatorios entre 0 y 100
        }
    }
}

/**
 * Convierte una matriz de enteros en una cadena de caracteres.
 * 
 * @param Matrizuno La matriz de enteros a convertir.
 * @param str La cadena de caracteres en la que se almacenará la matriz.
 */
void CrearStringMatriz(int Matrizuno[N][N], char str[N*N*10])
{
    str[0] = '\0'; // Inicializar la cadena como vacía
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            sprintf(str + strlen(str), " %d", Matrizuno[i][j]); // Agregar el número a la cadena
        }
    }
}

int main(int argc, char *argv[]) 
{ 
    STARTUPINFO si; /* Estructura de información inicial para Windows */ 
    PROCESS_INFORMATION pi; /* Estructura de información del administrador de procesos */ 
    int i;
    int j;
    
    srand(time(NULL)); // Inicializar la semilla para generación de números aleatorios

    // Declaración de las matrices
    int Matrizuno[N][N];
    int Matrizdos[N][N];

    // Llenar las matrices con valores aleatorios
    LlenarMatriz(Matrizuno);
    LlenarMatriz(Matrizdos);

    // Convertir las matrices en cadenas de caracteres
    char MatrizunoC[N*N*10];
    char MatrizdosC[N*N*10];

    // Crear las cadenas de las matrices
    CrearStringMatriz(Matrizuno, MatrizunoC);
    CrearStringMatriz(Matrizdos, MatrizdosC);

    // Creación de procesos hijos para ejecutar distintas operaciones
    char command[N*N*10];

    for(j = 1; j <= 6; j++)
    {
        ZeroMemory(&si, sizeof(si)); // Inicializar la estructura STARTUPINFO
        si.cb = sizeof(si); 
        ZeroMemory(&pi, sizeof(pi)); // Inicializar la estructura PROCESS_INFORMATION

        switch (j)
        {
            case 1:
                sprintf(command, "%s \"%s\" \"%s\"", "suma", MatrizunoC, MatrizdosC); // Preparar el comando para sumar matrices
                if (!CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
                {
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                break;
            case 2:
                sprintf(command, "%s \"%s\" \"%s\"", "resta", MatrizunoC, MatrizdosC); // Preparar el comando para restar matrices
                if (!CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                break;
            case 3:
                sprintf(command, "%s \"%s\" \"%s\"", "multiplicacion", MatrizunoC, MatrizdosC); // Preparar el comando para multiplicar matrices
                if (!CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                break;
            case 4:
                sprintf(command, "%s \"%s\" \"%s\"", "traspuesta", MatrizunoC, MatrizdosC); // Preparar el comando para transponer matrices
                if (!CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                break;
            case 5:
                sprintf(command, "%s \"%s\" \"%s\"", "inversa", MatrizunoC, MatrizdosC); // Preparar el comando para calcular la inversa de matrices
                if (!CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
                { 
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                break;
            case 6:
                sprintf(command, "archivo"); // Preparar el comando para guardar matrices en archivo
                if (!CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
                {
                    printf("Fallo al invocar CreateProcess (%d)\n", GetLastError()); 
                    return 1; 
                }
                break;
        }
        // Esperar a que el proceso hijo termine
        WaitForSingleObject(pi.hProcess, INFINITE); 
        CloseHandle(pi.hProcess); // Cerrar el handle del proceso
        CloseHandle(pi.hThread); // Cerrar el handle del hilo
    }
    return 0; 
}