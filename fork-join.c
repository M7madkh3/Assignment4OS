#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t s;

void *child(void *arg) {
    printf("Child\n");
    sleep(1);  // Simulate some work
    sem_post(&s);  // Signal that the child is done
    return NULL;
}

int main() {
    sem_init(&s, 0, 0);  // Initialize semaphore to 0

    pthread_t c;
    pthread_create(&c, NULL, child, NULL);

    sem_wait(&s);  // Wait for the child to finish
    printf("Parent\n");

    pthread_join(c, NULL);
    sem_destroy(&s);  // Clean up the semaphore
    return 0;
}
