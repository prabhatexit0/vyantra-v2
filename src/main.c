#include <stdio.h>
#include <stdlib.h>
#include "include/lexer.h"
#include "include/token.h"
#include "include/parser.h"
#include "include/yasm.h"

void dfs(Ast* root) {
	int i = 0;
	if(!root) return;
	printf("Type of root: %d\n", root->type);
	printf("Children size: %d\n", root->children_size);
	printf("----\n");
	for(i = 0; i < root->children_size; i++) {
		dfs(root->children[i]);
	}
}

int main(int argc, char* argv[]) {
	int i = 0;
	char codeString[10000];
	char ch;
	FILE* fptr = fopen(argv[1], "r");
	Token* temp = (void*)0;
	Lexer* lexer = (void*)0;
	Parser* parser = (void*)0;
	Ast* root = (void*)0;

	if(fptr == NULL) {
		printf("Error while opening the file!");
	}

	while((ch = fgetc(fptr)) != EOF)
		codeString[i++] = ch;
	codeString[i] = '\0';

	lexer = init_lexer(codeString);

	printf("Token Stream: ->\n");
	fflush(stdin);
	while((temp = lexer_get_next_token(lexer))->type != token_eof) {
		printf("Token type: %d  value: %s\n", temp->type, temp->value);
	}
	printf("--------\n\n");

	free(lexer);

	lexer = init_lexer(codeString);

	parser = init_parser(lexer);
	root = parser_parse_block(parser);
	printf("code String\n%s", lexer->codeString);
	dfs(root);

	return 0;
}
