#include <stdio.h>      // For printf
#include <stdlib.h>     // For exit
#include <semaphore.h>  // For sem_t, sem_wait, sem_post
#include <pthread.h>    // For pthread functions (if threads are used)
sem_t mutex = 1;
sem_t block = 0;
int waiting = 0;

void lock() {
    sem_wait(&mutex);
    if (waiting > 0) {
        waiting++;
        sem_post(&mutex);
        sem_wait(&block);
    } else {
        // Acquire lock
    }
}

void unlock() {
    sem_wait(&mutex);
    if (waiting > 0) {
        sem_post(&block);
    } else {
        sem_post(&mutex);
    }
}