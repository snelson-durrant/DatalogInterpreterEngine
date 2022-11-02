#ifndef DATABASE_H
#define DATABASE_H
#include <map>
#include "Relation.h"

class Database
{

private:
    std::map<std::string, Relation> relations;
    std::map<std::string, Relation>::iterator it;

public:
    Database() = default;

    void AddRelation(Relation newRelation) {
        relations.insert({ newRelation.getName(), newRelation });
    }
    Relation* GetRelation(std::string relationName) {
        it = relations.find(relationName);
        return &it->second;
    }
    Relation GetRelationCopy(std::string relationName) {
        it = relations.find(relationName);
        return it->second;
    }

};

#endif // DATABASE_H