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
            resultado[i][j] = 0; // Inicializa el elemento de resultado a 0.
            for (int k = 0; k < N; k++)
            {
                resultado[i][j] += matrizuno[i][k] * matrizdos[k][j]; // Calcula el producto escalar.
            }
        }
    }
}

/**
 * Escribe el resultado de la multiplicación de matrices en un archivo.
 * 
 * @param matriz La matriz cuyo contenido se escribirá en el archivo.
 */
void Archivo(int matriz[N][N])
{
    // Crear el directorio 'resultados' si no existe.
    struct stat st = {0};
    if (stat("resultados", &st) == -1)
    {
        mkdir("resultados", 0700); // Crear el directorio con permisos 0700.
    }
    
    // Crear la ruta completa para el archivo.
    char ruta_archivo[256];
    snprintf(ruta_archivo, sizeof(ruta_archivo), "resultados/Multiplicacion.txt");

    FILE *archivo = fopen(ruta_archivo, "w"); // Abre el archivo para escritura.
    if (archivo == NULL) 
    {
        printf("Error al abrir el archivo %s\n", ruta_archivo); // Maneja el error si no se puede abrir el archivo.
        exit(1);
    }

    fprintf(archivo, "\n--- Operacion---: Multiplicacion de matrices\n");

    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            fprintf(archivo, "%d ", matriz[i][j]); // Escribe cada elemento de la matriz en el archivo.
        }
        fprintf(archivo, "\n"); // Nueva línea al final de cada fila.
    }
    fclose(archivo); // Cierra el archivo.
}

/**
 * Función principal que realiza la multiplicación de matrices.
 * 
 * @param argc Número de argumentos.
 * @param argv Arreglo de argumentos.
 * @return Código de salida del programa.
 */
int main(int argc, char *argv[])
{
    printf("\tRealizo la multiplicacion de matrices\n");

    int MatrizUno[N][N]; // Declaración de la primera matriz.
    int MatrizDos[N][N]; // Declaración de la segunda matriz.
    int Resultado[N][N]; // Declaración de la matriz de resultado.

    // Extrae las matrices desde los argumentos pasados.
    ExtraerMatriz(MatrizUno, argv[1]);
    ExtraerMatriz(MatrizDos, argv[2]);

    // Multiplica las matrices.
    MultiplicarMatrices(MatrizUno, MatrizDos, Resultado);
    
    // Escribe el resultado en un archivo.
    Archivo(Resultado);

    return 0; // Termina la ejecución del programa.
}