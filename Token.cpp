#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    token_value = description;
    line_number = line;
    token_type = type;
}

std::string Token::toString(unsigned int i) {
    return "(" + TokenTypeToString(token_type) + "," + token_value + "," + toString(line_number) + ")";
}
