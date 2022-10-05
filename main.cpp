#include "Lexer.h"
#include "Parser.h"
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
    std::vector<Token*> infile_tokens = lexer->TokensToVector();

    delete lexer;
    Parser* parser = new Parser(infile_tokens);

    try {
        parser->Run();
        std::cout << "Success!";
    }
    catch (Token* errorToken) {
        std::cout << "Failure!" << std::endl;
        std::cout << "  " << errorToken->ToString();
    }

    delete parser;

    return 0;
}