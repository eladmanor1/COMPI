%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

int showToken(char* name, enum tokentype tokenType){
    printf("%d %s %s\n",yylineno,name,yytext);
    return tokenType;
}
%}

%x STRING_STAGE


%option yylineno
%option noyywrap
digit   		                    ([0-9])
letter  		                    ([a-zA-Z])
whitespace		                    ([\t\n ])
newline			                    (["\n""\r""\n\r"])
notnewline		                    ([^"\n""\r""\n\r"])


%%
void			                    return(showToken("VOID",VOID));
int                                 return(showToken("INT",INT));
byte                                return(showToken("BYTE",BYTE));
b                                   return(showToken("B",B));
bool                                return(showToken("BOOL",BOOL));
and                                 return(showToken("AND",AND));
or                                  return(showToken("OR",OR));
not                                 return(showToken("NOT",NOT));
true                                return(showToken("TRUE",TRUE));
false                               return(showToken("FALSE",FALSE));
else                                return(showToken("ELSE",ELSE));
while                               return(showToken("WHILE",WHILE));
break                               return(showToken("BREAK",BREAK));
continue                            return(showToken("CONTINUE",CONTINUE));
;                                   return(showToken("SC",SC));
"("                                 return(showToken("LPAREN",LPAREN));
")"                                 return(showToken("RPAREN",RPAREN));
"{"                                 return(showToken("LBRACE",LBRACE));
"}"                                 return(showToken("RBRACE",RBRACE));
=                                   return(showToken("ASSIGN",ASSIGN));
[!<>=]=                             return(showToken("RELOP",RELOP));
[<>]                                return(showToken("RELOP",RELOP));
[+\-*/]                             return(showToken("BINOP",BINOP));
{letter}+[{digit}{letter}]*         return(showToken("ID",ID));
0                                   return(showToken("NUM",NUM));
[1-9]+{digit}*                      return(showToken("NUM",NUM));
"/""/"({notnewline})*{newline}	    return(showToken("COMMENT", COMMENT));
\"                                  BEGIN(STRING_STAGE);
{whitespace}                        ;
.		                            printf("Lex doesn't know what that is!\n");



<STRING_STAGE>["\" "\n" "\r"]      {BEGIN(INITIAL); return(showToken("ERROR", STRING))};
<STRING_STAGE>\"                   {BEGIN(INITIAL); return(showToken("STRING", STRING));}
<STRING_STAGE>.                     ;
%%

