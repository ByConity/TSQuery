#include "TSQueryParserDriver.h"
#include "TSQueryExpression.h"
#include "TSQueryParser.tab.hh"
#include "TSQueryScanner.h"
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

    // For debug
    scanner->set_debug(true);
    
    TSQueryParser parser(*this);

    //For debug
    parser.set_debug_level(true);

    try
    {   
        parser.parse();
    }
    catch(...)
    {   
        std::cout << "error with parser" << std::endl;
        return nullptr;
    }

    if (result_ast!=nullptr)
    {   
        std::cout << result_ast->toString() << std::endl;
        return result_ast;
    }

    //TODO exception
    return nullptr;
}

void TSQueryParser::error(const std::string& msg)
{
    //TODO 
    throw  std::exception();
}
}


}