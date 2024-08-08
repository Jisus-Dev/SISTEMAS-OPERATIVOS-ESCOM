#include <windows.h>
#include <stdio.h>
#include <string.h>
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
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            matriz[i][j] = rand() % 101; // Genera un número aleatorio entre 0 y 100
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
            printf("%lf  ", matriz[i][j]);
        printf("\n");
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

int main(int argc, char *argv[]) 
{
    srand(time(NULL));

    int Matrizuno[N][N];
    int Matrizdos[N][N];

    // Llenar matrices con valores aleatorios
    LlenarMatriz(Matrizuno);
    LlenarMatriz(Matrizdos);

    // Imprimir matrices generadas
    printf("Matriz 1:\n");
    ImprimirMatriz(Matrizuno);
    printf("\nMatriz 2:\n");
    ImprimirMatriz(Matrizdos);

    // Declaración de manejadores para las tuberías
    HANDLE hLecturaPipe_hijo_I, hEscrituraPipe_hijo_I;
    SECURITY_ATTRIBUTES pipeSeg = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    DWORD escritos;

    // Estructuras para el proceso hijo
    STARTUPINFO siHijo;
    PROCESS_INFORMATION piHijo;
    GetStartupInfo(&siHijo);

    // Declaración de manejadores para las tuberías de lectura y escritura
    HANDLE hLecturaPipe_hijo_O, hEscrituraPipe_hijo_O;
    DWORD lectura;

    // Crear tuberías para comunicación entre procesos
    // Tubería para enviar datos al hijo
    CreatePipe(&hLecturaPipe_hijo_I, &hEscrituraPipe_hijo_I, &pipeSeg, 0);
    // Tubería para recibir datos del hijo
    CreatePipe(&hLecturaPipe_hijo_O, &hEscrituraPipe_hijo_O, &pipeSeg, 0);

    // Enviar las matrices a través de la tubería de escritura
    WriteFile(hEscrituraPipe_hijo_I, Matrizuno, sizeof(Matrizuno), &escritos, NULL);
    WriteFile(hEscrituraPipe_hijo_I, Matrizdos, sizeof(Matrizdos), &escritos, NULL);

    // Configuración de los manejadores estándar del proceso hijo
    siHijo.hStdInput = hLecturaPipe_hijo_I;
    siHijo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    siHijo.hStdOutput = hEscrituraPipe_hijo_O;
    siHijo.dwFlags = STARTF_USESTDHANDLES;

    // Creación del proceso hijo, heredando los manejadores de la tubería del padre
    CreateProcess(
        NULL, argv[1], NULL, NULL, TRUE, 0, NULL, NULL, &siHijo, &piHijo
    );

    // Esperar a que el proceso hijo termine
    WaitForSingleObject(piHijo.hProcess, INFINITE);

    // Declaración de matrices para los resultados
    int Resultado[N][N];
    double Inversa[N][N];

    // Leer el resultado de la multiplicación de matrices y calcular su inversa
    printf("\n\nInversa de la multiplicacion:\n");
    ReadFile(hLecturaPipe_hijo_O, Resultado, sizeof(Resultado), &lectura, NULL);    
    InversaMatriz(Resultado, Inversa);
    ImprimirInversa(Inversa);

    // Leer el resultado de la suma de matrices y calcular su inversa
    printf("\n\nInversa de la suma:\n");
    ReadFile(hLecturaPipe_hijo_O, Resultado, sizeof(Resultado), &lectura, NULL);    
    InversaMatriz(Resultado, Inversa);
    ImprimirInversa(Inversa);

    // Cerrar manejadores de las tuberías y el proceso hijo
    CloseHandle(hLecturaPipe_hijo_I);
    CloseHandle(hEscrituraPipe_hijo_I);
    CloseHandle(hLecturaPipe_hijo_O);
    CloseHandle(hEscrituraPipe_hijo_O);
    CloseHandle(piHijo.hThread); 
    CloseHandle(piHijo.hProcess);

    return 0;
}