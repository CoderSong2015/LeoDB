//
// Created by songhaolin on 2020-05-27.
//

#include "metacommand.h"
namespace simpledb{

int JudgeMetaCommand(const string & command){
    if (command == "quit"){
        return META_QUIT;
    }

    return META_NOT_META_COMMAND;
}





}//namespace simpledb
