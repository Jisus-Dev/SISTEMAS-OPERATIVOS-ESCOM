#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/**
 * Función principal del programa.
 *
 * @param num_args Número de argumentos de línea de comandos.
 * @param argumento Arreglo de argumentos de línea de comandos.
 * @return 0 si el programa se ejecuta correctamente.
 */
int main(int num_args, char *argumento[])
{
    // Verifica que se proporcionen exactamente tres argumentos: nombre del programa, nombre del archivo y permisos en decimal.
    if (num_args != 3)
    {
        fprintf(stderr, "Uso: %s <nombre_archivo> <permisos_en_decimal>\n", argumento[0]);
        exit(EXIT_FAILURE);
    }

    char *nombre_archivo = argumento[1];  // Nombre del archivo
    DWORD permisos = atoi(argumento[2]);  // Permisos en formato decimal

    // Intenta cambiar los atributos de archivo usando SetFileAttributes
    if (!SetFileAttributes(nombre_archivo, permisos))
    {
        perror("SetFileAttributes fallido");  // Muestra un mensaje de error si falla SetFileAttributes
        exit(EXIT_FAILURE);
    }

    printf("Permisos cambiados con exito para el archivo %s\n", nombre_archivo);  // Mensaje de éxito

    return 0;
}