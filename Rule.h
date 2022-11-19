#ifndef RULE_H
#define RULE_H
#include "Predicate.h"

class Rule
{
private:

public:
    Rule();
    ~Rule();

    Predicate* headPredicate;
    std::vector<Predicate*> bodyPredicates;

    void add_head(Predicate* input);
    void add_pred(Predicate* input);
    std::string toString();

};

#endif // RULE_H

