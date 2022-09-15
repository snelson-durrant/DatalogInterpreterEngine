#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    ADD,
    COMMA,
    LEFT_PAREN,
    MULTIPLY,
    PERIOD,
    Q_MARK,
    RIGHT_PAREN,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EOF_TOKEN
};

class Token
{
private:
    std::string token_value;
    unsigned int line_number;
    TokenType token_type;

public:
    Token(TokenType type, std::string description, int line);

    std::string TokenTypeToString();
    std::string ToString();
};

#endif // TOKEN_H

