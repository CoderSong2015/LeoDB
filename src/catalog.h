//
// Created by songhaolin on 2020-06-24.
//

#ifndef SIMPLE_DATABASE_CATALOG_H
#define SIMPLE_DATABASE_CATALOG_H

#include <string>
#include <map>
#include "storage/storage_rocksdb.h"
#include "storage/storage.h"
namespace simpledb{

typedef enum{
    T_MEMORY = 0,
    T_ROCKSDB,
}StorageType;
static StorageType STORAGE_TYPE = T_ROCKSDB;

using std::string;
using std::map;

class Object{
    virtual StorageType ObjectType() = 0;
    virtual int64_t ObjectID() = 0;
    virtual string ObjectName() = 0;
};

class TableDef:Object{
 public:

    //id get from catalog::GenarateTableID
    TableDef(const string&name, int64_t id):name_(name), type_(STORAGE_TYPE), ID_(id){

    }
    StorageType ObjectType();
    int64_t ObjectID();
    string ObjectName();
 private:
    StorageType type_;
    int64_t ID_;
    const string name_;
};
class Catalog {
 public:
    explicit Catalog(Storage *st);

    void FindTableByID();
    Object* FindTableByName(const string& table_name);
    void AddTable(TableDef *td);
    int64_t GenarateTableID();
 private:
    Storage * storage_;
    // Initialize when constructing from storage
    std::atomic<int64_t> max_table_id_;
    // 未来做一个table的LRU
    // map<string, MemoryTableDef *> table_;
};

static Catalog* catalog;
}//namespace simpledb

#endif //SIMPLE_DATABASE_CATALOG_H
