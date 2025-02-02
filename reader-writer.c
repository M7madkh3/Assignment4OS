sem_t rw_mutex = 1;
sem_t mutex = 1;
int readers = 0;

void *reader(void *arg) {
    sem_wait(&mutex);
    readers++;
    if (readers == 1) sem_wait(&rw_mutex);
    sem_post(&mutex);
    
    // Reading
    
    sem_wait(&mutex);
    readers--;
    if (readers == 0) sem_post(&rw_mutex);
    sem_post(&mutex);
}

void *writer(void *arg) {
    sem_wait(&rw_mutex);
    
    // Writing
    
    sem_post(&rw_mutex);
}