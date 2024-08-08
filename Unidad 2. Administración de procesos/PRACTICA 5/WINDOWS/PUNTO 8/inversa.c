#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * Definiciones de constantes para el tamaño de la matriz
 * 
 * N: Tamaño de la matriz.
 */
#define N 10

/**
 * Extrae los elementos de una cadena de caracteres y los asigna a una matriz.
 * 
 * @param matriz La matriz en la que se almacenarán los elementos extraídos.
 * @param str La cadena de caracteres de la que se extraerán los elementos.
 */
void ExtraerMatriz(int matriz[N][N], char str[])
{
    int fila = 0, columna = -1;
    int i = 0;
    int num = 0;
    char num_str[10] = {'\0'};

    while (str[i] != '\0')
    {
        if (str[i] == ' ')
        {
            // Convertir el número almacenado en num_str a entero y asignarlo a la matriz
            matriz[fila][columna++] = atoi(num_str);
            num = 0;
            memset(num_str, '\0', sizeof(num_str));
        }
        else if (str[i] >= '0' && str[i] <= '9')
        {
            // Almacenar el carácter numérico en num_str
            num_str[num++] = str[i];
        }
        else if (str[i] == '\n')
        {
            // Convertir y asignar el número cuando se encuentra un salto de línea
            matriz[fila][columna++] = atoi(num_str);
            fila++;
            columna = 0;
            num = 0;
            memset(num_str, '\0', sizeof(num_str));
        }
        i++;
    }
    // Asignar el último número de la cadena
    matriz[fila][columna] = atoi(num_str);
}

/**
 * Calcula el cofactor de una matriz cuadrada.
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
 * Guarda una matriz en un archivo dentro del directorio 'resultados'.
 * 
 * @param matriz La matriz que se guardará en el archivo.
 * @param n Identificador de la matriz (1 o 2) para determinar el nombre del archivo.
 */
void Archivo(double matriz[N][N], int n)
{
    // Crear el directorio 'resultados' si no existe
    struct stat st = {0};
    if (stat("resultados", &st) == -1) 
    {
        mkdir("resultados", 0700); // Crea el directorio con permisos de lectura/escritura/ejecución para el usuario
    }

    // Crear la ruta completa para el archivo
    char ruta_archivo[256];
    if(n == 1)
    {
        snprintf(ruta_archivo, sizeof(ruta_archivo), "resultados/Inversa1.txt");
    }
    else if (n == 2)
    {
        snprintf(ruta_archivo, sizeof(ruta_archivo), "resultados/Inversa2.txt");
    }

    // Abrir el archivo para escribir
    FILE *archivo = fopen(ruta_archivo, "w");
    if (archivo == NULL) 
    {
        printf("Error al abrir el archivo %s\n", ruta_archivo);
        exit(1); // Terminar el programa si hay un error al abrir el archivo
    }

    // Escribir el resultado de la operación en el archivo
    if(n == 1)
    {
        fprintf(archivo, "\n--- Operacion ---: Inversa de la Matriz 1\n");
    }
    else if (n == 2)
    {
        fprintf(archivo, "\n--- Operacion ---: Inversa de la Matriz 2\n");
    }

    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            fprintf(archivo, "%lf ", matriz[i][j]);
        }
        fprintf(archivo, "\n");
    }
    fclose(archivo); // Cerrar el archivo
}

int main(int argc, char *argv[])
{
    // Imprimir el PID del proceso hijo
    printf("\nSoy el proceso hijo 5 con PID: %d \n", GetCurrentProcessId());
    printf("\tRealizo la inversa de matrices\n");

    int MatrizUno[N][N];
    int MatrizDos[N][N];
    double InversaUno[N][N];
    double InversaDos[N][N];

    // Extraer matrices de las cadenas pasadas como argumentos
    ExtraerMatriz(MatrizUno, argv[1]);
    ExtraerMatriz(MatrizDos, argv[2]);

    // Calcular la inversa de las matrices
    InversaMatriz(MatrizUno, InversaUno);
    InversaMatriz(MatrizDos, InversaDos);

    // Guardar las matrices inversas en archivos
    Archivo(InversaUno, 1);
    Archivo(InversaDos, 2);

    return 0;
}