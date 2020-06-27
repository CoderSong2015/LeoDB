//
// Created by songhaolin on 2020-06-04.
//

#ifndef SIMPLE_DATABASE_NODES_H
#define SIMPLE_DATABASE_NODES_H

#include <iostream>
#include <vector>
using std::string;
using std::vector;

namespace simpledb{

typedef enum NodeTag {
    T_Invalid = 0,
    T_String,
    T_Int,
    T_InsertStmt,
    T_RangeVar,
    T_CreateStmt,
    T_ColDef,

}NodeTag;

typedef struct Value
{
    NodeTag		type;			/* tag appropriately (eg. T_String) */
    union
    {
        int			ival;		/* machine integer */
        char	   *sval;		/* string */
    };
} Value;

typedef struct Node{
    NodeTag		type;
}Node;

typedef struct StringNode:Node{
    NodeTag type;
    string val;
    int location;  /* token location, or -1 if unknown */
}StringNode;

inline Node * makeStringNode(const string& s, int location){
    StringNode *n = new StringNode();
    n->type = T_String;
    n->val = s;
    n->location = location;
    return n;
}

typedef struct RangeVar :Node
{
    NodeTag		type;
    string      catalogname;	/* the catalog (database) name, or NULL */
    string      schemaname;		/* the schema name, or NULL */
    string      relname;		/* the relation/sequence name */
    bool		inh;			/* expand rel by inheritance? recursively act
								 * on children? */
    char		relpersistence; /* see RELPERSISTENCE_* in pg_class.h */
    //Alias	   *alias;			/* table alias & optional column aliases */
    int			location;		/* token location, or -1 if unknown */
} RangeVar;

inline Node * makeRangeVarNode(Node* catalogname){
    RangeVar *n = new RangeVar();
    n->type = T_RangeVar;
    n->catalogname = ((StringNode *)catalogname)->val;
    return n;
}

/* ----------------------
 *		Insert Statement
 *
 * The source expression is represented by SelectStmt for both the
 * SELECT and VALUES cases.  If selectStmt is NULL, then the query
 * is INSERT ... DEFAULT VALUES.
 * ----------------------
 */
typedef struct InsertStmt:Node{
    NodeTag		       type;
    RangeVar           *relation;		/* relation to insert into */
    vector<string>	   *cols;			/* optional: names of the target columns */
    Node	   *selectStmt;		/* the source SELECT/VALUES, or NULL */

} InsertStmt;

inline Node * makeInsertStmt(Node* s, vector<string> *cols, Node *selectStmt){
    InsertStmt *n = new InsertStmt();
    n->type = T_InsertStmt;
    n->relation = (RangeVar *)s;
    n->cols = cols;
    n->selectStmt = selectStmt;
    return n;
}

typedef struct NumNode:Node{
    NodeTag type;
    Value   val;
    int location;  /* token location, or -1 if unknown */
}NumNode;

inline Node * makeNumNode(int64_t num, int location){
    NumNode *n = new NumNode();
    n->type = T_Int;
    n->val.ival = num;
    n->location = location;
    return n;
}

typedef struct CreateStmt:Node{
    NodeTag		       type;
    string             tablename;		/* relation to insert into */
    vector<Node *>	   *cols;			/* optional: names of the target columns */

} CreateStmt;

inline Node * makeCreateStmt(const string& name, vector<Node *> *cols){
    CreateStmt *n = new CreateStmt();
    n->type = T_CreateStmt;
    n->tablename = name;
    n->cols = cols;
    return n;
}

typedef struct ColumnDefNode:Node{
    NodeTag		       type;
    string             col_name;		/* relation to insert into */
    string	           type_name;			/* optional: names of the target columns */

} ColumnDefNode;

inline Node * makeColumnDefNode(const string& col_name, const string& col_type){
    ColumnDefNode *n = new ColumnDefNode();
    n->type = T_ColDef;
    n->col_name = col_name;
    n->type_name = col_type;
    return n;
}
/* location type
typedef struct YYLTYPE
{
    int first_line;
    int first_column;
    int last_line;
    int last_column;
} YYLTYPE;
*/

}// namespace simpledb
#endif //SIMPLE_DATABASE_NODES_H
