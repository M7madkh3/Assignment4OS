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