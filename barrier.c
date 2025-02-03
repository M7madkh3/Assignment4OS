#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define N 5  // Total number of threads

sem_t mutex;
sem_t barrier;
int count = 0;

void *worker(void *arg) {
    printf("Before barrier\n");

    sem_wait(&mutex);
    count++;
    if (count == N) {
        sem_post(&barrier);  // Release one thread
    }
    sem_post(&mutex);

    sem_wait(&barrier);
    sem_post(&barrier);  // Allow all threads to proceed

    printf("After barrier\n");
    return NULL;
}


int main() {
    sem_init(&mutex, 0, 1);   // Initialize mutex semaphore
    sem_init(&barrier, 0, 0); // Initialize barrier semaphore

    pthread_t threads[N];
    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&barrier);
    return 0;
}
