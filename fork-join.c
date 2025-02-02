#include <stdio.h>      // For printf
#include <stdlib.h>     // For exit
#include <semaphore.h>  // For sem_t, sem_wait, sem_post
#include <pthread.h>    // For pthread functions (if threads are used)
sem_t s;

int main() {
    sem_init(&s, 0, 0);
    
    if (fork() == 0) {
        printf("Child\n");
        sem_post(&s);
        exit(0);
    } else {
        sem_wait(&s);
        printf("Parent\n");
    }
}