#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

// Inicialización de un mutex para proteger el acceso a recursos compartidos.
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * Función que ejecuta el hilo 3.
 * 
 * @param arg Argumento pasado al hilo (no utilizado en este caso).
 */
void *hilo3(void *arg)
{
    pthread_mutex_lock(&mutex); // Bloquea el mutex para evitar condiciones de carrera.
    char* men = (char*)arg; // Se castiga el argumento a char* (no se usa).
    printf("\t\tPractica 6 hilo terminal\n"); // Imprime un mensaje.
    pthread_mutex_unlock(&mutex); // Libera el mutex.
    pthread_exit(NULL); // Termina el hilo.
}

/**
 * Función que ejecuta el hilo 2.
 * 
 * @param arg Argumento pasado al hilo (no utilizado en este caso).
 */
void *hilo2(void *arg)
{
    int id = pthread_self(); // Obtiene el ID del hilo actual.
    printf("\t2- %d\n", id); // Imprime el ID del hilo.

    pthread_t id_hilo[10]; // Arreglo para almacenar los IDs de los hilos que se crearán.

    // Crea 10 hilos que ejecutarán la función hilo3.
    for(int i = 0; i < 10; i++)
    {
        pthread_create(&id_hilo[i], NULL, (void*)hilo3, NULL);
    }

    // Espera a que todos los hilos creados terminen su ejecución.
    for(int i = 0; i < 10; i++)
    {
        pthread_join(id_hilo[i], NULL);
    }

    pthread_exit(NULL); // Termina el hilo.
}

/**
 * Función que ejecuta el hilo 1.
 * 
 * @param arg Argumento pasado al hilo (no utilizado en este caso).
 */
void *hilo(void *arg)
{
    int id = pthread_self(); // Obtiene el ID del hilo actual.
    printf("1- %d\n", id); // Imprime el ID del hilo.

    pthread_t id_hilo[15]; // Arreglo para almacenar los IDs de los hilos que se crearán.

    // Crea 15 hilos que ejecutarán la función hilo2.
    for(int i = 0; i < 15; i++)
    {
        pthread_create(&id_hilo[i], NULL, (void*)hilo2, NULL);
    }

    // Espera a que todos los hilos creados terminen su ejecución.
    for(int i = 0; i < 15; i++)
    {
        pthread_join(id_hilo[i], NULL);
    }

    pthread_exit(NULL); // Termina el hilo.
}

int main(void)
{
    int id_proc;

    id_proc = fork(); // Crea un nuevo proceso.

    if(id_proc == 0) // Código del proceso hijo.
    {
        pthread_t id_hilo[20]; // Arreglo para almacenar los IDs de los hilos que se crearán.

        // Crea 20 hilos que ejecutarán la función hilo.
        for(int i = 0; i < 20; i++)
        {
            pthread_create(&id_hilo[i], NULL, (void*)hilo, NULL);
        }

        // Espera a que todos los hilos creados terminen su ejecución.
        for(int i = 0; i < 20; i++)
        {
            pthread_join(id_hilo[i], NULL);
        }
    }
    else wait(0); // El proceso padre espera a que el hijo termine.

    return 0; // Termina el programa.
}