#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
            matriz[i][j] = *punteroDatos++;
        }
    }
}

/**
 * Lee los datos de una matriz de doubles desde la memoria compartida.
 * 
 * @param matriz La matriz donde se almacenarán los datos leídos.
 * @param punteroDatos El puntero a la memoria compartida desde donde se leerá la matriz.
 */
void LeerMemoriaCompartidaD(double matriz[N][N], double* punteroDatos)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = *punteroDatos++;
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
            TAM_MEM_INT
        )) == NULL) {
        printf("No se enlazó la memoria compartida: (%i)\n", GetLastError());
        CloseHandle(hMemCom);
        exit(-1);
    }
    return apDatos;
}

/**
 * Mapea la memoria compartida a la memoria del proceso para doubles.
 *
 * @param nombre El nombre de la memoria compartida.
 * @param hMemCom El manejador de la memoria compartida.
 * @return Un puntero a la memoria mapeada.
 */
double* MapearMemoriaCompartidaD(const char* nombre, HANDLE hMemCom)
{
    double* apDatos;
    if ((apDatos = (double *)MapViewOfFile(
            hMemCom,             // Manejador del mapeo
            FILE_MAP_ALL_ACCESS, // Permiso de lectura/escritura en la memoria
            0,
            0,
            TAM_MEM_DOUBLE
        )) == NULL) {
        printf("No se enlazó la memoria compartida: (%i)\n", GetLastError());
        CloseHandle(hMemCom);
        exit(-1);
    }
    return apDatos;
}

int main(int argc, char *argv[])
{
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

    printf("\nResultado suma: \n");
    ImprimirMatriz(Resultado_sum);

    // Marcar que la matriz resultado de la suma fue leída
    apDatosResum[0] = -1;

    // Desmapear la vista del archivo de la memoria del proceso para matriz del resultado de suma
    UnmapViewOfFile(apDatosResum);

    // Cerrar el manejador de la memoria compartida para matriz del resultado de suma
    CloseHandle(hMemComResum);


    // *********** Seccion : Lectura del Resultado de Resta ***********
    HANDLE hMemComResrest;
    int* apDatosResrest;

    // Abre el mapeo de archivo de la memoria compartida para la matriz de resultado de resta
    EsperarMemoriaCompartida("Memoria_Compartida_Res_Rest", &hMemComResrest);

    // Mapea la vista del archivo a la memoria del proceso para matriz de resultado de resta
    apDatosResrest = MapearMemoriaCompartida("Memoria_Compartida_Res_Rest", hMemComResrest);

    // Leer la matriz de resultado de resta de la memoria compartida
    int Resultado_rest[N][N];

    LeerMemoriaCompartida(Resultado_rest, apDatosResrest);
    printf("\nResultado resta: \n");
    ImprimirMatriz(Resultado_rest);

    // Marcar que la matriz resultado de la resta fue leída
    apDatosResrest[0] = -1;

    // Desmapear la vista del archivo de la memoria del proceso para matriz del resultado de resta
    UnmapViewOfFile(apDatosResrest);

    // Cerrar el manejador de la memoria compartida para matriz del resultado de resta
    CloseHandle(hMemComResrest);


    // *********** Seccion : Lectura del Resultado de Multiplicacion ***********
    HANDLE hMemComResmul;
    int* apDatosResmul;
    
    // Abre el mapeo de archivo de la memoria compartida para la matriz de resultado de multiplicacion
    EsperarMemoriaCompartida("Memoria_Compartida_Res_Mul", &hMemComResmul);
    
    // Mapea la vista del archivo a la memoria del proceso para matriz de resultado de multiplicacion
    apDatosResmul = MapearMemoriaCompartida("Memoria_Compartida_Res_Mul", hMemComResmul);

    // Leer la matriz de resultado de multiplicacion de la memoria compartida
    int Resultado_multi[N][N];

    LeerMemoriaCompartida(Resultado_multi, apDatosResmul);
    printf("\nResultado multiplicacion: \n");
    ImprimirMatriz(Resultado_multi);

    // Marcar que la matriz resultado de la multiplicacion fue leída
    apDatosResmul[0] = -1;
    
    // Desmapear la vista del archivo de la memoria del proceso para matriz del resultado de multiplicacion
    UnmapViewOfFile(apDatosResmul);
    
    // Cerrar el manejador de la memoria compartida para matriz del resultado de multiplicacion
    CloseHandle(hMemComResmul);
    

    // *********** Seccion : Lectura del Resultado de Traspuesta uno ***********
    HANDLE hMemComRestrasu;
    int* apDatosRestrasu;
    
    // Abre el mapeo de archivo de la memoria compartida para la matriz de resultado de traspuesta uno
    EsperarMemoriaCompartida("Memoria_Compartida_Res_TrasU", &hMemComRestrasu);
    
    // Mapea la vista del archivo a la memoria del proceso para matriz de resultado de traspuesta uno
    apDatosRestrasu = MapearMemoriaCompartida("Memoria_Compartida_Res_TrasU", hMemComRestrasu);

    // Leer la matriz de resultado de traspuesta uno de la memoria compartida
    int Resultado_traspuestau[N][N];

    LeerMemoriaCompartida(Resultado_traspuestau, apDatosRestrasu);
    printf("\nResultado traspuesta uno: \n");
    ImprimirMatriz(Resultado_traspuestau);

    // Marcar que la matriz resultado de la traspuesta uno fue leída
    apDatosRestrasu[0] = -1;
    
    // Desmapear la vista del archivo de la memoria del proceso para matriz del resultado de traspuesta uno
    UnmapViewOfFile(apDatosRestrasu);
    
    // Cerrar el manejador de la memoria compartida para matriz del resultado de traspuesta uno
    CloseHandle(hMemComRestrasu);


    // *********** Seccion : Lectura del Resultado de Traspuesta dos ***********
    HANDLE hMemComRestrasd;
    int* apDatosRestrasd;
    
    // Abre el mapeo de archivo de la memoria compartida para la matriz de resultado de traspuesta dos
    EsperarMemoriaCompartida("Memoria_Compartida_Res_TrasD", &hMemComRestrasd);
    
    // Mapea la vista del archivo a la memoria del proceso para matriz de resultado de traspuesta dos
    apDatosRestrasd = MapearMemoriaCompartida("Memoria_Compartida_Res_TrasD", hMemComRestrasd);

    // Leer la matriz de resultado de traspuesta dos de la memoria compartida
    int Resultado_traspuestad[N][N];
    printf("\nResultado traspuesta dos: \n");
    LeerMemoriaCompartida(Resultado_traspuestad, apDatosRestrasd);

    ImprimirMatriz(Resultado_traspuestad);

    // Marcar que la matriz resultado de la traspuesta dos fue leída
    apDatosRestrasd[0] = -1;
    
    // Desmapear la vista del archivo de la memoria del proceso para matriz del resultado de traspuesta dos
    UnmapViewOfFile(apDatosRestrasd);
    
    // Cerrar el manejador de la memoria compartida para matriz del resultado de traspuesta dos
    CloseHandle(hMemComRestrasd);


    // *********** Seccion : Lectura del Resultado de Inversa uno ***********
    HANDLE hMemComResinvu;
    double* apDatosResinvu;
    
    // Abre el mapeo de archivo de la memoria compartida para la matriz de resultado de inversa uno
    EsperarMemoriaCompartida("Memoria_Compartida_Res_InvU", &hMemComResinvu);
    
    // Mapea la vista del archivo a la memoria del proceso para matriz de resultado de inversa uno
    apDatosResinvu = MapearMemoriaCompartidaD("Memoria_Compartida_Res_InvU", hMemComResinvu);

    // Leer la matriz de resultado de inversa uno de la memoria compartida
    double Resultado_inversau[N][N];
    printf("\nResultado inversa uno: \n");
    LeerMemoriaCompartidaD(Resultado_inversau, apDatosResinvu);

    ImprimirInversa(Resultado_inversau);

    // Marcar que la matriz resultado de la inversa uno fue leída
    apDatosResinvu[0] = -1;
    
    // Desmapear la vista del archivo de la memoria del proceso para matriz del resultado de inversa uno
    UnmapViewOfFile(apDatosResinvu);
    
    // Cerrar el manejador de la memoria compartida para matriz del resultado de inversa uno
    CloseHandle(hMemComResinvu);


    // *********** Seccion : Lectura del Resultado de Inversa dos ***********
    HANDLE hMemComResinvd;
    double* apDatosResinvd;
    
    // Abre el mapeo de archivo de la memoria compartida para la matriz de resultado de inversa dos
    EsperarMemoriaCompartida("Memoria_Compartida_Res_InvD", &hMemComResinvd);
    
    // Mapea la vista del archivo a la memoria del proceso para matriz de resultado de inversa dos
    apDatosResinvd = MapearMemoriaCompartidaD("Memoria_Compartida_Res_InvD", hMemComResinvd);

    // Leer la matriz de resultado de inversa dos de la memoria compartida
    double Resultado_inversad[N][N];
    printf("\nResultado inversa dos: \n");
    LeerMemoriaCompartidaD(Resultado_inversad, apDatosResinvd);

    ImprimirInversa(Resultado_inversad);

    // Marcar que la matriz resultado de la inversa dos fue leída
    apDatosResinvd[0] = -1;
    
    // Desmapear la vista del archivo de la memoria del proceso para matriz del resultado de inversa dos
    UnmapViewOfFile(apDatosResinvd);
    
    // Cerrar el manejador de la memoria compartida para matriz del resultado de inversa dos
    CloseHandle(hMemComResinvd);

    return 0;
}