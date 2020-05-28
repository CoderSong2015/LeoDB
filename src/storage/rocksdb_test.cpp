//
// Created by songhaolin on 2020-05-28.
//

#include <cstdio>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"

//#include "db/db_impl/db_impl.h"
//#include "db/db_impl/db_impl_readonly.h"

using namespace rocksdb;

std::string kDBPath = "simplekv_test";
void test(){

    Options options;
    options.create_if_missing = true;
    DB* db;
    Status s;

    s = DB::Open(options, kDBPath, &db);
    assert(s.ok());

    // create column family
    ColumnFamilyHandle *cf;
    s = db->CreateColumnFamily(ColumnFamilyOptions(), "new_cf", &cf);
    assert(s.ok());
    // close DB
    delete cf;
    delete db;


    std::vector<ColumnFamilyDescriptor> column_families;
    // have to open default column family
    column_families.push_back(ColumnFamilyDescriptor(
            kDefaultColumnFamilyName, ColumnFamilyOptions()));
    // open the new one, too
    column_families.push_back(ColumnFamilyDescriptor(
            "new_cf", ColumnFamilyOptions()));
    std::vector<ColumnFamilyHandle*> handles;
    Options options1;
    //options1.max_total_wal_size = 100;
    s = DB::Open(options1, kDBPath, column_families, &handles, &db);
    assert(s.ok());

    s = db->Put(WriteOptions(), handles[0], "primary1-11", "value11");
    std::string value;
    s = db->Get(ReadOptions(), handles[0],"primary1-11", &value);
    std::cout << "read value: "<< value << std::endl;
}

int main() {

    test();
    return 0;
}