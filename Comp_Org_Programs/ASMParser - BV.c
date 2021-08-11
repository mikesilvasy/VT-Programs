#include <inttypes.h>  // I used functions from these Standard modules in
#include <string.h>    // my solution; you may or may not need all of them,
#include <stdlib.h>    // and you might need additional ones, depending on
#include <stdio.h>     // your approach to the problem.
#include <assert.h>
#include "opCode.h"
#include "mipsData.h"
#include "ASMParser.h"
#include "intToBinary.h"

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


ParseResult* parseASM(const char* const pASM) {
	int i = 0, j = 0;

	const IData* data2;
	const IData* data3;
	ParseResult* result = malloc(sizeof(ParseResult));
	result->ASMInstruction = calloc(strlen(pASM)+1, sizeof(char)); 
	result->Mnemonic = calloc(1, sizeof(char));
	for(j = 0; j <strlen(pASM); j++){
		*(result->ASMInstruction+j) = *(pASM + j);
	}

	while(*(pASM+i) != ' '){
		result->Mnemonic = realloc(result->Mnemonic, sizeof(char)*(i+1));
		*(result->Mnemonic+i) = *(pASM+ i);
		i++;
	}
		result->Mnemonic = realloc(result->Mnemonic,sizeof(char)*(i+1));
		*(result->Mnemonic+i) = '\0';
	const OpData* data;
	data = Search(result->Mnemonic);
	int16_t intImm;
	int count = 0;
	if(data->immediate){
		//used when there are 3 instructions and an immediate is one of them
		if(data->numInstructs == 3){
			result->rtName = calloc(4,sizeof(char));
			result->rsName = calloc(4,sizeof(char));
			char* imm = calloc(1, sizeof(char));
			while(*(pASM+i) != '$'){
			i++;
			}
		while(*(pASM+i) != ','){
			*(result->rtName + count) = *(pASM+i);
			i++;
			count++;
		}
		while(*(pASM+i) != '$'){
		i++;
		}
		count = 0;
		while(*(pASM+i) != ','){
		*(result->rsName + count) = *(pASM+i);
		i++;
		count++;
		}
		while(*(pASM+i) == ' ' || *(pASM+i) == ','){
		i++;
		}
		count = 0;
		while(*(pASM+i) != '\0'){
			imm = realloc(imm, sizeof(char)*(count+2));
			*(imm + count) = *(pASM + i);
			*(imm + (count+1)) = '\0';
			i++;
			count++;
		}
		intImm = atoi(imm);
		result->rdName = NULL;
		result->Imm = intImm;
		result->Opcode = calloc(strlen(data->opCode)+1, sizeof(char));
		strcpy(result->Opcode,data->opCode);
		result->Funct = NULL;
		result->IMM = calloc(17, sizeof(char));
		convertNum(intImm, result->IMM);
		data1 = Find(result->rtName);
		result->RT = calloc(strlen(data1->regValueTwos)+1, sizeof(char));
		result->rt = data1->regValue;
		strcpy(result->RT,data1->regValueTwos);
		data2 = Find(result->rsName);
		result->RS = calloc(strlen(data2->regValueTwos)+1, sizeof(char));
		result->rs = data2->regValue;
		strcpy(result->RS,data2->regValueTwos);
		result->rd = 255;
		result->RD = NULL;
		free(imm);
	}
	//used when there are 2 instructions and an immediate is one of them
		else if(data->numInstructs == 2){
			result->rtName = calloc(4, sizeof(char));
			char* imm = calloc(1, sizeof(char));
			while(*(pASM+i) != '$'){
				i++;
			}
			while(*(pASM+i) != ','){
				*(result->rtName + count) = *(pASM+i);
				i++;
				count++;
			} 
			i++;
			while(*(pASM+i) == ' '){
			i++;
			}
			count = 0;
			while(*(pASM+i) != '\0'){
				if(*(pASM + i) == '('){
					i++;
					count = 0;
					result->rsName = calloc(4, sizeof(char));
					while(*(pASM+i) != ')'){
					*(result->rsName + count) = *(pASM + i);
					i++;
					count++;
				}
					break;
				}
				imm = realloc(imm, sizeof(char)*(count+2));
				*(imm + count) = *(pASM + i);
				*(imm + count+1) = '\0';
				i++;
				count++;
			}
			
			intImm = atoi(imm);
			result->rdName = NULL;
			result->Imm = intImm;
			result->Opcode = calloc(strlen(data->opCode)+1, sizeof(char));
			strcpy(result->Opcode, data->opCode);
			result->Funct = NULL;
			result->IMM = calloc(17, sizeof(char));
			convertNum(intImm, result->IMM);
			data1 = Find(result->rtName);
			result->RT = calloc(strlen(data1->regValueTwos)+1, sizeof(char));
			result->rt = data1->regValue;
			strcpy(result->RT, data1->regValueTwos);
			if(*(result->Mnemonic+1) == 'w'){
				data2 = Find(result->rsName);
				result->RS = calloc(strlen(data2->regValueTwos)+1, sizeof(char));
				result->rs = data2->regValue;
				strcpy(result->RS, data2->regValueTwos);
				
			}
			else{
			result->RS = calloc(6, sizeof(char));
			result->rsName = NULL;
			result->rs = 0;
			strcpy(result->RS, "00000");
			}
			result->rd = 255;
			result->RD = NULL;
			free(imm);
		}
	}
	else{
		//used when there are 3 instructions and no immediate(R-Type)
		result->rdName = calloc(4, sizeof(char));
		result->rsName = calloc(4, sizeof(char));
		result->rtName = calloc(4, sizeof(char));
		while(*(pASM+i) != '$'){
		i++;
		}
		while(*(pASM+i) != ','){
			*(result->rdName + count) = *(pASM + i);
			i++;
			count++;
		}
		while(*(pASM+i) != '$'){
			i++;
		}
		count = 0;
		while(*(pASM+i) != ','){
			*(result->rsName + count) = *(pASM+i);
			i++;
			count++;
		}
		while(*(pASM+i) != '$'){
			i++;
		}
		count = 0;
		while(*(pASM+i) != '\0'){
			*(result->rtName + count) = *(pASM+i);
			i++;
			count++;
		}
		intImm= 0;
		result->Imm = intImm;
		result->Opcode = calloc(strlen(data->opCode)+1, sizeof(char));
		result->Funct = calloc(strlen(data->funct)+1, sizeof(char));
		strcpy(result->Opcode,data->opCode);
		strcpy(result->Funct,data->funct);
		result->IMM = NULL;
		data1 = Find(result->rdName);
		result->RD = calloc(strlen(data1->regValueTwos)+1, sizeof(char));
		result->rd = data1->regValue;
		strcpy(result->RD, data1->regValueTwos);
		data2 = Find(result->rsName);
		result->RS = calloc(strlen(data2->regValueTwos)+1, sizeof(char));
		result->rs = data2->regValue;
		strcpy(result->RS,data2->regValueTwos);
		data3 = Find(result->rtName);	
		result->RT = calloc(strlen(data3->regValueTwos)+1, sizeof(char));
		result->rt = data3->regValue;
		strcpy(result->RT,data3->regValueTwos);
	}
	
   return result;
}
