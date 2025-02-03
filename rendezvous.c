#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t aArrived;
sem_t bArrived;

void *threadA(void *arg) {
    printf("A1\n");
    sem_post(&aArrived);  // Signal that A has arrived
    sem_wait(&bArrived);  // Wait for B to arrive
    printf("A2\n");
    return NULL;
}

void *threadB(void *arg) {
    printf("B1\n");
    sem_post(&bArrived);  // Signal that B has arrived
    sem_wait(&aArrived);  // Wait for A to arrive
    printf("B2\n");
    return NULL;
}

int main() {
    sem_init(&aArrived, 0, 0);  // Initialize semaphores
    sem_init(&bArrived, 0, 0);

    pthread_t tA, tB;
    pthread_create(&tA, NULL, threadA, NULL);
    pthread_create(&tB, NULL, threadB, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);

    sem_destroy(&aArrived);  // Clean up semaphores
    sem_destroy(&bArrived);
    return 0;
}