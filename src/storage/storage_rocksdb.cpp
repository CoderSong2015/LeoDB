//
// Created by songhaolin on 2020-05-28.
//

#include "storage_rocksdb.h"

void StorageRocksdb::Init() {
    rocksdb::Status s = rocksdb::DB::Open(*options_, db_path_, &db_);
    if (!s.ok()){
        std::cout << s.ToString()<< std::endl;
        exit(1);
    }
}

simpledb::Status StorageRocksdb::Put(const string &k, const string &value) {
    rocksdb::Status s =  db_->Put(rocksdb::WriteOptions(), k, value);
    if (s.ok()){
        return simpledb::Status();
    }
    return simpledb::Status::Error();
}

simpledb::Status StorageRocksdb::Get(const string &k, string* value) {
    rocksdb::Status s =  db_->Get(rocksdb::ReadOptions(), k, value);
    if (s.ok()){
        return simpledb::Status();
    }
    return simpledb::Status::Error();
}
