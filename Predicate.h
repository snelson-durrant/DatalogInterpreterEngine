#ifndef PREDICATE_H
#define PREDICATE_H
#include <vector>
#include "Parameter.h"

class Predicate
{
private:
    std::string id;
    std::vector<Parameter*> parameters;

public:
    Predicate();
    ~Predicate();

    void add_par(Parameter* input);
    void add_id(std::string input);
    std::vector<std::string> getDomain();
    std::string toString();

};

#endif // PREDICATE_H

