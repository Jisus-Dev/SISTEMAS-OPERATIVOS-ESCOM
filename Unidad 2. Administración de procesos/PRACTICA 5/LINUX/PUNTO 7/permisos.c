#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/**
 * Función principal del programa.
 *
 * @param num_args Número de argumentos de línea de comandos.
 * @param argumento Arreglo de argumentos de línea de comandos.
 * @return 0 si el programa se ejecuta correctamente.
 */
int main(int num_args, char *argumento[])
{
    // Verifica que se pasen exactamente 2 argumentos (nombre del archivo y permisos)
    if (num_args != 3)
    {
        fprintf(stderr, "Uso: %s <nombre_archivo> <permisos>\n", argumento[0]);
        exit(EXIT_FAILURE);
    }

    // Obtiene el nombre del archivo del segundo argumento
    char *nombre_archivo = argumento[1];

    // Convierte el tercer argumento (permisos) de cadena a un valor de tipo mode_t
    mode_t permisos = strtol(argumento[2], NULL, 8);

    // Intenta cambiar los permisos del archivo especificado
    if (chmod(nombre_archivo, permisos) == -1)
    {
        perror("chmod fallido");
        exit(EXIT_FAILURE);
    }

    // Imprime un mensaje indicando que los permisos se cambiaron correctamente
    printf("\t\tPermisos cambiados con exito para el archivo %s\n", nombre_archivo);

    return 0;
}