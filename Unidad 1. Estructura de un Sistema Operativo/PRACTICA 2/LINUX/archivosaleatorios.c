#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>

#define num_archivos 10
#define num_caracter 100

/**
 * Genera una cadena de caracteres aleatoria de longitud num_caracter.
 *
 * @return Puntero a la cadena generada.
 */
char* generar_contenido()
{
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char* contenido = (char*)malloc((num_caracter + 1) * sizeof(char));

    if (contenido == NULL)
    {
        perror("malloc fallido");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_caracter; ++i)
    {
        contenido[i] = charset[rand() % (sizeof(charset) - 1)];
    }

    contenido[num_caracter] = '\0';
    return contenido;
}

/**
 * Función principal del programa.
 *
 * @param num_args Número de argumentos de línea de comandos.
 * @param argumento Arreglo de argumentos de línea de comandos.
 * @return 0 si el programa se ejecuta correctamente.
 */
int main(int num_args, char *argumento[])
{
    if (num_args != 2)
    {
        fprintf(stderr, "Uso: %s <ruta_path>\n", argumento[0]);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));  // Inicializa el generador de números aleatorios con la hora actual.

    char* directorio_path = argumento[1];

    struct stat st;

    // Verifica si el directorio ya existe
    if (stat(directorio_path, &st) == 0)
    {
        fprintf(stderr, "Error: El directorio '%s' ya existe.\n", directorio_path);
        exit(EXIT_FAILURE);
    }

    // Crea el directorio
    if (mkdir(directorio_path, 0700) == -1)
    {
        perror("mkdir fallido");
        exit(EXIT_FAILURE);
    }

    // Cambia el directorio actual al nuevo directorio
    if (chdir(directorio_path) == -1)
    {
        perror("chdir fallido");
        exit(EXIT_FAILURE);
    }

    // Crea los archivos y escribe contenido aleatorio en ellos
    for (int i = 0; i < num_archivos; i++)
    {
        char nomarchivo[20];
        snprintf(nomarchivo, sizeof(nomarchivo), "archivo_%d.txt", i);
        int datosarchivo = open(nomarchivo, O_CREAT | O_WRONLY | O_TRUNC, 0600);

        if (datosarchivo == -1)
        {
            perror("Fallo al abrir el archivo");
            exit(EXIT_FAILURE);
        }

        char* contenido = generar_contenido();

        if (write(datosarchivo, contenido, strlen(contenido)) == -1)
        {
            perror("Fallo al escribir en el archivo");
            exit(EXIT_FAILURE);
        }

        if (close(datosarchivo) == -1)
        {
            perror("Fallo al cerrar el archivo");
            exit(EXIT_FAILURE);
        }

        free(contenido);
    }

    printf("Archivos aleatorios creados en el directorio: %s\n", directorio_path);

    return 0;
}