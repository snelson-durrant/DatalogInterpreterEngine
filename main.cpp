#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
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
        c = infile.get();
        infile_string.push_back(c);
    }
    infile.close();

    // convert to tokens and print
    lexer->Run(infile_string);
    std::vector<Token*> infile_tokens = lexer->TokensToVector();

    delete lexer;
    Parser* parser = new Parser(infile_tokens);
    DatalogProgram* datalog_program;

    try {
        parser->Run();
        datalog_program = parser->get_program();
    }
    catch (Token* errorToken) {
        std::cout << "Failure!" << std::endl;
        std::cout << "  " << errorToken->ToString();
    }

    infile_tokens.clear();

    Interpreter* interpreter = new Interpreter(datalog_program);
    interpreter->InterpretSchemes();
    interpreter->InterpretFacts();
    interpreter->InterpretQueries();

    delete parser; // FIX THIS

    return 0;
}