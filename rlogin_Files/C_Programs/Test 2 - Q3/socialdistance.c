/*
 * A supermarket is implementing social distancing, allowing only
 * a fixed number of customers to enter at a time.  Each customer
 * is a thread.  Implement this constraint by adding the necessary
 * synchronization below.
 * You may change only code in the area outlined.
 */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

pthread_mutex_t customerLock;   // protects currentCustomerCount and totalCustomerCount
int currentCustomerCount;       // number of customers in store currently
int totalCustomerCount;         // total number of customers who shopped
int maxCustomerCount;           // maximum customer count at any point
const int MAX_CUSTOMERS = 6;    // number of customers allowed
const int N_CUSTOMERS = 50;     // total number of customers attempting to shop

/********************************************************
 * BEGIN of AREA you may change 
 ********************************************************/

// declare any variables you may need here

sem_t sem;
int total_customer_count;

static void shop_init(void)
{
    // add any initialization code here
    pthread_mutex_init(&customerLock, NULL);
    currentCustomerCount = 0;
    totalCustomerCount = 0;
    maxCustomerCount = 0;

    sem_init(&sem, 0, 1);
    sem_wait(&sem);
    total_customer_count = 0;
}

static void enter_store(void)
{
    // Write code that is called when a customer attempts to
    // enter the store and which ensures that at most MAX_CUSTOMERS 
    // enter
    pthread_mutex_lock(&customerLock);
    total_customer_count += 1;                      // Tried using totalCustomerCount in place of total_customer_count but did not work.
    if (total_customer_count > MAX_CUSTOMERS) {
        pthread_mutex_unlock(&customerLock);
        sem_wait(&sem);
    }
    else {
        pthread_mutex_unlock(&customerLock);
    }
}

static void leave_store(void)
{
    // Write code that is called when a customer leaves the store
    sem_post(&sem);
    pthread_exit(NULL);
}
/********************************************************
 * END of AREA you may change 
 ********************************************************/

static void * shopper(void *arg) {
    struct timespec shoppingTime = { .tv_sec = 0, .tv_nsec = 500000 };

    enter_store();

    pthread_mutex_lock(&customerLock);
    currentCustomerCount++;
    if (currentCustomerCount > maxCustomerCount)
        maxCustomerCount = currentCustomerCount;

    if (currentCustomerCount > MAX_CUSTOMERS) {
        printf("More than %d customers are not allowed\n", MAX_CUSTOMERS);
        abort();
    }
    totalCustomerCount++;
    pthread_mutex_unlock(&customerLock);

    nanosleep(&shoppingTime, NULL);

    pthread_mutex_lock(&customerLock);
    currentCustomerCount--;
    pthread_mutex_unlock(&customerLock);

    leave_store();
    return NULL;
}

int
main()
{
    pthread_t t[N_CUSTOMERS];

    shop_init();
    for (int ti = 0; ti < N_CUSTOMERS; ti++)
        pthread_create(t+ti, NULL, shopper, NULL);

    for (int ji = 0; ji < N_CUSTOMERS; ji++)
        pthread_join(t[ji], NULL);

    if (totalCustomerCount != N_CUSTOMERS) {
        printf("Some customers didn't get to shop\n");
        abort();
    }

    if (maxCustomerCount < MAX_CUSTOMERS) {
        printf("Social distancing is too strict: only %d customers "
               "were in store ever out of %d allowed\n", 
            maxCustomerCount, MAX_CUSTOMERS);
        abort();
    }
    printf("Thank you for observing Social Distancing in the store\n");
}

