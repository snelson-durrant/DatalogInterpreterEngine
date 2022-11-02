#ifndef HEADER_H
#define HEADER_H
#include <vector>
#include <string>

class Header
{

public:
    std::vector<std::string> columnNames;

    Header() = default;
    Header(std::vector<std::string> columnNames) {
        this->columnNames = columnNames;
    }
};

#endif // HEADER_H