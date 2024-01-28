%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

%}

%option yylineno
%option noyywrap
digit   		([0-9])
letter  		([a-zA-Z])
whitespace		([\t\n ])

%%
<<<<<<< HEAD

{digit}+          			return NUM;
{letter}+					return WORD;
{letter}+@{letter}+\.com	return EMAIL;
void					    return VOID;
=======
{void }					    return VOID;
{digit}+          			return NUM;
{letter}+					return WORD;
{letter}+@{letter}+\.com	return EMAIL;
>>>>>>> 6683ea52887bb3e952e266262cea5f7e67e15a70
{letter}+@{letter}+\.com	return EMAIL;
{whitespace}				;
.		                    printf("Lex doesn't know what that is!\n");

%%

