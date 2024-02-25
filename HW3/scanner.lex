%{

/* Declarations section */
#include <stdio.h>
#include <stdlib.h>
#include "hw3_output.hpp"
#include "hw3.hpp"
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
int                                 {yylval.type_type = new struct typeType("int"); return INT;}
byte                                {yylval.type_type = new struct typeType("byte"); return BYTE;}
b                                   return B;
bool                                {yylval.type_type = new struct typeType("bool"); return BOOL;}
and                                 return AND;
or                                  return OR;
not                                 return NOT;
true                                {yylval.bool_type = new boolType(true, yytext); return TRUE;};
false                               {yylval.bool_type = new boolType(false, yytext); return FALSE;};
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
[!=]=                               return EQUALITY;
[<>]=                               return RELATION;
[<>]                                return RELATION;
[+\-]                               return ADD_SUB;
[*/]                                return MUL_DIV;
{letter}+[0-9a-zA-Z]*               {yylval.type_ID = new typeID(yytext, unionTypes(new string("none")), "none"); return ID;}
0                                   {yylval.int_type = new struct intType(atoi(yytext)); return NUM;}
[1-9]+{digit}*                      {yylval.int_type = new struct intType(atoi(yytext)); return NUM;}
\"([^\n\r\"\\]|\\[rnt"\\])+\"       {yylval.string_type = new struct stringType(yytext); return STRING;}
"/""/"[^\r\n]*[\r|\n|\r\n]?         ;
{whitespace}                        ;
.		                            {output::errorLex(yylineno); exit(0);}


%%
