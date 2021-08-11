/* module2.c, made for pid silvasym */
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include "header.h"

void setmyst89(int i) {
    myst89 = i;
}

int global21 = 15;

int
main()
{
    assert(sizeof(comm71) == sizeof(long));
    assert(sizeof(myst89) == sizeof(int));
    assert(sizeof(global21) == sizeof(int));
    
    comm71 = 13;
    myst89 = 11;
    
    assert(global21 == 15);
    int x = fun87(15);
    assert(global21 == 18);
    assert(x == 13 - 7 * (15 + 7));
    int y = addmyst89(x);
    assert(y == x + 15);
    printf("Ok\n");
}
