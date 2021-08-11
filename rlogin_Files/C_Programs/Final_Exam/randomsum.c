#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define N   1000
struct pair {
    uint32_t sum;
    uint32_t fd;
};

static struct pair
writefile(int n) {
    const char * fname = ".myfile";
    int myfd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0600);
    unlink(fname);
    uint32_t sum = 0;
    for (uint32_t i = 0; i < n; i++) {
        uint32_t rnd = rand() % n;
        sum += rnd;
        write(myfd, &rnd, sizeof (rnd));
    }

    return (struct pair){ .sum = sum, .fd = myfd };
}

int
main()
{
    uint32_t sum = 0;
    srand(time(NULL));
    struct pair sumfd = writefile(N);

    /* Insert missing code here so that this program prints "Ok". 
     * You may not use the read, readv, preadv, or preadv2 system calls
     */

    struct stat stats;
    fstat(sumfd.fd, &stats);
    uint32_t * addr = mmap(NULL, stats.st_size, PROT_READ, MAP_SHARED, sumfd.fd, 0);

    for (uint32_t i = 0; i < N; i++)
        sum += addr[i];

    if (sum != sumfd.sum)
        abort();
    printf("Ok\n");
}
