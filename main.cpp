#include "Lexer.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {

    // Lexer* lexer = new Lexer();

    // TODO
    char c;
    std::string filename = argv[1];
    std::ifstream infile(filename);
    std::string infile_string;
    while (infile >> c) {
        // maybe don't need c?
        c = infile.get();
        infile_string.push_back(c);
    }
    infile.close();

    // delete lexer;

    return 0;
}