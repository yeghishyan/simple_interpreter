#pragma once
#include <string>
#include <map>

#include "token.hpp"

class ast_node;
class ast_program;

class print_statement;
class assignment_statement;

template <typename T> 
class literal_expression;
class identifier_expression;
class binary_expression;
class unary_expression;


class visitor {
public:
    virtual void visit(ast_program*) = 0;
    virtual void visit(assignment_statement*) = 0;
    virtual void visit(print_statement*) = 0;
    
    virtual void visit(literal_expression<int>*) = 0;
    virtual void visit(literal_expression<float>*) = 0;
    virtual void visit(literal_expression<std::string>*) = 0;

    virtual void visit(identifier_expression*) = 0;
    virtual void visit(binary_expression*) = 0;
    virtual void visit(unary_expression*) = 0;
};