#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

//#define _BSD_SOURCE

/*
 * Uses up two seconds by utilizing gettimeofday and timersub functions.
 */
static void wait_two_seconds() {
    struct timeval start;
    struct timeval end;
    struct timeval result;
    gettimeofday(&start, NULL);
    do {
        gettimeofday(&end, NULL);
        timersub(&end, &start, &result);
    } while(result.tv_sec < 2);
}

/*
 * Function used for threads.  This function uses up two seconds of user time.
 */
static void * thread(void * arg) {
    wait_two_seconds();
    return NULL;
}

/*
 * Creates three threads and waits two seconds afterwards.
 */
int main() {
    pthread_t t[3];
    for (int i = 0; i < 3; i++) {
        pthread_create(&t[i], NULL, thread, NULL);
    }

    wait_two_seconds();

    return 0;
}