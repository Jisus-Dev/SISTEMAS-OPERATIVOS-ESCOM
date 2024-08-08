#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

/**
 * Definiciones de constantes para el tamaño de la matriz
 * 
 * N: Tamaño de la matriz.
 */
#define N 10

/**
 * Llena una matriz con valores aleatorios entre 0 y 100.
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
            matriz[i][j] = rand() % 101; // Genera un número aleatorio entre 0 y 100.
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
            printf("%d\t", matriz[i][j]); // Imprime cada elemento seguido de una tabulación.
        printf("\n"); // Nueva línea al final de cada fila.
    }
}

/**
 * Suma dos matrices cuadradas y guarda el resultado en una tercera matriz.
 * 
 * @param matrizuno La primera matriz de entrada.
 * @param matrizdos La segunda matriz de entrada.
 * @param resultado La matriz de salida donde se guarda el resultado de la suma.
 */
void SumarMatrices(int matrizuno[N][N], int matrizdos[N][N], int resultado[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            resultado[i][j] = matrizuno[i][j] + matrizdos[i][j]; // Suma elemento a elemento.
        }
    }
}

/**
 * Resta dos matrices y guarda el resultado en una tercera matriz.
 * 
 * @param matrizuno La primera matriz de entrada.
 * @param matrizdos La segunda matriz de entrada.
 * @param resultado La matriz de salida donde se guarda el resultado de la resta.
 */
void RestarMatrices(int matrizuno[N][N], int matrizdos[N][N], int resultado[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            resultado[i][j] = matrizuno[i][j] - matrizdos[i][j]; // Resta elemento a elemento.
        }
    }
}

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

/**
 * Transpone una matriz cuadrada.
 * 
 * Esta función toma una matriz cuadrada y calcula su matriz traspuesta.
 * La matriz traspuesta se obtiene intercambiando las filas por las columnas.
 * 
 * @param matriz La matriz original.
 * @param resultado La matriz traspuesta resultante.
 */
void TransponerMatriz(int matriz[N][N], int resultado[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            resultado[j][i] = matriz[i][j]; // Intercambia filas y columnas.
        }
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
 * Guarda una matriz en un archivo dentro del directorio 'resultados2'.
 * 
 * @param matriz Puntero a la matriz que se desea guardar.
 * @param nombre_archivo Nombre del archivo donde se guardará la matriz, sin la ruta.
 * @param operacion Descripción de la operación realizada que se incluirá en el archivo.
 * @param tipo Tipo de matriz ('i' para enteros, 'd' para dobles).
 * 
 * Esta función crea el directorio 'resultados2' si no existe, construye la ruta
 * completa para el archivo y escribe los elementos de la matriz en el archivo
 * junto con la descripción de la operación.
 */
void Archivo(void *matriz, char *nombre_archivo, char *operacion, char tipo) 
{
    // Crear el directorio 'resultados2' si no existe
    struct stat st = {0};
    if (stat("resultados2", &st) == -1)
    {
        mkdir("resultados2", 0700); // Crear el directorio con permisos 0700
    }

    // Crear la ruta completa para el archivo
    char ruta_archivo[256];
    snprintf(ruta_archivo, sizeof(ruta_archivo), "resultados2/%s", nombre_archivo);

    FILE *archivo = fopen(ruta_archivo, "w");
    if (archivo == NULL) 
    {
        printf("Error al abrir el archivo %s\n", ruta_archivo);
        exit(1);
    }

    fprintf(archivo, "\n--- Operacion---: %s\n", operacion); // Escribe la descripción de la operación.

    if (tipo == 'i') 
    {
        int (*matriz_int)[N] = (int (*)[N]) matriz; // Convierte el puntero a matriz de enteros.
        for (int i = 0; i < N; i++) 
        {
            for (int j = 0; j < N; j++) 
            {
                fprintf(archivo, "%d ", matriz_int[i][j]); // Escribe cada elemento.
            }
            fprintf(archivo, "\n"); // Nueva línea al final de cada fila.
        }
    } 
    else if (tipo == 'd') 
    {
        double (*matriz_double)[N] = (double (*)[N]) matriz; // Convierte el puntero a matriz de doubles.
        for (int i = 0; i < N; i++) 
        {
            for (int j = 0; j < N; j++) 
            {
                fprintf(archivo, "%lf ", matriz_double[i][j]); // Escribe cada elemento.
            }
            fprintf(archivo, "\n"); // Nueva línea al final de cada fila.
        }
    }
    
    fclose(archivo); // Cierra el archivo.
}

int main()
{
    srand(time(NULL)); // Inicializa la semilla para la generación de números aleatorios.

    int Matrizuno[N][N]; // Declaración de la primera matriz.
    int Matrizdos[N][N]; // Declaración de la segunda matriz.

    LlenarMatriz(Matrizuno); // Llena la primera matriz con valores aleatorios.
    LlenarMatriz(Matrizdos); // Llena la segunda matriz con valores aleatorios.

    int Resultado[N][N]; // Matriz para almacenar resultados de operaciones.

    printf("Matriz 1:\n");
    ImprimirMatriz(Matrizuno); // Imprime la primera matriz.
    printf("\nMatriz 2:\n");
    ImprimirMatriz(Matrizdos); // Imprime la segunda matriz.

    printf("\nRealizo la suma de matrices\n");
    SumarMatrices(Matrizuno, Matrizdos, Resultado); // Realiza la suma de matrices.
    Archivo(Resultado, "Suma.txt", "Suma de matrices", 'i'); // Guarda el resultado en un archivo.

    printf("Realizo la resta de matrices\n");
    RestarMatrices(Matrizuno, Matrizdos, Resultado); // Realiza la resta de matrices.
    Archivo(Resultado, "Resta.txt", "Resta de matrices", 'i'); // Guarda el resultado en un archivo.

    printf("Realizo la multiplicacion de matrices\n");
    MultiplicarMatrices(Matrizuno, Matrizdos, Resultado); // Realiza la multiplicación de matrices.
    Archivo(Resultado, "Multiplicacion.txt", "Multiplicacion de matrices", 'i'); // Guarda el resultado en un archivo.

    printf("Realizo la traspuesta de matrices\n");
    int Traspuestauno[N][N]; // Matriz para almacenar la traspuesta de la primera matriz.
    int Traspuestados[N][N]; // Matriz para almacenar la traspuesta de la segunda matriz.
    TransponerMatriz(Matrizuno, Traspuestauno); // Transpone la primera matriz.
    TransponerMatriz(Matrizdos, Traspuestados); // Transpone la segunda matriz.
    Archivo(Traspuestauno, "Transpuesta1.txt", "Traspuesta de la Matriz 1", 'i'); // Guarda la traspuesta en un archivo.
    Archivo(Traspuestados, "Transpuesta2.txt", "Traspuesta de la Matriz 2", 'i'); // Guarda la traspuesta en un archivo.

    printf("Realizo la inversa de matrices\n");
    double Inversauno[N][N]; // Matriz para almacenar la inversa de la primera matriz.
    double Inversados[N][N]; // Matriz para almacenar la inversa de la segunda matriz.
    InversaMatriz(Matrizuno, Inversauno); // Calcula la inversa de la primera matriz.
    InversaMatriz(Matrizdos, Inversados); // Calcula la inversa de la segunda matriz.
    Archivo(Inversauno, "Inversa1.txt", "Inversa de la Matriz 1", 'd'); // Guarda la inversa en un archivo.
    Archivo(Inversados, "Inversa2.txt", "Inversa de la Matriz 2", 'd'); // Guarda la inversa en un archivo.

    // Muestra el contenido de los archivos generados
    execlp("cat", "cat", "resultados2/Suma.txt", "resultados2/Resta.txt", "resultados2/Multiplicacion.txt", "resultados2/Transpuesta1.txt", "resultados2/Transpuesta2.txt", "resultados2/Inversa1.txt", "resultados2/Inversa2.txt", NULL);
    
    return 0; // Finaliza el programa.
}