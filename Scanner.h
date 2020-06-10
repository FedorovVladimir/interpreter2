//
// Created by vladimir on 10.06.2020.
//

#ifndef INTERPRETER_SCANNER_H
#define INTERPRETER_SCANNER_H

#include <string>
#include "Node.h"

using namespace std;

class Scanner {
public:
    explicit Scanner(string text);

    Node *next();

    Node *getCurrentNode();

    int getCurrentPosition() const;

    void setCurrentPosition(int position);

    Node *getNextNode();

private:
    string text;
    int currentPosition = 0;

    void swapGarbageSymbols();

    void swapComment();
};


#endif //INTERPRETER_SCANNER_H
