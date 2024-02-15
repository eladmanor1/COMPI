%{

/* Declarations section */
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.hpp"

%}

%x STRING_STAGE


%option yylineno
%option noyywrap
digit   		                    ([0-9])
letter  		                    ([a-zA-Z])
whitespace		                    ([\t\n\r ])
newline			                    (["\n""\r""\n\r"])
notnewline		                    ([^"\n""\r""\n\r"])
dd                                 ([a-fA-F0-9][a-fA-F0-9])
xd                                  (x[a-fA-F0-9])


%%
int                                 return INT;
byte                                return BYTE;
b                                   return B;
bool                                return BOOL;
and                                 return AND;
or                                  return OR;
not                                 return NOT;
true                                return TRUE;
false                               return FALSE;
return                              return RETURN;
if                                  return IF;
else                                return ELSE;
while                               return WHILE;
break                               return BREAK;
continue                            return CONTINUE;
;                                   return SC;
"("                                 return LPAREN;
")"                                 return RPAREN;
"{"                                 return LBRACE;
"}"                                 return RBRACE;
=                                   return ASSIGN;
[!<>=]=                             return RELOP;
[<>]                                return RELOP;
[+\-]                               return ADD_SUB;
[*/]                                return MUL_DIV;
{letter}+[0-9a-zA-Z]*               return ID;
0                                   return NUM;
[1-9]+{digit}*                      return NUM;
\"([^\n\r\"\\]|\\[rnt"\\])+\"       return STRING;
{whitespace}                        ;
.		                            {printf("Error %s\n",yytext); exit(0);}


%%
