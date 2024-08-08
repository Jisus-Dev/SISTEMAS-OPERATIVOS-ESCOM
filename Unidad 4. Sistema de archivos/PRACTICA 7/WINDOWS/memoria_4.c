#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Definiciones de constantes para el tamaño de la matriz
 * 
 * N: Tamaño de la matriz.
 * TAM_MEM: Tamaño de la memoria compartida.
 */
#define N 10
#define TAM_MEM (N * N * sizeof(int))

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
            TAM_MEM
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

    // *********** Seccion : Realizar la multiplicacion de matrices en el hijo *********

    int Resultado[N][N];
    MultiplicarMatrices(Matrizuno, Matrizdos,Resultado);

    // *********** Seccion : Creacion de la memoria compartida para la matriz de resultado de la multiplicacion *********

    int* apDatosResmulti;

    HANDLE hMemComResmulti = CrearMemoriaCompartida("Memoria_Compartida_Res_Multi", &apDatosResmulti);
    
    EscribirMemoriaCompartida(Resultado, apDatosResmulti);

    // Esperar hasta que el padre haya leído el resultado de la multiplicacion
    while (apDatosResmulti[0] != -1) {
        Sleep(1);
    }

    // Desmapear la vista del archivo de la memoria del proceso para matriz de resultado de la multiplicacion
    UnmapViewOfFile(apDatosResmulti);
    // Cerrar el manejador de la memoria compartida para matriz de resultado de la multiplicacion
    CloseHandle(hMemComResmulti);

    // *********** Seccion : Creacion de la memoria compartida para la matriz uno y la matriz dos (se envían al nieto) *********

    int* apDatosUno;
    int* apDatosDos;

    HANDLE hMemComUno = CrearMemoriaCompartida("Memoria_Compartida_MU_HN", &apDatosUno);
    HANDLE hMemComDos = CrearMemoriaCompartida("Memoria_Compartida_MD_HN", &apDatosDos);
    
    EscribirMemoriaCompartida(Matrizuno, apDatosUno);
    EscribirMemoriaCompartida(Matrizdos, apDatosDos);

    // *********** Seccion : Creación del proceso nieto *********

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(NULL,"memoria_5", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("Fallo al invocar CreateProcess (%d)\n", GetLastError());
        return 1;
    }

    // Esperar hasta que el nieto haya leído las matrices
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

    // Esperar a que el proceso hijo termine
    WaitForSingleObject(pi.hProcess, INFINITE);
    
    // Terminación controlada del proceso e hilo asociado de ejecución 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}