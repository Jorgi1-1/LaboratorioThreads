#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define arr 5

int arreglo [arr] = {0};
int n = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *productor (void *arg) 
{
    int i;

    for (i = 0; i < arr; i++) 
    {
        printf("Ingrese el valor número %i: ", i+1);
        scanf ("%d", &arreglo[i]);
        pthread_mutex_lock(&mutex);
        pthread_mutex_unlock(&mutex);
        n++;
    }
    pthread_cond_signal(&cond);
    pthread_exit(NULL);
}

void *consumidor (void *arg) 
{
    int i;
    while (1) 
    {
        pthread_mutex_lock(&mutex);
        while (n == 0) 
        {
            pthread_cond_wait(&cond, &mutex);
        }
        
        for (i = 0; i < arr; i++) 
        {
            if (arreglo[i] != 0) 
            {
                printf("Número distinto de 0: %d\n", arreglo[i]);
                arreglo [i] = 0;
                n --;
            }
            if (n == 0 && i == arr - 1) 
            {
                printf("Hemos terminado. \n");
                pthread_mutex_unlock(&mutex);
                pthread_exit(NULL);
            }
        }
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t pThread, cThread;

    pthread_create(&pThread, NULL, productor, NULL); 
    pthread_create(&cThread, NULL, consumidor, NULL);

    pthread_join(pThread, NULL); 
    pthread_join(cThread, NULL);

    return 0;
}
