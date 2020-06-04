
%{

#include <iostream>
#include "nodes.h"
using simpledb::Node;
int yylex();


void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
}

%}
%union{
       int                   ival;
       std::string           *sval;

       Node                  *node;
       std::vector<Node *>   *vec;
}
%token  TOKEN_WORD TOKEN_TABLE TOKEN_INSERT TOKEN_STRING TOKEN_INTO TOKEN_VALUE TOKEN_DOUBLE
%token <sval> IDENTIFIER
%token <ival> NUMBER TOKEN_INTEGER

%type <node>   ColId a_expr exprConst
%type <vec> expr_list

%type  <node> insert_target
%%

stmt:
    InsertStmt
;


InsertStmt:
    TOKEN_INSERT TOKEN_INTO insert_target value_clause
    {
        printf("\tHeat turned on or off");
    }
;
insert_target:
    ColId
        {
        printf("\t 1111 ");
        $$ = $1;
        }
;

value_clause:
     TOKEN_VALUE '(' expr_list ')'
         {
             printf("go here\n");
         }
;

/*将表达式制作成一个node list*/
expr_list:
     a_expr
         {
             vector<Node *> v;
             v.push_back($1);
             $$ = &v;
         }
     | expr_list ',' a_expr
           {
               $1->push_back($3);
     	       $$ = $1
     	   }
;

a_expr:
     ColId            { $$ = $1 }  /*ColId是字符串，将其制作为string node*/
     | exprConst      { $$ = $1 }  /*处理数字*/
;

/* 根据token返回不同的node*/
exprConst:
     TOKEN_INTEGER  { $$ = simpledb::makeNumNode($1, @1.first_column) }
     /*| TOKEN_DOUBLE {}*/

ColId:
     IDENTIFIER     { $$ = simpledb::makeStringNode(*$1, @1.first_column)  }
;
%%