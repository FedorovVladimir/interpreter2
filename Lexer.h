//
// Created by vladimir on 10.06.2020.
//

#ifndef INTERPRETER_LEXER_H
#define INTERPRETER_LEXER_H

#include <iostream>
#include <vector>
#include "Scanner.h"

using namespace std;

class Lexer {
public:
    explicit Lexer(Scanner *scanner);

    void start();

    bool isType(const string& name);

private:
    Scanner *scanner{};
    Node *root;
    Node *currentNode;
    vector<string> structures;

    void addNode(Node *node);

    static void logErr(const string &text);

    static void logInfo(const string &text);

    void variableOpisanie();

    void mainFunctionOpisanie();

    void structOpisanie();

    void expected(TypeLexeme typeLexeme, const string& text) const;

    void ifOpisanie();

    void saveOpisanie();

    void expressionOpisanie();

    void listOpisanie();
};


#endif //INTERPRETER_LEXER_H
