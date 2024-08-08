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

/**
 * Guarda una matriz en un archivo dentro del directorio 'resultados'.
 * 
 * @param matriz La matriz que se guardará en el archivo.
 * @param n Identificador de la matriz (1 o 2) para determinar el nombre del archivo.
 */
void Archivo(int matriz[N][N], int n)
{
    // Crear el directorio 'resultados' si no existe
    struct stat st = {0};
    if (stat("resultados", &st) == -1) 
    {
        mkdir("resultados", 0700); // Crea el directorio con permisos de lectura/escritura/ejecución para el usuario
    }

    // Crear la ruta completa para el archivo
    char ruta_archivo[256];
    if (n == 1)
    {
        snprintf(ruta_archivo, sizeof(ruta_archivo), "resultados/Traspuesta1.txt");
    }
    else if (n == 2)
    {
        snprintf(ruta_archivo, sizeof(ruta_archivo), "resultados/Traspuesta2.txt");
    }

    // Abrir el archivo para escribir
    FILE *archivo = fopen(ruta_archivo, "w");
    if (archivo == NULL) 
    {
        printf("Error al abrir el archivo %s\n", ruta_archivo);
        exit(1); // Terminar el programa si hay un error al abrir el archivo
    }

    // Escribir el resultado de la operación en el archivo
    if (n == 1)
    {
        fprintf(archivo, "\n--- Operacion ---: Traspuesta de la Matriz 1\n");
    }
    else if (n == 2)
    {
        fprintf(archivo, "\n--- Operacion ---: Traspuesta de la Matriz 2\n");
    }

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
    printf("\nSoy el proceso hijo 4 con PID: %d \n", GetCurrentProcessId());
    printf("\tRealizo la traspuesta de matrices\n");

    int MatrizUno[N][N];
    int MatrizDos[N][N];
    int Traspuestauno[N][N];
    int Traspuestados[N][N];

    // Extraer matrices de las cadenas pasadas como argumentos
    ExtraerMatriz(MatrizUno, argv[1]);
    ExtraerMatriz(MatrizDos, argv[2]);

    // Calcular la traspuesta de las matrices
    TransponerMatriz(MatrizUno, Traspuestauno);
    TransponerMatriz(MatrizDos, Traspuestados);

    // Guardar las matrices traspuestas en archivos
    Archivo(Traspuestauno, 1);
    Archivo(Traspuestados, 2);

    return 0;
}
