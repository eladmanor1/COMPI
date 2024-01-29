%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"
#include <stdlib.h>

char str[1024];
int index1 = 0;

int hexToDecimal(char* str);

int showToken(char* name, enum tokentype tokenType){
    printf("%d %s %s\n",yylineno,name,yytext);
    return tokenType;
}

int showStringToken(){
    int j=0;
    printf("%d %s %s\n",yylineno,"STRING",str);
    return STRING;
}

void addEscapeCharToString(){
    switch(yytext[1]){
        case ('n'):
            str[index1]='\n'; index1++;break;
        case ('r'):
            str[index1]='\r';index1++;break;
        case ('t'):
            str[index1]='\t';index1++;break;
        case ('0'):
            str[index1]='\0';index1++;break;
        case ('\"'):
            str[index1]='\"';index1++;break;
        case ('\\'):
            str[index1]='\\';index1++;break;
        default:
            printf("debug - we are screwed");
    }
}
bool checkIfHexaInRange(int ascVal){
    if((ascVal >= 0x20 && ascVal <= 0x7E) || (ascVal == 0x09) || (ascVal == 0x0d) || (ascVal == 0x0a)) {
        return true;
    }
    return false;
}

bool addHexaToString(){
	int ascVal = hexToDecimal(&yytext[2]);
    if(!checkIfHexaInRange(ascVal))
        return false;
	str[index1] = ascVal;
	index1++;
    return true;
}


int hexToDecimal(char hex[2]) {
    int result = 0;
    for(int i=0;i<2;i++) {
        char currentChar = *hex;
        // Convert hex character to its decimal equivalent
        int digit;
        if (currentChar >= '0' && currentChar <= '9') {
            digit = currentChar - '0';
        } else if (currentChar >= 'a' && currentChar <= 'f') {
            digit = 10 + currentChar - 'a';
        } else if (currentChar >= 'A' && currentChar <= 'F') {
            digit = 10 + currentChar - 'A';
        } else {
            fprintf(stderr, "Error: Invalid character in hex string: %c\n", currentChar);
            return 0;
        }
        result = result * 16 + digit; // Multiply by 16 and add the new digit
        hex++;
    }
    return result;
}

void resetString() {
    for (int i = 0; i < 1024; i++) {
        str[i] = '\0';
    }
    index1 = 0;
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
dd                                 ([a-fA-F0-9][a-fA-F0-9])
xd                                  (x[a-fA-F0-9])


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
"/""/"({notnewline})*{newline}	    {printf("%d %s %s\n",yylineno,name,"//"); return COMMENT;}
{letter}+[{digit}{letter}]*         return(showToken("ID",ID));
0                                   return(showToken("NUM",NUM));
[1-9]+{digit}*                      return(showToken("NUM",NUM));
\"                                  {BEGIN(STRING_STAGE); resetString();}
{whitespace}                        ;
.		                            {printf("ERROR %s\n",yytext); exit(0);}

<STRING_STAGE>{
\"                      {BEGIN(INITIAL); return(showStringToken());}
"\n"			        {BEGIN(INITIAL); printf("Error unclosed string\n"); exit(0);}
"\r"                    {BEGIN(INITIAL); printf("Error unclosed string\n"); exit(0);}
\\[\"nrt0\\]            addEscapeCharToString();
\\x{dd}                 {if(!addHexaToString()){BEGIN(INITIAL); printf("rule 1Error undefined escape sequence %s\n", yytext + 1); exit(0);}}
\\x[^{whitepsace}\"][^{whitepsace}\"]                    {BEGIN(INITIAL); printf("rule 2Error undefined escape sequence %s\n", yytext + 1); exit(0);}
\\x[^{whitepsace}\"]                    {BEGIN(INITIAL); printf("rule 3Error undefined escape sequence %s\n", yytext + 1); exit(0);}
\\[^\"nrt0\\{whitespace}]           {BEGIN(INITIAL); printf("rule 4Error undefined escape sequence %c\n", yytext[1]); exit(0);}
\\{whitespace}                      {BEGIN(INITIAL); printf("Error unclosed string\n"); exit(0);}

.			            {str[index1] =  *yytext; index1++;}
}
%%

