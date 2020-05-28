//
// Created by songhaolin on 2020-05-27.
//

#ifndef SIMPLE_DATABASE_STATUS_H
#define SIMPLE_DATABASE_STATUS_H

#include <string>
namespace simpledb{

class Status {
 public:

    //默认构造成功的Status
    Status():code_(kSuccess), state_(nullptr){};
    ~Status(){ delete[] state_; }

    enum Code {
        kSuccess = 0,
        kError = 1,
        kQueryNotExcept = 2,
    };

    Code code() const { return code_; }

    static Status OK(){ return Status(); }

    static Status Error() { return Status(kError); }
    static Status QueryNotExcept(const char * msg) { return Status(kQueryNotExcept, msg); }

    bool ok() { return code_ == kSuccess; }

    std::string toString() const;
 private:
    Code code_;
    const char * state_;

    explicit Status(Code code)
        : code_(code) , state_(nullptr){}

    //需要重新new空间来拷贝msg
    explicit Status(Code code, const char * msg)
            : code_(code) {

        int len = strlen(msg);
        char * const result = new char [len + 1];
        memcpy(result, msg, len);
        state_ = result;
    }
};

}//namespace simpledb



#endif //SIMPLE_DATABASE_STATUS_H
