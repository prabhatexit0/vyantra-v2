#include <stdio.h>
#include <stdlib.h>
#include "include/lexer.h"
#include "include/token.h"

int main(int argc, char* argv[]) {
	FILE* fptr;
	char codeString[10000];
	char ch;
	int i = 0;
	Token* temp = (void*)0;
	Lexer* lexer = init_lexer("");

	fptr = fopen("/home/prabhatexit0/work/privado/vy-asm/src/test.vy", "r");

	while((ch = fgetc(fptr)) != EOF)
		codeString[i++] = ch;
	codeString[i] = '\0';

	lexer->codeString = codeString;
	lexer->c = codeString[0];

	while((temp = lexer_get_next_token(lexer)) != (void*)0) {
		printf("Token type: %d  value: %s\n", temp->type, temp->value);
	}
	

	return 0;
}
