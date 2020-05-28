//
// Created by songhaolin on 2020-05-28.
//

#ifndef SIMPLE_DATABASE_STORAGE_ROCKSDB_H
#define SIMPLE_DATABASE_STORAGE_ROCKSDB_H

#include "storage.h"
#include <iostream>
class StorageRocksdb: public Storage {

 public:
    StorageRocksdb():Storage(){};
    ~StorageRocksdb(){ delete db_; };
    void Init();

    StorageRocksdb(rocksdb::Options *op, const string & db_path): options_(op), db_path_(db_path), db_(nullptr){
        Init();
    }


    rocksdb::Status Get(const string& k, string* value);
    rocksdb::Status Put(const string& k, const string& value);
    rocksdb::DB *GetDB(){ return db_; }
 private:
    string db_path_;
    rocksdb::DB *db_;
    rocksdb::Options* options_;
};


#endif //SIMPLE_DATABASE_STORAGE_ROCKSDB_H
