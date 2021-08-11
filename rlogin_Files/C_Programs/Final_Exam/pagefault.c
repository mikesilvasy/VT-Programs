#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/mman.h>

static void
report_vm_stats()
{
    struct rusage u;
    getrusage(RUSAGE_SELF, &u);
    printf("ru_minflt %ld\n", u.ru_minflt);
    printf("ru_majflt %ld\n", u.ru_majflt);
}

/* you may make changes here */
#define X 256000
/*
* Task 1:
*          I used the number 256 after seeing that we wanted to increase the number of minor faults by a factor of 256.  I then
*          scaled 256 by multiples of 10 until I got a number of minor page faults between 415 and 445.  I suspect that 256000 worked
*          because, eventually, approximately 256 nums entries were realloced.
*/

int
main()
{
    /* you may make changes here */
    int * nums = malloc(X * sizeof(int));
    for (int i = 0; i < X; i++) {
        *(nums + i) = 0;
    }

    report_vm_stats();
}

/*
 * Task 2:
 *          A major page fault is difficult to cause in this scenario because we have no file to read from disk.  Also, even if we did have
 *          a file to read from disk, the file would have to be of a great size in order to get a number of major page faults between
 *          415 and 445.  The chances we would have a file of that size is unlikely.
 */