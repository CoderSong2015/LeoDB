//
// Created by songhaolin on 2020-05-27.
//

#ifndef SIMPLE_DATABASE_SQLHANDLER_H
#define SIMPLE_DATABASE_SQLHANDLER_H

#include <iostream>
#include "statement.h"
#include "parser/parser.h"
using std::string;
using std::cout;
using std::endl;

namespace simpledb{

    void handlesql(const string & command){
        Statement *st = new Statement(command);
//        Status ss = st->GetCommandType();
//        if (ss.ok()){
//            cout << "get commandType ok" << endl;
//        }else{
//            cout << ss.toString() << endl;
//        }

        Parser::parserString(command);
    }
}
#endif //SIMPLE_DATABASE_SQLHANDLER_H
