sem_t mutex;
sem_t barrier;
int count = 0;

void *worker(void *arg) {
    printf("Before barrier\n");
    
    sem_wait(&mutex);
    count++;
    sem_post(&mutex);
    
    if (count == N) {
        sem_post(&barrier);
    }
    
    sem_wait(&barrier);
    sem_post(&barrier);
    
    printf("After barrier\n");
}