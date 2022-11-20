#include <stdio.h>
#include <stdlib.h>
#include "include/lexer.h"
#include "include/token.h"

int main(int argc, char* argv[]) {
	int i = 0;
	char codeString[10000];
	char ch;
	FILE* fptr = fopen(argv[1], "r");
	Token* temp = (void*)0;
	Lexer* lexer = (void*)0;

	if(fptr == NULL) {
		printf("Error while opening the file!");
	}

	while((ch = fgetc(fptr)) != EOF)
		codeString[i++] = ch;
	codeString[i] = '\0';

	lexer = init_lexer(codeString);
	printf("code String\n %s", lexer->codeString);
	while((temp = lexer_get_next_token(lexer)) != (void*)0) {
		printf("Token type: %d  value: %s\n", temp->type, temp->value);
	}

	return 0;
}
