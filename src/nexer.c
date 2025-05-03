#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum { 
	TOKEN_CWORD,
	TOKEN_UWORD,
	TOKEN_NUM,
	TOKEN_SYMBOL,
	TOKEN_UNDEF
} TokenType;

typedef struct {
	TokenType type;
	char text[64];
} NolanToken;

typedef struct {
	NolanToken *ntokens;
	int pos;
	int count;
}Parser;




void print_token(NolanToken nToken){

	const char *type_str;
	switch (nToken.type){
		case TOKEN_CWORD: type_str = "C language word"; break;
		case TOKEN_UWORD: type_str = "User defined word"; break;
		case TOKEN_NUM: type_str = "Number"; break;
		case TOKEN_SYMBOL: type_str = "Symbol"; break;
		default: type_str = "Undefined nToken"; break;
	}

	//printf("Received: %s which is nToken [%s]", nToken.text, type_str);
	
	FILE *output_file = fopen("output.txt", "a");
    if (!output_file) {
        fprintf(stderr, "Error w/file.\n");
        exit(1);
    }

    fprintf(output_file, "Received: %s which is nToken [%s]\n", nToken.text, type_str);

    fclose(output_file);
}

int is_cword(const char *str){

	if(strcmp(str, "int") == 0 || strcmp(str, "return") == 0){
		return 1;
	}else{
		return 0;
	}

}

int main(){

	FILE *file = fopen("test.c", "r");
	if (!file){
		printf("error w/file");
		return 1;
	}

	NolanToken nToken;
	char rChar;

	const int MAX_TOKENS = 1024;
	NolanToken n_tokens[MAX_TOKENS];
	int tokenCount = 0;


	while ((rChar = fgetc(file)) != EOF){
		if (isspace(rChar)) continue;

		if (isalpha(rChar) || rChar =='_'){
			int i = 0;
			nToken.text[i] = rChar;
			i++;

			while (isalnum(rChar = fgetc(file)) | rChar == '_'){
				nToken.text[i] = rChar;
				i++;
			}

			nToken.text[i] = '\0';
			ungetc(rChar, file);

			if (is_cword(nToken.text)){
				nToken.type = TOKEN_CWORD;
			}
			else{
				nToken.type = TOKEN_UWORD;
			}
			
			print_token(nToken);

			if (tokenCount < MAX_TOKENS){
				n_tokens[tokenCount] = nToken;
				tokenCount++;
			}
			else{
				printf("exceeds token count");
			}
		}

		else if(isdigit(rChar)){
			int i = 0;
			nToken.text[i] = rChar;
			i++;
			while (isdigit(rChar = fgetc(file))){
				nToken.text[i] = rChar;
				i++;
			}
			nToken.text[i] = '\0';
			ungetc(rChar, file);

			nToken.type = TOKEN_NUM;
			print_token(nToken);

			if (tokenCount < MAX_TOKENS){
				n_tokens[tokenCount] = nToken;
				tokenCount++;
			}
			else{
				printf("exceeds token count");
			}

		}

		else if(ispunct(rChar)){
			if (rChar == '#'){
				int i = 0;
				nToken.text[i] = rChar;
				i++;
				while(isalnum(rChar = fgetc(file)) | rChar == '_'){
					//int i = 0;
					nToken.text[i] = rChar;
					i++;
				}
				nToken.text[i] = '\0';
				ungetc(rChar, file);
				nToken.type = TOKEN_CWORD;
			}else {
			nToken.text[0] = rChar;
			nToken.text[1] = '\0';
			nToken.type = TOKEN_SYMBOL;
			}

			print_token(nToken);

			if (tokenCount < MAX_TOKENS){
				n_tokens[tokenCount] = nToken;
				tokenCount++;
			}
			else{
				printf("exceeds token count");
			}
		}

	}

	fclose(file);
	return 0;
}