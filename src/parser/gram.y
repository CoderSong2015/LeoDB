
%code top{
#include <iostream>

int yylex();


void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
}

}
%code requires {
  #include "nodes.h"
  using simpledb::Node;
  using simpledb::StringNode;
}
%union{
       int                   ival;
       std::string           *sval;
       Node                  *node;
       std::vector<Node *>   *vec;
}
%token  TOKEN_WORD TOKEN_TABLE TOKEN_INSERT TOKEN_STRING TOKEN_INTO TOKEN_VALUE TOKEN_DOUBLE TOKEN_CREATE
%token <sval> IDENTIFIER
%token <ival> NUMBER TOKEN_INTEGER

%type <node>   ColId a_expr exprConst InsertStmt CreateStmt Column_Def
%type <vec> expr_list TableElementList

%type  <node> insert_target
%type <sval> col_name type_name table_name
%%

stmt:
    InsertStmt
    | CreateStmt
;


InsertStmt:
    TOKEN_INSERT TOKEN_INTO insert_target value_clause
    {
        Node* rv = simpledb::makeRangeVarNode($3);
        $$ = simpledb::makeInsertStmt((Node *)rv, NULL, NULL);
        printf("\tHeat turned on or off");
    }
;
insert_target:
    ColId
        {
        printf("%s", ((StringNode *)$1)->val.c_str());
        $$ = $1;
        }
;

value_clause:
     TOKEN_VALUE  expr_list
         {
             printf("go here\n");
         }
;

CreateStmt:
    TOKEN_CREATE TOKEN_TABLE table_name '(' TableElementList ')'
    {
        $$ = simpledb::makeCreateStmt(*$3, $5);
        printf("table name: %s\n", $3->c_str());
        for(auto ct:(*$5)){
            printf("column name: %s\n", ((simpledb::ColumnDefNode *)ct)->col_name.c_str());
        }
    }
;

TableElementList:
    Column_Def
     {
          printf("column name2: %s\n", ((simpledb::ColumnDefNode *)$1)->col_name.c_str());
          vector<Node *> *v = new vector<Node *>;
          v->push_back($1);
          $$ = v;

     }
     | TableElementList ',' Column_Def
     {

         $1->push_back($3);
         $$ = $1;

     }

;

//column定义 name type
Column_Def:
    col_name type_name
    {
        $$ = simpledb::makeColumnDefNode(*($1), *($2));
    }
;

type_name:
   IDENTIFIER
    {
        $$ = $1;
    }
;
col_name:
   IDENTIFIER
    {
        $$ = $1;
    }
;

table_name:
   IDENTIFIER
    {
        $$ = $1;
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
     	       $$ = $1;
     	   }
;

a_expr:
     ColId            { $$ = $1; }  /*ColId是字符串，将其制作为string node*/
     | exprConst      { $$ = $1; }  /*处理数字*/
;

/* 根据token返回不同的node*/
exprConst:
     TOKEN_INTEGER  { $$ = simpledb::makeNumNode($1, @1.first_column); }
     /*| TOKEN_DOUBLE {}*/

ColId:
     IDENTIFIER     { $$ = simpledb::makeStringNode(*$1, @1.first_column);  }
;
%%