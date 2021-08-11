#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char VAR1[50];      // Assuming VAR1 is no greater than 50 characters
char * VAR2;
char * VAR3;
char VAR4[50];      // Assuming VAR4 is no greater than 50 characters
char * VAR5;
FILE * file;

/*
 * Outputs desired output when "source runmyst.sh" is run from the command line.
 */
int main(int argc, char * argv[]) {
    read(0, VAR1, 50);

    VAR3 = getenv("ENVVAR");

    VAR2 = argv[1];
    VAR5 = argv[2];
    
    file = fopen(argv[3], "r");
    fscanf(file, "%s", VAR4);

    printf("%s\n", VAR1);
    printf("%s\n", VAR2);
    printf("%s\n", VAR3);

    fprintf(stderr, "%s\n", VAR4);
    fprintf(stderr, "%s\n", VAR5);

    return 0;
}