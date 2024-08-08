#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
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
            if (fila != p && col != q) // Verifica si no es la fila o columna a eliminar.
            {
                temp[i][j++] = matriz[fila][col]; // Copia el elemento a la matriz temporal.
                if (j == n - 1) 
                {
                    j = 0; // Reinicia la columna.
                    i++; // Avanza a la siguiente fila.
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

    if (n == 1) // Caso base para matrices de 1x1.
        return matriz[0][0];
    
    int temp[N][N];
    int signo = 1; // Alterna el signo en la expansión.
    for (int f = 0; f < n; f++)
    {
        Cofactor(matriz, temp, 0, f, n); // Calcula el cofactor.
        determinante += signo * matriz[0][f] * DeterminanteMatriz(temp, n - 1); // Suma el producto.
        signo = -signo; // Alterna el signo.
    }
    return determinante; // Retorna el determinante calculado.
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
        adjunta[0][0] = 1; // La adjunta de una matriz 1x1 es 1.
        return;
    }

    int temp[N][N];
    int signo = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Cofactor(matriz, temp, i, j, n); // Calcula el cofactor.
            signo = ((i + j) % 2 == 0) ? 1 : -1; // Determina el signo.
            adjunta[j][i] = (signo) * (DeterminanteMatriz(temp, n - 1)); // Calcula la adjunta.
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
    double determinante = (double)DeterminanteMatriz(matriz, N); // Calcula el determinante.

    if (determinante == 0) // Verifica si la matriz es singular.
    {
        printf("La matriz es singular, no se puede calcular la inversa.\n");
        return;
    }

    double adjunta[N][N];
    AdjuntaMatriz(matriz, adjunta, N); // Calcula la matriz adjunta.

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inversa[i][j] = adjunta[i][j] / determinante; // Calcula la inversa dividiendo la adjunta por el determinante.
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

/**
 * Espera hasta que se cree la memoria compartida con un nombre específico.
 *
 * @param nombre El nombre de la memoria compartida.
 * @param hMemCom Un puntero al manejador de la memoria compartida.
 */
void EsperarMemoriaCompartida(const char* nombre, HANDLE* hMemCom)
{
    while ((*hMemCom = OpenFileMapping(
            FILE_MAP_ALL_ACCESS, 
            FALSE,               
            nombre
        )) == NULL) {
        Sleep(100); // Esperar 100 milisegundos antes de volver a verificar
    }
}

/**
 * Lee los datos de una matriz desde la memoria compartida.
 *
 * @param matriz La matriz donde se almacenarán los datos leídos.
 * @param punteroDatos El puntero a la memoria compartida desde donde se leerá la matriz.
 */
void LeerMemoriaCompartida(int matriz[N][N], int* punteroDatos)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = *punteroDatos++; // Lee cada elemento de la memoria compartida y lo almacena en la matriz.
        }
    }
}

/**
 * Mapea la memoria compartida a la memoria del proceso.
 *
 * @param nombre El nombre de la memoria compartida.
 * @param hMemCom El manejador de la memoria compartida.
 * @return Un puntero a la memoria mapeada.
 */
int* MapearMemoriaCompartida(const char* nombre, HANDLE hMemCom)
{
    int* apDatos;
    if ((apDatos = (int *)MapViewOfFile(
            hMemCom,             // Manejador del mapeo
            FILE_MAP_ALL_ACCESS, // Permiso de lectura/escritura en la memoria
            0,
            0,
            TAM_MEM
        )) == NULL) {
        printf("No se enlazó la memoria compartida: (%i)\n", GetLastError());
        CloseHandle(hMemCom);
        exit(-1);
    }
    return apDatos;
}

int main(int argc, char* argv[])
{
    // *********** Seccion : Llenar Matrices Aleatorias ***********
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
    
    // *********** Seccion : Creacion de la memoria compartida para la matriz uno y la matriz dos (se envían al hijo) ***********
    int* apDatosUno;
    int* apDatosDos;

    HANDLE hMemComUno = CrearMemoriaCompartida("Memoria_Compartida_MU_PH", &apDatosUno);
    HANDLE hMemComDos = CrearMemoriaCompartida("Memoria_Compartida_MD_PH", &apDatosDos);
    
    EscribirMemoriaCompartida(Matrizuno, apDatosUno);
    EscribirMemoriaCompartida(Matrizdos, apDatosDos);

    // *********** Seccion : Creacion de Proceso hijo ***********
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(NULL, argv[1], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("Fallo al invocar CreateProcess (%d)\n", GetLastError());
        return 1;
    }

    // Esperar hasta que el hijo haya leído las matrices
    while (apDatosUno[0] != -1 && apDatosDos[0] != -1)
    {
        Sleep(1);
    }

    // Desmapear la vista del archivo de la memoria del proceso para matriz uno y matriz dos
    UnmapViewOfFile(apDatosUno);
    UnmapViewOfFile(apDatosDos);

    // Cerrar el manejador de la memoria compartida para matriz uno y matriz dos
    CloseHandle(hMemComUno);
    CloseHandle(hMemComDos);

    // *********** Seccion : Lectura del Resultado de Multiplicacion ***********
    HANDLE hMemComResmulti;
    int* apDatosResmulti;
    
    // Abre el mapeo de archivo de la memoria compartida para la matriz de resultado de multiplicacion
    EsperarMemoriaCompartida("Memoria_Compartida_Res_Multi", &hMemComResmulti);
    
    // Mapea la vista del archivo a la memoria del proceso para matriz de resultado de multiplicación
    apDatosResmulti = MapearMemoriaCompartida("Memoria_Compartida_Res_Multi", hMemComResmulti);

    // Leer la matriz de resultado de multiplicación de la memoria compartida
    int Resultado_multi[N][N];

    LeerMemoriaCompartida(Resultado_multi, apDatosResmulti);

    // Marcar que la matriz resultado de la multiplicación fue leída
    apDatosResmulti[0] = -1;
    
    // Desmapear la vista del archivo de la memoria del proceso para matriz del resultado de multiplicación
    UnmapViewOfFile(apDatosResmulti);
    
    // Cerrar el manejador de la memoria compartida para matriz del resultado de multiplicación
    CloseHandle(hMemComResmulti);

    // *********** Seccion : Lectura del Resultado de Suma ***********
    HANDLE hMemComResum;
    int* apDatosResum;

    // Abre el mapeo de archivo de la memoria compartida para la matriz de resultado de suma
    EsperarMemoriaCompartida("Memoria_Compartida_Res_Sum", &hMemComResum);

    // Mapea la vista del archivo a la memoria del proceso para matriz de resultado de suma
    apDatosResum = MapearMemoriaCompartida("Memoria_Compartida_Res_Sum", hMemComResum);

    // Leer la matriz de resultado de suma de la memoria compartida
    int Resultado_sum[N][N];

    LeerMemoriaCompartida(Resultado_sum, apDatosResum);

    // Marcar que la matriz resultado de la suma fue leída
    apDatosResum[0] = -1;

    // Desmapear la vista del archivo de la memoria del proceso para matriz del resultado de suma
    UnmapViewOfFile(apDatosResum);

    // Cerrar el manejador de la memoria compartida para matriz del resultado de suma
    CloseHandle(hMemComResum);

    // *** Seccion : Realizar la inversa de las matrices del resultado de la suma y la multiplicacion en el padre ***
    double Inversa[N][N];

    printf("\n\nInversa de la multiplicacion:\n");    
    InversaMatriz(Resultado_multi,Inversa);
    ImprimirInversa(Inversa);

    printf("\n\nInversa de la suma:\n");
    InversaMatriz(Resultado_sum,Inversa);
    ImprimirInversa(Inversa);

    // Esperar a que el proceso hijo termine
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Terminación controlada del proceso e hilo asociado de ejecución 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}