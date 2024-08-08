#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define tam_buffer 1024

/**
 * Función para mostrar el contenido de un archivo en la consola.
 *
 * @param nombre_archivo Nombre del archivo del cual se desea mostrar el contenido.
 */
void mostrar_contenido_archivo(const char *nombre_archivo)
{
    // Abrir el archivo en modo lectura
    HANDLE archivo = CreateFile(nombre_archivo, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (archivo == INVALID_HANDLE_VALUE)
    {
        perror("No se pudo abrir el archivo");
        return;
    }

    DWORD bytes_leidos;
    char buffer[tam_buffer];

    // Mostrar el nombre del archivo y empezar a leer y mostrar su contenido
    printf("Contenido de %s:\n\n", nombre_archivo);

    while (ReadFile(archivo, buffer, tam_buffer, &bytes_leidos, NULL) && bytes_leidos > 0)
    {
        // Escribir en la consola el contenido leído
        WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, bytes_leidos, &bytes_leidos, NULL);
    }

    printf("\n\n");

    // Cerrar el archivo después de leer todo el contenido
    CloseHandle(archivo);
}

/**
 * Función para copiar un archivo desde el origen al destino.
 *
 * @param origen Ruta del archivo de origen.
 * @param destino Ruta del archivo de destino.
 */
void copiar_archivo(const char *origen, const char *destino)
{
    // Abrir el archivo de origen en modo lectura
    HANDLE archivo_origen = CreateFile(origen, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (archivo_origen == INVALID_HANDLE_VALUE)
    {
        perror("No se pudo abrir el archivo de origen");
        return;
    }

    // Abrir o crear el archivo de destino en modo escritura
    HANDLE archivo_destino = CreateFile(destino, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (archivo_destino == INVALID_HANDLE_VALUE)
    {
        perror("No se pudo abrir el archivo de destino");
        CloseHandle(archivo_origen);
        return;
    }

    DWORD bytes_leidos, bytes_escritos;
    char buffer[tam_buffer];

    // Leer del archivo de origen y escribir en el archivo de destino
    while (ReadFile(archivo_origen, buffer, tam_buffer, &bytes_leidos, NULL) && bytes_leidos > 0)
    {
        WriteFile(archivo_destino, buffer, bytes_leidos, &bytes_escritos, NULL);

        if (bytes_escritos != bytes_leidos)
        {
            perror("Error al escribir en el archivo de destino");
            CloseHandle(archivo_origen);
            CloseHandle(archivo_destino);
            return;
        }
    }

    // Cerrar ambos archivos después de completar la copia
    CloseHandle(archivo_origen);
    CloseHandle(archivo_destino);

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
    // Verificar que se proporcionen exactamente dos argumentos (directorio de origen y directorio de destino)
    if (num_args != 3)
    {
        fprintf(stderr, "Uso: %s <directorio_origen> <directorio_destino>\n", argumento[0]);
        exit(EXIT_FAILURE);
    }

    // Construir la ruta del directorio de origen con un comodín para listar todos los archivos
    char ruta_origen[MAX_PATH];
    snprintf(ruta_origen, MAX_PATH, "%s\\*", argumento[1]);

    // Buscar el primer archivo en el directorio de origen
    WIN32_FIND_DATA find_file_data;
    HANDLE hFind = FindFirstFile(ruta_origen, &find_file_data);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        perror("Error al abrir el directorio de origen");
        exit(EXIT_FAILURE);
    }

    // Mostrar los archivos disponibles para copiar (ignorar directorios)
    printf("Archivos disponibles para copiar:\n");

    do
    {
        if (!(find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            printf("- %s\n", find_file_data.cFileName);
        }
    } while (FindNextFile(hFind, &find_file_data) != 0);  // Encontrar el siguiente archivo en el directorio

    FindClose(hFind);  // Cerrar el identificador de búsqueda

    char nombre_archivo[tam_buffer];

    // Ciclo para mostrar el contenido de archivos seleccionados por el usuario
    while (1)
    {
        printf("Ingrese el nombre del archivo que desea mostrar (o '0' para terminar): ");
        fgets(nombre_archivo, tam_buffer, stdin);
        nombre_archivo[strcspn(nombre_archivo, "\n")] = '\0';

        if (strcmp(nombre_archivo, "0") == 0)
        {
            break;
        }

        // Construir la ruta completa del archivo de origen
        char origen[tam_buffer];
        snprintf(origen, tam_buffer, "%s\\%s", argumento[1], nombre_archivo);

        // Mostrar el contenido del archivo seleccionado
        mostrar_contenido_archivo(origen);
    }

    // Ciclo para copiar archivos seleccionados por el usuario al directorio de destino
    char nombres_archivos[tam_buffer];
    printf("Ingrese los nombres de los archivos que desea copiar (separados por comas): ");
    fgets(nombres_archivos, tam_buffer, stdin);
    nombres_archivos[strcspn(nombres_archivos, "\n")] = '\0';

    char *archivo = strtok(nombres_archivos, ",");

    while (archivo != NULL)
    {
        // Construir las rutas completas de los archivos de origen y destino
        char origen[tam_buffer];
        snprintf(origen, tam_buffer, "%s\\%s", argumento[1], archivo);

        char destino[tam_buffer];
        snprintf(destino, tam_buffer, "%s\\%s", argumento[2], archivo);

        // Copiar el archivo seleccionado
        copiar_archivo(origen, destino);

        archivo = strtok(NULL, ",");
    }

    return 0;
}