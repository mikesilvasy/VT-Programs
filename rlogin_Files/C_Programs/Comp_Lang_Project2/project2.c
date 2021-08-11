#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char next_token;
int hex_num;

void lex(FILE * file);
void E(FILE * file);
void A(FILE * file);
void B(FILE * file);
void C(FILE * file);
bool is_hex();
int to_hex();

int main() {
	FILE * file;
	if ((file = fopen("input.txt", "r")) == NULL) {
		printf("Error: Could not find file.");
		return 1;
	}

	hex_num = -1;

	lex(file);
	while (next_token != '\r' && next_token != EOF) {
		E(file);
		lex(file);
		lex(file);
		printf(" = ");
		switch (hex_num) {
			case 10:
				printf("a\n");
				break;
			case 11:
				printf("b\n");
				break;
			case 12:
				printf("c\n");
				break;
			case 13:
				printf("d\n");
				break;
			case 14:
				printf("e\n");
				break;
			case 15:
				printf("f\n");
				break;
			default:
				printf("%i\n", hex_num);
				break;
		}
	}

	return 0;
}

void lex(FILE * file) {
	next_token = fgetc(file);
}

void E(FILE * file) {
	A(file);

	while (next_token == '|') {
		printf("|");
		int expr1 = hex_num;
		lex(file);
		A(file);
		hex_num = expr1 | hex_num;
	}
}

void A(FILE * file) {
	B(file);

	while (next_token == '^') {
		printf("^");
		int expr1 = hex_num;
		lex(file);
		B(file);
		hex_num = expr1 ^ hex_num;
	}
}

void B(FILE * file) {
	C(file);

	while (next_token == '&') {
		printf("&");
		int expr1 = hex_num;
		lex(file);
		C(file);
		hex_num = expr1 & hex_num;
	}
}

void C(FILE * file) {
	if (is_hex()) {
		printf("%c", next_token);
		hex_num = to_hex();
		lex(file);
	}
	else if (next_token == '~') {
		printf("~");
		lex(file);
		C(file);
		hex_num = 0xf - hex_num;
	}
	else if (next_token == '>') {
		printf(">");
		lex(file);
		C(file);
		hex_num = (hex_num >> 1) & 0xf;
	}
	else if (next_token == '<') {
		printf("<");
		lex(file);
		C(file);
		hex_num = (hex_num << 1) & 0xf;
	}
	else {		// Paranthesis
		if (next_token == '(') {
			printf("(");
			lex(file);
			E(file);
			if (next_token == ')') {
				printf(")");
				lex(file);
			}
		}
	}
}

bool is_hex() {
	if (next_token == '0' || next_token == '1' || next_token == '2' || next_token == '3' || next_token == '4' ||
		next_token == '5' || next_token == '6' || next_token == '7' || next_token == '8' || next_token == '9' ||
		next_token == 'a' || next_token == 'b' || next_token == 'c' || next_token == 'd' || next_token == 'e' ||
		next_token == 'f') {
		return true;
	}
	return false;
}

int to_hex() {
	switch (next_token) {
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		case 'a':
			return 10;
		case 'b':
			return 11;
		case 'c':
			return 12;
		case 'd':
			return 13;
		case 'e':
			return 14;
		default:
			return 15;
	}
}