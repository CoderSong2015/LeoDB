//
// Created by songhaolin on 2020-05-28.
//

#include "storage_rocksdb.h"
#include <iostream>
using namespace rocksdb;
int main(){
    Options options;
    options.create_if_missing = true;
    string db_path = "storage_rocksdbkv_test";

    auto *strdb = new StorageRocksdb(&options,db_path);

    strdb->Put("haolin", "song");
    string value;
    strdb->Get("haolin", &value);
    std::cout << value << std::endl;
}