#include "Parameter.h"

Parameter::Parameter(std::string input) {
    p = input;
}

Parameter::~Parameter() {

}

std::string Parameter::toString() {
    return p;
}
