#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/lexer.h"
#include "include/token.h"
#include "include/parser.h"
#include "include/yasm.h"
#include "include/yantra.h"

void dfs(Ast* root) {
	int i = 0;
	if(!root) return;
	printf("Type of AST Node: %d\n", root->type);
	if(root->identifier)
		printf("Identifier of AST Node: %s\n", root->identifier);
	printf("Number of Children: %d\n", root->children_size);
	if(root->type == ast_func) {
		printf("func block children: %d\n", root->block->children_size);
	}
	printf("----\n");


	for(i = 0; i < root->children_size; i++) {
        dfs(root->children[i]);
	}
    if(root->block != NULL) {
        for(i = 0; i < root->block->children_size; i++) {
            dfs(root->block->children[i]);
        }
    }
}  

void verbose_stdout(char* source_code) {
    int i = 0;
	Token* temp = NULL;
	Parser* parser = NULL;
	Ast* root = NULL;
    Lexer* lexer = init_lexer(source_code);

	printf("Token Stream: \n");
    printf("=====\n");
	while((temp = lexer_get_next_token(lexer))->type != token_eof) {
		printf("Token type: %d  value: %s\n", temp->type, temp->value);
	}
	printf("--------\n\n");

	free(lexer);

	lexer = init_lexer(source_code);

	parser = init_parser(lexer);
	root = parser_parse_block(parser);
    printf("Source Code: \n");
    printf("=====\n");
    printf("%s\n", lexer->source_code);
	printf("--------\n\n");

    printf("AST Traversal: \n");
    printf("=====\n");
	dfs(root);
	printf("--------\n\n");

    printf("Instructions in HEX: \n");
    printf("=====\n");

	int length_of_ins = root->children_size;
	InstrContainer* instr_cont = yas_visit_block(root);
	for(i = 0; i < instr_cont->size; i++) {
		printf("Instruction: %x\n", instr_cont->instructions[i]);	
	}
	printf("--------\n\n");

    printf("Yantra VM:\n");
    printf("=====\n");
	yantra_run(instr_cont->instructions, instr_cont->size);
	printf("--------\n\n");
}

void non_verbose_stdout(char* source_code) {
    Lexer* lexer = init_lexer(source_code);
	Parser* parser = NULL;
	Ast* root = NULL;
	lexer = init_lexer(source_code);
	parser = init_parser(lexer);
	root = parser_parse_block(parser);
	int length_of_ins = root->children_size;
	InstrContainer* instr_cont = yas_visit_block(root);
	yantra_run(instr_cont->instructions, instr_cont->size);
}

int main(int argc, char* argv[]) {
    int i = 0;
    char ch;
	char source_code[10000];
	FILE* fptr = fopen(argv[1], "r");

	if(fptr == NULL) {
		printf("Error while opening the file!");
	}

	while((ch = fgetc(fptr)) != EOF)
		source_code[i++] = ch;
	source_code[i] = '\0';
    
    if(argc > 2 && !strcmp("-v", argv[2])) 
        verbose_stdout(source_code);
    else 
        non_verbose_stdout(source_code);

	return 0;
}
