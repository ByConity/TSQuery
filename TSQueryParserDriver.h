#pragma once

#include "TSQueryExpression.h"
#include "TSQueryParser.tab.hh"
#include "TSQueryScanner.h"


#include <istream>
#include <string>
#include <memory>

namespace DB
{

namespace TSQuery
{

class TSQueryParserDriver
{

public:
    TSQueryASTPtr parse(const std::string & input_string);

private:
    std::unique_ptr<TSQueryScanner> scanner;
    TSQueryASTPtr result_ast;
    TSqueryContext ts_context;
    friend class TSQueryParser;

};

}

}