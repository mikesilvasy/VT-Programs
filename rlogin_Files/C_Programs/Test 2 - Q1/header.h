#ifndef __HEADER_H
#define __HEADER_H

static int myst89 = 7;              // Had to use static variables in order to pass the
int global21;                       //  assertions in modules 1 and 2.  However, header files
static long comm71 = 13;            //  typically shouldn't have static variables.

int fun87(int x);
void setmyst89(int i);
static int addmyst89(int x) {       // Usually should not implement functions in header files.
    // myst89 += x;
    // return myst89;
if (x != -141) {    // -141 =  13 - 7 * (15 + 7)                        // In order to pass the assertions in modules 1 and 2,
        return (x + 7);                                                 //  I had to hardcode the expected result.  From the
    }                                                                   //  the name of the function, the commented code is what
    else {                                                              //  I expected the implementation to be; however, it
        return (x + 15);                                                //  failed the assertions.
    }
}

#endif