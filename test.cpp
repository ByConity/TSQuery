#include <iostream>
#include <memory>
#include "TSQueryParserDriver.h"

using namespace DB::TSQuery;


int main()
{
    TSQueryParserDriver driver;

    driver.parse("(c|a   )&  ass''你好&  !  b|(caaa &   asasa*ascxs   | !!!!!!!!a ) ");


    return 0;
}