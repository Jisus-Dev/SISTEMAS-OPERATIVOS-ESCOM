#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/**
 * Definiciones de constantes para el tamaño de la matriz
 * 
 * N: Tamaño de la matriz.
 */
#define N 10

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
            resultado[j][i] = matriz[i][j]; // Intercambia filas por columnas.
        }
    }
}

/**
 * Escribe la traspuesta de una matriz en un archivo dentro del directorio 'resultados'.
 * 
 * @param matriz La matriz cuya traspuesta se escribirá en el archivo.
 * @param n Indica qué matriz se está procesando (1 o 2).
 */
void Archivo(int matriz[N][N], int n)
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
        snprintf(ruta_archivo, sizeof(ruta_archivo), "resultados/Traspuesta1.txt");
    }
    else if (n == 2)
    {
        snprintf(ruta_archivo, sizeof(ruta_archivo), "resultados/Traspuesta2.txt");
    }

    FILE *archivo = fopen(ruta_archivo, "w"); // Abre el archivo para escritura.
    if (archivo == NULL) 
    {
        printf("Error al abrir el archivo traspuesta\n"); // Maneja el error si no se puede abrir el archivo.
        exit(1);
    }

    // Escribe el encabezado en el archivo.
    if(n == 1)
    {
        fprintf(archivo, "\n--- Operacion---: Traspuesta de la Matriz 1\n");
    }
    else if (n == 2)
    {
        fprintf(archivo, "\n--- Operacion---: Traspuesta de la Matriz 2\n");
    }

    // Escribe cada elemento de la matriz en el archivo.
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            fprintf(archivo, "%d ", matriz[i][j]);
        }
        fprintf(archivo, "\n"); // Nueva línea al final de cada fila.
    }    
    fclose(archivo); // Cierra el archivo.
}

/**
 * Función principal que realiza la trasposición de matrices.
 * 
 * @param argc Número de argumentos.
 * @param argv Arreglo de argumentos.
 * @return Código de salida del programa.
 */
int main(int argc, char *argv[])
{
    printf("\tRealizo la traspuesta de matrices\n");

    int MatrizUno[N][N]; // Declaración de la primera matriz.
    int MatrizDos[N][N]; // Declaración de la segunda matriz.
    int Traspuestauno[N][N]; // Matriz para almacenar la traspuesta de la primera.
    int Traspuestados[N][N]; // Matriz para almacenar la traspuesta de la segunda.

    // Extrae las matrices desde los argumentos pasados.
    ExtraerMatriz(MatrizUno, argv[1]);
    ExtraerMatriz(MatrizDos, argv[2]);
    
    // Transpone ambas matrices.
    TransponerMatriz(MatrizUno, Traspuestauno);
    TransponerMatriz(MatrizDos, Traspuestados);

    // Escribe las traspuestas en archivos.
    Archivo(Traspuestauno, 1);
    Archivo(Traspuestados, 2);

    return 0; // Termina la ejecución del programa.
}