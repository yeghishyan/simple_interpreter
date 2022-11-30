#pragma once
#include <string>
#include <map>

#include "visitor.hpp"
#include "ast.hpp"

typedef struct vT {
    vT() : i(0), r(0), s("") {};
    int i;
    float r;
    std::string s;
} value_t;

class interpreter_scope {
public:
    bool already_declared(std::string);
    
    void declare(std::string, int);
    void declare(std::string, float);
    void declare(std::string, std::string);
    
    TokenType type_of(std::string);
    value_t value_of(std::string);
private:
    std::map<std::string,
             std::pair<TokenType, value_t>> symbol_table;
};

class interpreter : public visitor {
public:
    interpreter();
    ~interpreter();

    virtual void visit(ast_program*) override;
    virtual void visit(assignment_statement*) override;
    virtual void visit(print_statement*) override;
    
    virtual void visit(literal_expression<int>*) override;
    virtual void visit(literal_expression<float>*) override;
    virtual void visit(literal_expression<std::string>*) override;

    virtual void visit(identifier_expression*) override;
    virtual void visit(binary_expression*) override;
    virtual void visit(unary_expression*) override;

private:
    interpreter_scope* scope;
    
    value_t current_expression_value;
    TokenType current_expression_type;
};

std::string type_str(TokenType);