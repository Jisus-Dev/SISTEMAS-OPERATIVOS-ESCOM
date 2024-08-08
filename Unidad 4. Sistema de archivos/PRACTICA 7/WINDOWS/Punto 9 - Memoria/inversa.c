#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Definiciones de constantes para el tamaño de la matriz
 * 
 * N: Tamaño de la matriz.
 * TAM_MEM_INT: Tamaño de la memoria compartida para enteros.
 * TAM_MEM_DOUBLE: Tamaño de la memoria compartida para doubles.
 */
#define N 10
#define TAM_MEM_INT (N * N * sizeof(int))
#define TAM_MEM_DOUBLE (N * N * sizeof(double))

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

// Función para crear memoria compartida para enteros
HANDLE CrearMemoriaCompartida(const char* nombre, int** punteroDatos)
{
    HANDLE hMemoria;
    if ((hMemoria = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            TAM_MEM_INT,
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
            TAM_MEM_INT
        )) == NULL) {
        printf("No se enlazó la memoria compartida: (%i)\n", GetLastError());
        CloseHandle(hMemoria);
        exit(-1);
    }

    return hMemoria;
}

/**
 * Crea memoria compartida con un nombre específico.
 *
 * @param nombre El nombre de la memoria compartida.
 * @param punteroDatos Un puntero a un puntero de enteros donde se almacenará la dirección de la memoria compartida.
 * @return El manejador de la memoria compartida.
 */
HANDLE CrearMemoriaCompartidaD(const char* nombre, double** punteroDatos)
{
    HANDLE hMemoria;
    if ((hMemoria = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            TAM_MEM_DOUBLE,
            nombre
        )) == NULL) {
        printf("No se creó la memoria compartida: (%i)\n", GetLastError());
        exit(-1);
    }

    if ((*punteroDatos = (double*)MapViewOfFile(
            hMemoria,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            TAM_MEM_DOUBLE
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
 * Escribe los datos de una matriz double en la memoria compartida.
 * 
 * @param matriz La matriz a escribir.
 * @param punteroDatos El puntero a la memoria compartida donde se escribirá la matriz.
 */
void EscribirMemoriaCompartidaD(double matriz[N][N], double* punteroDatos)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            *punteroDatos++ = matriz[i][j];
        }
    }
}

/**
 * Verifica si hay un error al acceder a la memoria compartida.
 * 
 * @param nombre El nombre de la memoria compartida.
 * @param hMemCom El manejador de la memoria compartida.
 */
void ErrorMemoriaCompartida(const char* nombre, HANDLE* hMemCom)
{
    if ((*hMemCom = OpenFileMapping(
            FILE_MAP_ALL_ACCESS, // Acceso lectura/escritura de la memoria compartida
            FALSE,               // No se hereda el nombre
            nombre      // Identificador de la memoria compartida
        )) == NULL) {
        printf("No se accedió a la memoria compartida para %s: (%i)\n", nombre, GetLastError());
        exit(-1);
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
            TAM_MEM_INT
        )) == NULL) {
        printf("No se enlazó la memoria compartida: (%i)\n", GetLastError());
        CloseHandle(hMemCom);
        exit(-1);
    }
    return apDatos;
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
            matriz[i][j] = *punteroDatos++;
        }
    }
}

int main(void)
{
    int Matrizuno[N][N];
    int Matrizdos[N][N];

    // *********** Seccion : Lectura de la matriz uno del proceso padre *********

    HANDLE hMemComMatrizUno;
    int* apDatosMatrizUno;

    ErrorMemoriaCompartida("Memoria_Compartida_MU_PH", &hMemComMatrizUno);
    apDatosMatrizUno = MapearMemoriaCompartida("Memoria_Compartida_MU_PH", hMemComMatrizUno);
    LeerMemoriaCompartida(Matrizuno, apDatosMatrizUno);
    apDatosMatrizUno[0] = -1;

    // Desmapear la vista del archivo de la memoria del proceso para matriz uno
    UnmapViewOfFile(apDatosMatrizUno);
    // Cerrar el manejador de la memoria compartida para matriz uno
    CloseHandle(hMemComMatrizUno);

    // *********** Seccion : Lectura de la matriz dos del proceso padre *********

    HANDLE hMemComMatrizDos;
    int* apDatosMatrizDos;

    ErrorMemoriaCompartida("Memoria_Compartida_MD_PH", &hMemComMatrizDos);
    apDatosMatrizDos = MapearMemoriaCompartida("Memoria_Compartida_MD_PH", hMemComMatrizDos);
    LeerMemoriaCompartida(Matrizdos, apDatosMatrizDos);
    apDatosMatrizDos[0] = -1;

        
    // Desmapear la vista del archivo de la memoria del proceso para matriz dos
    UnmapViewOfFile(apDatosMatrizDos);
    // Cerrar el manejador de la memoria compartida para matriz dos
    CloseHandle(hMemComMatrizDos);

    // *********** Seccion : Realizar la inversa uno *********

    double Inversa_uno[N][N];
    InversaMatriz(Matrizuno,Inversa_uno);

    // *********** Seccion : Creacion de la memoria compartida para la matriz de resultado de la inversa uno *********

    double* apDatosResinvu; // Cambio de tipo de puntero

    HANDLE hMemComResinvu = CrearMemoriaCompartidaD("Memoria_Compartida_Res_InvU", &apDatosResinvu);
    
    EscribirMemoriaCompartidaD(Inversa_uno, apDatosResinvu);

    // Esperar hasta que recoleccion haya leído el resultado de la inversa uno
    while (apDatosResinvu[0] != -1) {
        Sleep(1);
    }

    // Desmapear la vista del archivo de la memoria del proceso para el resultado de la matriz de inversa uno
    UnmapViewOfFile(apDatosResinvu);
    // Cerrar el manejador de la memoria compartida para el resultado de la matriz de inversa uno
    CloseHandle(hMemComResinvu);

    // *********** Seccion : Realizar la inversa dos *********

    double Inversa_dos[N][N];
    InversaMatriz(Matrizdos,Inversa_dos);

    // *********** Seccion : Creacion de la memoria compartida para la matriz de resultado de la inversa dos *********

    double* apDatosResinvd; // Cambio de tipo de puntero

    HANDLE hMemComResinvd = CrearMemoriaCompartidaD("Memoria_Compartida_Res_InvD", &apDatosResinvd);
    
    EscribirMemoriaCompartidaD(Inversa_dos, apDatosResinvd);
    
    // Esperar hasta que recoleccion haya leído el resultado de la inversa dos
    while (apDatosResinvd[0] != -1) {
        Sleep(1);
    }

    // Desmapear la vista del archivo de la memoria del proceso para el resultado de la matriz de inversa dos
    UnmapViewOfFile(apDatosResinvd);
    // Cerrar el manejador de la memoria compartida para el resultado de la matriz de inversa dos
    CloseHandle(hMemComResinvd);

    return 0;
}