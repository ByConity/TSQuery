#pragma once 

#include <istream>
#include <ostream>
#include <sstream>

#include "TSQueryExpression.h"
#include "TSQueryParser.tab.hh"

#if ! defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer TSQueryScannerFlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL DB::TSQuery::TSQueryParser::token_type \
                DB::TSQuery::TSQueryScanner::getNextToken( \
                    DB::TSQuery::TSQueryParser::semantic_type* yylval)

namespace DB
{

namespace TSQuery
{

class TSQueryScanner : public TSQueryScannerFlexLexer
{
public:

    TSQueryScanner(
        std::istream* input_stream = 0, 
        std::ostream* output_stream = 0)
        : TSQueryScannerFlexLexer(input_stream, output_stream)
    {}

    TSQueryParser::token_type getNextToken(TSQueryParser::semantic_type* yylval);

};

}

}

