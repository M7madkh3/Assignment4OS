#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t mutex;
sem_t block;
int waiting = 0;

void lock() {
    sem_wait(&mutex);
    waiting++;
    printf("Thread trying to acquire lock, waiting: %d\n", waiting);

    if (waiting > 1) {  // If there's already a waiting thread, wait
        sem_post(&mutex);
        sem_wait(&block);
    } else {
        sem_post(&mutex);
    }

    printf("Thread acquired lock\n");
}

void unlock() {
    sem_wait(&mutex);
    waiting--;

    if (waiting > 0) {  // If another thread is waiting, wake it up
        sem_post(&block);
        printf("Lock passed to next waiting thread\n");
    } else {
        sem_post(&mutex);
        printf("Mutex released\n");
    }
}

void *test_thread(void *arg) {
    lock();
    printf("Thread in critical section\n");
    sleep(1);
    unlock();
    return NULL;
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&block, 0, 0);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, test_thread, NULL);
    sleep(1);
    pthread_create(&t2, NULL, test_thread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&mutex);
    sem_destroy(&block);
    return 0;
}
