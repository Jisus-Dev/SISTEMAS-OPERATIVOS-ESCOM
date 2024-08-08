#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Muestra el contenido de un archivo en la consola.
 * 
 * @param archivo La ruta del archivo que se va a mostrar.
 */
void mostrar(char *archivo)
{
    FILE *file = fopen(archivo, "r"); // Abrir el archivo en modo lectura
    if (file == NULL) // Verificar si el archivo se abrió correctamente
    {
        printf("Error al abrir el archivo %s\n", archivo);
        return;
    }
    
    int i = 0, j = 0;
    char num;

    // Leer el archivo carácter por carácter y mostrar en consola
    while ((num = fgetc(file)) != EOF && j < 10) // Leer hasta el final del archivo o hasta 10 líneas
    {
        printf("%c", num); // Imprimir el carácter leído
        if (num == '\n') {
            j++;
            printf("\n"); // Imprimir una línea nueva para separación
        }
        i++;
    }
    fclose(file); // Cerrar el archivo
}

int main(int argc, char *argv[])
{
    printf("\nSoy el proceso hijo 6 con PID: %d \n", GetCurrentProcessId());

    // Mostrar el contenido de los archivos de resultados
    mostrar("resultados/Suma.txt");
    mostrar("resultados/Resta.txt");
    mostrar("resultados/Multiplicacion.txt");
    mostrar("resultados/Traspuesta1.txt");
    mostrar("resultados/Traspuesta2.txt");
    mostrar("resultados/Inversa1.txt");
    mostrar("resultados/Inversa2.txt");

    return 0;
}