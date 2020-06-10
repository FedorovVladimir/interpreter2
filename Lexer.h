//
// Created by vladimir on 10.06.2020.
//

#ifndef INTERPRETER_LEXER_H
#define INTERPRETER_LEXER_H

#include <iostream>
#include "Scanner.h"

using namespace std;

class Lexer {
public:
    explicit Lexer(Scanner *scanner);

    void start();

private:
    Scanner *scanner{};
    Node *root;
    Node *currentNode;

    void addNode(Node *node);

    static void logErr(const string &text);

    static void logInfo(const string &text);

    static void variableOpisanie();

    static void mainFunctionOpisanie();

    static void structOpisanie();
};


#endif //INTERPRETER_LEXER_H
