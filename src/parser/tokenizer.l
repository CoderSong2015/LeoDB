
%{

#include <stdio.h>
#include <string.h>
#include <string>

#include "gram.h"

%}

%option noyywrap
digit           [0-9]
space			[ \t\n\r\f]
integer			{digit}+

ident_start		[A-Za-z\200-\377_]
ident_cont		[A-Za-z\200-\377_0-9\$]

identifier		{ident_start}{ident_cont}*

%%

insert {
    return TOKEN_INSERT;
}

into {
    return TOKEN_INTO;
}

values {
    return TOKEN_VALUE;
}

{integer} {
    yylval.ival = atol(yytext + 1);
    return TOKEN_INTEGER;
}

{identifier} {
    yylval.sval = new std::string (yytext); return IDENTIFIER;
}

%%