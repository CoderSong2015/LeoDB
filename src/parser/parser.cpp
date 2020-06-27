//
// Created by songhaolin on 2020-05-29.
//

#include "parser.h"

namespace simpledb{
    void Parser::parserString(const std::string& s) {

        yy_scan_string(s.c_str());
        yyparse();
}
}
