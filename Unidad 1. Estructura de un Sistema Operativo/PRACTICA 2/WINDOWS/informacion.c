#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/**
 * Muestra información detallada de un archivo.
 *
 * @param nombre_archivo Nombre del archivo del cual se desea mostrar la información.
 */
void mostrar_archivo_info(const char *nombre_archivo)
{
    WIN32_FILE_ATTRIBUTE_DATA file_info;

    // Obtiene los atributos del archivo especificado
    if (!GetFileAttributesEx(nombre_archivo, GetFileExInfoStandard, &file_info))
    {
        fprintf(stderr, "GetFileAttributesEx fallido\n");
        return;
    }

    // Convierte la hora de acceso a la hora local
    FILETIME ftLocal;
    FileTimeToLocalFileTime(&(file_info.ftLastAccessTime), &ftLocal);

    SYSTEMTIME stLocal;
    FileTimeToSystemTime(&ftLocal, &stLocal);

    // Imprime la información del archivo
    printf("Nombre: %s\n", nombre_archivo);
    printf("Tamaño: %lld bytes\n", ((LONGLONG)file_info.nFileSizeHigh << 32) | file_info.nFileSizeLow);
    printf("Fecha y hora de acceso: %02d/%02d/%d %02d:%02d\n", stLocal.wMonth, stLocal.wDay, stLocal.wYear, stLocal.wHour, stLocal.wMinute);
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
    // Verifica si se proporciona un argumento (la ruta del directorio)
    if (num_args != 2)
    {
        fprintf(stderr, "Uso: %s <ruta_path>\n", argumento[0]);
        exit(EXIT_FAILURE);
    }

    // Construye la ruta del directorio con un comodín para listar todos los archivos y subdirectorios
    char ruta_dir[MAX_PATH];
    snprintf(ruta_dir, sizeof(ruta_dir), "%s\\*", argumento[1]);

    // Busca el primer archivo o subdirectorio en la ruta especificada
    WIN32_FIND_DATA find_file_data;
    HANDLE hFind = FindFirstFile(ruta_dir, &find_file_data);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "FindFirstFile fallido\n");
        exit(EXIT_FAILURE);
    }

    // Itera sobre todos los archivos y subdirectorios encontrados
    do
    {
        // Ignora las entradas "." y ".." que representan el directorio actual y el padre
        if (strcmp(find_file_data.cFileName, ".") == 0 || strcmp(find_file_data.cFileName, "..") == 0)
        {
            continue;
        }

        // Construye la ruta absoluta del archivo o subdirectorio
        char ruta_absoluta[MAX_PATH];
        snprintf(ruta_absoluta, sizeof(ruta_absoluta), "%s\\%s", argumento[1], find_file_data.cFileName);

        // Muestra la información detallada del archivo o subdirectorio
        mostrar_archivo_info(ruta_absoluta);

    } while (FindNextFile(hFind, &find_file_data) != 0);  // Encuentra el siguiente archivo o subdirectorio

    FindClose(hFind);  // Cierra el identificador de búsqueda

    return 0;
}