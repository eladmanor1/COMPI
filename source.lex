%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

%}

%x COMMENT_STAGE





%option yylineno
%option noyywrap
digit   		([0-9])
letter  		([a-zA-Z])
whitespace		([\t\n ])

%%
void					    return VOID;
int                         return INT;
byte                        return BYTE;
b                           return B;
bool                        return BOOL;
and                         return AND;
or                          return OR;
not                         return NOT;
true                        return TRUE;
false                       return FALSE;
else                        return ELSE;
while                       return WHILE;
break                       return BREAK;
continue                    return CONTINUE;
;                           return SC;
(                           return LPAREN;
)                           return RPAREN;
{                           return LBRACE;
}                           return RBRACE;
=                           return ASSIGN;
[!<>=]=                     return RELOP;
[<>]                        return RELOP;
[+-*/]                      return BINOP;
[+-*/]                      return COMMENT;

//                          BEGIN(COMMENT_STAGE);
<COMMENT_STAGE> [\r\n]      BEGIN(INITIAL);
<COMMENT_STAGE> \r\n        BEGIN(INITIAL);
<COMMENT_STAGE> .           printf("my name is Noa kirel");





{digit}+          			return NUM;
{whitespace};

.		                    printf("Lex doesn't know what that is!\n");

%%
