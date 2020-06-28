
%{

#include <stdio.h>
#include <string.h>
#include <string>

#include "gram.h"
int yylex(YYSTYPE * lvalp, YYLTYPE *, yyscan_t scanner);
/*
 * Set the type of YYSTYPE.
 */
#define YYSTYPE core_YYSTYPE

%}

%option noyywrap
%option reentrant
%option bison-bridge
%option extra-type="struct pass_to_bison *"

digit           [0-9]
space			[ \t\n\r\f]
integer			{digit}+

ident_start		[A-Za-z\200-\377_]
ident_cont		[A-Za-z\200-\377_0-9\$]

identifier		{ident_start}{ident_cont}*
self			[,()\[\].;\:\+\-\*\/\%\^\<\>\=]
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

create {
    return TOKEN_CREATE;
}

table {
    return TOKEN_TABLE;
}

{integer} {
    yylval_param->ival = atol(yytext + 1);
    return TOKEN_INTEGER;
}

{identifier} {
    yylval_param->sval = new std::string (yytext); return IDENTIFIER;
}


{self} {
    return yytext[0];
}
%%