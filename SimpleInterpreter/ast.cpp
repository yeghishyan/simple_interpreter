#include "ast.hpp"

ast_program::ast_program(std::vector<ast_node*> st)
	: _statements(st) {}

void ast_program::accept(visitor* v) { v->visit(this); }


assignment_statement::assignment_statement(std::string id, ast_expr* expr)
	:_id(id), _expr(expr) {}

assignment_statement::~assignment_statement() {
	if (_expr != nullptr) delete _expr;
	_expr = nullptr;
}

void assignment_statement::accept(visitor* v) { v->visit(this); }


print_statement::print_statement(ast_expr* expr)
	:_expr(expr) {}

print_statement::~print_statement() {
	if (_expr != nullptr) delete _expr;
	_expr = nullptr;
}

void print_statement::accept(visitor* v) { v->visit(this); }

identifier_expression::identifier_expression(const std::string& id)
	: _id(id) {}

void identifier_expression::accept(visitor* v) { v->visit(this); }


unary_expression::unary_expression(ast_expr* expr, std::string op)
	: _expr(expr), _op(op) {}

unary_expression::~unary_expression() {
	if (_expr != nullptr) delete _expr;
	_expr = nullptr;
}

void unary_expression::accept(visitor* v) { v->visit(this); }


binary_expression::binary_expression(ast_expr* left, ast_expr* right, std::string op)
	: _left(left), _right(right), _op(op) {}

binary_expression::~binary_expression() {
	if (_left != nullptr) delete _left;
	if (_right != nullptr) delete _right;
	_right = _left = nullptr;
}

void binary_expression::accept(visitor* v) { v->visit(this); }
