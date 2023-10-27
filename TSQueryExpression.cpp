#include "TSQueryExpression.h"
#include "TSQueryException.h"


namespace  DB
{

namespace TSQuery 
{

std::string TSQueryAST::queryOperatorTypeToString(const QueryOperatorType & type)
{
    switch (type) 
    {
        case QueryOperatorType::OP_OR:
            return " | " ;
        case QueryOperatorType::OP_AND:
            return " & " ;
        case QueryOperatorType::OP_NOT:
            return " ! " ;
        default:
            throw TSQueryException("UNKNOWN Operator Type");
    }
}

TSQueryAST::TSQueryAST(
    QueryOperand query_operand_)
    : type(QueryItermType::QI_VAL)
    , left(nullptr)
    , right(nullptr)
    , query_operator(QueryOperatorType::OP_UNKNOWN)
    , query_operand(std::move(query_operand_))
{
}


TSQueryAST::TSQueryAST(
    QueryOperator query_operator_, 
    TSQueryASTPtr left_)
    : type(QueryItermType::QI_OPR)
    , left(std::move(left_))
    , right(nullptr)
    , query_operator(std::move(query_operator_))
    , query_operand("")
{
    if ( query_operator.type != QueryOperatorType::OP_NOT)
    {
        throw TSQueryException("Only NOT  Operator have one left node");
    }

}


TSQueryAST::TSQueryAST(
    QueryOperator query_operator_, 
    TSQueryASTPtr left_, 
    TSQueryASTPtr right_)
    : type(QueryItermType::QI_OPR)
    , left(std::move(left_))
    , right(std::move(right_))
    , query_operator(std::move(query_operator_))
    , query_operand("")
{
}

std::string TSQueryAST::toString() const
{
    if (type == QueryItermType::QI_VAL)
    {
        return " " + query_operand.val + " ";
    }
    else 
    {
        std::string result;
        result = " ( " + queryOperatorTypeToString(query_operator.type);

        if ( left != nullptr)
        {
            result += left->toString();
        }
        
        if ( right != nullptr)
        {
            result += right->toString();
        }

        result += " ) ";

        return result;
    }
    
}


TSQueryAST::QueryItermType TSQueryAST::getQueryItermType() const
{
    return type;
}

TSQueryAST::QueryOperator  TSQueryAST::getQueryOperator() const
{
    if (type == QueryItermType::QI_VAL)
    {
        throw TSQueryException("Node is not a operator node.");
    }
    return query_operator;
}

TSQueryAST::QueryOperand   TSQueryAST::getQueryOperand() const
{
    if (type == QueryItermType::QI_OPR)
    {
        throw TSQueryException("Node is not a operand node.");
    }

    return query_operand;
}

TSQueryASTPtr  TSQueryAST::getLeftNode() const
{
    return left;
}

TSQueryASTPtr  TSQueryAST::getRightNode() const
{
    return right;
}

}

}
