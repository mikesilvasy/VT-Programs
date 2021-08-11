/*
 * This program uses multiple threads to allocate buffers
 * and fill them with numbers drawn from non-overlapping
 * ranges.  These buffers are then added to a list, which
 * is then sorted and checked.
 *
 * This program contains one or more datarace(s), which you
 * should find and fix.
 *
 * NOTE: To maximize parallelism, make sure to avoid any 
 *       unnecessary serialization!
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct buffer {
    struct list_elem link;
    size_t n;               // number of ints in buf
    int data[0];
};

struct list buffers;
int offset;
pthread_mutex_t lock;

// make a buffer of size n
static struct buffer *
make_buffer(size_t n)
{
    struct buffer * buf = malloc(sizeof(struct buffer) 
                                 + n * sizeof(int));
    buf->n = n;
    return buf;
}

static void * fill_buffer(void *arg) {
    int myoffset;
    struct buffer * buf;

    // create buffer
    buf = make_buffer((uintptr_t) arg);
    int sz = buf->n;

    // obtain offset and increment it
    pthread_mutex_lock(&lock);
    myoffset = offset;
    //pthread_mutex_lock(&lock);
    offset += sz;
    //pthread_mutex_unlock(&lock);

    // fill buffer with data
    for (int i = 0; i < buf->n; i++)
        buf->data[i] = myoffset + i;

    // add buffer to list
    list_push_back(&buffers, &buf->link);
    pthread_mutex_unlock(&lock);
    return NULL;
}

bool sort_by_first (const struct list_elem *a,
                    const struct list_elem *b,
                    void *aux)
{
    struct buffer * ba = list_entry(a, struct buffer, link);
    struct buffer * bb = list_entry(b, struct buffer, link);
    return ba->data[0] < bb->data[0];
}

#define N_THREADS   10
int
main()
{
    pthread_t t[N_THREADS];
    pthread_mutex_init(&lock, NULL);
    list_init(&buffers);
    int startingoffset = 1000;
    offset = startingoffset;

    for (int ti = 0; ti < N_THREADS; ti++)
        pthread_create(t+ti, NULL, fill_buffer, (void *)4096);

    for (int ji = 0; ji < N_THREADS; ji++)
        pthread_join(t[ji], NULL);

    list_sort(&buffers, sort_by_first, /* aux */NULL);
    int i = 0;
    for (struct list_elem *e = list_begin(&buffers); 
            e != list_end(&buffers); 
            e = list_next(e)) {
        struct buffer * b = list_entry(e, struct buffer, link);
        assert(b->data[0] == startingoffset + i++ * 4096);
    }
}
