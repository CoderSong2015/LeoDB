//
// Created by songhaolin on 2020-05-29.
//

#ifndef SIMPLE_DATABASE_PARSER_H
#define SIMPLE_DATABASE_PARSER_H
#include <iostream>

//#include "gram.h"
#include "nodes.h"

typedef struct pass_to_bison {
    yyscan_t scanner;
    Node *   stmt;
} x;

#define YY_EXTRA_TYPE x*
extern int yyparse(yyscan_t scanner);
extern void yyset_extra(YY_EXTRA_TYPE user_defined , yyscan_t yyscanner);
extern struct yy_buffer_state * yy_scan_string(const char * yystr, yyscan_t yyscanner );
extern int yylex_init(yyscan_t *);
extern int yylex_destroy(void *);
//extern YY_BUFFER_STATE yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscanner);
namespace simpledb{

class Parser {
 public:
    static void parserString(const std::string& s);
};

}//namespace simpledb



#endif //SIMPLE_DATABASE_PARSER_H
