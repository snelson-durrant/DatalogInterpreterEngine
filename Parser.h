#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "Token.h"
#include "DatalogProgram.h"

class Parser
{
private:
    std::vector<Token*> tokens;
    int token_counter;
    DatalogProgram* datalog_program = new DatalogProgram();

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
    Predicate* headPredicate();
    Predicate* predicate();
    std::vector<Predicate*> predicateList();
    std::vector<Parameter*> parameterList();
    std::vector<Parameter*> stringList();
    std::vector<Parameter*> idList();
    Parameter* parameter();

    void Run();

    void print();

    std::vector<Predicate*> pred_list;
    std::vector<Parameter*> par_list;
    std::vector<Parameter*> str_list;
    std::vector<Parameter*> id_list;

};

#endif // PARSER_H

