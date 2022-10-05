#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include "Rule.h"
#include <iostream>

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
    void print_schemes();
    void print_facts();
    void print_queries();
    void print_rules();

};

#endif // DATALOGPROGRAM_H

