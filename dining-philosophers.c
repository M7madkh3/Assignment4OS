#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define N 5  // Number of philosophers

sem_t forks[N];
sem_t waiter;  // Prevent deadlock

void *philosopher(void *arg) {
    int id = *(int *)arg;
    
    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        sem_wait(&waiter);
        sem_wait(&forks[id]);
        sem_wait(&forks[(id + 1) % N]);

        printf("Philosopher %d is eating\n", id);
        sleep(1);

        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);
        sem_post(&waiter);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    sem_init(&waiter, 0, N - 1);  // Allow only N-1 philosophers to pick up forks
    for (int i = 0; i < N; i++) sem_init(&forks[i], 0, 1);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) pthread_join(philosophers[i], NULL);

    for (int i = 0; i < N; i++) sem_destroy(&forks[i]);
    sem_destroy(&waiter);

    return 0;
}