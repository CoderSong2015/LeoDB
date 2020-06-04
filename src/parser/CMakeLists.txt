project(parser)

#include_directories(. ${CMAKE_CURRENT_BINARY_DIR} )



message(${CMAKE_CURRENT_LIST_DIR})
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)


#后面的是生成的.h .cpp类似于 lex.yy.c y.tab.c y.tab.h
BISON_TARGET(MyParser ${CMAKE_CURRENT_LIST_DIR}/gram.y ${CMAKE_CURRENT_LIST_DIR}/gram.cpp DEFINES_FILE ${CMAKE_CURRENT_LIST_DIR}/gram.h)
FLEX_TARGET(MyScanner tokenizer.l ${CMAKE_CURRENT_LIST_DIR}/tokenizer.cpp)

message(${BISON_MyParser_INPUT})
message(${FLEX_MyScanner_INPUT})
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)
#include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(parser)

add_library(${PROJECT_NAME}
        parser.cpp
        nodes.cpp
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS})

target_include_directories(${PROJECT_NAME} PUBLIC
        parser.h
        nodes.h
        )

message(${FLEX_MyScanner_OUTPUTS})

#add_executable(Foo
#        ${BISON_MyParser_OUTPUTS}
#        ${FLEX_MyScanner_OUTPUTS}
#        )
#target_link_libraries(Foo ${FLEX_LIBRARIES})