
%{
#define YYSTYPE char *
#include <stdio.h>
#include <string.h>

//extern void yyerror(char* s);
//
%}

%token  TOKEN_WORD TOKEN_TABLE TOKEN_INSERT TOKEN_STRING


%%

commands:
    | commands command
;

command: heat_switch
;

heat_switch:
    TOKEN_INSERT TOKEN_STRING
    {
        printf("\tHeat turned on or off %s\n",$2);
    }
;
%%