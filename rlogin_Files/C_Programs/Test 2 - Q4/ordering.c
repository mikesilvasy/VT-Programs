
// Modify the program below so that exactly all of the following
// become possible outputs of this program
// 
// BACDE
// BACED
// BADCE
// BADEC
// BAECD
// BAEDC
// BDACE
// BDAEC
// DBACE
// DBAEC
// 
// You may not change the main routine or the location of the printf()
// statements.

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

// you will need to use these 
sem_t sem[5];


static void * printA(void *_arg)                        // sem[0]
{
    /* write code here if necessary */
    sem_wait(&sem[1]);
    printf("A");
    /* write code here if necessary */
    sem_post(&sem[0]);
    sem_post(&sem[0]);
    return NULL;
}

static void * printB(void *_arg)                        // sem[1]
{
    /* write code here if necessary */
    printf("B");
    /* write code here if necessary */
    sem_post(&sem[1]);
    sem_post(&sem[1]);
    sem_post(&sem[1]);
    return NULL;
}

static void * printC(void *_arg)                        // sem[2]
{
    /* write code here if necessary */
    sem_wait(&sem[0]);
    sem_wait(&sem[1]);
    printf("C");
    /* write code here if necessary */
    return NULL;
}

static void * printD(void *_arg)                        // sem[3]
{
    /* write code here if necessary */
    printf("D");
    /* write code here if necessary */
    return NULL;
}

static void * printE(void *_arg)                        // sem[4]
{
    /* write code here if necessary */
    sem_wait(&sem[0]);
    sem_wait(&sem[1]);
    printf("E");
    /* write code here if necessary */
    return NULL;
}


// no changes allowed to main
int
main()
{
    int i;
    void * (*f[])(void *) = { 
        printA, printB, printC, printD, printE
    };
    for (i = 0; i < sizeof(sem)/sizeof(sem[0]); i++)
        sem_init(sem + i, 0, 0);

    const int N = sizeof(f)/sizeof(f[0]);
    pthread_t t[N];
    for (i = 0; i < N; i++)
        pthread_create(t+i, NULL, f[i], NULL);

    for (i = 0; i < N; i++)
        pthread_join(t[i], NULL);
}
// Task generated for pid silvasym; hash 342407818
