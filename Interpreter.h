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

    void InterpretQueries() {
        for (Predicate* query : program->get_queries()) {
            Relation matchingRelation = *database->GetRelation(query->get_id());
            std::vector<std::string> variableNames;
            std::vector<int> variableCols;
            for (unsigned int i = 0; i < query->get_parameters().size(); i++) {
                std::string value = query->get_parameters()[i]->get_p();
                if (value[0] == '\'') {
                    matchingRelation = matchingRelation.select1(i, value);
                } else {
                    bool isFound = false;
                    for (unsigned int j = 0; j < variableNames.size(); j++) {
                        if (value == variableNames[j]) {
                            matchingRelation = matchingRelation.select2(variableCols[j], i);
                            isFound = true;
                        }
                    }
                    if (not isFound) {
                        variableNames.push_back(value);
                        variableCols.push_back(i);
                    }
                }
            }
            matchingRelation = matchingRelation.project(variableCols);
            matchingRelation = matchingRelation.rename(variableNames);
            std::cout << query->toString() << "? ";
            if (matchingRelation.getTuples().size() > 0) {
                std::cout << "Yes(" << matchingRelation.getTuples().size() << ")" << std::endl;
            } else {
                std::cout << "No" << std::endl;
            }
            matchingRelation.toString();
        }
    }

};

#endif // INTERPRETER_H