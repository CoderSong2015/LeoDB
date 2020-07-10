//
// Created by songhaolin on 2020-05-28.
//

#ifndef SIMPLE_DATABASE_STORAGE_H
#define SIMPLE_DATABASE_STORAGE_H

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "../status.h"

using std::string;
class Storage {
 public:

    //Storage(){};
    virtual ~Storage() = default;
    //void Init();
    virtual simpledb::Status Get(const string& k, string* value) = 0;
    virtual simpledb::Status Put(const string& k, const string& value) = 0;

 //private:

};


#endif //SIMPLE_DATABASE_STORAGE_H
