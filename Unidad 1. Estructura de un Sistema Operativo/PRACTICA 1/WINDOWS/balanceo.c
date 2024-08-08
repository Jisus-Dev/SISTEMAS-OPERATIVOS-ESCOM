#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Estructura que representa una pila.
 */
typedef struct
{
    char *elementos;  ///< Array que almacena los elementos de la pila.
    int tope;         ///< indice del elemento en la parte superior de la pila.
    unsigned int capacidad;  ///< Capacidad maxima de la pila.
} Pila;

/**
 * Crea una pila con una capacidad dada.
 *
 * @param pila Puntero a la pila a ser inicializada.
 * @param capacidad Capacidad maxima de la pila.
 */
void crearPila(Pila *pila, unsigned int capacidad)
{
    pila->capacidad = capacidad;
    pila->tope = -1;
    pila->elementos = (char*) malloc(pila->capacidad * sizeof(char));
}

/**
 * Verifica si la pila esta vacia.
 *
 * @param pila Puntero a la pila.
 * @return 1 si la pila esta vacia, 0 en caso contrario.
 */
int estaVacia(Pila *pila)
{
    return pila->tope == -1;
}

/**
 * Verifica si la pila esta llena.
 *
 * @param pila Puntero a la pila.
 * @return 1 si la pila esta llena, 0 en caso contrario.
 */
int estaLlena(Pila *pila)
{
    return pila->tope == pila->capacidad - 1;
}

/**
 * Inserta un elemento en la pila.
 *
 * @param pila Puntero a la pila.
 * @param elemento El elemento a ser insertado.
 */
void apilar(Pila *pila, char elemento)
{
    if (estaLlena(pila))
    {
        printf("La pila esta llena\n");
        return;
    }
    pila->elementos[++pila->tope] = elemento;
}

/**
 * Elimina y devuelve el elemento en la parte superior de la pila.
 *
 * @param pila Puntero a la pila.
 * @return El elemento en la parte superior de la pila. Si la pila esta vacia, devuelve '\0'.
 */
char desapilar(Pila *pila)
{
    if (estaVacia(pila))
    {
        printf("La pila esta vacia\n");
        return '\0';
    }
    return pila->elementos[pila->tope--];
}

/**
 * Verifica si los parentesis, corchetes y llaves en una expresion estan balanceados.
 *
 * @param expresion La expresion a ser verificada.
 * @return 1 si los parentesis, corchetes y llaves estan balanceados, 0 en caso contrario.
 */
int estanBalanceados(char *expresion)
{
    Pila pila;
    crearPila(&pila, 100);
    char x;
    for (int i = 0; expresion[i] != '\0'; i++)
    {
        if (expresion[i] == '(' || expresion[i] == '{' || expresion[i] == '[')
        {
            apilar(&pila, expresion[i]);
            continue;
        }
        if (estaVacia(&pila))
        {
            return 0;
        }
        switch (expresion[i])
        {
            case ')':
                x = desapilar(&pila);
                if (x != '(') 
                {
                    return 0;
                }
                break;
            case '}':
                x = desapilar(&pila);
                if (x != '{')
                {
                    return 0;
                }
                break;
            case ']':
                x = desapilar(&pila);
                if (x != '[')
                {
                    return 0;
                }
                break;
        }
    }
    return estaVacia(&pila);
}

/**
 * Funcion principal del programa.
 *
 * @return 0 si el programa se ejecuta correctamente.
 */
int main()
{
    char expresion[100];

    // Solicita al usuario que ingrese una expresion con parentesis, corchetes o llaves
    printf("Ingrese una expresion con parentesis, corchetes o llaves: ");
    fflush(stdout); // Limpiar el buffer de salida antes de leer la entrada

    // Lee la entrada de manera segura usando fgets
    if (fgets(expresion, sizeof(expresion), stdin) == NULL)
    {
        printf("Error al leer la expresion.\n");
        return 1;
    }

    // Elimina el salto de linea del final de la cadena leida por fgets, si existe
    expresion[strcspn(expresion, "\n")] = '\0';

    // Verifica si la entrada no esta vacia
    if (strlen(expresion) == 0)
    {
        printf("No se ingreso ninguna expresion.\n");
        return 1;
    }

    // Verifica si la expresion esta balanceada y muestra el resultado
    if (estanBalanceados(expresion))
    {
        printf("Los parentesis estan balanceados.\n");
    }
    else 
    {
        printf("Los parentesis no estan balanceados.\n");
    }

    return 0;
}