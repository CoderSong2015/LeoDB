# LeoDB
A relational database based on rocksdb 

## Requires
- Bison >= 3.6.4
- Flex  >= 2.6.4
- cmake >= 3.14
- Rocksdb >= 6.6


## Catalog Table KV Set

we need a Self-increasing Table ID
key: Self-Inc_TableID
value: tableid

table metadata:
Key:  CATALOG_[DATABASE]_[TABLE_NAME]_[TABLE_ID]
Value: [col1,col1type....,PRIMARYKEY]

table index:
Key: TABLE_ID/TABLE_NAME
Value: table metadata key

## TABLE VALUE KV Set

Key： [TABLE_NAME]_[TABLE_ID]_[ROWID]
Value: [col1, col2, col3, col4]
