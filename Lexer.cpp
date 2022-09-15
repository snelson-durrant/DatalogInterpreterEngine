#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "AddAutomaton.h"
#include "CommaAutomaton.h"
#include "LeftParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "PeriodAutomaton.h"
#include "QMarkAutomaton.h"
#include "RightParenAutomaton.h"
#include "IDAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO check if this did anything at all?
    // for (Automaton* automaton : automata) {
    //    delete automaton;
    // }
    // automata.clear();
    // for (Token* token : tokens) {
    //    delete token;
    // }
    // tokens.clear();
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QMarkAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new IDAutomaton());
    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;
    // While there are more characters to tokenize
    while (input.size() > 0) {
        int maxRead = 0;
        Automaton* maxAutomaton = automata[0];

        // Here is the "Parallel" part of the algorithm
        // Each automaton runs with the same input
        for (Automaton* automaton : automata) {
            int inputRead = automaton->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automaton;
            }
        }
        // Here is the "Max" part of the algorithm
        if (maxRead > 0) {
            Token* newToken = maxAutomaton->CreateToken(input.std::string::substr(0, maxRead), lineNumber);
            tokens.push_back(newToken);
        }
        // No automaton accepted input
        // Create single character undefined token
        else if (!isspace(input[0]) and input[0] != EOF) {
            maxRead = 1;
            Token* newToken = new Token(TokenType::UNDEFINED, input.std::string::substr(0, 1), lineNumber);
            tokens.push_back(newToken);
        } else {
            if (input[0] == '\n') {
                lineNumber++;
            }
            maxRead = 1;
        }
        input.erase(0, maxRead);
    }
    Token* newToken = new Token(TokenType::EOF_TOKEN, "", lineNumber);
    tokens.push_back(newToken);
}

std::vector<std::string> Lexer::TokensToVector() {
    std::vector<std::string> all_tokens;
    for (Token* token : tokens) {
        std::string token_str = token->ToString();
        all_tokens.push_back(token_str);
    }
    return all_tokens;
}
