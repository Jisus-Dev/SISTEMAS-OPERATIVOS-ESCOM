#include <stdio.h>
#include <pthread.h>

void *hilo(void *arg);

int main(void)
{
    pthread_t id_hilo;
    pthread_create(&id_hilo, NULL, (void*)hilo, NULL);
    pthread_join(id_hilo, NULL);
    return 0;
}

void *hilo(void *arg)
{
    printf("Hola mundo desde un hilo en Linux\n");
    return NULL;
}