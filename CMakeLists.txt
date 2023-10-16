cmake_minimum_required(VERSION 3.17)

SET(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

execute_process(COMMAND flex -i TSQueryScanner.ll WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
execute_process(COMMAND bison -d -v TSQueryParser.yy WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test test.cpp TSQueryParserDriver.cpp TSQueryExpression.cpp TSQueryParser.tab.cc lex.TSQueryScanner.cc)


