#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Estructura que representa una pila.
 * 
 * @tope indice del elemento superior de la pila.
 * @capacidad Capacidad maxima de la pila.
 * @arreglo Arreglo que almacena los elementos de la pila.
 */
struct Pila 
{
    int tope;
    unsigned capacidad;
    int* arreglo;
};

/**
 * Crea una pila con la capacidad dada.
 * 
 * @param capacidad Capacidad maxima de la pila.
 * @return Puntero a la pila creada.
 */
struct Pila* crearPila(unsigned capacidad)
{
    struct Pila* pila = (struct Pila*)malloc(sizeof(struct Pila));
    pila->capacidad = capacidad;
    pila->tope = -1;
    pila->arreglo = (int*)malloc(pila->capacidad * sizeof(int));
    return pila;
}

/**
 * Verifica si la pila esta vacia.
 * 
 * @param pila Puntero a la pila.
 * @return 1 si la pila esta vacia, 0 en caso contrario.
 */
int estaVacia(struct Pila* pila)
{
    return pila->tope == -1;
}

/**
 * Inserta un elemento en la pila.
 * 
 * @param pila Puntero a la pila.
 * @param elemento Elemento a insertar en la pila.
 */
void push(struct Pila* pila, int elemento)
{
    pila->arreglo[++pila->tope] = elemento;
}

/**
 * Elimina y devuelve el elemento superior de la pila.
 * 
 * @param pila Puntero a la pila.
 * @return Elemento superior de la pila, o -1 si la pila esta vacia.
 */
int pop(struct Pila* pila)
{
    if (!estaVacia(pila))
        return pila->arreglo[pila->tope--];
    return -1;
}

/**
 * Devuelve el elemento superior de la pila sin eliminarlo.
 * 
 * @param pila Puntero a la pila.
 * @return Elemento superior de la pila, o -1 si la pila esta vacia.
 */
int peek(struct Pila* pila)
{
    if (!estaVacia(pila))
        return pila->arreglo[pila->tope];
    return -1;
}

/**
 * Devuelve la precedencia de un operador.
 * 
 * @param op Operador.
 * @return Precedencia del operador.
 */
int precedencia(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

/**
 * Aplica un operador a dos operandos.
 * 
 * @param a Primer operando.
 * @param b Segundo operando.
 * @param op Operador.
 * @return Resultado de la operacion.
 */
int aplicarOperador(int a, int b, char op)
{
    switch (op)
    {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b != 0)
                return a / b;
            else
            {
                printf("Error: Division por cero\n");
                exit(EXIT_FAILURE);
            }
    }
    return 0; // No deberia llegar aqui
}

/**
 * Evalua una expresion matematica.
 * 
 * @param expresion Expresion matematica.
 * @return Resultado de la evaluacion, o -1 si hay un error.
 */
int evaluarExpresion(const char* expresion)
{
    struct Pila* pila = crearPila(strlen(expresion));
    int i;

    // Verificar balanceo de parentesis
    for (i = 0; expresion[i]; ++i)
    {
        if (expresion[i] == '(')
            push(pila, expresion[i]);
        else if (expresion[i] == ')')
        {
            if (estaVacia(pila))
            {
                printf("Error: Parentesis desbalanceados\n");
                return -1;
            }
            pop(pila);
        }
    }

    if (!estaVacia(pila))
    {
        printf("Error: Parentesis desbalanceados\n");
        return -1;
    }

    struct Pila* operandos = crearPila(strlen(expresion));
    struct Pila* operadores = crearPila(strlen(expresion));

    // Evaluar la expresion
    for (i = 0; expresion[i]; ++i)
    {
        if (isdigit(expresion[i]))
        {
            int operando = 0;
            while (isdigit(expresion[i]))
            {
                operando = operando * 10 + (expresion[i] - '0');
                i++;
            }
            i--;
            push(operandos, operando);
        } 
        else if (expresion[i] == '+' || expresion[i] == '-' || expresion[i] == '*' || expresion[i] == '/')
        {
            while (!estaVacia(operadores) && precedencia(expresion[i]) <= precedencia(peek(operadores)))
            {
                int val2 = pop(operandos);
                int val1 = pop(operandos);
                char op = pop(operadores);
                push(operandos, aplicarOperador(val1, val2, op));
            }
            push(operadores, expresion[i]);
        } 
        else if (expresion[i] == '(')
        {
            push(operadores, expresion[i]);
        } 
        else if (expresion[i] == ')')
        {
            while (!estaVacia(operadores) && peek(operadores) != '(')
            {
                int val2 = pop(operandos);
                int val1 = pop(operandos);
                char op = pop(operadores);
                push(operandos, aplicarOperador(val1, val2, op));
            }
            pop(operadores);
        }
    }

    while (!estaVacia(operadores))
    {
        int val2 = pop(operandos);
        int val1 = pop(operandos);
        char op = pop(operadores);
        push(operandos, aplicarOperador(val1, val2, op));
    }

    int resultado = pop(operandos);
    free(pila->arreglo);
    free(pila);
    free(operandos->arreglo);
    free(operandos);
    free(operadores->arreglo);
    free(operadores);
    return resultado;
}

/**
 * Funcion principal del programa.
 * 
 * @return 0 si el programa se ejecuta correctamente.
 */
int main(int argc, char *argv[])
{
    char *expresion = argv[1];
    
    // Elimina el salto de línea final agregado por fgets si está presente
    if ((strlen(expresion) > 0) && (expresion[strlen(expresion) - 1] == '\n'))
        expresion[strlen(expresion) - 1] = '\0';

    int resultado = evaluarExpresion(expresion);

    if (resultado != -1)
        printf("\t\tResultado de la expresión: %d\n", resultado);

    return 0;
}