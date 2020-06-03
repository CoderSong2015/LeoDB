
%{
#define YYSTYPE char *
#include <stdio.h>
#include <string.h>

int yylex();


void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
}
%}

%token  TOKEN_WORD TOKEN_TABLE TOKEN_INSERT TOKEN_STRING TOKEN_INTO

%%

commands:
    | commands command
;

command: heat_switch
;

heat_switch:
    TOKEN_INSERT TOKEN_INTO
    {
        printf("\tHeat turned on or off %s\n",$2);
    }
;
%%