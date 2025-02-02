
#include <stdio.h>      // For printf
#include <stdlib.h>     // For exit
#include <semaphore.h>  // For sem_t, sem_wait, sem_post
#include <pthread.h>    // For pthread functions (if threads are used)sem_t aArrived;

sem_t bArrived;

void *threadA(void *arg) {
    printf("A1\n");
    sem_post(&aArrived);
    sem_wait(&bArrived);
    printf("A2\n");
}

void *threadB(void *arg) {
    printf("B1\n");
    sem_post(&bArrived);
    sem_wait(&aArrived);
    printf("B2\n");
}