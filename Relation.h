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

    void setName(std::string newName) { name = newName; }
    void setColumnNames(Header newColumnNames) { columnNames = newColumnNames; }
    std::set<Tuple> getTuples() { return tuples; }
    std::string getName() { return name; }
    void addTuple(Tuple newTuple) { tuples.insert(newTuple); }

    Relation select1(int columnIndex, std::string value) {
        Relation newRelation(this->name, this->columnNames);
        for (Tuple tuple : tuples) {
            if (tuple.rowValues[columnIndex] == value) {
                newRelation.addTuple(tuple);
            }
        }
        return newRelation;
    }

    Relation select2(int columnIndex1, int columnIndex2) {
        Relation newRelation(this->name, this->columnNames);
        for (Tuple tuple : tuples) {
            if (tuple.rowValues[columnIndex1] == tuple.rowValues[columnIndex2]) {
                newRelation.addTuple(tuple);
            }
        }
        return newRelation;
    }

    Relation project(std::vector<int> columnsToProject) {
        std::vector<std::string> tempCols;
        for(int col : columnsToProject) {
            tempCols.push_back(columnNames.columnNames[col]);
        }
        Header tempHeader(tempCols);
        Relation newRelation(this->name, tempHeader);
        for(Tuple tuple : tuples) {
            std::vector<std::string> tempVals;
            for(int col : columnsToProject) {
                tempVals.push_back(tuple.rowValues[col]);
            }
            Tuple tempTuple(tempVals);
            newRelation.addTuple(tempTuple);
        }
        return newRelation;
    }

    Relation rename(std::vector<std::string> newColumnNames) {
        Header newHeader(newColumnNames);
        Relation newRelation(this->name, newHeader);
        for (Tuple tuple : tuples) {
            newRelation.addTuple(tuple);
        }
        return newRelation;
    }

    void toString() {
        for (Tuple t : tuples) {
            bool isPrinted = false;
            for (std::vector<std::string>::size_type i = 0; i < t.rowValues.size(); i++) {
                if (not isPrinted) {
                    std::cout << "  ";
                }
                std::cout << this->columnNames.columnNames[i] << "=" << t.rowValues[i] << "";
                if (i != (t.rowValues.size() - 1) ) {
                    std::cout << ", ";
                }
                isPrinted = true;
            }
            if (isPrinted) {
                std::cout << std::endl;
            }
        }
    }

};

#endif // RELATION_H