#include "Lexer.h"
#include <iostream>
#include <fstream>
#include <vector>

int main (int argc, char** argv) {

    Lexer* lexer = new Lexer();

    // read in the file
    char c = '\0';
    std::string filename = argv[1];
    std::ifstream infile(filename);
    std::string infile_string;
    while (EOF != c) {
        // maybe don't need c?
        c = infile.get();
        infile_string.push_back(c);
    }
    infile.close();

    // convert to tokens and print
    lexer->Run(infile_string);
    std::vector<std::string> infile_tokens = lexer->TokensToVector();
    for (std::string token : infile_tokens) {
        std::cout << token << '\n';
    }
    std::cout << "Total Tokens = " << infile_tokens.size();
    delete lexer;

    return 0;
}