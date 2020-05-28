//
// Created by songhaolin on 2020-05-27.
//

#ifndef SIMPLE_DATABASE_STATEMENT_H
#define SIMPLE_DATABASE_STATEMENT_H

#include <iostream>
#include <map>
#include "status.h"

using std::string;
using std::map;

namespace simpledb{

enum StatementType{
    STATEMENT_INSERT = 0,
    STATEMENT_SELECT = 10,
};

class Statement {
 public:
     Statement(const string & command) : command_(command){
         //GetCommandType(command_);
     }

     Status GetCommandType();
 private:
     static map<string, int> TypeMap;
     string command_;
     int statement_type_;
};

}



#endif //SIMPLE_DATABASE_STATEMENT_H
