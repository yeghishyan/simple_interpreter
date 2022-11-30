#include "parser.hpp"

#include <stdexcept>
#include <iostream>

Parser::Parser(const std::string& program) {
    Lexer lex(program);
    _log = new logger(program);

    while (true) {
        auto token = lex.next_token();

        if (token.type == TokenType::EndOfLineToken) {
            _tokens.push_back(token);
            break;
        }
        if (token.type == TokenType::BadToken) {
            _log->push("|Unexpected symbol {" + token.contents + "}", token.position);
            continue;
        }

        _tokens.push_back(token);
        //std::cout<<"Token ["<<token.pos()<<"]: "<<token.contents<<std::endl;    
    }
}

ast_program* Parser::parse() {
    auto st = parse_statement();
    std::vector<ast_node*> sts;
    sts.push_back(st);

    auto prog = new ast_program(sts);

    while (current_token().type != TokenType::EndOfLineToken) {
        _log->push("Unexpected token {" + current_token().contents + "}", current_token().position);
        next_token();
    }
    
    if (!_log->is_empty()) {
        throw std::runtime_error("Lexical error");
    }

    return prog;
}

ast_expr* Parser::parse_factor() {
    //<literal>
    if (current_token().type == TokenType::IntNumber) {
        int value = std::stoi(current_token().contents);
        next_token();
        return new literal_expression<int>(value);
    }
    if (current_token().type == TokenType::RealNumber) {
        float value = std::stof(current_token().contents);

        next_token();
        return new literal_expression<float>(value);
    }
    if (current_token().type == TokenType::String) {
        //  TODO 
        //  replace double-slash,\n,\t
        std::string str = current_token().contents;
        str = str.substr(1, str.length() - 2);

        next_token();
        return new literal_expression<std::string>(str);
    }

    //<identifier>
    if (current_token().type == TokenType::Identifier) {
        std::string id = current_token().contents;

        next_token();
        return new identifier_expression(id);
    }

    //<sub-expression>
    if (current_token().type == TokenType::LParen) {
        next_token();
        auto node = parse_expr();

        if (current_token().type != TokenType::RParen)
            _log->push("Expected ')'", current_token().position);
        else
            next_token();

        return node;
    }

    //<unary>
    if (current_token().type == TokenType::PlusToken ||
        current_token().type == TokenType::MinusToken) {
        auto op = current_token().contents;
        next_token();
        return new unary_expression(parse_expr(), op);
    }

    _log->push("Expected <expression>", current_token().position);
    throw std::runtime_error("Syntax error");
}

ast_expr* Parser::parse_term() {
    auto left_node = parse_factor();

    while (current_token().type == TokenType::Asteriks || 
           current_token().type == TokenType::Backslash ||
           current_token().type == TokenType::PowerToken) {
        auto op = current_token().contents;
        next_token();
        left_node = new binary_expression(left_node, parse_factor(), op);
    }

    return left_node;
}

ast_expr* Parser::parse_expr() {
    auto left_node = parse_term();

    while (current_token().type == TokenType::PlusToken || current_token().type == TokenType::MinusToken) {
        auto op = current_token().contents;
        next_token();
        left_node = new binary_expression(left_node, parse_term(), op);
    }

    return left_node;
}

print_statement* Parser::parse_print() {
    ast_expr* expr = parse_expr();

    //if (current_token().type != TokenType::Semicolon)
    //  _log->push("Expected ';' after print statement", current_token().position);

    next_token();
    return new print_statement(expr);
}

assignment_statement* Parser::parse_assignment() {
    std::string id{};
    ast_expr* expr;

    if (current_token().type != TokenType::Identifier) {
        _log->push("Expected <identifier>", current_token().position);
        throw std::runtime_error("Syntax error");
    }
    id = current_token().contents;
    next_token();

    if (current_token().type != TokenType::Equal) {
        _log->push("Expected '=' after identifier {" + id + "}", current_token().position);
        throw std::runtime_error("Syntax error");
    }

    next_token();
    expr = parse_expr();

    //if (current_token().type != TokenType::Semicolon)
    //  _log->push("Expected ';' after print statement", current_token().position);

    next_token();
    return new assignment_statement(id, expr);
}

ast_statement* Parser::parse_statement() {
    if (current_token().type == TokenType::Identifier) {
        return parse_assignment();
    }

    if (current_token().type == TokenType::Print) {
        //skip 'print' keyword
        next_token();
        return parse_print();
    }
    else {
        //
        return parse_print();
    }


    //_log->push("Invalid statement starting with '" + current_token().contents + "'", current_token().position);
    //throw std::runtime_error("Syntax error");
}
