%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"
#include <string>

char str[1024];
int index = 0;
int showToken(char* name, enum tokentype tokenType){
    printf("%d %s %s\n",yylineno,name,yytext);
    return tokenType;
}

int showStringToken(){
    printf("%d %s %s\n",yylineno,"STRING",str);
    return STRING;
}

void addEscapeCharToString(){
    switch(yytext[1]){
        case ("n"):
            str+="\n";
        case ("r"):
            str+="\r";
        case ("t"):
            str+="\t";
        case ("0"):
            str+="\0";
        case ("\""):
            str+="\"";
        case ("\\"):
            str+="\\";
        default:
            printf("debug - we are screwed");

    }
}
void checkIfHexaInRange(){
    int ascVal = stoi(yylex[2],0,16);
    if(ascVal < 0x20 || ascVal > 0x7E || ascVal != 0x09 || ascVal != 0x0d || ascVal != 0x0a) {
        printf("debug - error of hexa");
        BEGIN(INITIAL);
        return;
    }

}

void addHexaTostring(){
	int ascVal = stoi(yylex[2],0,16);
	str[index] = ascVal;
	index++;
}

void resetString(){
	for(int i= 0; i <1024; i++){
	str[i] = "\0";
	}
	index = x;
%}

%x STRING_STAGE


%option yylineno
%option noyywrap
digit   		                    ([0-9])
letter  		                    ([a-zA-Z])
whitespace		                    ([\t\n ])
newline			                    (["\n""\r""\n\r"])
notnewline		                    ([^"\n""\r""\n\r"])
xdd                                 (x[a-fA-F0-9][a-fA-F0-9])


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
return                              return(showToken("RETURN",RETURN));
if                                  return(showToken("IF",IF));
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
"/""/"({notnewline})*{newline}	    return(showToken("COMMENT", COMMENT));
{letter}+[{digit}{letter}]*         return(showToken("ID",ID));
0                                   return(showToken("NUM",NUM));
[1-9]+{digit}*                      return(showToken("NUM",NUM));
\"                                  {BEGIN(STRING_STAGE); resetString();}
{whitespace}                        ;
.		                            printf("Lex doesn't know what that is\n");
<STRING_STAGE>{
\"                      {BEGIN(INITIAL); return(showStringToken());}
"\n"			        {BEGIN(INITIAL); return(showToken("ERROR backslash n", STRING));}
"\r"                    {BEGIN(INITIAL); return(showToken("ERROR backslsh r", STRING));}
\\[\"nrt0\\]            addEscapeCharToString();
\\{xdd}                 {checkIfHexaInRange(); addHexaToString();}
\\                      {BEGIN(INITIAL); return(showToken("ERROR backslsh ", STRING));}
.			{str[index] =  yytext; index++;}
}
%%
