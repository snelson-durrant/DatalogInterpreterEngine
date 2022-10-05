#include "Parameter.h"

Parameter::Parameter(std::string input) {
    p = input;
}

Parameter::~Parameter() {
    // for (Automaton* automaton : automata) {
    //    delete automaton;
    // }
    // automata.clear();
    // for (Token* token : tokens) {
    //    delete token;
    // }
    // tokens.clear();
}

std::string Parameter::toString() {
    return p;
}
