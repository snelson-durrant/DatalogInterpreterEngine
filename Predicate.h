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
    std::string get_id() {
        return id;
    }
    std::vector<Parameter*> get_parameters() {
        return parameters;
    }


};

#endif // PREDICATE_H

