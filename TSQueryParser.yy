%language "c++"

/* disable after debug %debug */
%debug

%define api.namespace { DB::TSQuery }
%define parser_class_name {TSQueryParser}

%code requires
{
    #include "TSQueryExpression.h"
    namespace DB{ namespace TSQuery{ class TSQueryParserDriver; } }
}

%union
{   
    const TSQueryAST* ast;
    std::string* str;    
}

%parse-param { class TSQueryParserDriver& dirver}

%token <str> TOKEN_VAL
%token TOKEN_OPEN TOKEN_CLOSE
%token TOKEN_AND TOKEN_OR
%token TOKEN_NOT
%token TOKEN_END 0

%type <ast> exp term

%left TOKEN_OR
%left TOKEN_AND
%right TOKEN_NOT

%{

#include "TSQueryScanner.h"
#include "TSQueryParserDriver.h"

#undef yylex
#define yylex dirver.scanner->getNextToken
    
    
%}


%%

tsquery:
    | exp TOKEN_END { dirver.result_ast = $1; }
;

exp: term { $$ = $1; }
    | exp TOKEN_AND exp { $$ = dirver.ts_context.getNewTSQueryAST( TSQueryAST::QueryOperator(TSQueryAST::QueryOperatorType::OP_AND), $1, $3 ); }
    | exp TOKEN_OR exp { $$ = dirver.ts_context.getNewTSQueryAST( TSQueryAST::QueryOperator(TSQueryAST::QueryOperatorType::OP_OR), $1, $3 ); }
;

term: TOKEN_VAL { $$ = dirver.ts_context.getNewTSQueryAST( TSQueryAST::QueryOperand($1) ); }
    | TOKEN_NOT term { $$ = dirver.ts_context.getNewTSQueryAST( TSQueryAST::QueryOperator(TSQueryAST::QueryOperatorType::OP_NOT), $2 ); }
    | TOKEN_OPEN exp TOKEN_CLOSE { $$ = $2; }
;

%%

