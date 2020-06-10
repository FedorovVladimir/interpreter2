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

    void variableOpisanie();

    void mainFunctionOpisanie();

    void structOpisanie();

    void expected(TypeLexeme typeLexeme, const string& text) const;

    static void ifOpisanie();

    static void saveOpisanie();
};


#endif //INTERPRETER_LEXER_H
