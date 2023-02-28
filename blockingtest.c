/*
 * This example uses a blocking lock
 *
 *  Created on: Mar 1, 2016
 *      Author: dchiu
 */


#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "rtclock.h"

int x = 0;
pthread_mutex_t *lock;  //declare the lock in global scope

void* doStuff(void*);

int main(int argc, char *argv[]) {

    //initialize the lock
    lock = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(lock, NULL);

    double start = rtclock();
    pthread_t t1, t2;
    pthread_create(&t1, NULL, doStuff, NULL);
    pthread_create(&t2, NULL, doStuff, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Value of x is %d\n", x);

    // done with lock; deallocate
    pthread_mutex_destroy(lock);
    free(lock);
    lock = NULL;

    double end = rtclock();
    printf("Time taken: %.6f sec\n", (end-start));
    return 0;
}

/**
 * Thread function: increment x 10 million times
 */
void* doStuff(void* args) {
    for (int i = 0; i < 10000000; i++) {
        pthread_mutex_lock(lock);
        x++;
        pthread_mutex_unlock(lock);
    }
    return NULL;
}