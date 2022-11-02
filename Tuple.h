#ifndef TUPLE_H
#define TUPLE_H
#include <vector>
#include <string>

class Tuple
{

public:
    std::vector<std::string> rowValues;

    Tuple() = default;
    Tuple(std::vector<std::string> rowValues) {
        this->rowValues = rowValues;
    }

    bool operator< (const Tuple &rhs) const {
        return rowValues < rhs.rowValues;
    }

};

#endif // TUPLE_H