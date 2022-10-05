#include "Rule.h"

Rule::Rule() {

}

Rule::~Rule() {
    // for (Automaton* automaton : automata) {
    //    delete automaton;
    // }
    // automata.clear();
    // for (Token* token : tokens) {
    //    delete token;
    // }
    // tokens.clear();
}

std::string Rule::toString() {
    std::string output = headPredicate->toString() + " :- ";
    for (Predicate* pred : bodyPredicates) {
        output = output + pred->toString() + ",";
    }
    output.pop_back();
    output = output + ".";
    return output;
}

void Rule::add_head(Predicate* input) {
    headPredicate = input;
}

void Rule::add_pred(Predicate* input) {
    bodyPredicates.push_back(input);
}
