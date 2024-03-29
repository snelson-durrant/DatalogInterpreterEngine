cmake_minimum_required(VERSION 3.16)
project(snelsond_project1)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include_directories(.)

add_executable(snelsond_project1
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h
        AddAutomaton.cpp
        AddAutomaton.h
        CommaAutomaton.cpp
        CommaAutomaton.h
        LeftParenAutomaton.cpp
        LeftParenAutomaton.h
        MultiplyAutomaton.cpp
        MultiplyAutomaton.h
        PeriodAutomaton.cpp
        PeriodAutomaton.h
        QMarkAutomaton.cpp
        QMarkAutomaton.h
        RightParenAutomaton.cpp
        RightParenAutomaton.h
        IDAutomaton.cpp
        IDAutomaton.h
        StringAutomaton.cpp
        StringAutomaton.h
        MLCommentAutomaton.cpp
        MLCommentAutomaton.h
        CommentAutomaton.cpp
        CommentAutomaton.h
        SchemesAutomaton.cpp
        SchemesAutomaton.h
        FactsAutomaton.cpp
        FactsAutomaton.h
        QueriesAutomaton.cpp
        QueriesAutomaton.h
        RulesAutomaton.cpp
        RulesAutomaton.h
        Parser.cpp
        Parser.h
        DatalogProgram.cpp
        DatalogProgram.h
        Parameter.cpp
        Parameter.h
        Predicate.cpp
        Predicate.h
        Rule.cpp
        Rule.h
        Header.h
        Tuple.h
        Relation.h
        Database.h
        Interpreter.h
        Graph.h
        )
