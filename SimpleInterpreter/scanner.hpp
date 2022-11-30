#pragma once
#include <string>
#include <vector>

#include "token.hpp"

class Lexer {
public:
    Lexer(const std::string& program);

    Token next_token();

private:
    char current() {
        if (_position >= _line.size())
            return '\0';
        return _line[_position];
    }

    void next() { _position++; }

private:
    uint _position{};
    std::string _line{};
};