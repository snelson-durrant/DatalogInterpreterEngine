#include "DatalogProgram.h"

DatalogProgram::DatalogProgram() {

}

DatalogProgram::~DatalogProgram() {
    schemes.clear();
    facts.clear();
    queries.clear();
    rules.clear();
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

std::vector<Predicate*> DatalogProgram::get_schemes() {
    return schemes;
}

std::vector<Predicate*> DatalogProgram::get_facts() {
    return facts;
}

std::vector<Predicate*> DatalogProgram::get_queries() {
    return queries;
}

std::vector<Rule*> DatalogProgram::get_rules() {
    return rules;
}

std::vector<std::string> DatalogProgram::get_domain() {
    std::vector<std::string> domains;
    std::vector<std::string> insert;
    for (Predicate* fact : facts) {
        insert = fact->getDomain();
        for (std::string str : insert) {
            domains.push_back(str);
        }
    }

    std::sort(domains.begin(), domains.end());
    domains.erase( std::unique(domains.begin(), domains.end()), domains.end());
    std::cout << "Domain(" + std::to_string(domains.size()) + "):" << std::endl;
    return domains;

}