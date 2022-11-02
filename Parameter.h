#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>

class Parameter
{
private:
    std::string p;

public:
    Parameter(std::string input);
    ~Parameter();

    std::string toString();
    std::string get_p() {
        return p;
    }

};

#endif // PARAMETER_H

