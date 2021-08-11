#include "mipsData.h"
#include <stdlib.h>
#include <string.h>

#define NUMREGISTERS 8

// On my honor:
//
// - I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants
// assigned to this course.
//
// - I have not used C language code obtained from another student,
// or any other unauthorized source, including the Internet,
// either modified or unmodified.
//
// - If any C language code or documentation used in my program
// was obtained from an allowed source, such as a text book or course
// notes, that has been clearly noted with a proper citation in
// the comments of my program.
//
// Brandon Venable
// bkven99

static IData IDataTable[NUMREGISTERS] = {
	{"$t0", 8, "01000"},
	{"$t1", 9, "01001"},
	{"$t2", 10, "01010"},
	{"$t3", 11, "01011"},
	{"$s0", 16, "10000"},
	{"$s1", 17, "10001"},
	{"$s2", 18, "10010"},
	{"$s3", 19, "10011"}
};

const IData* Find(const char* const reg){
	int i;
	for(i = 0; i<NUMREGISTERS; i++){
		if(strcmp(reg,IDataTable[i].regName)==0){
			return &IDataTable[i];
		} 
	}
	return NULL;
}
