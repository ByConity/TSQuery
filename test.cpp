#include <iostream>
#include <memory>
#include <string>
#include "TSQueryParserDriver.h"

using namespace DB::TSQuery;


int main(int argc, char* argv[])
{
    TSQueryParserDriver driver;

    if (argc != 2 )
    {
        std::cout << "need 1 argument for parse" << std::endl;
        return 0;
    }

    std::string query(argv[1]);

    auto ast  = driver.parse(query);

    std::cout << query << " : " << ast->toString() << std::endl;

    return 0;
}