cmake_minimum_required(VERSION 3.14)
project(simple_database)

set(CMAKE_CXX_STANDARD 17)
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -W -Wregister -Wunused-parameter")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -W -Wregister -Wunused-parameter")

add_subdirectory(src/parser)

link_directories($ENV{ROCKSDB_PATH})
message("rocksdb path: " $ENV{ROCKSDB_PATH})
#MESSAGE( $ENV{ROCKSDB_PATH})
INCLUDE_DIRECTORIES($ENV{ROCKSDB_PATH}/db)
INCLUDE_DIRECTORIES($ENV{ROCKSDB_PATH}/include)
INCLUDE_DIRECTORIES(parser)
#include_directories(${CMAKE_CURRENT_BINARY_DIR})

list(APPEND THIRDPARTY_LIBS librocksdb.a)
set(SOURCE_NOMAIN
        src/status.h
        src/metacommand.h
        src/metacommand.cpp
        src/sqlhandler.h
        src/statement.cpp
        src/statement.h
        src/status.cpp
        src/storage/storage.cpp
        src/storage/storage.h
        src/storage/storage_rocksdb.cpp
        src/storage/storage_rocksdb.h
        src/parser/parser.h
        src/parser/parser.cpp
        src/parser/gram.cpp
        src/parser/gram.h
        src/parser/tokenizer.cpp

        )
list(APPEND SOURCE src/main.cpp ${SOURCE_NOMAIN})
add_executable(simple_database ${SOURCE} ${FLEX_LIBRARIES})
ADD_DEPENDENCIES(simple_database parser)

list(APPEND LIBS ${THIRDPARTY_LIBS})

#可执行文件要包括子目录的
target_link_libraries(simple_database ${LIBS} )

set(TESTS
        src/storage/rocksdb_test.cpp
        src/storage/storage_rocksdb_test.cpp
        )

set(TEST_EXES ${TESTS})

foreach(sourcefile ${TEST_EXES})
    get_filename_component(exename ${sourcefile} NAME_WE)
    add_executable(${exename} ${sourcefile} ${SOURCE_NOMAIN})
    target_link_libraries(${exename} ${LIBS})
endforeach(sourcefile ${TEST_EXES})



