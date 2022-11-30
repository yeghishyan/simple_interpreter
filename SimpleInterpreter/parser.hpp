#pragma once

#include <vector>

#include "scanner.hpp"
#include "logger.hpp"
#include "ast.hpp"

class Parser {
public:
    Parser(const std::string& program);
    ~Parser() {
        if (_log != nullptr)
            delete _log;
        _log = nullptr;
    }

    ast_program* parse();

    logger* log() { return _log; }

private:
    ast_expr* parse_factor();
    ast_expr* parse_term();
    ast_expr* parse_expr();

    print_statement* parse_print();
    assignment_statement* parse_assignment();

    ast_statement* parse_statement();

private:
    Token current_token() {
        if(_position < _tokens.size())
            return _tokens[_position];
        else
            return Token(TokenType::EndOfLineToken, "", -1);   
    }

    void next_token() { 
        _position++;
    }

private:
    uint _position {};
    std::vector<Token> _tokens;

    logger* _log;
};