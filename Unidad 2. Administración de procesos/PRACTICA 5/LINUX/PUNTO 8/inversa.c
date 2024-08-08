#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#define N 10 // Tamaño de la matriz

/**
 * Extrae una matriz de una cadena de caracteres.
 * 
 * @param matriz La matriz a llenar.
 * @param str La cadena de caracteres que contiene los valores de la matriz.
 */
void ExtraerMatriz(int matriz[N][N], char *str)
{
    char *token = strtok(str, " "); // Divide la cadena en tokens usando espacio como delimitador.
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matriz[i][j] = atoi(token); // Convierte el token a entero y lo almacena en la matriz.
            token = strtok(NULL, " "); // Obtiene el siguiente token.
        }
    }
}

// ***** PROCESO PARA CALCULAR LA INVERSA DE UNA MATRIZ *****

/**
 * Calcula el cofactor de una matriz cuadrada.
 *
 * @param matriz La matriz original de tamaño N x N.
 * @param temp La matriz temporal donde se almacenará el cofactor.
 * @param p La fila a eliminar.
 * @param q La columna a eliminar.
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
 * Calcula el determinante de una matriz cuadrada utilizando un enfoque recursivo.
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
 * Escribe la inversa de una matriz en un archivo dentro del directorio 'resultados'.
 * 
 * @param matriz La matriz cuya inversa se escribirá en el archivo.
 * @param n Indica qué matriz se está procesando (1 o 2).
 */
void Archivo(double matriz[N][N], int n)
{
    // Crear el directorio 'resultados' si no existe.
    struct stat st = {0};
    if (stat("resultados", &st) == -1)
    {
        mkdir("resultados", 0700); // Crear el directorio con permisos 0700.
    }

    // Crear la ruta completa para el archivo basado en el número de matriz.
    char ruta_archivo[256];
    if(n == 1)
    {
        snprintf(ruta_archivo, sizeof(ruta_archivo), "resultados/Inversa1.txt");
    }
    else if (n == 2)
    {
        snprintf(ruta_archivo, sizeof(ruta_archivo), "resultados/Inversa2.txt");
    }

    FILE *archivo = fopen(ruta_archivo, "w"); // Abre el archivo para escritura.
    if (archivo == NULL) 
    {
        printf("Error al abrir el archivo inversa\n"); // Maneja el error si no se puede abrir el archivo.
        exit(1);
    }

    // Escribe el encabezado en el archivo.
    if(n == 1)
    {
        fprintf(archivo, "\n--- Operacion---: Inversa de la Matriz 1\n");
    }
    else if (n == 2)
    {
        fprintf(archivo, "\n--- Operacion---: Inversa de la Matriz 2\n");
    }

    // Escribe cada elemento de la matriz en el archivo.
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            fprintf(archivo, "%lf ", matriz[i][j]);
        }
        fprintf(archivo, "\n"); // Nueva línea al final de cada fila.
    }
    fclose(archivo); // Cierra el archivo.
}

/**
 * Función principal que realiza el cálculo de la inversa de matrices.
 * 
 * @param argc Número de argumentos.
 * @param argv Arreglo de argumentos.
 * @return Código de salida del programa.
 */
int main(int argc, char *argv[])
{
    printf("\tRealizo la inversa de matrices\n");

    int MatrizUno[N][N]; // Declaración de la primera matriz.
    int MatrizDos[N][N]; // Declaración de la segunda matriz.
    double InversaUno[N][N]; // Matriz para almacenar la inversa de la primera.
    double InversaDos[N][N]; // Matriz para almacenar la inversa de la segunda.

    // Extrae las matrices desde los argumentos pasados.
    ExtraerMatriz(MatrizUno, argv[1]);
    ExtraerMatriz(MatrizDos, argv[2]);

    // Calcula la inversa de ambas matrices.
    InversaMatriz(MatrizUno, InversaUno);
    InversaMatriz(MatrizDos, InversaDos);

    // Escribe las inversas en archivos.
    Archivo(InversaUno, 1);
    Archivo(InversaDos, 2);

    return 0; // Termina la ejecución del programa.
}