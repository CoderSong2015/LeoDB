//
// Created by songhaolin on 2020-05-27.
//

#include "status.h"

namespace simpledb{

std::string Status::toString() const{
    char tmp[30];
    const char * type;
    switch(code_){
        case kSuccess:
            return "Success";
        case kQueryNotExcept:
            type = "Query Not EXCEPT:";
            break;
        case kError:
            type = "Error:";
            break;
        default:
            snprintf(tmp, sizeof(tmp), "Unknown code(%d): ",
                     static_cast<int>(code()));
            type = tmp;
            break;
    }

    std::string result(type);
    if (state_ != nullptr){
        result.append(state_);
    }

    return result;
}
}