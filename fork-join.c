#include <semaphore.h>
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