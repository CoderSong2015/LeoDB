//
// Created by songhaolin on 2020-06-24.
//

#include "catalog.h"

namespace simpledb{

int64_t TableDef::ObjectID() {
    return ID_;
}

string TableDef::ObjectName() {
    return name_;
}

StorageType TableDef::ObjectType() {
    return STORAGE_TYPE;
}

Catalog::Catalog(Storage* storage_) {
    string id_value;
    simpledb::Status s = storage_->Get("Self-Inc_TableID", &id_value);
    //这里有问题,应该是Status::IsNotFound()为true时才设置这个key
    if (!s.ok()){
        id_value = "0";
        simpledb::Status s = storage_->Put("Self-Inc_TableID", id_value);
        max_table_id_.store(0);
    }else{
        max_table_id_.store(std::stol(id_value));
    }

    // set max_table_id_ next value
    max_table_id_.fetch_add(1);

}
Object* Catalog::FindTableByName(const std::string &table_name) {

}

void Catalog::AddTable(simpledb::TableDef *td) {

}

int64_t Catalog::GenarateTableID() {
    return max_table_id_.fetch_add(1);
}

}// namespace simpledb
