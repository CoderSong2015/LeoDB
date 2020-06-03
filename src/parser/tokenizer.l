
%{
#define YYSTYPE char *
#include <stdio.h>
#include <string.h>
#include "gram.h"

%}

%option noyywrap

space			[ \t\n\r\f]
integer			{digit}+

ident_start		[A-Za-z\200-\377_]
ident_cont		[A-Za-z\200-\377_0-9\$]

identifier		{ident_start}{ident_cont}*

%%

insert {
    yylval = strdup(yytext); return TOKEN_INSERT;
}

into {
    yylval = strdup(yytext); return TOKEN_INTO;
}

%%