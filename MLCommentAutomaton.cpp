#include "MLCommentAutomaton.h"

void MLCommentAutomaton::S0(const std::string& input) {
    ChangeToken(TokenType::COMMENT);
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void MLCommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

void MLCommentAutomaton::S2(const std::string& input) {
    if (input[index] == EOF) {
        ChangeToken(TokenType::UNDEFINED);
    } else if (input[index] == '|') {
        inputRead++;
        index++;
        S3(input);
    } else {
        inputRead++;
        index++;
        S2(input);
    }
}

void MLCommentAutomaton::S3(const std::string& input) {
    if (input[index] == EOF) {
        ChangeToken(TokenType::UNDEFINED);
    } else if (input[index] == '#') {
        inputRead++;
    } else {
        inputRead++;
        index++;
        S2(input);
    }
}