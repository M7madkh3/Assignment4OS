Reader-Writer Problem (No Starvation) (reader-writer-nostarve.c):
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t rw_mutex;
sem_t mutex;
sem_t write_mutex;
int readers = 0;
int waiting_writers = 0;
int writing = 0;

void *reader(void *arg) {
    sem_wait(&write_mutex);  // Prevent writer starvation
    sem_wait(&mutex);
    readers++;
    if (readers == 1) sem_wait(&rw_mutex);  // First reader locks writers
    sem_post(&mutex);
    sem_post(&write_mutex);

    printf("Reader is reading\n");
    sleep(1);  // Simulate reading

    sem_wait(&mutex);
    readers--;
    if (readers == 0) sem_post(&rw_mutex);  // Last reader unlocks writers
    sem_post(&mutex);
    return NULL;
}

void *writer(void *arg) {
    sem_wait(&write_mutex);
    sem_wait(&rw_mutex);
    printf("Writer is writing\n");
    sleep(1);  // Simulate writing
    sem_post(&rw_mutex);
    sem_post(&write_mutex);
    return NULL;
}

int main() {
    sem_init(&rw_mutex, 0, 1);  // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&write_mutex, 0, 1);

    pthread_t r1, r2, w1;
    pthread_create(&r1, NULL, reader, NULL);
    pthread_create(&w1, NULL, writer, NULL);
    pthread_create(&r2, NULL, reader, NULL);

    pthread_join(r1, NULL);
    pthread_join(w1, NULL);
    pthread_join(r2, NULL);

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);
    sem_destroy(&write_mutex);
    return 0;
}