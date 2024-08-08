#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/**
 * Función principal que ejecuta el comando 'cat' para mostrar el contenido de varios archivos.
 * 
 * @param argc Número de argumentos.
 * @param argv Arreglo de argumentos.
 * @return Código de salida del programa.
 */
int main(int argc, char *argv[])
{
    // Llama a la función execlp para ejecutar el comando 'cat' con los archivos especificados.
    execlp("cat", "cat", "resultados/Suma.txt", "resultados/Resta.txt", "resultados/Multiplicacion.txt", "resultados/Traspuesta1.txt", "resultados/Traspuesta2.txt", "resultados/Inversa1.txt", "resultados/Inversa2.txt", NULL);
}
