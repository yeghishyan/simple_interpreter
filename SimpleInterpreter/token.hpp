#pragma once
#include <string>

using uint = unsigned int;

enum class TokenType {
    BadToken,
    ErrorToken,
    EndOfLineToken,
    EndOfFile, //TODO

    Identifier,
    Equal,
    Semicolon,
    Print,
    
    IntNumber,
    RealNumber,
    String,

    PlusToken,
    MinusToken,
    Backslash,
    Asteriks,
    PowerToken,
    
    RParen,
    LParen
};

class Token {
public:
    Token() = default;
    Token(TokenType t, std::string s, uint pos) :type(t), contents(s), position(pos) {}

    uint position;
    TokenType type;
    std::string contents;    
};