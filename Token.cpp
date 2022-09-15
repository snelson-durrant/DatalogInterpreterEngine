#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    token_value = description;
    line_number = line;
    token_type = type;
}

std::string Token::ToString() {
    return "(" + Token::TokenTypeToString() + ",\"" + token_value + "\"," + std::to_string(line_number) + ")";
}

std::string Token::TokenTypeToString() {
    switch (token_type) {
        case TokenType::COLON: return "COLON";
        case TokenType::COLON_DASH: return "COLON_DASH";
        case TokenType::ADD: return "ADD";
        case TokenType::COMMA: return "COMMA";
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::MULTIPLY: return "MULTIPLY";
        case TokenType::PERIOD: return "PERIOD";
        case TokenType::Q_MARK: return "Q_MARK";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::UNDEFINED: return "UNDEFINED";
        case TokenType::EOF_TOKEN: return "EOF";
    }
    return "ERROR"; // a string MUST be returned by the end
}
