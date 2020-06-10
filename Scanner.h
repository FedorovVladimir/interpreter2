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

    bool eof();

    TypeLexeme getCurrentLexemType();

    int getCurrentLine() const;

    int getCurrentLinePosition() const;

private:
    string text;
    int currentPosition;
    int currentLine;
    int currentLinePosition;
    char c;
    char nc;

    void swapGarbageSymbols();

    void swapComment();

    void nextPosition();

    void setCurrentLine(int i);

    void setCurrentLinePosition(int i);
};


#endif //INTERPRETER_SCANNER_H
