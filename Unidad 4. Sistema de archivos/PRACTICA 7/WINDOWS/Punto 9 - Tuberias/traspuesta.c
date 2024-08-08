#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Definiciones de constantes para el tamaño de la matriz
 * 
 * N: Tamaño de la matriz.
 */
#define N 10

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

int main(int argc, char *argv[])
{
    // Para lectura
    HANDLE hLecturaPipe_hijo_nieto = GetStdHandle(STD_INPUT_HANDLE);
    DWORD lectura;

    // Para escritura
    HANDLE hEscrituraPipe_hijo_nieto = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD escritura;

    int Matrizuno[N][N];
    int Matrizdos[N][N];

    // Leer las matrices del hijo
    ReadFile(hLecturaPipe_hijo_nieto, Matrizuno, sizeof(Matrizuno), &lectura, NULL);
    ReadFile(hLecturaPipe_hijo_nieto, Matrizdos, sizeof(Matrizdos), &lectura, NULL);

    int Traspuesta_uno[N][N];
    TransponerMatriz(Matrizuno,Traspuesta_uno);

    int Traspuesta_dos[N][N];
    TransponerMatriz(Matrizdos,Traspuesta_dos);

    //Escribir el resultado en la tuberia
    WriteFile(hEscrituraPipe_hijo_nieto, Traspuesta_uno, sizeof(Traspuesta_uno), &escritura, NULL);
    WriteFile(hEscrituraPipe_hijo_nieto, Traspuesta_dos, sizeof(Traspuesta_dos), &escritura, NULL);

    CloseHandle(hLecturaPipe_hijo_nieto);
    CloseHandle(hEscrituraPipe_hijo_nieto);

    return 0;
}   