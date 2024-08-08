#include <windows.h>
#include <stdio.h>
#include <string.h>

/**
 * Definiciones de constantes para el tamaño de la matriz
 * 
 * N: Tamaño de la matriz.
 */
#define N 10

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
            resultado[i][j] = 0; // Inicializa el elemento en 0 antes de la suma.
            for (int k = 0; k < N; k++)
            {
                resultado[i][j] += matrizuno[i][k] * matrizdos[k][j]; // Multiplicación y suma.
            }
        }
    }
}

int main()
{
    // Manejador para lectura desde la tubería estándar de entrada
    HANDLE hLecturaPipe = GetStdHandle(STD_INPUT_HANDLE);
    DWORD lectura;

    // Manejador para escritura hacia la tubería estándar de salida
    HANDLE hEscrituraPipe = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD escritura;

    // Manejadores para las tuberías de lectura y escritura del proceso nieto
    HANDLE hLecturaPipe_nieto_I, hEscrituraPipe_nieto_I;
    HANDLE hLecturaPipe_nieto_O, hEscrituraPipe_nieto_O;
    SECURITY_ATTRIBUTES pipeSeg = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

    // Estructuras para el proceso hijo
    STARTUPINFO siHijo;
    PROCESS_INFORMATION piHijo;

    // Creación de las tuberías para comunicación entre el proceso hijo y el proceso nieto
    CreatePipe(&hLecturaPipe_nieto_I, &hEscrituraPipe_nieto_I, &pipeSeg, 0);
    CreatePipe(&hLecturaPipe_nieto_O, &hEscrituraPipe_nieto_O, &pipeSeg, 0);

    int Matrizuno[N][N];
    int Matrizdos[N][N];

    // Leer las matrices enviadas desde el proceso padre
    ReadFile(hLecturaPipe, Matrizuno, sizeof(Matrizuno), &lectura, NULL);
    ReadFile(hLecturaPipe, Matrizdos, sizeof(Matrizdos), &lectura, NULL);

    int Resultado[N][N];

    // Multiplicar las matrices y guardar el resultado
    MultiplicarMatrices(Matrizuno, Matrizdos, Resultado);

    // Escribir el resultado de la multiplicación de matrices en la tubería para el proceso padre
    WriteFile(hEscrituraPipe, Resultado, sizeof(Resultado), &escritura, NULL);

    // Obtener la información de inicio del proceso hijo
    GetStartupInfo(&siHijo);
    
    // Escribir las matrices en las tuberías para el proceso nieto
    WriteFile(hEscrituraPipe_nieto_I, Matrizuno, sizeof(Matrizuno), &escritura, NULL);
    WriteFile(hEscrituraPipe_nieto_I, Matrizdos, sizeof(Matrizdos), &escritura, NULL);

    // Configuración de los manejadores estándar del proceso nieto
    siHijo.hStdInput = hLecturaPipe_nieto_I;
    siHijo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    siHijo.hStdOutput = hEscrituraPipe_nieto_O;
    siHijo.dwFlags = STARTF_USESTDHANDLES;

    // Creación del proceso nieto, heredando los manejadores de la tubería del hijo
    CreateProcess(
        NULL, "tuberias_2_2", NULL, NULL, TRUE, 0, NULL, NULL, &siHijo, &piHijo
    );

    // Esperar a que el proceso nieto termine
    WaitForSingleObject(piHijo.hProcess, INFINITE);

    // Leer el resultado de la operación realizada por el proceso nieto
    ReadFile(hLecturaPipe_nieto_O, Resultado, sizeof(Resultado), &lectura, NULL);

    // Escribir el resultado de vuelta al proceso padre
    WriteFile(hEscrituraPipe, Resultado, sizeof(Resultado), &escritura, NULL);

    // Cerrar los manejadores de las tuberías y del proceso nieto
    CloseHandle(hLecturaPipe); 
    CloseHandle(hEscrituraPipe);
    CloseHandle(hLecturaPipe_nieto_I);
    CloseHandle(hLecturaPipe_nieto_O);
    CloseHandle(hEscrituraPipe_nieto_I);
    CloseHandle(hEscrituraPipe_nieto_O);
    
    return 0;
}