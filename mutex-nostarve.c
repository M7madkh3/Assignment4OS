No-Starve Mutex (mutex-nostarve.c):
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t mutex;
sem_t block;
int waiting = 0;

void lock() {
    sem_wait(&mutex);
    waiting++;
    sem_post(&mutex);

    sem_wait(&block);  // Wait until granted access
}

void unlock() {
    sem_wait(&mutex);
    waiting--;
    if (waiting > 0) {
        sem_post(&block);  // Grant access to next waiting thread
    } else {
        sem_post(&mutex);
    }
}


int main() {
    sem_init(&mutex, 0, 1);  // Initialize semaphores
    sem_init(&block, 0, 0);

    // Test lock and unlock here
    lock();
    printf("Critical Section\n");
    unlock();

    sem_destroy(&mutex);
    sem_destroy(&block);
    return 0;
}