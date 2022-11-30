#pragma once
//TODO use move semantics
#include <vector>
#include <string>

#include "token.hpp"
#include "visitor.hpp"

class ast_node {
public:
	virtual ~ast_node() {};
	virtual void accept(visitor*) = 0;
};

class ast_expr : public ast_node {
public:
	virtual void accept(visitor*) = 0;
};

class ast_statement : public ast_node {
public:
	virtual void accept(visitor*) = 0;
};

//program
class ast_program : public ast_node {
public:
	ast_program(std::vector<ast_node*> st);
    
	void accept(visitor* v) override;
    
public:
	std::vector<ast_node*> _statements;
};

//statements
class assignment_statement : public ast_statement {
public:
	assignment_statement(std::string id, ast_expr* expr);
	~assignment_statement()  override;
        
	void accept(visitor* v) override;

public:
    std::string _id;
    ast_expr* _expr;
};

class print_statement : public ast_statement {
public:
	print_statement(ast_expr* expr);
	~print_statement()  override;
        
	void accept(visitor* v) override;

public:
    ast_expr* _expr;
};

//expressions
template <typename T>
class literal_expression : public ast_expr {
public:
	literal_expression(T value = {});
    void accept(visitor* v) override;

public:
    T _value;
};

template<typename T>
literal_expression<T>::literal_expression(T value) : _value(value) {}

template<typename T>
void literal_expression<T>::accept(visitor* v) { v->visit(this); }

/*
template<>
void literal_expression<int>::accept(visitor* v) { v->visit(this); }

template<>
void literal_expression<float>::accept(visitor* v) { v->visit(this); }

template<>
void literal_expression<std::string>::accept(visitor* v) { v->visit(this); }
*/



class identifier_expression : public ast_expr {
public:
	identifier_expression(const std::string& id);

	void accept(visitor* v) override;

public:
	std::string _id;
};

class unary_expression : public ast_expr {
public:
	unary_expression(ast_expr* expr, std::string op);

	~unary_expression() override;

	void accept(visitor* v) override;

public:
	std::string _op{};
	ast_expr* _expr{nullptr};
};

class binary_expression : public ast_expr {
public:
	binary_expression(ast_expr* left, ast_expr* right, std::string op);
	
	~binary_expression() override;

	void accept(visitor* v) override;

public:
	std::string _op{};
	ast_expr* _left{nullptr};
	ast_expr* _right{nullptr};
};