#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Definiciones de constantes para el tamaño de la matriz
 * 
 * N: Tamaño de la matriz.
 * OPERACIONES: Número de operaciones a realizar.
 */
#define N 10
#define OPERACIONES 5

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

int main(int argc, char *argv[])
{
    int i;
    int Resultado[N][N];
    double Inversa[N][N];
    DWORD lectura;

    // Nombres de las operaciones
    char *nombres_operaciones[7] = {
        "Suma",
        "Resta",
        "Multiplicacion",
        "Traspuesta uno",
        "Traspuesta dos",
        "Inversa uno",
        "Inversa dos"
    };

    // Leer y mostrar resultados de las operaciones
    for (i = 0; i < OPERACIONES; i++)
    {
        ReadFile(GetStdHandle(STD_INPUT_HANDLE), Resultado, sizeof(Resultado), &lectura, NULL);
        printf("\n\nResultado de %s:\n", nombres_operaciones[i]);
        ImprimirMatriz(Resultado);
    }

    // Leer y mostrar resultados de las inversas
    for (i = 5; i <= 6; i++)
    {
        ReadFile(GetStdHandle(STD_INPUT_HANDLE), Inversa, sizeof(Inversa), &lectura, NULL);
        printf("\n\nResultado de %s:\n", nombres_operaciones[i]);
        ImprimirInversa(Inversa);
    }
    
    return 0;
}
