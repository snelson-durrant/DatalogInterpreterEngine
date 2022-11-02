#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter
{

private:
    DatalogProgram* program;
    Database* database = new Database();

public:
    Interpreter() = default;
    Interpreter(DatalogProgram* program) {
        this->program = program;
    }

    void InterpretSchemes() {
        for (Predicate* scheme : program->get_schemes()) {
            std::vector<std::string> schemeHeaders;
            for (Parameter* par : scheme->get_parameters()) {
                schemeHeaders.push_back(par->get_p());
            }
            Header schHeader(schemeHeaders);
            Relation schemeRelation(scheme->get_id(), schHeader);
            database->AddRelation(schemeRelation);
        }
    }
    void InterpretFacts() {
        for (Predicate* fact : program->get_facts()) {
            std::vector<std::string> factTuples;
            for (Parameter* par : fact->get_parameters()) {
                factTuples.push_back(par->get_p());
            }
            Tuple fTuple(factTuples);
            database->GetRelation(fact->get_id())->addTuple(fTuple);
        }
    };
    // void InterpretRules();
    // void InterpretQueries();

};

#endif // INTERPRETER_H