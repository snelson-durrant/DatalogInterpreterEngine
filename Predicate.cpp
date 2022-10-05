#include "Predicate.h"

Predicate::Predicate() {

}

Predicate::~Predicate() {
    parameters.clear();
}

void Predicate::add_par(Parameter* input) {
    parameters.push_back(input);
}

void Predicate::add_id(std::string input) {
    id = input;
}

std::string Predicate::toString() {
    std::string output = id + "(";
    for (Parameter* par : parameters) {
        output = output + par->toString() + ",";
    }
    output.pop_back();
    output = output + ")";
    return output;
}

std::vector<std::string> Predicate::getDomain() {
    std::vector<std::string> output;
    for (Parameter* par : parameters) {
        output.push_back(par->toString());
    }
    return output;
}
