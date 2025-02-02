sem_t rw_mutex = 1;
sem_t mutex = 1;
sem_t write_mutex = 1;
int readers = 0;
int waiting_writers = 0;
int writing = 0;

// Implement writer preference logic here