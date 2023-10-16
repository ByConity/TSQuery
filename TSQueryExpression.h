#pragma once

#include <cstddef>
#include <string>
#include <memory>
#include <vector>

namespace DB
{

namespace TSQuery
{

class TSQueryAST;
using TSQueryASTPtr = const TSQueryAST *;

class TSQueryAST
{
public:
    enum class QueryItermType
    {
        QI_VAL = 1,
        QI_OPR = 2
    };

    enum class QueryOperatorType
    {
        OP_OR = 1,  // |
        OP_AND = 2, // &
        OP_NOT = 3,  // !
        OP_UNKNOWN = 99
    };

    static std::string queryOperatorTypeToString(const QueryOperatorType & type);

    struct QueryOperator
    {
        QueryOperatorType type;

        QueryOperator(const QueryOperatorType & type_): type(type_) {};
    };

    struct QueryOperand
    {
        std::string val; 

        QueryOperand(const std::string * val_): val(*val_) {};

        QueryOperand(const std::string & val_): val(val_) {};
    };

    std::string toString() const;

private:
    QueryItermType type;
    TSQueryASTPtr left;
    TSQueryASTPtr right;
    QueryOperator query_operator;
    QueryOperand query_operand;

    // TSQueryAST only can create by TSqueryContext to avoid memory leak
    TSQueryAST(QueryOperand query_operand_);
    TSQueryAST(QueryOperator query_operator_, TSQueryASTPtr left_);
    TSQueryAST(QueryOperator query_operator_, TSQueryASTPtr left_, TSQueryASTPtr right_);

    friend class TSqueryContext;
};

class TSqueryContext
{
public:
    ~TSqueryContext()
    {
        for( size_t i = 0 ; i < expressions.size() ; i++)
        {
            delete expressions[i];
        }
        expressions.clear();
    }

    inline TSQueryASTPtr getNewTSQueryAST(const TSQueryAST::QueryOperand & query_operand_)
    {
        TSQueryASTPtr exp = new TSQueryAST(query_operand_);
        expressions.push_back(exp);
        return exp;
    }

    inline TSQueryASTPtr getNewTSQueryAST(const TSQueryAST::QueryOperator & query_operator_, TSQueryASTPtr left_)
    {
        TSQueryASTPtr exp = new TSQueryAST(query_operator_, left_);
        expressions.push_back(exp);
        return exp;
    }

    inline TSQueryASTPtr getNewTSQueryAST(const TSQueryAST::QueryOperator & query_operator_, TSQueryASTPtr left_, TSQueryASTPtr right_)
    {
        TSQueryASTPtr exp = new TSQueryAST(query_operator_, left_, right_);
        expressions.push_back(exp);
        return exp;
    }

private:
    std::vector<TSQueryASTPtr> expressions;

};

}

}
