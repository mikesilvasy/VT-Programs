#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ParseResult.h"
#include "ASMParser.h"
#include "OpcodeTable.h"
#include "RegTable.h"

char *replace_str(char *str, char *original, char *replace);
//char *charToBinary(char c);

int main(int argc, char** argv) {
	// Check that invocation is correct.
	if (argc < 3 || argc > 5) {
		printf("Invocation:  assemble <input file> <output file>\n\tor\nassemble <input file> <output file> [-symbol]\n");
		return 1;
	}

	// Opens .asm file.
	FILE* src = fopen(argv[1], "r");
	if (src == NULL) {
		printf("Unable to find file %s... exiting.\n", argv[1]);
		return 2;
	}

	// Creates and opens result .o file.
	FILE* results = fopen(argv[2], "w");
	
	char nextLine[256 + 1];
	
	// For .data section
	char **vars = calloc(1, sizeof(char*));
	int *vAddresses = calloc(1, sizeof(int));
	int vIndex = 0;
	
	char *dataBin = calloc(1, sizeof(char));
	int dataAddress = 8192;
	int dataBinIndex = 0;
	
	bool dataSection = false;
	bool firstData = true;
	// For .text section
	char **flags = calloc(1, sizeof(char*));
	int *flagPC = calloc(1, sizeof(int));
	int fIndex = 0;
	
	int textPC = 0;
	
	bool textSection = false;
	bool firstText = true;
	// -----------------------------------
	// FIRST RUN THROUGH THE .asm FILE
	// -----------------------------------
	while (fgets(nextLine, 256 + 1, src) != NULL) {
		// If you are looking through the .data section.
		if (dataSection) {
			int lengthToNullTerm = 0;
			while (nextLine[lengthToNullTerm] != '\0') {
				lengthToNullTerm += 1;
			}
			
			// If you reach a blank line, you are no longer in the .data section.
			if (lengthToNullTerm == 1) {
				dataSection = false;
			}
			// Otherwise, you are still in the .data section.
			else {
				// Gets and stores the variable name.
				int i = 0;
				char var[256 + 1] = "";
				while (nextLine[i] != ':') {
					var[i] = nextLine[i];
					i += 1;
				}
				vars = realloc(vars, (sizeof(char*) * (vIndex + 1)));
				vars[vIndex] = calloc((strlen(var) + 1), sizeof(char));
				strcpy(vars[vIndex], var);
				vAddresses = realloc(vAddresses, (sizeof(int) * (vIndex + 1)));
				// If this variable is the first variable, the first address is 0x00002000 (8192).
				if (firstData) {
					vAddresses[vIndex] = 8192;
				}
				// Otherwise, the variable address is dataAddress.
				else {
					vAddresses[vIndex] = dataAddress;
				}
				vIndex += 1;
				firstData = false;
				
				// Stores the type (.asciiz, .word) of the variable.
				while (nextLine[i] != '.') {
					i += 1;
				}
				char type[7 + 1] = "";
				int x = 0;
				while (nextLine[i] != ' ') {
					type[x] = nextLine[i];
					i += 1;
					x += 1;
				}
				
				// Saves the variables data.
				while (nextLine[i] == ' ') {
					i += 1;
				}
				char data[256 + 1] = "";
				x = 0;
				while (nextLine[i] != '\n') {
					data[x] = nextLine[i];
					i += 1;
					x += 1;
				}
				
				// If the variable is type .asciiz.
				if (type[1] == 'a') {
					int count = 1;
					// Bounds are because data contains the "" marks.
					int j;
					for (j = 4; j < (int)strlen(data) - 1; j += 4) {
						char subData3[8] = "";
						int v = 0;
						int y = 7;
						while (y >= 0) {
							int z = data[j - 3] >> y;
							if (z & 1) {
								subData3[v] = '1';
							}
							else {
								subData3[v] = '0';
							}
							v += 1;
							y -= 1;
						}
						char subData2[8] = "";
						v = 0;
						y = 7;
						while (y >= 0) {
							int z = data[j - 2] >> y;
							if (z & 1) {
								subData2[v] = '1';
							}
							else {
								subData2[v] = '0';
							}
							v += 1;
							y -= 1;
						}
						char subData1[8] = "";
						v = 0;
						y = 7;
						while (y >= 0) {
							int z = data[j - 1] >> y;
							if (z & 1) {
								subData1[v] = '1';
							}
							else {
								subData1[v] = '0';
							}
							v += 1;
							y -= 1;
						}
						char subData[8] = "";
						v = 0;
						y = 7;
						while (y >= 0) {
							int z = data[j] >> y;
							if (z & 1) {
								subData[v] = '1';
							}
							else {
								subData[v] = '0';
							}
							v += 1;
							y -= 1;
						}
						count += 4;
						
						dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
						*(dataBin + dataBinIndex) = '\n';
						dataBinIndex += 1;
						for (int w = 0; w < 8; w++) {
							dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
							*(dataBin + dataBinIndex) = *(subData3 + w);
							dataBinIndex += 1;
						}
						for (int w = 0; w < 8; w++) {
							dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
							*(dataBin + dataBinIndex) = *(subData2 + w);
							dataBinIndex += 1;
						}
						for (int w = 0; w < 8; w++) {
							dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
							*(dataBin + dataBinIndex) = *(subData1 + w);
							dataBinIndex += 1;
						}
						for (int w = 0; w < 8; w++) {
							dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
							*(dataBin + dataBinIndex) = *(subData + w);
							dataBinIndex += 1;
						}
						dataAddress += 4;
					}
					
					int numLeftOver = strlen(data) - 1 - count;
					if (numLeftOver != 0) {
						dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
						*(dataBin + dataBinIndex) = '\n';
						dataBinIndex += 1;
						for (int w = 0; w < numLeftOver; w++) {
							char subData[8] = "";
							int v = 0;
							int y = 7;
							while (y >= 0) {
								int z = data[count] >> y;
								if (z & 1) {
									subData[v] = '1';
								}
								else {
									subData[v] = '0';
								}
								v += 1;
								y -= 1;
							}
							count += 1;
							
							for (int w = 0; w < 8; w++) {
								dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
								*(dataBin + dataBinIndex) = *(subData + w);
								dataBinIndex += 1;
							}
						}
						for (int w = 0; w < 4 - numLeftOver; w++) {
							for (int v = 0; v < 8; v++) {
								dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
								*(dataBin + dataBinIndex) = '0';
								dataBinIndex += 1;
							}
						}
						dataAddress += 4;
					}
					/*else {
						for (int c = 0; c < 32; c++) {
							dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
							*(dataBin + dataBinIndex) = '0';
							dataBinIndex += 1;
						}
					}*/
				}
				// If the variable is type .word.
				else {
					bool singleVal = true;
					bool arrayComma = false;
					
					int y = 0;
					while (y < (int)strlen(data)) {
						if (data[y] == ',') {
							arrayComma = true;
							singleVal = false;
						}
						else if (data[y] == ':') {
							singleVal = false;
						}
						y += 1;
					}
					
					// If value is a single 32 bit int.
					if (singleVal) {
						int v = 0;
						int32_t k = atoi(data);
						int z = 31;
						char currDataBin[32] = "";
						while (z >= 0) {
							int m = k >> z;
							if (m & 1) {
								currDataBin[v] = '1';
							}
							else {
								currDataBin[v] = '0';
							}
							v += 1;
							z -= 1;
						}
						dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
						*(dataBin + dataBinIndex) = '\n';
						dataBinIndex += 1;
						for (int w = 0; w < v; w++) {
							dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
							*(dataBin + dataBinIndex) = currDataBin[w];
							dataBinIndex += 1;
						}
						dataAddress += 4;
					}
					// If value is an array in the format x0, x1, x2, ...
					else if (arrayComma) {
						int v = 0;
						while (v < (int)strlen(data)) {
							char currNum[256 + 1] = "";
							int w = 0;
							while (data[v] != ',' && v < (int)strlen(data)) {
								currNum[w] = data[v];
								w += 1;
								v += 1;
							}
							
							if (strcmp("", currNum) != 0) {
								w = 0;
								int32_t k = atoi(currNum);
								int z = 31;
								char currDataBin[32] = "";
								while (z >= 0) {
									int m = k >> z;
									if (m & 1) {
										currDataBin[w] = '1';
									}
									else {
										currDataBin[w] = '0';
									}
									w += 1;
									z -= 1;
								}
								
								dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
								*(dataBin + dataBinIndex) = '\n';
								dataBinIndex += 1;
								for (int k = 0; k < w; k++) {
									dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
									*(dataBin + dataBinIndex) = currDataBin[k];
									dataBinIndex += 1;
								}
								dataAddress += 4;
							}
							v += 1;
						}
					}
					// If value is an array in the format x:y.
					else {
						int v = 0;
						char num[256 + 1] = "";
						while (data[v] != ':') {
							num[v] = data[v];
							v += 1;
						}
						v += 1;
						int iNum = atoi(num);
						
						int w = 0;
						char numOfNums[256 + 1] = "";
						while (v < (int)strlen(data)) {
							numOfNums[w] = data[v];
							v += 1;
							w += 1;
						}
						int iNumOfNums = atoi(numOfNums);
						
						w = 0;
						int z = 31;
						char currDataBin[32] = "";
						while (z >= 0) {
							int m = iNum >> z;
							if (m & 1) {
								currDataBin[w] = '1';
							}
							else {
								currDataBin[w] = '0';
							}
							w += 1;
							z -= 1;
						}
						for (int k = 0; k < iNumOfNums; k++) {
							dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
							*(dataBin + dataBinIndex) = '\n';
							dataBinIndex += 1;
							for (int m = 0; m < w; m++) {
								dataBin = realloc(dataBin, sizeof(char) * (dataBinIndex + 1));
								*(dataBin + dataBinIndex) = currDataBin[m];
								dataBinIndex += 1;
							}
							dataAddress += 4;
						}
					}
				}
			}
		}
		if (textSection) {
			// If you are now in the .data section, you are no longer in the .text section.
			if (dataSection) {
				textSection = false;
			}
			// Otherwise, you are still in the .text section.
			else {
				int lengthToNullTerm = 0;
				while (nextLine[lengthToNullTerm] != '\0') {
					lengthToNullTerm += 1;
				}
				
				bool isFlag = false;
				for(int i = 0; i < (int)strlen(nextLine); i++) {
					if (nextLine[i] == ':') {
						isFlag = true;
					}
				}
				
				// If the line contains a flag/label.
				if (isFlag) {
					int i = 0;
					char flag[256 + 1] = "";
					while (nextLine[i] != ':') {
						flag[i] = nextLine[i];
						i += 1;
					}
					flags = realloc(flags, (sizeof(char*) * (fIndex + 1)));
					flags[fIndex] = calloc((strlen(flag) + 1), sizeof(char));
					strcpy(flags[fIndex], flag);
					flagPC = realloc(flagPC, (sizeof(int) * (fIndex + 1)));
					*(flagPC + fIndex) = textPC + 4;
					fIndex += 1;
				}
				// Otherwise, you add 4 to textPC.
				else if (!isFlag && !firstText && lengthToNullTerm != 1 && strstr(nextLine, "#") == NULL) {
					textPC += 4;
				}
				
				if (lengthToNullTerm != 1 && strstr(nextLine, "#") == NULL && !isFlag) {
					firstText = false;
				}
			}
		}
		
		// Determines if you are in the .data section.
		if (strlen(nextLine) >= 5 && nextLine[0] == '.' &&
			nextLine[1] == 'd' && nextLine[2] == 'a' &&
			nextLine[3] == 't' && nextLine[4] == 'a') {
			dataSection = true;
		}
		// Determines if you are in the .text section.
		if (strlen(nextLine) >= 5 && nextLine[0] == '.' &&
			nextLine[1] == 't' && nextLine[2] == 'e' &&
			nextLine[3] == 'x' && nextLine[4] == 't') {
			textSection = true;
		}
	}

	// Reopens the .asm file.
	FILE* src2 = fopen(argv[1], "r");
	if (src2 == NULL) {
		printf("Unable to find file %s... exiting.\n", argv[1]);
		return 2;
	}
	
	char asmInstruction[256 + 1];

	char *mnemonic = malloc(sizeof(char));
	char *finASMInstruction = malloc(sizeof(char));
	char *temp = malloc(sizeof(char) * 5);
	int dataLineCount = 0;
	dataSection = false;
	textSection = false;
	bool firstMnemonic = true;
	bool firstTemp = true;
	bool firstFinASMInstruction = true;
	// -----------------------------------
	// GOES THROUGH THE .asm FILE AGAIN
	// -----------------------------------
	while (fgets(asmInstruction, 256 + 1, src2) != NULL) {
		// If you are in the .data section.
		if (dataSection) {
			int lengthToNullTerm = 0;
			while (asmInstruction[lengthToNullTerm] != '\0') {
				lengthToNullTerm += 1;
			}
			
			// If you reach a blank line, you are no longer in the .data section.
			if (lengthToNullTerm == 1) {
				dataSection = false;
			}
		}
		// If you are in the .text section.
		if (textSection) {
			int lengthToNullTerm = 0;
			while (asmInstruction[lengthToNullTerm] != '\0') {
				lengthToNullTerm += 1;
			}
			
			// If you are in the .data section, you are no longer in the .text section.
			if (dataSection) {
				textSection = false;
			}
			// Otherwise, you are still in the .text section.
			else {
				if (lengthToNullTerm > 1) {
					int containsDataIndex = -1;
					int containsFlagIndex = -1;
					// **Check to see if it is last part of line (think m2test05)**
					// Determines if the current instruction contains a variable or flag/label.
					for (int i = 0; i < vIndex; i++) {
						if (strstr(asmInstruction, vars[i]) != NULL && strstr(asmInstruction, ":") == NULL) {
							containsDataIndex = i;
						}
					}
					for (int i = 0; i < fIndex; i++) {
						if (strstr(asmInstruction, flags[i]) != NULL && strstr(asmInstruction, ":") == NULL) {
							containsFlagIndex = i;
						}
					}
					
					// Stores the mnemonic in the current line.
					int x = 0;
					if (!firstMnemonic) {
						memset(mnemonic, 0, strlen(mnemonic));
					}
					else {
						firstMnemonic = false;
					}
					while (asmInstruction[x] == ' ') {
						x += 1;
					}
					int y = 0;
					while (asmInstruction[x] != ' ') {
						mnemonic = realloc(mnemonic, (sizeof(char) * (y + 1)));
						*(mnemonic + y) = asmInstruction[x];
						x += 1;
						y += 1;
					}
					mnemonic = realloc(mnemonic, (sizeof(char) * (y + 1)));
					*(mnemonic + y) = '\0';
					
					// If the line contains a variable.
					if (containsDataIndex != -1) {
						// For la instruction
						if (strcmp(mnemonic, "la") == 0 || strcmp(mnemonic, "lw") == 0) {
							if (!firstTemp) {
								memset(temp, 0, strlen(temp));
							}
							else {
								firstTemp = false;
							}
							sprintf(temp, "%d", vAddresses[containsDataIndex]);
							int replaceStrLen = strlen(replace_str(asmInstruction, vars[containsDataIndex], temp));
							int i;
							if (!firstFinASMInstruction) {
								memset(finASMInstruction, 0, strlen(finASMInstruction));
							}
							else {
								firstFinASMInstruction = false;
							}
							for (i = 0; i < replaceStrLen; i++) {
								finASMInstruction = realloc(finASMInstruction, (sizeof(char) * (i + 1)));
								*(finASMInstruction + i) = *(replace_str(asmInstruction, vars[containsDataIndex], temp) + i);
							}
							finASMInstruction = realloc(finASMInstruction, (sizeof(char) * (i + 1)));
							*(finASMInstruction + i) = '\0';
							
							for (i = 0; i < (int)strlen(finASMInstruction); i++) {
								asmInstruction[i] = *(finASMInstruction + i);
							}
							while (asmInstruction[i] != '\0') {
								asmInstruction[i] = '\0';
								i += 1;
							}
						}
					}
					// If the line contains a flag/label.
					if (containsFlagIndex != -1) {
						// For beq, bne instructions
						if (strcmp(mnemonic, "beq") == 0 || strcmp(mnemonic, "bne") == 0 ||
							strcmp(mnemonic, "j") == 0 || strcmp(mnemonic, "blez") == 0 ||
							strcmp(mnemonic, "bgtz") == 0 || strcmp(mnemonic, "blt") == 0) {
							if (!firstTemp) {
								memset(temp, 0, strlen(temp));
							}
							else {
								firstTemp = false;
							}
							sprintf(temp, "%d", ((flagPC[containsFlagIndex]) - ((dataLineCount + 1) * 4)) / 4);
							int replaceStrLen = strlen(replace_str(asmInstruction, flags[containsFlagIndex], temp));
							int i;
							if (!firstFinASMInstruction) {
								memset(finASMInstruction, 0, strlen(finASMInstruction));
							}
							else {
								firstFinASMInstruction = false;
							}
							for (i = 0; i < replaceStrLen; i++) {
								finASMInstruction = realloc(finASMInstruction, (sizeof(char) * (i + 1)));
								*(finASMInstruction + i) = *(replace_str(asmInstruction, flags[containsFlagIndex], temp) + i);
							}
							finASMInstruction = realloc(finASMInstruction, (sizeof(char) * (i + 1)));
							*(finASMInstruction + i) = '\0';
							
							for (i = 0; i < (int)strlen(finASMInstruction); i++) {
								asmInstruction[i] = *(finASMInstruction + i);
							}
							while (asmInstruction[i] != '\0') {
								asmInstruction[i] = '\0';
								i += 1;
							}
						}
					}
					
					int i = 0;
					while (i < (int)strlen(asmInstruction)) {
						if (asmInstruction[i] == '\n') {
							asmInstruction[i] = '\0';
						}
						i += 1;
					}
					
					// ------------------------------------------
					// 	WRITING TO RESULTS FILE USING ASMPARSER
					// ------------------------------------------
					if (strstr(asmInstruction, ":") == NULL && strstr(asmInstruction, "#") == NULL) {
						ParseResult* studentParse = parseASM(asmInstruction);
						printf("%s\n", asmInstruction);
						
						if (studentParse == NULL) {
							fprintf(results, "Error:  parseASM() returned NULL for %s\n", asmInstruction);
							return 1;
						}

						if (strcmp(getOpcodeInfo(studentParse->Mnemonic)->mnemonic, "lw") == 0 && strstr(asmInstruction, "(") == NULL) {
							fprintf(results, "10001100000%s%s\n", getRegInfo(studentParse->rtName)->regBinary, studentParse->IMM);
						}
						else if (getOpcodeInfo(studentParse->Mnemonic)->type == 'R') {
							// The ASMParser has the rs and rt registers swapped; you need to compensate for that.
							if(strcmp(getOpcodeInfo(studentParse->Mnemonic)->mnemonic, "srav") == 0) {
								fprintf(results, "%s%s%s%s00000%s\n", studentParse->Opcode, getRegInfo(studentParse->rtName)->regBinary,
									getRegInfo(studentParse->rsName)->regBinary, getRegInfo(studentParse->rdName)->regBinary,
									studentParse->Funct);
							}
							else {
								fprintf(results, "%s%s%s%s00000%s\n", studentParse->Opcode, getRegInfo(studentParse->rsName)->regBinary,
									getRegInfo(studentParse->rtName)->regBinary, getRegInfo(studentParse->rdName)->regBinary,
									studentParse->Funct);
							}
						}
						else if (getOpcodeInfo(studentParse->Mnemonic)->type == 'I') {
							if (getOpcodeInfo(studentParse->Mnemonic)->numArgs == 3) {
								// The ASMParser has the rs and rt registers swapped; you need to compensate for that.
								if (strcmp(getOpcodeInfo(studentParse->Mnemonic)->mnemonic, "beq") == 0 ||
									strcmp(getOpcodeInfo(studentParse->Mnemonic)->mnemonic, "bne") == 0) {
									fprintf(results, "%s%s%s%s\n", studentParse->Opcode, getRegInfo(studentParse->rtName)->regBinary,
										getRegInfo(studentParse->rsName)->regBinary, studentParse->IMM);
								}
								else if (strcmp(getOpcodeInfo(studentParse->Mnemonic)->mnemonic, "sra") == 0 ||
									strcmp(getOpcodeInfo(studentParse->Mnemonic)->mnemonic, "sll") == 0) {
									fprintf(results, "%s00000%s%s%s%s\n", studentParse->Opcode, getRegInfo(studentParse->rsName)->regBinary,
										getRegInfo(studentParse->rtName)->regBinary, studentParse->IMM, studentParse->Funct);
										//printf("%s\n", studentParse->Funct);
								}
								else if (strcmp(getOpcodeInfo(studentParse->Mnemonic)->mnemonic, "blt") == 0) {
									fprintf(results, "000000%s%s0000100000101010\n", getRegInfo(studentParse->rtName)->regBinary,
										getRegInfo(studentParse->rsName)->regBinary);
									fprintf(results, "0001010000100000%s\n", studentParse->IMM);
								}
								else {
									fprintf(results, "%s%s%s%s\n", studentParse->Opcode, getRegInfo(studentParse->rsName)->regBinary,
										getRegInfo(studentParse->rtName)->regBinary, studentParse->IMM);
								}
							}
							else if (strcmp(getOpcodeInfo(studentParse->Mnemonic)->mnemonic, "lw") == 0 ||
								strcmp(getOpcodeInfo(studentParse->Mnemonic)->mnemonic, "sw") == 0) {
								fprintf(results, "%s%s%s%s\n", studentParse->Opcode, getRegInfo(studentParse->rsName)->regBinary,
									getRegInfo(studentParse->rtName)->regBinary, studentParse->IMM);
							}
							// The ASMParser has what is supposed to be the rs register saved in the rt register; you need to compensate for that.
							else if (strcmp(getOpcodeInfo(studentParse->Mnemonic)->mnemonic, "blez") == 0 ||
								strcmp(getOpcodeInfo(studentParse->Mnemonic)->mnemonic, "bgtz") == 0) {
								fprintf(results, "%s%s00000%s\n", studentParse->Opcode, getRegInfo(studentParse->rtName)->regBinary,
									studentParse->IMM);
							}
							else { // lui, li
								fprintf(results, "%s00000%s%s\n", studentParse->Opcode, getRegInfo(studentParse->rtName)->regBinary,
									studentParse->IMM);
							}
						}
						else if (getOpcodeInfo(studentParse->Mnemonic)->type == 'J') {
							fprintf(results, "%s%s\n", studentParse->Opcode, studentParse->IMM);
						}
						else {
							if (strcmp(getOpcodeInfo(studentParse->Mnemonic)->mnemonic, "syscall") == 0) {
								fprintf(results, "%s00000000000000000000%s\n", studentParse->Opcode, studentParse->Funct);
							}
							else if (strcmp(getOpcodeInfo(studentParse->Mnemonic)->mnemonic, "la") == 0) { // la
								fprintf(results, "%s00000%s%s\n", studentParse->Opcode, getRegInfo(studentParse->rdName)->regBinary,
									studentParse->IMM);
							}
							else if (strcmp(getOpcodeInfo(studentParse->Mnemonic)->mnemonic, "move") == 0) {
								fprintf(results, "00000000000%s%s00000100001\n", getRegInfo(studentParse->rsName)->regBinary,
									getRegInfo(studentParse->rdName)->regBinary);
							}
							else {
								fprintf(results, "%s\n", studentParse->IMM);
							}
						}
						
						clearResult(studentParse);
						free(studentParse);
						dataLineCount += 1;
					}
				}
			}
		}
		
		// Determines if you are in the .data section.
		if (strlen(asmInstruction) >= 5 && asmInstruction[0] == '.' &&
			asmInstruction[1] == 'd' && asmInstruction[2] == 'a' &&
			asmInstruction[3] == 't' && asmInstruction[4] == 'a') {
			dataSection = true;
		}
		// Determines if you are in the .text section.
		if (strlen(asmInstruction) >= 5 && asmInstruction[0] == '.' &&
			asmInstruction[1] == 't' && asmInstruction[2] == 'e' &&
			asmInstruction[3] == 'x' && asmInstruction[4] == 't') {
			textSection = true;
		}
	}
	
	fprintf(results, "%s", dataBin);
	
	// Frees all used variables.
	for (int l = 0; l < vIndex; l++) {
		free(vars[l]);
	}
	free(vars);
	free(vAddresses);
	free(dataBin);
	for (int l = 0; l < fIndex; l++) {
		free(flags[l]);
	}
	free(flags);
	free(flagPC);
	free(mnemonic);
	free(finASMInstruction);
	free(temp);

	fclose(src);
	fclose(src2);
	fclose(results);
	
	//printf("TEST...");

	return 0;
}

// Replaces the string original with replace in str.
char *replace_str(char *str, char *original, char *replace) {
	static char replaceStr[256 + 1];
	char *begOrigInStr = strstr(str, original);
	strncpy(replaceStr, str, begOrigInStr-str);
	int i = 0;
	int x = begOrigInStr-str;
	while (i < (int)strlen(replace)) {
	  replaceStr[x] = *(replace + i);
	  i += 1;
	  x += 1;
	}
	replaceStr[x] = '\0';
	return replaceStr;
}

/*char *charToBinary(char c) {
	static char subData[8];
	int x = 0;
	int y = 7;
	while (y >= 0) {
		int z = c >> y;
		if (z & 1) {
			subData[x] = '1';
		}
		else {
			subData[x] = '0';
		}
		x += 1;
		y -= 1;
	}
	return subData;
}*/
