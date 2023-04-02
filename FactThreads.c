#include <stdio.h>
#include <pthread.h>

int fact = 1;

void *factorial(void *arg) 
{
    int start = *((int *) arg);
    int end = start + 2;
    int i;
    
    for (i = start; i <= end; i++) 
    {
        fact = fact * i;
    }
    pthread_exit(NULL);
}

int main() 
{
    pthread_t thread[3];
    int thread_args[3];
    int i;
    
    thread_args[0] = 1;
    thread_args[1] = 4;
    thread_args[2] = 7;
    
    for (i = 0; i < 3; i++) 
    {
        pthread_create(&thread[i], NULL, factorial, (void *) &thread_args[i]);
    }
    
    for (i = 0; i < 3; i++) 
    {
        pthread_join(thread[i], NULL);
    }
    
    printf("El factorial de 9 es: %d\n", fact);
    
    return 0;
}
