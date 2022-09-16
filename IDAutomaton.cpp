#include "IDAutomaton.h"

void IDAutomaton::S0(const std::string& input) {
    ChangeToken(TokenType::ID);
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string& input) {
    if (isalpha(input[index]) or isdigit(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    if (input.substr(0, inputRead) == "Schemes") {
        ChangeToken(TokenType::SCHEMES);
    } else if (input.substr(0, inputRead) == "Facts") {
        ChangeToken(TokenType::FACTS);
    } else if (input.substr(0, inputRead) == "Rules") {
        ChangeToken(TokenType::RULES);
    } else if (input.substr(0, inputRead) == "Queries") {
        ChangeToken(TokenType::QUERIES);
    }
}
