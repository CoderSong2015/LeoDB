//
// Created by songhaolin on 2020-05-29.
//

#ifndef SIMPLE_DATABASE_PARSER_H
#define SIMPLE_DATABASE_PARSER_H
#include <iostream>

//#include "gram.h"

extern int yyparse();
extern struct yy_buffer_state * yy_scan_string(const char * yystr);
//extern int yylex_init(void*);
namespace simpledb{

typedef void* yyscan_t;
class Parser {
 public:
    static void parserString(const std::string& s);
};

}//namespace simpledb



#endif //SIMPLE_DATABASE_PARSER_H
