#include "DatalogProgram.h"

DatalogProgram::DatalogProgram() {

}

DatalogProgram::~DatalogProgram() {
    // for (Automaton* automaton : automata) {
    //    delete automaton;
    // }
    // automata.clear();
    // for (Token* token : tokens) {
    //    delete token;
    // }
    // tokens.clear();
}

void DatalogProgram::add_scheme(Predicate* scheme) {
    schemes.push_back(scheme);
}

void DatalogProgram::add_fact(Predicate* fact) {
    facts.push_back(fact);
}

void DatalogProgram::add_query(Predicate* query) {
    queries.push_back(query);
}

void DatalogProgram::add_rule(Rule* rule) {
    rules.push_back(rule);
}

void DatalogProgram::print_schemes() {
    std::cout << "Schemes(" + std::to_string(schemes.size()) + "):" << std::endl;
    for (Predicate* scheme : schemes) {
        std::cout << "  " << scheme->toString() << std::endl;
    }
}

void DatalogProgram::print_facts() {
    std::cout << "Facts(" + std::to_string(facts.size()) + "):" << std::endl;
    for (Predicate* fact : facts) {
        std::cout << "  " << fact->toString() << "." << std::endl;
    }
}

void DatalogProgram::print_queries() {
    std::cout << "Queries(" + std::to_string(queries.size()) + "):" << std::endl;
    for (Predicate* query : queries) {
        std::cout << "  " << query->toString() << "?" << std::endl;
    }
}

void DatalogProgram::print_rules() {
    std::cout << "Rules(" + std::to_string(rules.size()) + "):" << std::endl;
    for (Rule* rule : rules) {
        std::cout << "  " << rule->toString() << std::endl;
    }
}