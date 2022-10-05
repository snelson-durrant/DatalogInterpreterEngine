#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "Token.h"

class Parser
{
private:
    std::vector<Token*> tokens;
    int token_counter;

public:
    Parser(std::vector<Token*> input_tokens);
    ~Parser();
    void match(std::string token_type);

    void datalogProgram();
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();
    void headPredicate();
    void predicate();
    void predicateList();
    void parameterList();
    void stringList();
    void idList();
    void parameter();

    void Run();

};

#endif // PARSER_H

