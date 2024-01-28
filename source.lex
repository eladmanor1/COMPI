%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

int showToken(char* name, enum tokentype tokenType){
    printf("%d %s %d/n",yylineno,name,yytext);
    return tokenType;
}
%}

%x COMMENT_STAGE





%option yylineno
%option noyywrap
digit   		([0-9])
letter  		([a-zA-Z])
whitespace		([\t\n ])

%%
void					    return(showToken("VOID",VOID));
int                         return(showToken("INT",INT));
byte                        return(showToken("BYTE",BYTE));
b                           return(showToken("B",B));
bool                        return(showToken("BOOL",BOOL));
and                         return(showToken("AND",AND));
or                          return(showToken("OR",OR));
not                         return(showToken("NOT",NOT));
true                        return(showToken("TRUE",TRUE));
false                       return(showToken("FALSE",FALSE));
else                        return(showToken("ELSE",ELSE));
while                       return(showToken("WHILE",WHILE));
break                       return(showToken("BREAK",BREAK));
continue                    return(showToken("CONTINUE",CONTINUE));
;                           return(showToken("SC",SC));
"("                         return(showToken("LPAREN",LPAREN));
")"                         return(showToken("RPAREN",RPAREN));
"{"                         return(showToken("LBRACE",LBRACE));
"}"                         return(showToken("RBRACE",RBRACE));
=                           return(showToken("ASSIGN",ASSIGN));
[!<>=]=                     return(showToken("RELOP",RELOP));
[<>]                        return(showToken("RELOP",RELOP));
[+-*/]                      return(showToken("BINOP",BINOP));

//                          BEGIN(COMMENT_STAGE);
<COMMENT_STAGE> [\r\n]      {BEGIN(INITIAL); return COMMENT};
<COMMENT_STAGE> \r\n        {BEGIN(INITIAL); return COMMENT};
<COMMENT_STAGE> .           printf("my name is Noa kirel");

{digit}+          			return NUM;
{whitespace};

.		                    printf("Lex doesn't know what that is!\n");

%%
