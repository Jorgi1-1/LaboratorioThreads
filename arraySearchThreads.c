#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 12
#define SUBARRAY_SIZE 4

int array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; 
int target_number = 2; 
int found_flag = 0; 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

void* search(void* arg) 
{
    int* subarray = (int*) arg;
    for (int i = 0; i < SUBARRAY_SIZE; i++) 
    {
        if (subarray[i] == target_number) 
        {
            pthread_mutex_lock(&mutex);
            found_flag = 1;
            pthread_mutex_unlock(&mutex);
            printf("Hilo %ld: el número %d se encuentra en el arreglo.\n", pthread_self(), target_number);
            return NULL;
        }
    }
    printf("Hilo %ld: el número %d no se encuentra en el subarreglo.\n", pthread_self(), target_number);
    return NULL;
}

int main() 
{
    pthread_t threads[3];

    int subarrays[3][SUBARRAY_SIZE] = 
    {
        {array[0], array[1], array[2], array[3]},
        {array[4], array[5], array[6], array[7]},
        {array[8], array[9], array[10], array[11]}
    };

    for (int i = 0; i < 3; i++) 
    {
        if (pthread_create(&threads[i], NULL, search, subarrays[i]) != 0) 
        {
            fprintf(stderr, "Error al crear hilo %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 3; i++) 
    {
        if (pthread_join(threads[i], NULL) != 0) 
        {
            fprintf(stderr, "Error al esperar a que termine el hilo %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    if (found_flag) 
    {
        printf("El número %d se encuentra en el arreglo.\n", target_number);
    } else 
    {
        printf("El número %d no se encuentra en el arreglo.\n", target_number);
    }

    return 0;
}
