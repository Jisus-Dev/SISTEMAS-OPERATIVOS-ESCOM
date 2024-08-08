#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>

/**
 * Muestra información sobre un archivo.
 *
 * @param nombre_archivo Nombre del archivo del cual se mostrará la información.
 */
void mostrar_archivo_info(const char *nombre_archivo)
{
    struct stat archivo_info;

    // Obtiene información sobre el archivo utilizando stat
    if (stat(nombre_archivo, &archivo_info) == -1)
    {
        perror("stat fallido");
        return;
    }

    // Muestra el nombre del archivo
    printf("Nombre: %s\n", nombre_archivo);

    // Muestra el tamaño del archivo en bytes
    printf("Tamaño: %ld bytes\n", archivo_info.st_size);

    // Muestra la fecha y hora de acceso del archivo
    printf("Fecha y hora de acceso: %s", ctime(&archivo_info.st_atime));

    printf("\n");
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
    // Verifica que se pase exactamente 1 argumento adicional (la ruta del directorio)
    if (num_args != 2)
    {
        fprintf(stderr, "Uso: %s <ruta_path>\n", argumento[0]);
        exit(EXIT_FAILURE);
    }

    // Abre el directorio especificado en el argumento
    DIR *directorio = opendir(argumento[1]);

    if (directorio == NULL)
    {
        perror("opendir fallido");
        exit(EXIT_FAILURE);
    }

    struct dirent *entrada;

    // Lee cada entrada en el directorio
    while ((entrada = readdir(directorio)) != NULL)
    {
        // Omite las entradas "." y ".."
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0)
        {
            continue;
        }

        char ruta_absoluta[PATH_MAX];

        // Construye la ruta completa al archivo
        snprintf(ruta_absoluta, sizeof(ruta_absoluta), "%s/%s", argumento[1], entrada->d_name);

        // Muestra información sobre el archivo
        mostrar_archivo_info(ruta_absoluta);
    }

    // Cierra el directorio
    closedir(directorio);

    return 0;
}