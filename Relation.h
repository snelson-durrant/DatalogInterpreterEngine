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
    Header getColumnNames() { return columnNames; }
    std::string getName() { return name; }
    void addTuple(Tuple newTuple) { tuples.insert(newTuple); }

    Relation join(Relation relationToJoin) {
        Relation newRelation(this->name, this->columnNames);
        std::vector<int> matchingNames1;
        std::vector<int> matchingNames2;
        std::vector<int> toAdd;
        std::vector<std::string> newNames = this->columnNames.columnNames;

        for (unsigned int j = 0; j < relationToJoin.columnNames.columnNames.size(); j++) {
            bool matched = false;
            for (unsigned int i = 0; i < this->columnNames.columnNames.size(); i++) {
                if (this->columnNames.columnNames[i] == relationToJoin.columnNames.columnNames[j]) {
                    matchingNames1.push_back(i);
                    matchingNames2.push_back(j);
                    matched = true;
                }
            }
            if (!matched) {
                toAdd.push_back(j);
                newNames.push_back(relationToJoin.columnNames.columnNames[j]);
            }
        }
        newRelation.setColumnNames(newNames);

        for (Tuple tuple1 : tuples) {
            for (Tuple tuple2 : relationToJoin.getTuples()) {
                bool joinable = true;
                for (unsigned int i = 0; i < matchingNames1.size(); i++) {
                    if (!(tuple1.rowValues[matchingNames1[i]] == tuple2.rowValues[matchingNames2[i]])) {
                        joinable = false;
                    }
                }
                if (joinable) {
                    Tuple newTuple = tuple1;
                    for (int add: toAdd) {
                        newTuple.rowValues.push_back(tuple2.rowValues[add]);
                    }
                    newRelation.addTuple(newTuple);
                }
            }
        }
        return newRelation;

    }

    bool UnitedSoA(Relation toAdd) {
        bool success = false;
        for (Tuple tup : toAdd.tuples) {
            if (tuples.insert(tup).second) {
                success = true;
                bool isPrinted = false;
                for (std::vector<std::string>::size_type i = 0; i < tup.rowValues.size(); i++) {
                    if (not isPrinted) {
                        std::cout << "  ";
                    }
                    std::cout << this->columnNames.columnNames[i] << "=" << tup.rowValues[i] << "";
                    if (i != (tup.rowValues.size() - 1) ) {
                        std::cout << ", ";
                    }
                    isPrinted = true;
                }
                if (isPrinted) {
                    std::cout << std::endl;
                }
            }
        }

        return success;
    }

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