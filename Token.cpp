#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    token_value = description;
    line_number = line;
    token_type = type;
}

std::string Token::toString() {
    return "(" + Token::TokenTypeToString() + "," + token_value + "," + std::to_string(line_number) + ")";
}

std::string Token::TokenTypeToString() {
    switch (token_type) {
        case TokenType::COLON: return "COLON"; break;
        case TokenType::COLON_DASH: return "COLON_DASH"; break;
        case TokenType::UNDEFINED: return "UNDEFINED"; break;
    }
    return "ERROR"; // a string MUST be returned by the end
}
