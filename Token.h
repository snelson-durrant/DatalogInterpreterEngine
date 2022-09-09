#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    // TODO: add the other types of tokens
    UNDEFINED
};

std::string TokenTypeToString(TokenType tokenType) {
    switch (tokenType) {
        case TokenType::COLON: return "COLON"; break;
        case TokenType::COLON_DASH: return "COLON_DASH"; break;
        case TokenType::UNDEFINED: return "UNDEFINED"; break;
    }
    return "ERROR"; // a string MUST be returned by the end
}

class Token
{
private:
    // TODO: add member variables for information needed by Token
    std::string token_value;
    unsigned int line_number;
    TokenType token_type;

public:
    Token(TokenType type, std::string description, int line);

    // TODO: add other needed methods
    std::string toString(unsigned int i);
};

#endif // TOKEN_H

