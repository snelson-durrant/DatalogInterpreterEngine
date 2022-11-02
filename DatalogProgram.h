#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include "Rule.h"
#include <iostream>
#include <algorithm>

class DatalogProgram
{
private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;

public:
    DatalogProgram();
    ~DatalogProgram();

    void add_scheme(Predicate* scheme);
    void add_fact(Predicate* fact);
    void add_query(Predicate* query);
    void add_rule(Rule* rule);
    std::vector<Predicate*> get_schemes();
    std::vector<Predicate*> get_facts();
    std::vector<Predicate*> get_queries();
    std::vector<Rule*> get_rules();
    std::vector<std::string> get_domain();

};

#endif // DATALOGPROGRAM_H

