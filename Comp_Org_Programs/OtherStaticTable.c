#include "opCode.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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


#define NUMOPCODES 7

static OpData OpDataTable[NUMOPCODES] ={

	{"add", "000000", "100000", 3, false},
	{"and", "000000", "100100", 3, false},
	{"sub", "000000", "100010", 3, false},
	{"addi", "001000", "", 3, true},
	{"andi", "001100", "", 3, true},
	{"lui", "001111", "", 2, true},
	{"lw", "100011", "", 2, true}
};

const OpData* Search(const char* const instructName){
	int i;
	for(i = 0; i < NUMOPCODES; i++){
		if(strcmp(instructName, OpDataTable[i].instruct) == 0){
			return &OpDataTable[i];
		}
	}
	return NULL;
}

