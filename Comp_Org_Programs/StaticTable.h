#ifndef MIPSDATA_H
#define MIPSDATA_H
#include <stdint.h>

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


struct _IData{
	char* regName;
	uint8_t regValue;
	char* regValueTwos;
	
};
typedef struct _IData IData;

const IData* Find(const char* const regName);

#endif
