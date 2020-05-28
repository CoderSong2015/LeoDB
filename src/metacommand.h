//
// Created by songhaolin on 2020-05-27.
//

#ifndef SIMPLE_DATABASE_METACOMMAND_H
#define SIMPLE_DATABASE_METACOMMAND_H

#include <iostream>

using std::string;
namespace simpledb{

    enum MetaCommand {
        META_ERROR = -1,
        META_SUCCESS = 0,
        META_NOT_META_COMMAND = 1,
        META_QUIT = 2,
    };

    int JudgeMetaCommand(const string & );

}//namespace simpledb


#endif //SIMPLE_DATABASE_METACOMMAND_H
