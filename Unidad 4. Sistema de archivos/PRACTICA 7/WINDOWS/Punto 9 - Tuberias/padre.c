#include <windows.h>
#include <stdio.h>
#include <time.h>

/**
 * Definiciones de constantes para el tamaño de la matriz
 * 
 * N: Tamaño de la matriz.
 * OPERACIONES: Número de operaciones a realizar.
 */
#define N 10
#define OPERACIONES 5

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
 * Imprime una matriz de doubles (decimales).
 * 
 * @param matriz La matriz a imprimir.
 */
void ImprimirInversa(double matriz[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%lf  ", matriz[i][j]); // Imprime cada elemento de la matriz con formato double
        printf("\n"); // Nueva línea al final de cada fila
    }
}

int main(int argc, char *argv[])
{
    int i, j;

    srand(time(NULL));

    // Declaración de las matrices
    int Matrizuno[N][N];
    int Matrizdos[N][N];

    // Se llenan las matrices con valores aleatorios
    LlenarMatriz(Matrizuno);
    LlenarMatriz(Matrizdos);

    // Mostrar los valores de las matrices
    printf("\nMatriz uno: \n");
    ImprimirMatriz(Matrizuno);
    printf("\nMatriz dos: \n");
    ImprimirMatriz(Matrizdos);

    // Para escritura
    HANDLE hLecturaPipe_hijo_I, hEscrituraPipe_hijo_I;
    SECURITY_ATTRIBUTES pipeSeg = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    DWORD escritos;

    // Para el proceso hijo
    STARTUPINFO siHijo;
    PROCESS_INFORMATION piHijo;
    GetStartupInfo(&siHijo);

    // Para lectura
    HANDLE hLecturaPipe_hijo_O, hEscrituraPipe_hijo_O;
    DWORD lectura;

    // Configuración de los manejadores estándar del proceso hijo
    siHijo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    siHijo.dwFlags = STARTF_USESTDHANDLES;

    // Array para almacenar los resultados de las operaciones
    int Resultados[OPERACIONES][N][N];
    double ResultadosInversos[2][N][N]; // Dos matrices inversas
    int indiceResultado = 0;

    for (j = 1; j <= 6; j++)
    {
        // Crear un proceso
        int Resultado1[N][N], Resultado2[N][N];
        double Inversa1[N][N], Inversa2[N][N];

        // Creación de las tuberías
        // Envío
        CreatePipe(&hLecturaPipe_hijo_I, &hEscrituraPipe_hijo_I, &pipeSeg, 0);
        // Recepción
        CreatePipe(&hLecturaPipe_hijo_O, &hEscrituraPipe_hijo_O, &pipeSeg, 0);

        // Configuración de los manejadores estándar del proceso hijo
        siHijo.hStdInput = hLecturaPipe_hijo_I;
        siHijo.hStdOutput = hEscrituraPipe_hijo_O;

        switch (j)
        {
            case 1:
                // Crear un proceso llamado suma
                CreateProcess(NULL, "suma.exe", NULL, NULL, TRUE, 0, NULL, NULL, &siHijo, &piHijo);
                // Escribir las matrices en el proceso hijo
                WriteFile(hEscrituraPipe_hijo_I, Matrizuno, sizeof(Matrizuno), &escritos, NULL);
                WriteFile(hEscrituraPipe_hijo_I, Matrizdos, sizeof(Matrizdos), &escritos, NULL);

                // Leer el resultado del proceso hijo
                ReadFile(hLecturaPipe_hijo_O, Resultado1, sizeof(Resultado1), &lectura, NULL);

                // Almacenar el resultado en el array
                memcpy(Resultados[indiceResultado++], Resultado1, sizeof(Resultado1));
                break;

            case 2:
                // Crear un proceso llamado resta
                CreateProcess(NULL, "resta.exe", NULL, NULL, TRUE, 0, NULL, NULL, &siHijo, &piHijo);
                // Escribir las matrices en el proceso hijo
                WriteFile(hEscrituraPipe_hijo_I, Matrizuno, sizeof(Matrizuno), &escritos, NULL);
                WriteFile(hEscrituraPipe_hijo_I, Matrizdos, sizeof(Matrizdos), &escritos, NULL);

                // Leer el resultado del proceso hijo
                ReadFile(hLecturaPipe_hijo_O, Resultado1, sizeof(Resultado1), &lectura, NULL);

                // Almacenar el resultado en el array
                memcpy(Resultados[indiceResultado++], Resultado1, sizeof(Resultado1));
                break;

            case 3:
                // Crear un proceso llamado multiplicacion
                CreateProcess(NULL, "multiplicacion.exe", NULL, NULL, TRUE, 0, NULL, NULL, &siHijo, &piHijo);
                // Escribir las matrices en el proceso hijo
                WriteFile(hEscrituraPipe_hijo_I, Matrizuno, sizeof(Matrizuno), &escritos, NULL);
                WriteFile(hEscrituraPipe_hijo_I, Matrizdos, sizeof(Matrizdos), &escritos, NULL);

                // Leer el resultado del proceso hijo
                ReadFile(hLecturaPipe_hijo_O, Resultado1, sizeof(Resultado1), &lectura, NULL);

                // Almacenar el resultado en el array
                memcpy(Resultados[indiceResultado++], Resultado1, sizeof(Resultado1));
                break;

            case 4:
                // Crear un proceso llamado traspuesta
                CreateProcess(NULL, "traspuesta.exe", NULL, NULL, TRUE, 0, NULL, NULL, &siHijo, &piHijo);
                // Escribir las matrices en el proceso hijo
                WriteFile(hEscrituraPipe_hijo_I, Matrizuno, sizeof(Matrizuno), &escritos, NULL);
                WriteFile(hEscrituraPipe_hijo_I, Matrizdos, sizeof(Matrizdos), &escritos, NULL);

                // Leer el resultado del proceso hijo
                ReadFile(hLecturaPipe_hijo_O, Resultado1, sizeof(Resultado1), &lectura, NULL);
                ReadFile(hLecturaPipe_hijo_O, Resultado2, sizeof(Resultado2), &lectura, NULL);

                // Almacenar el resultado en el array
                memcpy(Resultados[indiceResultado++], Resultado1, sizeof(Resultado1));
                memcpy(Resultados[indiceResultado++], Resultado2, sizeof(Resultado2));
                break;

            case 5:
                // Crear un proceso llamado inversa
                CreateProcess(NULL, "inversa.exe", NULL, NULL, TRUE, 0, NULL, NULL, &siHijo, &piHijo);
                // Escribir las matrices en el proceso hijo
                WriteFile(hEscrituraPipe_hijo_I, Matrizuno, sizeof(Matrizuno), &escritos, NULL);
                WriteFile(hEscrituraPipe_hijo_I, Matrizdos, sizeof(Matrizdos), &escritos, NULL);

                // Leer el resultado del proceso hijo
                ReadFile(hLecturaPipe_hijo_O, Inversa1, sizeof(Inversa1), &lectura, NULL);
                ReadFile(hLecturaPipe_hijo_O, Inversa2, sizeof(Inversa2), &lectura, NULL);

                // Almacenar el resultado en el array
                memcpy(ResultadosInversos[0], Inversa1, sizeof(Inversa1));
                memcpy(ResultadosInversos[1], Inversa2, sizeof(Inversa2));
                break;

            case 6:
                // Crear un proceso llamado recoleccion

                siHijo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

                CreateProcess(NULL, "recoleccion.exe", NULL, NULL, TRUE, 0, NULL, NULL, &siHijo, &piHijo);

                // Escribir los resultados de las operaciones en el proceso hijo
                for(i = 0; i < indiceResultado; i++)
                {
                    WriteFile(hEscrituraPipe_hijo_I, Resultados[i], sizeof(Resultados[i]), &escritos, NULL);
                }
                // Escribir los resultados inversos en el proceso hijo
                WriteFile(hEscrituraPipe_hijo_I, ResultadosInversos[0], sizeof(ResultadosInversos[0]), &escritos, NULL);
                WriteFile(hEscrituraPipe_hijo_I, ResultadosInversos[1], sizeof(ResultadosInversos[1]), &escritos, NULL);

                // Esperar a que el proceso hijo termine
                WaitForSingleObject(piHijo.hProcess, INFINITE);
                break;
        }
    }

    // Cerrar manejadores
    CloseHandle(piHijo.hProcess);
    CloseHandle(piHijo.hThread);
    CloseHandle(hLecturaPipe_hijo_I);
    CloseHandle(hEscrituraPipe_hijo_I);
    CloseHandle(hLecturaPipe_hijo_O);
    CloseHandle(hEscrituraPipe_hijo_O);

    return 0;
}