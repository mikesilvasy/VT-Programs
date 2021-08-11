#include <inttypes.h>  // I used functions from these Standard modules in
#include <string.h>    // my solution; you may or may not need all of them,
#include <stdlib.h>    // and you might need additional ones, depending on
#include <stdio.h>     // your approach to the problem.
#include <assert.h>

#include "ASMParser.h"
#include "OpcodeTable.h"
#include "RegTable.h"

// On my honor:
//
// - I have not discussed the C language code in my program with
//   anyone other than my instructor or the teaching assistants
//   assigned to this course.
//
// - I have not used C language code obtained from another student,
//   or any other unauthorized source, including the Internet,
//      either modified or unmodified.
//
// - If any C language code or documentation used in my program
//   was obtained from an allowed source, such as a text book or course
//   notes, that has been clearly noted with a proper citation in
//   the comments of my program.
//
//    <Mike Silvasy>
//    <silvasym> 

/**  Breaks up given MIPS32 assembly instruction and creates a proper 
 *   ParseResult object storing information about that instruction.
 * 
 *   Pre:  pASM points to an array holding the bits (as chars) of a
 *         syntactically valid assembly instruction, whose mnemonic is
 *         one of the following:
 *             add  addi  and  andi  lui  lw  or  ori  sub
 * 
 *   Returns:
 *         A pointer to a proper ParseResult object whose fields have been
 *         correctly initialized to correspond to the target of pASM.
 */
ParseResult* parseASM(const char* const pASM) {
	ParseResult* pR = malloc(sizeof(ParseResult));
	
	pR->ASMInstruction = calloc((strlen(pASM) + 1), sizeof(char));
	int i = 0;
	while (i < (int)strlen(pASM)) {
		*(pR->ASMInstruction + i) = *(pASM + i);
		i += 1;
	}
	// Zero terminating char already in pASM
	//printf("ASMInstruction:  %s\n", pR->ASMInstruction);
	
	pR->Mnemonic = calloc((strlen(pASM) + 1), sizeof(char));
	i = 0;
	while (*(pASM + i) == ' ') {
		i += 1;
	}
	int x = 0;
	while (*(pASM + i) != ' ') {
		pR->Mnemonic = realloc(pR->Mnemonic, (sizeof(char) * (x + 1)));
		*(pR->Mnemonic + x) = *(pASM + i);
		i += 1;
		x += 1;
	}
	// Add zero terminating char
	pR->Mnemonic = realloc(pR->Mnemonic, (sizeof(char) * (x + 1)));
	*(pR->Mnemonic + x) = '\0';
	//printf("Mnemonic:  %s\n", pR->Mnemonic);
	
	// R type instructions
	if(getOpcodeInfo(pR->Mnemonic)->type == 'R') {
		//printf("%s\n", "R");
		
		// $rd register
		while (*(pASM + i) != '$') {
			i += 1;
		}
		pR->rdName = calloc(4, sizeof(char));
		int x = 0;
		while(*(pASM + i) != ',') {
			*(pR->rdName + x) = *(pASM + i);
			i += 1;
			x += 1;
		}
		*(pR->rdName + x) = '\0';
		
		// $rs register
		while (*(pASM + i) != '$') {
			i += 1;
		}
		pR->rsName = calloc(4, sizeof(char));
		x = 0;
		while (*(pASM + i) != ',') {
			*(pR->rsName + x) = *(pASM + i);
			i += 1;
			x += 1;
		}
		*(pR->rsName + x) = '\0';
		
		// $rt register
		while (*(pASM + i) != '$') {
			i += 1;
		}
		pR->rtName = calloc(4, sizeof(char));
		x = 0;
		while (i < (int)strlen(pASM)) {
			*(pR->rtName + x) = *(pASM + i);
			i += 1;
			x += 1;
		}
		*(pR->rtName + x) = '\0';
		
		// Assign values to pR->Imm, rd, rs, rt
		pR->Imm = 0;
		pR->rs = getRegInfo(pR->rsName)->regNum;
		pR->rt = getRegInfo(pR->rtName)->regNum;
		pR->rd = getRegInfo(pR->rdName)->regNum;
		
		// Assign values to pR->IMM, RS, RT, RD
		pR->IMM = NULL;
		pR->RS = calloc(6, sizeof(char));
		pR->RT = calloc(6, sizeof(char));
		pR->RD = calloc(6, sizeof(char));
		x = 0;
		while (x < (int)strlen(getRegInfo(pR->rsName)->regBinary)) {
			*(pR->RS + x) = *(getRegInfo(pR->rsName)->regBinary + x);
			*(pR->RT + x) = *(getRegInfo(pR->rtName)->regBinary + x);
			*(pR->RD + x) = *(getRegInfo(pR->rdName)->regBinary + x);
			x += 1;
		}
		*(pR->RS + 5) = '\0';
		*(pR->RT + 5) = '\0';
		*(pR->RD + 5) = '\0';
		
		// Assign pR->Opcode, Funct values
		pR->Opcode = calloc(7, sizeof(char));
		pR->Funct = calloc(7, sizeof(char));
		x = 0;
		while (x < (int)strlen(getOpcodeInfo(pR->Mnemonic)->opcode)) {
			*(pR->Opcode + x) = '0';
			*(pR->Funct + x) = *(getOpcodeInfo(pR->Mnemonic)->funct + x);
			x += 1;
			
		}
		*(pR->Opcode + 6) = '\0';
		*(pR->Funct + 6) = '\0';
	}
	// I type instructions
	else if (getOpcodeInfo(pR->Mnemonic)->type == 'I') {
		//printf("%s\n", "I");
		
		// addi, andi, slti instructions
		if (getOpcodeInfo(pR->Mnemonic)->numArgs == 3) {
			// $rt register
			while (*(pASM + i) != '$') {
				i += 1;
			}
			pR->rtName = calloc(4, sizeof(char));
			int x = 0;
			while (*(pASM + i) != ',') {
				*(pR->rtName + x) = *(pASM + i);
				i += 1;
				x += 1;
			}
			*(pR->rtName + x) = '\0';
			
			// $rs register
			while (*(pASM + i) != '$') {
				i += 1;
			}
			pR->rsName = calloc(4, sizeof(char));
			x = 0;
			while (*(pASM + i) != ',') {
				*(pR->rsName + x) = *(pASM + i);
				i += 1;
				x += 1;
			}
			*(pR->rsName + x) = '\0';
			
			// $rd register
			pR->rdName = NULL;
			
			// Imm value
			i += 1;
			while (*(pASM + i) == ' ') {
				i += 1;
			}
			char* immediate = calloc(1, sizeof(char));
			x = 0;
			while (i < (int)strlen(pASM)) {
				immediate = realloc(immediate, (sizeof(char) * (x + 1)));
				*(immediate + x) = *(pASM + i);
				i += 1;
				x += 1;
			}
			immediate = realloc(immediate, (sizeof(char) * (x + 1)));
			*(immediate + x) = '\0';
			pR->Imm = atoi(immediate);
			free(immediate);
			
			// Assign values to pR->rs, rt, rd
			pR->rs = getRegInfo(pR->rsName)->regNum;
			pR->rt = getRegInfo(pR->rtName)->regNum;
			pR->rd = 255;
			
			// Assign values to pR->IMM, RS, RT, RD
			pR->IMM = calloc(17, sizeof(char));
			x = 0;
			int y = 15;
			while (y >= 0) {
				int z = pR->Imm >> y;
				if (z & 1) {
					*(pR->IMM + x) = '1';
				}
				else {
					*(pR->IMM + x) = '0';
				}
				x += 1;
				y -= 1;
			}
			*(pR->IMM + x) = '\0';
			pR->RS = calloc(6, sizeof(char));
			pR->RT = calloc(6, sizeof(char));
			pR->RD = NULL;
			x = 0;
			while (x < (int)strlen(getRegInfo(pR->rsName)->regBinary)) {
				*(pR->RS + x) = *(getRegInfo(pR->rsName)->regBinary + x);
				*(pR->RT + x) = *(getRegInfo(pR->rtName)->regBinary + x);
				x += 1;
			}
			*(pR->RS + 5) = '\0';
			*(pR->RT + 5) = '\0';
			
			// Assign pR->Opcode, Funct values
			pR->Opcode = calloc(7, sizeof(char));
			pR->Funct = NULL;
			x = 0;
			while (x < (int)strlen(getOpcodeInfo(pR->Mnemonic)->opcode)) {
				*(pR->Opcode + x) = *(getOpcodeInfo(pR->Mnemonic)->opcode + x);
				x += 1;
				
			}
			*(pR->Opcode + 6) = '\0';
		}
		// lui instruction
		else if (strcmp(getOpcodeInfo(pR->Mnemonic)->mnemonic, "lui") == 0) {
			// $rs register
			pR->rsName = NULL;
			
			// $rt register
			while (*(pASM + i) != '$') {
				i += 1;
			}
			pR->rtName = calloc(4, sizeof(char));
			int x = 0;
			while (*(pASM + i) != ',') {
				*(pR->rtName + x) = *(pASM + i);
				i += 1;
				x += 1;
			}
			*(pR->rtName + x) = '\0';
			
			// $rd register
			pR->rdName = NULL;
			
			// Imm value
			i += 1;
			while (*(pASM + i) == ' ') {
				i += 1;
			}
			char* immediate = calloc(1, sizeof(char));
			x = 0;
			while (i < (int)strlen(pASM)) {
				immediate = realloc(immediate, (sizeof(char) * (x + 1)));
				*(immediate + x) = *(pASM + i);
				i += 1;
				x += 1;
			}
			immediate = realloc(immediate, (sizeof(char) * (x + 1)));
			*(immediate + x) = '\0';
			pR->Imm = atoi(immediate);
			free(immediate);
			
			// Assign values to pR->rs, rt, rd
			pR->rs = 0;
			pR->rt = getRegInfo(pR->rtName)->regNum;
			pR->rd = 255;
			
			// Assign values to pR->IMM, RS, RT, RD
			pR->IMM = calloc(17, sizeof(char));
			x = 0;
			int y = 15;
			while (y >= 0) {
				int z = pR->Imm >> y;
				if (z & 1) {
					*(pR->IMM + x) = '1';
				}
				else {
					*(pR->IMM + x) = '0';
				}
				x += 1;
				y -= 1;
			}
			*(pR->IMM + x) = '\0';
			pR->RS = calloc(6, sizeof(char));
			pR->RT = calloc(6, sizeof(char));
			pR->RD = NULL;
			x = 0;
			while (x < (int)strlen(getRegInfo(pR->rtName)->regBinary)) {
				*(pR->RS + x) = '0';
				*(pR->RT + x) = *(getRegInfo(pR->rtName)->regBinary + x);
				x += 1;
			}
			*(pR->RS + 5) = '\0';
			*(pR->RT + 5) = '\0';
			
			// Assign pR->Opcode, Funct values
			pR->Opcode = calloc(7, sizeof(char));
			pR->Funct = NULL;
			x = 0;
			while (x < (int)strlen(getOpcodeInfo(pR->Mnemonic)->opcode)) {
				*(pR->Opcode + x) = *(getOpcodeInfo(pR->Mnemonic)->opcode + x);
				x += 1;
				
			}
			*(pR->Opcode + 6) = '\0';
		}
		//lw instruction
		else {
			// $rt register
			while (*(pASM + i) != '$') {
				i += 1;
			}
			pR->rtName = calloc(4, sizeof(char));
			int x = 0;
			while (*(pASM + i) != ',') {
				*(pR->rtName + x) = *(pASM + i);
				i += 1;
				x += 1;
			}
			*(pR->rtName + x) = '\0';
			
			// Imm value
			while (*(pASM + i) == ' ') {
				i += 1;
			}
			i += 1;
			char* immediate = calloc(1, sizeof(char));
			x = 0;
			while (*(pASM + i) != '(') {
				immediate = realloc(immediate, (sizeof(char) * (x + 1)));
				*(immediate + x) = *(pASM + i);
				i += 1;
				x += 1;
			}
			immediate = realloc(immediate, (sizeof(char) * (x + 1)));
			*(immediate + x) = '\0';
			pR->Imm = atoi(immediate);
			free(immediate);
			i += 1;
			
			// $rs register
			pR->rsName = calloc(4, sizeof(char));
			x = 0;
			while (*(pASM + i) != ')') {
				*(pR->rsName + x) = *(pASM + i);
				i += 1;
				x += 1;
			}
			*(pR->rsName + x) = '\0';
			
			// $rd register
			pR->rdName = NULL;
			
			// Assign values to pR->rt, rs, rd
			pR->rs = getRegInfo(pR->rsName)->regNum;
			pR->rt = getRegInfo(pR->rtName)->regNum;
			pR->rd = 255;
			
			// Assign values to pR->IMM, RS, RT, RD
			pR->IMM = calloc(17, sizeof(char));
			x = 0;
			int y = 15;
			while (y >= 0) {
				int z = pR->Imm >> y;
				if (z & 1) {
					*(pR->IMM + x) = '1';
				}
				else {
					*(pR->IMM + x) = '0';
				}
				x += 1;
				y -= 1;
			}
			*(pR->IMM + x) = '\0';
			pR->RS = calloc(6, sizeof(char));
			pR->RT = calloc(6, sizeof(char));
			pR->RD = NULL;
			x = 0;
			while (x < (int)strlen(getRegInfo(pR->rtName)->regBinary)) {
				*(pR->RS + x) = *(getRegInfo(pR->rsName)->regBinary + x);
				*(pR->RT + x) = *(getRegInfo(pR->rtName)->regBinary + x);
				x += 1;
			}
			*(pR->RS + 5) = '\0';
			*(pR->RT + 5) = '\0';
			
			// Assign pR->Opcode, Funct values
			pR->Opcode = calloc(7, sizeof(char));
			pR->Funct = NULL;
			x = 0;
			while (x < (int)strlen(getOpcodeInfo(pR->Mnemonic)->opcode)) {
				*(pR->Opcode + x) = *(getOpcodeInfo(pR->Mnemonic)->opcode + x);
				x += 1;
				
			}
			*(pR->Opcode + 6) = '\0';
		}
	}
	// Special Instructions
	else {
		//printf("%s\n", "S");
		
		// $rt, $rs, $rd registers
		pR->rtName = NULL;
		pR->rsName = NULL;
		pR->rdName = NULL;
		
		// Assign values to pR->Imm, rd, rs, rt
		pR->Imm = 0;
		pR->rd = 255;
		pR->rs = 255;
		pR->rt = 255;

		// Assign values to pR->IMM, RS, RT, RD
		pR->IMM = NULL;
		pR->RS = NULL;
		pR->RT = NULL;
		pR->RD = NULL;

		// Assign pR->Opcode, Funct values
		pR->Opcode = calloc(7, sizeof(char));
		pR->Funct = calloc(7, sizeof(char));
		x = 0;
		while (x < (int)strlen(getOpcodeInfo(pR->Mnemonic)->opcode)) {
			*(pR->Opcode + x) = '0';
			*(pR->Funct + x) = *(getOpcodeInfo(pR->Mnemonic)->funct + x);
			x += 1;
			
		}
		*(pR->Opcode + 6) = '\0';
		*(pR->Funct + 6) = '\0';
	}

	//printf("rsName:  %s\n", pR->rsName);
	//printf("rtName:  %s\n", pR->rtName);
	//printf("rdName:  %s\n", pR->rdName);
	//printf("Imm:  %d\n", pR->Imm);
	//printf("rs:  %d\n", pR->rs);
	//printf("rt:  %d\n", pR->rt);
	//printf("rd:  %d\n", pR->rd);
	//printf("IMM:  %s\n", pR->IMM);
	//printf("RS:  %s\n", pR->RS);
	//printf("RT:  %s\n", pR->RT);
	//printf("RD:  %s\n", pR->RD);
	//printf("Opcode:  %s\n", pR->Opcode);
	//printf("Funct:  %s\n", pR->Funct);
	
	return pR;
}
