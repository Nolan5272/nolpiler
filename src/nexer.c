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


void print_token(NolanToken nToken){

	const char *type_str;
	switch (nToken.type){
		case TOKEN_CWORD: type_str = "C language word"; break;
		case TOKEN_UWORD: type_str = "User defined word"; break;
		case TOKEN_NUM: type_str = "Number"; break;
		case TOKEN_SYMBOL: type_str = "Symbol"; break;
		default: type_str = "Undefined nToken"; break;
	}
	printf("Received: %s which is nToken [%s]", nToken.text, type_str);

}