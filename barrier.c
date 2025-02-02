#include <stdio.h>      // For printf
#include <stdlib.h>     // For exit
#include <semaphore.h>  // For sem_t, sem_wait, sem_post
#include <pthread.h>    // For pthread functions (if threads are used)

sem_t mutex;
sem_t barrier;
int count = 0;

void *worker(void *arg) {
    printf("Before barrier\n");
    
    sem_wait(&mutex);
    count++;
    sem_post(&mutex);
    
    if (count == N) {
        sem_post(&barrier);
    }
    
    sem_wait(&barrier);
    sem_post(&barrier);
    
    printf("After barrier\n");
}