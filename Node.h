//
// Created by vladimir on 10.06.2020.
//

#ifndef INTERPRETER_NODE_H
#define INTERPRETER_NODE_H

#include <string>
#include "TypeLexeme.h"

using namespace std;

class Node {
public:
    explicit Node(TypeLexeme typeLexeme);

    TypeLexeme getTypeLexem();

    string toString();

    Node(TypeLexeme typeLexeme, const string &text, const string &name = "");

    Node *parent = nullptr;
    Node *right = nullptr;
    Node *left = nullptr;

    string getName();

private:
    TypeLexeme typeLexeme;
    string name;
    union {
        double valueDouble;
        int valueInteger;
    };
};


#endif //INTERPRETER_NODE_H
