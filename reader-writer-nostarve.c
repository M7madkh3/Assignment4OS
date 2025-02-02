#include <stdio.h>      // For printf
#include <stdlib.h>     // For exit
#include <semaphore.h>  // For sem_t, sem_wait, sem_post
#include <pthread.h>    // For pthread functions (if threads are used)
sem_t rw_mutex = 1;
sem_t mutex = 1;
sem_t write_mutex = 1;
int readers = 0;
int waiting_writers = 0;
int writing = 0;

// Implement writer preference logic here