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
#include "StringAutomaton.h"
#include "MLCommentAutomaton.h"
#include "CommentAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "QueriesAutomaton.h"
#include "RulesAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
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
    // put these before IDAutomaton
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new RulesAutomaton());
    //
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new MLCommentAutomaton());
    automata.push_back(new CommentAutomaton());
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
            maxRead = 1;
        }
        for (char c : input.substr(0, maxRead)) {
            if (c == '\n') {
                lineNumber ++;
            }
        }
        input.erase(0, maxRead);
    }
    Token* newToken = new Token(TokenType::EOF_TOKEN, "", lineNumber);
    tokens.push_back(newToken);
}

std::vector<Token*> Lexer::TokensToVector() {
    return tokens;
}
