#include <stdio.h>

/**
 * Resuelve el problema de la Torre de Hanoi.
 *
 * @param n Numero de discos.
 * @param origen El nombre de la torre de origen.
 * @param destino El nombre de la torre de destino.
 * @param auxiliar El nombre de la torre auxiliar.
 */
void hanoi(int n, char origen, char destino, char auxiliar)
{
    if (n == 1)
    {
        // Movimiento base: mover el disco 1 desde la torre de origen a la torre de destino
        printf("Mueva el disco 1 desde %c hasta %c\n", origen, destino);
        return;
    }
    
    // Mover n-1 discos desde la torre de origen a la torre auxiliar, usando la torre de destino como auxiliar
    hanoi(n - 1, origen, auxiliar, destino);
    
    // Mover el disco n desde la torre de origen a la torre de destino
    printf("Mueva el disco %d desde %c hasta %c\n", n, origen, destino);
    
    // Mover los n-1 discos desde la torre auxiliar a la torre de destino, usando la torre de origen como auxiliar
    hanoi(n - 1, auxiliar, destino, origen);
}

/**
 * Funcion principal del programa.
 *
 * @return 0 si el programa se ejecuta correctamente.
 */
int main()
{
    int num_discos;
    
    // Solicita al usuario que ingrese el numero de discos
    printf("Ingrese el numero de discos: ");
    scanf("%d", &num_discos);

    // Indica el inicio de la secuencia de movimientos
    printf("Los movimientos a realizar son:\n");
    
    // Llama a la funcion hanoi para resolver el problema con el numero de discos ingresado
    hanoi(num_discos, 'A', 'C', 'B');
    
    return 0;
}