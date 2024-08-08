/* hola.c Programa que sera invocado */
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char mensaje[100];
    strcpy(mensaje, "Hola Mundo ");
    strcat(mensaje, argv[1]);
    printf("%s\n", mensaje);
    return 0;
}