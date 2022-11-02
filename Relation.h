#ifndef RELATION_H
#define RELATION_H
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include "Header.h"
#include "Tuple.h"

class Relation
{

private:
    std::string name;
    Header columnNames;
    std::set<Tuple> tuples;

public:
    Relation() = default;
    Relation(std::string name, Header columnNames) {
        this->name = name;
        this->columnNames = columnNames;
    }

    std::string getName () { return name; }
    void addTuple(Tuple newTuple) { tuples.insert(newTuple); }

    Relation select1(int columnIndex, std::string value);
    Relation select2(int columnIndex1, int columnIndex2);
    Relation project(std::vector<int> columnsToProject);
    Relation rename(std::vector<std::string> newColumnNames);

    void toString() {
        for (Tuple t : tuples) {
            for (std::vector<std::string>::size_type i = 0; i < t.rowValues.size(); i++) {
                std::cout << this->columnNames.columnNames[i] << "='" << t.rowValues[i] << "'";
                if (i != (t.rowValues.size() - 1) ) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
    }

};

#endif // RELATION_H