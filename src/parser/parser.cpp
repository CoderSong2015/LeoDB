//
// Created by songhaolin on 2020-05-29.
//

#include "parser.h"

namespace simpledb{
    void Parser::parserString(const std::string& s) {

        struct pass_to_bison x;
        int c = yylex_init (&(x.scanner));
        yyset_extra(&x, x.scanner);
        yy_scan_string(s.c_str(), x.scanner);
        int d = yyparse ( x.scanner);
        std::cout <<"go here:" << ((FakeStmt *)x.stmt)->type << std::endl;

        yylex_destroy (x.scanner);
        std::cout <<"go here 3" << std::endl;
}
}
