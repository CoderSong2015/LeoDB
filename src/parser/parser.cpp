//
// Created by songhaolin on 2020-05-29.
//

#include "parser.h"

namespace simpledb{
    void Parser::parserString(const std::string& s) {
        //yyscan_t	scanner;

//        core_yyset_extra(yyext, scanner);

        //yy_scan_string(s.c_str());
        //yyparse();
        std::cout <<"go here 1" << std::endl;
        struct pass_to_bison x;
        int c = yylex_init (&(x.scanner));
        std::cout <<"go here 2:" << c<< std::endl;
        yyset_extra(&x, x.scanner);
        yy_scan_string(s.c_str(), x.scanner);
        int d = yyparse ( x.scanner);
        std::cout <<"go here 2.5:" << d << std::endl;
        yylex_destroy (x.scanner);
        std::cout <<"go here 3" << std::endl;
}
}
