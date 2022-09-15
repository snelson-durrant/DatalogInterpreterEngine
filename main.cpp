#include "Lexer.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();


    // TODO
    char c = '\0';
    std::string filename = argv[1];
    std::ifstream infile(filename);
    std::string infile_string;
    while (EOF != c) {
        // maybe don't need c?
        c = infile.get();
        infile_string.push_back(c);
    }
    std::cout << infile_string;
    infile.close();

    lexer->Run(infile_string);
    std::string token_string = lexer->AllTokensToString();
    std::cout << token_string;
    delete lexer;

    return 0;
}