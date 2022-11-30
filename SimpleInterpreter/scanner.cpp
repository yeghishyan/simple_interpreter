#include "scanner.hpp"

Lexer::Lexer(const std::string& program) {
    _line = program;
}

Token Lexer::next_token() {
    if (_position >= _line.length()) {
        return Token(TokenType::EndOfLineToken, "\0", _position);
    }

    if (std::isspace((current()))) {
        next();
        return next_token();
    }

    if (std::isalpha(current())) {
        std::string identifier{};
        TokenType type = TokenType::Identifier;

        while (std::isalnum(current()) && current() != '\0') {
            identifier += current();
            next();
        }

        if (identifier == "print")
            type = TokenType::Print;

        return Token(type, identifier, _position - identifier.length());
    }

    if (current() == '\"') {
        std::string str{};

        do {
            if (current() == '\0')
                return Token(TokenType::BadToken, str, _position - str.length());

            str += current();
            next();
        } while (current() != '\"');

        next();
        return Token(TokenType::String, str + '\"', _position - str.length());
    }

    if (std::isdigit(current())) {
        std::string number{};
        TokenType type = TokenType::IntNumber;

        while (std::isdigit(current())) {
            number += current();
            next();
        }

        if (current() == '.') {
            type = TokenType::RealNumber;
            do {
                number += current();
                next();
            } while (std::isdigit(current()));
        }

        if (number[number.length() - 1] == '.') number += '0';
        return Token(type, number, _position - number.length());
    }

    std::string current_symbol;
    current_symbol = current();

    if (current() == '=')
        return Token(TokenType::Equal, current_symbol, _position++);
    if (current() == ';')
        return Token(TokenType::Semicolon, current_symbol, _position++);
    if (current() == '^')
        return Token(TokenType::PowerToken, current_symbol, _position++);

    if (current() == '+')
        return Token(TokenType::PlusToken, current_symbol, _position++);
    if (current() == '-')
        return Token(TokenType::MinusToken, current_symbol, _position++);
    if (current() == '/')
        return Token(TokenType::Backslash, current_symbol, _position++);
    if (current() == '*')
        return Token(TokenType::Asteriks, current_symbol, _position++);
    if (current() == ')')
        return Token(TokenType::RParen, current_symbol, _position++);
    if (current() == '(')
        return Token(TokenType::LParen, current_symbol, _position++);

    return Token(TokenType::BadToken, current_symbol, _position++);
}
