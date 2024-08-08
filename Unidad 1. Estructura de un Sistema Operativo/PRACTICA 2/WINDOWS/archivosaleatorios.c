#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define num_archivos 10  // Número de archivos a crear
#define num_caracter 100  // Número de caracteres en cada archivo 

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
    // Verifica que se proporcionen exactamente dos argumentos: nombre del programa y ruta del directorio
    if (num_args != 2)
    {
        fprintf(stderr, "Uso: %s <ruta_path>\n", argumento[0]);
        exit(EXIT_FAILURE);
    }

    srand(GetTickCount());  // Inicializa el generador de números aleatorios con el tick actual.

    char* directorio_path = argumento[1];

    // Intenta crear el directorio especificado
    if (CreateDirectory(directorio_path, NULL) == 0)
    {
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            fprintf(stderr, "Error: El directorio '%s' ya existe.\n", directorio_path);
        } 
        else
        {
            perror("Fallo al crear el directorio");
        }
        exit(EXIT_FAILURE);
    }

    // Cambia el directorio de trabajo al nuevo directorio creado
    if (SetCurrentDirectory(directorio_path) == 0)
    {
        perror("Fallo al cambiar el directorio");
        exit(EXIT_FAILURE);
    }

    // Bucle para crear y escribir en los archivos
    for (int i = 0; i < num_archivos; i++)
    {
        char nomarchivo[20];
        snprintf(nomarchivo, sizeof(nomarchivo), "archivo_%d.txt", i);

        // Crea un nuevo archivo en modo escritura, truncando si ya existe
        HANDLE datosarchivo = CreateFile(nomarchivo, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (datosarchivo == INVALID_HANDLE_VALUE)
        {
            perror("Fallo al abrir el archivo");
            exit(EXIT_FAILURE);
        }

        char* contenido = generar_contenido();  // Genera el contenido aleatorio para el archivo

        DWORD bytesEscritos;
        // Escribe el contenido en el archivo
        if (WriteFile(datosarchivo, contenido, strlen(contenido), &bytesEscritos, NULL) == 0)
        {
            perror("Fallo al escribir en el archivo");
            exit(EXIT_FAILURE);
        }

        // Cierra el archivo después de escribir
        if (CloseHandle(datosarchivo) == 0)
        {
            perror("Fallo al cerrar el archivo");
            exit(EXIT_FAILURE);
        }

        free(contenido);  // Libera la memoria asignada para el contenido
    }

    printf("Archivos aleatorios creados en el directorio: %s\n", directorio_path);
    
    return 0;
}