project(parser)




#include_directories(. ${CMAKE_CURRENT_BINARY_DIR} )

message(${CMAKE_CURRENT_BINARY_DIR})
find_package(BISON)
find_package(FLEX)


#后面的是生成的.h .cpp类似于 lex.yy.c y.tab.c y.tab.h
BISON_TARGET(MyParser parser/gram.y ${CMAKE_CURRENT_BINARY_DIR}/gram.cpp)
#FLEX_TARGET(MyScanner lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
FLEX_TARGET(MyScanner tokenizer.l ${CMAKE_CURRENT_BINARY_DIR}/tokenizer.cpp)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)
include_directories(${CMAKE_CURRENT_BINARY_DIR})


add_library(${PROJECT_NAME}
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS})

target_include_directories(${PROJECT_NAME} PUBLIC
        parser.h)

message(${FLEX_MyScanner_OUTPUTS})

#add_executable(Foo
#        ${BISON_MyParser_OUTPUTS}
#        ${FLEX_MyScanner_OUTPUTS}
#        )
#target_link_libraries(Foo ${FLEX_LIBRARIES})