#include "Lexer.h"
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();

    // TODO
    char c;
    std::string filename = argv[1];
    std::ifstream infile(filename);
    std::vector<char> infile_chars;
    while (infile >> c) {
        c = infile.get();
        infile_chars.push_back(c);
        std::cout << c;
    }
    infile.close();

    delete lexer;

    return 0;
}