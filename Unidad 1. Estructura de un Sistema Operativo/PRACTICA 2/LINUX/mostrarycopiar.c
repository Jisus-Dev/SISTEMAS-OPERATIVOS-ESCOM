#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>

#define tam_buffer 1024  // Tamaño del buffer utilizado para leer y escribir archivos

/**
 * Muestra el contenido de un archivo en la consola.
 *
 * @param nombre_archivo Nombre del archivo a mostrar.
 */
void mostrar_contenido_archivo(const char *nombre_archivo)
{
    int archivo = open(nombre_archivo, O_RDONLY);  // Abre el archivo en modo solo lectura
    
    if (archivo == -1)
    {
        perror("No se pudo abrir el archivo");  // Muestra un mensaje de error si no se pudo abrir el archivo
        return;
    }

    char buffer[tam_buffer];  // Buffer para almacenar los datos leídos del archivo
    ssize_t bytes_leidos;  // Número de bytes leídos en cada iteración

    printf("Contenido de %s:\n\n", nombre_archivo);

    // Lee el contenido del archivo y lo muestra en la consola
    while ((bytes_leidos = read(archivo, buffer, tam_buffer)) > 0)
    {
        write(STDOUT_FILENO, buffer, bytes_leidos);
    }

    if (bytes_leidos == -1)
    {
        perror("Error al leer el archivo");  // Muestra un mensaje de error si hubo un problema al leer el archivo
    }
    
    printf("\n\n");

    close(archivo);  // Cierra el archivo
}

/**
 * Copia el contenido de un archivo a otro.
 *
 * @param origen Nombre del archivo de origen.
 * @param destino Nombre del archivo de destino.
 */
void copiar_archivo(const char *origen, const char* destino)
{
    int archivo_origen = open(origen, O_RDONLY);  // Abre el archivo de origen en modo solo lectura

    if (archivo_origen == -1)
    {
        perror("No se pudo abrir el archivo de origen");  // Muestra un mensaje de error si no se pudo abrir el archivo de origen
        return;
    }

    // Abre el archivo de destino en modo escritura, creándolo si no existe y truncándolo si existe
    int archivo_destino = open(destino, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (archivo_destino == -1)
    {
        perror("No se pudo abrir el archivo de destino");  // Muestra un mensaje de error si no se pudo abrir el archivo de destino
        close(archivo_origen);  // Cierra el archivo de origen
        return;
    }

    char buffer[tam_buffer];  // Buffer para almacenar los datos leídos del archivo de origen
    ssize_t bytes_leidos;  // Número de bytes leídos en cada iteración

    // Lee el contenido del archivo de origen y lo escribe en el archivo de destino
    while ((bytes_leidos = read(archivo_origen, buffer, tam_buffer)) > 0)
    {
        ssize_t bytes_escritos = write(archivo_destino, buffer, bytes_leidos);

        if (bytes_escritos != bytes_leidos)
        {
            perror("Error al escribir en el archivo de destino");  // Muestra un mensaje de error si hubo un problema al escribir en el archivo de destino
            close(archivo_origen);  // Cierra el archivo de origen
            close(archivo_destino);  // Cierra el archivo de destino
            return;
        }
    }

    if (bytes_leidos == -1)
    {
        perror("Error al leer el archivo de origen");  // Muestra un mensaje de error si hubo un problema al leer el archivo de origen
    }

    close(archivo_origen);  // Cierra el archivo de origen
    close(archivo_destino);  // Cierra el archivo de destino

    printf("Archivo copiado exitosamente a %s\n", destino);
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
    if (num_args != 3)
    {
        fprintf(stderr, "Uso: %s <directorio_origen> <directorio_destino>\n", argumento[0]);
        exit(EXIT_FAILURE);  // Termina el programa si el número de argumentos es incorrecto
    }

    DIR *directorio_origen = opendir(argumento[1]);  // Abre el directorio de origen

    if (!directorio_origen)
    {
        perror("Error al abrir el directorio de origen");  // Muestra un mensaje de error si no se pudo abrir el directorio de origen
        exit(EXIT_FAILURE);
    }

    printf("Archivos disponibles para copiar:\n");

    struct dirent *entrada;  // Estructura para almacenar la información de una entrada del directorio

    // Lee las entradas del directorio y muestra los nombres de los archivos regulares
    while ((entrada = readdir(directorio_origen)) != NULL)
    {
        if (entrada->d_type == DT_REG)
        {
            printf("- %s\n", entrada->d_name);
        }
    }

    closedir(directorio_origen);  // Cierra el directorio de origen

    char nombre_archivo[tam_buffer];

    // Bucle para mostrar el contenido de los archivos seleccionados por el usuario
    while (1)
    {
        printf("Ingrese el nombre del archivo que desea mostrar (o '0' para terminar): ");
        fgets(nombre_archivo, tam_buffer, stdin);  // Lee el nombre del archivo desde la entrada estándar
        nombre_archivo[strcspn(nombre_archivo, "\n")] = '\0';  // Elimina el carácter de nueva línea

        if (strcmp(nombre_archivo, "0") == 0)
        {
            break;  // Termina el bucle si el usuario ingresa '0'
        }

        char origen[tam_buffer];
        snprintf(origen, tam_buffer, "%s/%s", argumento[1], nombre_archivo);  // Construye la ruta completa del archivo

        mostrar_contenido_archivo(origen);  // Muestra el contenido del archivo
    }
    
    char nombres_archivos[tam_buffer];

    printf("Ingrese los nombres de los archivos que desea copiar (separados por comas): ");
    fgets(nombres_archivos, tam_buffer, stdin);  // Lee los nombres de los archivos desde la entrada estándar
    nombres_archivos[strcspn(nombres_archivos, "\n")] = '\0';  // Elimina el carácter de nueva línea

    char *archivo = strtok(nombres_archivos, ",");  // Divide la cadena en tokens separados por comas

    // Bucle para copiar cada archivo seleccionado por el usuario
    while (archivo != NULL)
    {
        char origen[tam_buffer];
        snprintf(origen, tam_buffer, "%s/%s", argumento[1], archivo);  // Construye la ruta completa del archivo de origen

        char destino[tam_buffer];
        snprintf(destino, tam_buffer, "%s/%s", argumento[2], archivo);  // Construye la ruta completa del archivo de destino

        copiar_archivo(origen, destino);  // Copia el archivo

        archivo = strtok(NULL, ",");  // Obtiene el siguiente token
    }
    
    return 0;  // Termina el programa exitosamente
}