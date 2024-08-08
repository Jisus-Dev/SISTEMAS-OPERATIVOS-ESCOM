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
 * Suma dos matrices cuadradas y guarda el resultado en una tercera matriz.
 * 
 * @param MatrizUno La primera matriz de entrada.
 * @param MatrizDos La segunda matriz de entrada.
 * @param Resultado La matriz de salida donde se guarda el resultado de la suma.
 */
void SumarMatrices(int MatrizUno[N][N], int MatrizDos[N][N], int Resultado[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // Sumar los elementos correspondientes de las dos matrices
            Resultado[i][j] = MatrizUno[i][j] + MatrizDos[i][j];
        }
    }
}

/**
 * Guarda una matriz en un archivo dentro del directorio 'resultados'.
 * 
 * @param matriz La matriz que se guardará en el archivo.
 */
void Archivo(int matriz[N][N])
{
    // Crear el directorio 'resultados' si no existe
    struct stat st = {0};
    if (stat("resultados", &st) == -1) 
    {
        mkdir("resultados", 0700); // Crea el directorio con permisos de lectura/escritura/ejecución para el usuario
    }

    // Crear la ruta completa para el archivo
    char ruta_archivo[256];
    snprintf(ruta_archivo, sizeof(ruta_archivo), "resultados/Suma.txt");

    // Abrir el archivo para escribir
    FILE *archivo = fopen(ruta_archivo, "w");
    if (archivo == NULL) 
    {
        printf("Error al abrir el archivo %s\n", ruta_archivo);
        exit(1); // Terminar el programa si hay un error al abrir el archivo
    }

    // Escribir el resultado de la operación en el archivo
    fprintf(archivo, "\n--- Operacion ---: Suma de matrices\n");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fprintf(archivo, "%d ", matriz[i][j]);
        }
        fprintf(archivo, "\n");
    }
    fclose(archivo); // Cerrar el archivo
}

int main(int argc, char *argv[])
{
    // Imprimir el PID del proceso hijo
    printf("\nSoy el proceso hijo 1 con PID: %d \n", GetCurrentProcessId());
    printf("\tRealizo la suma de matrices\n");

    int MatrizUno[N][N];
    int MatrizDos[N][N];
    int Resultado[N][N];

    // Extraer matrices de las cadenas pasadas como argumentos
    ExtraerMatriz(MatrizUno, argv[1]);
    ExtraerMatriz(MatrizDos, argv[2]);

    // Sumar las matrices
    SumarMatrices(MatrizUno, MatrizDos, Resultado);

    // Guardar el resultado de la suma en un archivo
    Archivo(Resultado);

    return 0;
}