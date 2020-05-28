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

rocksdb::Status StorageRocksdb::Put(const string &k, const string &value) {
    return db_->Put(rocksdb::WriteOptions(), k, value);
}

rocksdb::Status StorageRocksdb::Get(const string &k, string* value) {
    return db_->Get(rocksdb::ReadOptions(), k, value);
}
