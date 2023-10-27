#include "TSQueryParserDriver.h"
#include "TSQueryExpression.h"
#include "TSQueryParser.tab.hh"
#include "TSQueryScanner.h"
#include "TSQueryException.h"
#include <cstddef>
#include <exception>
#include <iostream>
#include <istream>
#include <sstream>


namespace DB
{

namespace TSQuery
{
TSQueryASTPtr TSQueryParserDriver::parse(const std::string & input_string)
{
    std::istringstream input_stream(input_string);
    scanner = std::make_unique<TSQueryScanner>(&input_stream);


    
    TSQueryParser parser(*this);

    //For debug
    //scanner->set_debug(true);
    //parser.set_debug_level(true);

    try
    {   
        parser.parse();
    }
    catch(TSQueryException &e)
    {
        throw e;
    }
    catch(...)
    {
        throw  TSQueryException("Error on parse.");
        return nullptr;
    }

    if (result_ast!=nullptr)
    {
        return result_ast;
    }

    throw  TSQueryException("Error on parse.");
}

void TSQueryParser::error(const std::string& msg)
{
    throw  TSQueryException("Error on parse : " + msg );
}
}


}