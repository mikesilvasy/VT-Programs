/*
 * The program below shows an buggy attempt at implementing
 * part of ex3, outfoxed.
 *
 * Discuss which problem can arise, describing step by step what
 * has to happen for the problem to occur.  Use line numbers
 * in your discussion.
 *
 * You do not have to provide a fix.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// detective_lock protects important detective information
pthread_mutex_t detective_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t shutdown_lock = PTHREAD_MUTEX_INITIALIZER;
bool shutdown = false;  // protected by shutdown_lock
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void * chicken_thread(void *_arg) 
{
    // acquire shutdown_lock before accessing 'shutdown'
    pthread_mutex_lock(&shutdown_lock);     
    while (!shutdown) {
        // give other chickens a chance to check 'shutdown'
        //pthread_mutex_unlock(&shutdown_lock);   

        //pthread_mutex_lock(&detective_lock);
        // wait for suspects or clues
        pthread_cond_wait(&cond, &shutdown_lock);  

        // do important detective work
        //pthread_mutex_unlock(&detective_lock);

        // prepare to safely recheck 'shutdown'
        //pthread_mutex_lock(&shutdown_lock); 
    }

    pthread_mutex_unlock(&shutdown_lock);
    return NULL;
}

#define N_THREADS   4
int
main()
{
    pthread_t t[N_THREADS];

    // start the chickens
    for (int ti = 0; ti < N_THREADS; ti++)
        pthread_create(t+ti, NULL, chicken_thread, NULL);

    // no thief on the loose this time, this is just a drill
    pthread_mutex_lock(&shutdown_lock);
    shutdown = true;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&shutdown_lock);

    for (int i = 0; i < N_THREADS; i++)
        pthread_join(t[i], NULL);
}
