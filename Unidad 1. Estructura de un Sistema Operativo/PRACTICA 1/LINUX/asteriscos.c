#include <stdio.h>

/**
 * Imprime una figura de dos piramides de asteriscos. 
 * 
 * La figura consiste en una piramide superior e inferior 
 * centradas horizontalmente.
 *
 * @param niveles La cantidad de niveles que tiene cada una de las dos piramides.
 */
void imprimir_figura(int niveles)
{
    int i, j, espacios, asteriscos;
    
    // Imprime la piramide superior
    for (i = 0; i < niveles; i++)
    {
        espacios = niveles - i - 1;
        asteriscos = 2 * i + 1;

        // Imprime los espacios antes de los asteriscos
        for (j = 0; j < espacios; j++)
        {
            printf(" ");
        }

        // Imprime la linea de asteriscos con sus correspondientes espacios
        if (espacios > 0)
        {
            for (j = 0; j < asteriscos; j++)
            {
                printf("*");
            }
            
            for (j = 0; j < espacios + (niveles - 1); j++)
            {
                printf(" ");
            }

            printf("*");
        }
        else
        {
            for (j = 0; j < asteriscos * 2; j++)
            {
                printf("*");
            }
        }

        printf("\n");
    }

    // Imprime la piramide inferior
    for (i = niveles - 1; i > 0; i--)
    {
        espacios = niveles - i;
        asteriscos = 2 * i - 1;

        // Imprime los espacios antes de la primera estrella de la linea
        for (j = 0; j < niveles - 1; j++)
        {
            printf(" ");
        }

        printf("*");

        // Imprime los espacios entre las estrellas
        for (j = 0; j < niveles - 1 + espacios; j++)
        {
            printf(" ");
        }

        // Imprime los asteriscos restantes
        for (j = 0; j < asteriscos; j++)
        {
            printf("*");
        }

        printf("\n");
    }
}

/**
 * Funcion principal del programa.
 *
 * @return 0 si el programa se ejecuta correctamente.
 */
int main()
{
    int base, i, niveles = 0;

    // Solicita al usuario que ingrese la cantidad de asteriscos en la linea horizontal con mas asteriscos
    printf("Ingrese la cantidad de asteriscos de la linea horizontal con mas asteriscos: ");
    scanf("%d", &base);

    // Asegura que la cantidad de asteriscos sea impar
    if (base % 2 == 0)
    {
        base++;
    }

    // Calcula la cantidad de niveles para las piramides
    for (i = 0; i < (base / 2); i++)
    {
        base -= 2;

        if (base >= 0)
        {
            niveles++;
        }
    }

    // Imprime la figura con los niveles calculados
    imprimir_figura(niveles);

    return 0;
}