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

    Predicate* sch = new Predicate();
    sch->add_id(tokens[token_counter]->TokenValueToString());
    match("ID");
    match("LEFT_PAREN");
    Parameter* par = new Parameter(tokens[token_counter]->TokenValueToString());
    sch->add_par(par);
    match("ID");

    std::vector<Parameter*> pars = idList();
    for (Parameter* p : pars) {
        sch->add_par(p);
    }

    match("RIGHT_PAREN");
    datalog_program->add_scheme(sch);

}

void Parser::fact() {

    Predicate* fac = new Predicate();
    fac->add_id(tokens[token_counter]->TokenValueToString());
    match("ID");
    match("LEFT_PAREN");
    Parameter* par = new Parameter(tokens[token_counter]->TokenValueToString());
    fac->add_par(par);
    match("STRING");

    std::vector<Parameter*> pars = stringList();
    for (Parameter* p : pars) {
        fac->add_par(p);
    }

    match("RIGHT_PAREN");
    match("PERIOD");
    datalog_program->add_fact(fac);

}

void Parser::rule() {

    Rule* rul = new Rule();
    rul->add_head(headPredicate());

    match("COLON_DASH");

    rul->add_pred(predicate());
    std::vector<Predicate*> preds = predicateList();
    for (Predicate* p : preds) {
        rul->add_pred(p);
    }

    match("PERIOD");
    datalog_program->add_rule(rul);

}

void Parser::query() {

    datalog_program->add_query(predicate());

    match("Q_MARK");

}

Predicate* Parser::headPredicate() {

    Predicate* head = new Predicate();
    head->add_id(tokens[token_counter]->TokenValueToString());
    match("ID");
    match("LEFT_PAREN");
    Parameter* par = new Parameter(tokens[token_counter]->TokenValueToString());
    head->add_par(par);
    match("ID");

    std::vector<Parameter*> pars = idList();
    for (Parameter* p : pars) {
        head->add_par(p);
    }

    match("RIGHT_PAREN");
    return head;

}

Predicate* Parser::predicate() {

    Predicate* pred = new Predicate();
    pred->add_id(tokens[token_counter]->TokenValueToString());
    match("ID");
    match("LEFT_PAREN");

    pred->add_par(parameter());
    std::vector<Parameter*> pars = parameterList();
    for (Parameter* p : pars) {
        pred->add_par(p);
    }

    match("RIGHT_PAREN");
    return pred;

}

std::vector<Predicate*> Parser::predicateList() {

    if (tokens[token_counter]->TokenTypeToString() == "COMMA") {
        match("COMMA");

        pred_list.push_back(predicate());
        predicateList();
    }
    return pred_list;

}

std::vector<Parameter*> Parser::parameterList() {

    if (tokens[token_counter]->TokenTypeToString() == "COMMA") {
        match("COMMA");

        par_list.push_back(parameter());
        parameterList();
    }
    return par_list;

}

std::vector<Parameter*>  Parser::stringList() {

    if (tokens[token_counter]->TokenTypeToString() == "COMMA") {
        match("COMMA");
        Parameter* par = new Parameter(tokens[token_counter]->TokenValueToString());
        str_list.push_back(par);
        match("STRING");

        stringList();
    }
    return str_list;

}

std::vector<Parameter*> Parser::idList() {

    if (tokens[token_counter]->TokenTypeToString() == "COMMA") {
        match("COMMA");
        Parameter* par = new Parameter(tokens[token_counter]->TokenValueToString());
        id_list.push_back(par);
        match("ID");

        idList();
    }
    return id_list;

}

Parameter* Parser::parameter() {

    if (tokens[token_counter]->TokenTypeToString() == "STRING") {
        Parameter* par = new Parameter(tokens[token_counter]->TokenValueToString());
        match("STRING");
        return par;
    } else if (tokens[token_counter]->TokenTypeToString() == "ID") {
        Parameter* par = new Parameter(tokens[token_counter]->TokenValueToString());
        match("ID");
        return par;
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

void Parser::print() {

    datalog_program->print_schemes();
    datalog_program->print_facts();
    datalog_program->print_rules();
    datalog_program->print_queries();

}
