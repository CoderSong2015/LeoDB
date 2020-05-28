//
// Created by songhaolin on 2020-05-27.
//

#include "statement.h"
#include <algorithm>

namespace simpledb{

map<string, int> Statement::TypeMap = {
        {"INSERT", STATEMENT_INSERT},
        {"SELECT",STATEMENT_SELECT}
};

Status Statement::GetCommandType() {
    int pos = command_.find(" ");
//    std::cout<< "pos:"<< pos << std::endl;
//    std::cout<< "npos:"<< command_.npos << std::endl;
//    std::cout<< "command:"<< command_ << std::endl;
    if (pos == -1){
        return Status::Error();
    }

    map<string ,int>::iterator l_it;
    string first_string = command_.substr(0, pos);
    transform(first_string.begin(), first_string.end(), first_string.begin(), ::toupper);
    l_it = TypeMap.find(first_string);
    if (l_it != TypeMap.end()){
        statement_type_ = l_it->second;
        return Status::OK();
    }else{
        return Status::QueryNotExcept(command_.c_str());
    }

}

}