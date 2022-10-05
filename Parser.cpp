#include "Parser.h"
#include <iostream>

Parser::Parser(std::vector<Token*> input_tokens) {
    tokens = input_tokens;
}

Parser::~Parser() {
    // for (Automaton* automaton : automata) {
    //    delete automaton;
    // }
    // automata.clear();
    // for (Token* token : tokens) {
    //    delete token;
    // }
    // tokens.clear();
}

void Parser::match(std::string token_type) {
    if (tokens[token_counter]->TokenTypeToString() == token_type) {
        token_counter += 1;
    } else {
        throw tokens[token_counter];
    }
}

void Parser::datalogProgram() {

    token_counter = 0;
    match("SCHEMES");
    match("COLON");

    scheme();
    schemeList();

    match("FACTS");
    match("COLON");

    factList();

    match("RULES");
    match("COLON");

    ruleList();

    match("QUERIES");
    match("COLON");

    query();
    queryList();

    match("EOF");

}

void Parser::schemeList(){

    if (tokens[token_counter]->TokenTypeToString() == "ID") {
        scheme();
        schemeList();
    }

}

void Parser::factList() {

    if (tokens[token_counter]->TokenTypeToString() == "ID") {
        fact();
        factList();
    }

}

void Parser::ruleList() {

    if (tokens[token_counter]->TokenTypeToString() == "ID") {
        rule();
        ruleList();
    }

}

void Parser::queryList() {

    if (tokens[token_counter]->TokenTypeToString() == "ID") {
        query();
        queryList();
    }

}

void Parser::scheme() {

    match("ID");
    match("LEFT_PAREN");
    match("ID");

    idList();

    match("RIGHT_PAREN");

}

void Parser::fact() {

    match("ID");
    match("LEFT_PAREN");
    match("STRING");

    stringList();

    match("RIGHT_PAREN");
    match("PERIOD");

}

void Parser::rule() {

    headPredicate();

    match("COLON_DASH");

    predicate();
    predicateList();

    match("PERIOD");

}

void Parser::query() {

    predicate();

    match("Q_MARK");

}

void Parser::headPredicate() {

    match("ID");
    match("LEFT_PAREN");
    match("ID");

    idList();

    match("RIGHT_PAREN");

}

void Parser::predicate() {

    match("ID");
    match("LEFT_PAREN");

    parameter();
    parameterList();

    match("RIGHT_PAREN");

}

void Parser::predicateList() {

    if (tokens[token_counter]->TokenTypeToString() == "COMMA") {
        match("COMMA");

        predicate();
        predicateList();
    }

}

void Parser::parameterList() {

    if (tokens[token_counter]->TokenTypeToString() == "COMMA") {
        match("COMMA");

        parameter();
        parameterList();
    }

}

void Parser::stringList() {

    if (tokens[token_counter]->TokenTypeToString() == "COMMA") {
        match("COMMA");
        match("STRING");

        stringList();
    }

}

void Parser::idList() {

    if (tokens[token_counter]->TokenTypeToString() == "COMMA") {
        match("COMMA");
        match("ID");

        idList();
    }

}

void Parser::parameter() {

    if (tokens[token_counter]->TokenTypeToString() == "STRING") {
        match("STRING");
    } else if (tokens[token_counter]->TokenTypeToString() == "ID") {
        match("ID");
    } else {
        throw tokens[token_counter];
    }

}

void Parser::Run() {

    // remove comments
    int i = 0;
    for (Token* token : tokens) {
        if (token->TokenTypeToString() == "COMMENT") {
            tokens.erase(tokens.begin(), tokens.begin() + i);
        }
        i += 1;
    }

    datalogProgram();

}
