#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"
#include <cctype>
#include <algorithm>

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

    bool isReflexive(Rule* rule) {
        bool ref = false;
        for(Predicate* pred : rule->bodyPredicates) {
            if (rule->headPredicate->get_id() == pred->get_id()) {
                ref = true;
            }
        }
        return ref;
    }


    void InterpretRules() {

        Graph graph;
        graph.add_nodes(program);
        graph.get_scc();
        // JUST NEED TO ADD THIS PART
        std::cout << "Rule Evaluation" << std::endl;

        for (std::vector<int> s : graph.scc) {
            std::cout << "SCC: ";
            std::sort(s.begin(),s.end());
            bool first = true;
            for (int ss : s) {
                if(!first) {
                    std::cout << ",";
                }
                std::cout << "R" << ss;
                first = false;
            }
            std::cout << std::endl;

            int passes = 0;
            bool tuplesAdded = true;
            bool reflexive = false;
            while (tuplesAdded and !reflexive) {
                passes++;
                tuplesAdded = false;
                for (int ss : s) {
                    std::cout << program->get_rules()[ss]->toString() << std::endl;
                    std::vector<Relation> newRelations;
                    for (Predicate* pred : program->get_rules()[ss]->bodyPredicates) {
                        Relation newRelation = EvaluatePredicate(pred);
                        newRelations.push_back(newRelation);
                    }

                    Relation fullRelation = newRelations[0];
                    if (newRelations.size() > 1) {
                        for (unsigned int r = 1; r < newRelations.size(); r++) {
                            fullRelation = fullRelation.join(newRelations[r]);
                        }
                    }

                    std::vector<int> headColumns;
                    for (unsigned int j = 0; j < program->get_rules()[ss]->headPredicate->get_parameters().size(); j++) {
                        for (unsigned int i = 0; i < fullRelation.getColumnNames().columnNames.size(); i++) {
                            if (fullRelation.getColumnNames().columnNames[i] == program->get_rules()[ss]->headPredicate->get_parameters()[j]->get_p()) {
                                headColumns.push_back(i);
                            }
                        }
                    }
                    fullRelation = fullRelation.project(headColumns);

                    fullRelation.setName(program->get_rules()[ss]->headPredicate->get_id());

                    Relation* dataRelation = database->GetRelation(fullRelation.getName());
                    fullRelation = fullRelation.rename(dataRelation->getColumnNames().columnNames);

                    if (dataRelation->UnitedSoA(fullRelation)) {
                        tuplesAdded = true;
                    }

                    if(s.size() == 1 and !isReflexive(program->get_rules()[s[0]])) {
                        reflexive = true;
                    }

                }

            }
            std::cout << passes << " passes: ";
            first = true;
            for (int ss : s) {
                if(!first) {
                    std::cout << ",";
                }
                std::cout << "R" << ss;
                first = false;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << "Query Evaluation" << std::endl;
    }


    Relation EvaluatePredicate(Predicate* pred) {
        Relation matchingRelation = *database->GetRelation(pred->get_id());
        std::vector<std::string> variableNames;
        std::vector<int> variableCols;
        for (unsigned int i = 0; i < pred->get_parameters().size(); i++) {
            std::string value = pred->get_parameters()[i]->get_p();
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
        return matchingRelation;
    }


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