//
// Created by songhaolin on 2020-06-29.
//

#ifndef SIMPLE_DATABASE_ANALYZER_H
#define SIMPLE_DATABASE_ANALYZER_H

#include "../catalog.h"
#include "../parser/nodes.h"
namespace simpledb{

class Analyzer {
 public:
    Analyzer(Catalog * catalog):catalog_(catalog){}

    void analyzer(CreateStmt * stmt);
    void analyzer(InsertStmt * stmt){};
 private:
    Catalog* catalog_;
};


}



#endif //SIMPLE_DATABASE_ANALYZER_H
