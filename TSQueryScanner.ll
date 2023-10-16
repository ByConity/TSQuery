%option C++
%option yyclass="DB::TSQuery::TSQueryScanner"
%option prefix="TSQueryScanner"
%option noyywrap
%option nodefault

/* disable after debug %option debug */
%option debug

%{

#include <string>
#include "TSQueryScanner.h"

using namespace DB::TSQuery;

#define yyterminate() return TSQueryParser::token::TOKEN_END

%}

whitespace      [ \t\n]+
token_value     [^ ()&|!\t\n]*

%%

{whitespace}        /*skip blanks and tabs*/
"("                 { return TSQueryParser::token::TOKEN_OPEN; }
")"                 { return TSQueryParser::token::TOKEN_CLOSE; }
"&"                 { return TSQueryParser::token::TOKEN_AND; }
"|"                 { return TSQueryParser::token::TOKEN_OR; }
"!"                 { return TSQueryParser::token::TOKEN_NOT; }

{token_value}       { 
    yylval->str = new std::string(yytext, yyleng); 
    return TSQueryParser::token::TOKEN_VAL; 
}


%%

