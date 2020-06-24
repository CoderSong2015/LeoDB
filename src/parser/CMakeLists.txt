project(parser)

#include_directories(. ${CMAKE_CURRENT_BINARY_DIR} )

#OnmacOS,searchHomebrewforkeg-onlyversionsofBisonandFlex.Xcodedoes
#notprovidenewenoughversionsforustouse.
if(CMAKE_HOST_SYSTEM_NAMEMATCHES"Darwin")
    execute_process(
            COMMANDbrew--prefixbison
            RESULT_VARIABLEBREW_BISON
            OUTPUT_VARIABLEBREW_BISON_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(BREW_BISONEQUAL0ANDEXISTS"${BREW_BISON_PREFIX}")
        message(STATUS"FoundBisonkeginstalledbyHomebrewat${BREW_BISON_PREFIX}")
        set(BISON_EXECUTABLE"${BREW_BISON_PREFIX}/bin/bison")
    endif()

    execute_process(
            COMMANDbrew--prefixflex
            RESULT_VARIABLEBREW_FLEX
            OUTPUT_VARIABLEBREW_FLEX_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(BREW_FLEXEQUAL0ANDEXISTS"${BREW_FLEX_PREFIX}")
        message(STATUS"FoundFlexkeginstalledbyHomebrewat${BREW_FLEX_PREFIX}")
        set(FLEX_EXECUTABLE"${BREW_FLEX_PREFIX}/bin/flex")
    endif()
endif()

message("CURRENT LIST: " ${CMAKE_CURRENT_LIST_DIR})
find_package(BISON 3.6.4 REQUIRED)
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