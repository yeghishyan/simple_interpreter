#include <iostream>
#include <vector>

#include "interpreter.hpp"
#include "token.hpp"
#include "ast.hpp"

bool interpreter_scope::already_declared(std::string identifier) {
    return symbol_table.find(identifier) != symbol_table.end();
}

void interpreter_scope::declare(std::string identifier, int int_value) {
    value_t value;
    value.i = int_value;
    symbol_table[identifier] = std::make_pair(TokenType::IntNumber, value);
}

void interpreter_scope::declare(std::string identifier, float real_value) {
    value_t value;
    value.r = real_value;
    symbol_table[identifier] = std::make_pair(TokenType::RealNumber, value);
}

void interpreter_scope::declare(std::string identifier, std::string string_value) {
    value_t value;
    value.s = string_value;
    symbol_table[identifier] = std::make_pair(TokenType::String, value);
}

TokenType interpreter_scope::type_of(std::string identifier) {
    return symbol_table[identifier].first;
}

value_t interpreter_scope::value_of(std::string identifier) {
    return symbol_table[identifier].second;
}

interpreter::interpreter() {
    scope = new interpreter_scope();
}

interpreter::~interpreter() {
    if(scope != nullptr) delete scope;
    scope = nullptr;
}

void interpreter::visit(ast_program* prog) {  
    for(auto &statement : prog ->_statements)
        statement -> accept(this);
}

void interpreter::visit(assignment_statement *assign) {  
    assign->_expr->accept(this);
    
    switch(current_expression_type){
        case TokenType::IntNumber:
            scope->declare(assign->_id, current_expression_value.i);            
            break;
        case TokenType::RealNumber:
            scope->declare(assign->_id, current_expression_value.r);
            break;
        case TokenType::String:
            scope->declare(assign->_id, current_expression_value.s);
            break;
    }
}

void interpreter::visit(print_statement *print){
    print->_expr->accept(this);

    switch(current_expression_type){
        case TokenType::IntNumber:
            std::cout << current_expression_value.i << std::endl;
            break;
        case TokenType::RealNumber:
            std::cout << current_expression_value.r << std::endl;
            break;
        case TokenType::String:
            std::cout << current_expression_value.s << std::endl;
            break;        
    }
}

void interpreter::visit(literal_expression<int> *lit) {
    value_t v;
    v.i = lit->_value;
    current_expression_type = TokenType::IntNumber;
    current_expression_value = v;
}

void interpreter::visit(literal_expression<float> *lit) {
    value_t v;
    v.r = lit->_value;
    current_expression_type = TokenType::RealNumber;
    current_expression_value = v;
}

void interpreter::visit(literal_expression<std::string> *lit) {
    value_t v;
    v.s = lit->_value;
    current_expression_type = TokenType::String;
    current_expression_value = v;
}

void interpreter::visit(binary_expression *bin) {
    std::string op = bin->_op;

    bin->_left->accept(this);
    TokenType l_type = current_expression_type;
    value_t l_value = current_expression_value;

    bin->_right->accept(this);
    TokenType r_type = current_expression_type;
    value_t r_value = current_expression_value;

    value_t result_v;
    
    if(l_type == TokenType::String) {
        current_expression_type = TokenType::String;
        if(l_type != r_type)
            throw std::runtime_error("Invalid expression");
        result_v.s = l_value.s + r_value.s;
    }
    else if(l_type == TokenType::IntNumber && r_type == TokenType::IntNumber) {
        current_expression_type = TokenType::IntNumber;
        if(op == "+")       result_v.i = l_value.i + r_value.i;
        else if(op == "-")  result_v.i = l_value.i - r_value.i;
        else if(op == "*")  result_v.i = l_value.i * r_value.i;
        else if (op == "^")  result_v.i = pow(l_value.i, r_value.i);
        else if(op == "/") {
            if (r_value.i == 0) throw std::runtime_error("SemanticError: Division by zero");
            result_v.i = l_value.i / r_value.i;
        }
    }
    else {
        if (l_type == TokenType::IntNumber) l_value.r = (float)l_value.i;
        else if (r_type == TokenType::IntNumber) r_value.r = (float)r_value.i;

        current_expression_type = TokenType::RealNumber;
        if(op == "+")       result_v.r = l_value.r + r_value.r;
        else if(op == "-")  result_v.r = l_value.r - r_value.r;
        else if(op == "*")  result_v.r = l_value.r * r_value.r;
        else if (op == "^")  result_v.r = pow(l_value.r, r_value.r);
        else if(op == "/") {
            if (r_value.r == 0) throw std::runtime_error("SemanticError: Division by zero");
            result_v.r = l_value.r / r_value.r;
        }
    }
    
    current_expression_value = result_v;
}

void interpreter::visit(identifier_expression *id) {
    if(scope->already_declared(id->_id) == false) {
        throw std::runtime_error("NameError: undeclared identifier "+id->_id);
    }

    current_expression_type = scope->type_of(id->_id);
    current_expression_value = scope->value_of(id->_id);
}

void interpreter::visit(unary_expression *un) {
    un->_expr->accept(this);

    switch(current_expression_type){
        case TokenType::IntNumber:
            if(un->_op == "-")
                current_expression_value.i *= -1;
            break;
        case TokenType::RealNumber:
            if(un->_op == "-")
                current_expression_value.r *= -1;
            break;
    }
}
