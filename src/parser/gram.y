
%code top{
#include <iostream>

}


%code requires {
  #include "nodes.h"
  #include "parser.h"
  extern int yylex(YYSTYPE * lvalp, YYLTYPE * yylloc, yyscan_t scanner);
  extern YY_EXTRA_TYPE yyget_extra  (yyscan_t yyscanner);
}
%define api.pure full
%parse-param {yyscan_t yyscanner}
%lex-param   {yyscan_t yyscanner}
%locations
%union{
       core_YYSTYPE          core_yystype;
       int                   ival;
       std::string           *sval;
       Node                  *node;
       std::vector<Node *>   *vec;
}

%{

void yyerror(YYLTYPE* yylloc, yyscan_t x,char const *msg){
    std::cout << msg << std::endl;
}
%}
%token  TOKEN_WORD TOKEN_TABLE TOKEN_INSERT TOKEN_STRING TOKEN_INTO TOKEN_VALUE TOKEN_DOUBLE TOKEN_CREATE
%token <sval> IDENTIFIER
%token <ival> NUMBER TOKEN_INTEGER

%type <node>   ColId a_expr exprConst InsertStmt CreateStmt Column_Def stmt
%type <vec> expr_list TableElementList

%type  <node> insert_target
%type <sval> col_name type_name table_name
%%


stmtblock:	stmt
			{
				yyget_extra(yyscanner)->stmt = $1;
				printf("stmt type: %d\n", ((Node *)$1)->type);
			}
;

stmt:
    InsertStmt
    | CreateStmt
;


InsertStmt:
    TOKEN_INSERT TOKEN_INTO insert_target value_clause
    {
        Node* rv = makeRangeVarNode($3);
        $$ = makeInsertStmt((Node *)rv, NULL, NULL);
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
        $$ = makeCreateStmt(*$3, $5);
        printf("table name: %s\n", $3->c_str());
        for(auto ct:(*$5)){
            printf("column name: %s\n", ((ColumnDefNode *)ct)->col_name.c_str());
        }
    }
;

TableElementList:
    Column_Def
     {
          printf("column name2: %s\n", ((ColumnDefNode *)$1)->col_name.c_str());
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
        $$ = makeColumnDefNode(*($1), *($2));
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
     TOKEN_INTEGER  { $$ = makeNumNode($1, @1.first_column); }
     /*| TOKEN_DOUBLE {}*/

ColId:
     IDENTIFIER     { $$ = makeStringNode(*$1, @1.first_column);  }
;
%%