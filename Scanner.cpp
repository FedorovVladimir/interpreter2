//
// Created by vladimir on 10.06.2020.
//

#include "Scanner.h"

#include <utility>
#include <cmath>

const string oneSymbols = ",;(){}*%/\n";
const TypeLexeme oneLexemes[] = {COMMA, POINT_COMMA, OPEN_KRUGLAY_SKOBKA, CLOSE_KRUGLAY_SKOBKA, OPEN_FIGURNAY_SKOBKA,
                                 CLOSE_FIGURNAY_SKOBKA, MUL, MOD, DIV, END_OF_FILE};

const string doubleSymbols = "||&&++--==";
const TypeLexeme doubleLexemes[] = {OR, OR_OR, AND, AND_AND, PLUS, INC, MINUS, DEC, SAVE, EQUAL};

const string s1 = "><";
const TypeLexeme l1[] = {LARGER, LESS};
const string s2 = "><";
const TypeLexeme l2[] = {LARGER_LARGER, LESS_LESS};
const string s3 = "==";
const TypeLexeme l3[] = {LARGER_EQUAL, LESS_EQUAL};

const int countWords = 7;
const string stringWord[] = {"if", "else", "void", "int", "double", "main", "struct"};
const TypeLexeme lexemeWord[] = {IF, ELSE, VOID, INT, DOUBLE, MAIN, STRUCT};

Scanner::Scanner(string text) {
    this->text = move(text);
    this->currentPosition = 0;
    this->currentLine = 1;
    this->currentLinePosition = 1;
    this->c = this->text[currentPosition];
    this->nc = this->text[currentPosition + 1];
}

Node *Scanner::next() {
    swapGarbageSymbols();
    swapComment();
    swapGarbageSymbols();

    if (currentPosition == text.length()) {
        return new Node(END_OF_FILE);
    }

    // , ; ( ) { } * % /
    int indexOneSymbols = oneSymbols.find(c);
    if (0 <= indexOneSymbols && indexOneSymbols < oneSymbols.length()) {
        nextPosition();
        return new Node(oneLexemes[indexOneSymbols]);
    }

    // | || & && + ++ - -- = ==
    int indexDoubleSymbols1 = doubleSymbols.find(c);
    if (0 <= indexDoubleSymbols1 && indexDoubleSymbols1 < doubleSymbols.length()) {
        nextPosition();
        int indexDoubleSymbols2 = doubleSymbols.find(c);
        if (0 <= indexDoubleSymbols2 && indexDoubleSymbols2 < doubleSymbols.length()) {
            nextPosition();
            return new Node(doubleLexemes[indexDoubleSymbols2 + 1]);
        } else {
            return new Node(doubleLexemes[indexDoubleSymbols1]);
        }
    }

    // !=
    if (c == '!') {
        nextPosition();
        if (c == '=') {
            nextPosition();
            return new Node(NOT_EQUAL);
        } else {
            return new Node(ERROR);
        }
    }

    // >> >= > << <= <
    int index1 = s1.find(c);
    if (0 <= index1 && index1 < s1.length()) {
        nextPosition();
        int index2 = s2.find(c);
        int index3 = s3.find(c);
        if (0 <= index2 && index2 < s2.length()) {
            nextPosition();
            return new Node(l2[index2]);
        } else if (0 <= index3 && index3 < s3.length()) {
            nextPosition();
            return new Node(l3[index3]);
        } else
            return new Node(l1[index1]);
    }

    // id
    if (isalpha(c)) {
        string s;
        s += c;
        nextPosition();
        while (isdigit(c) || isalpha(c)) {
            s += c;
            nextPosition();
        }
        for (int i = 0; i < countWords; i++) {
            if (s == stringWord[i]) {
                return new Node(lexemeWord[i]);
            }
        }
        return new Node(ID, "", s);
    }

    if (!isdigit(c) && c != '.') {
        return new Node(ERROR);
    }

    string s;
    if (isdigit(c)) {
        s += c;
        nextPosition();
        while (isdigit(c)) {
            s += c;
            nextPosition();
        }
        if (c == '.') {
            s += c;
            nextPosition();
            goto N1;
        } else if (c == 'E' || c == 'e') {
            s += c;
            nextPosition();
            goto N2;
        }
        return new Node(CONST_INT, s);
    }
    if (c == '.') {
        s += c;
        nextPosition();
        if (isdigit(c)) {
            s += c;
            nextPosition();
            goto N1;
        }
        return new Node(POINT, s);
    }
    N1:
    while (isdigit(c)) {
        s += c;
        nextPosition();
    }
    if (c == 'E' || c == 'e') {
        s += c;
        nextPosition();
        goto N2;
    }
    return new Node(CONST_DOUBLE, s);
    N2:
    if (c == '+' || c == '-') {
        s += c;
        nextPosition();
        if (isdigit(c)) {
            s += c;
            nextPosition();
            goto N3;
        } else {
            return new Node(ERROR);
        }
    }
    N3:
    while (isdigit(c)) {
        s += c;
        nextPosition();
    }

    return new Node(CONST_DOUBLE, s);
}

Node *Scanner::getCurrentNode() {
    int i1 = getCurrentPosition();
    int i2 = getCurrentLine();
    int i3 = getCurrentLinePosition();
    Node *pNode = next();
    setCurrentPosition(i1);
    setCurrentLine(i2);
    setCurrentLinePosition(i3);
    return pNode;
}

int Scanner::getCurrentPosition() const {
    return currentPosition;
}

void Scanner::setCurrentPosition(const int position) {
    this->currentPosition = position;
    c = text[currentPosition];
    nc = text[currentPosition + 1];
}

void Scanner::swapGarbageSymbols() {
    while (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
        nextPosition();
    }
}

void Scanner::swapComment() {
    if (c == '/' && nc == '/') {
        nextPosition();
        nextPosition();
        while (c != '\n') {
            nextPosition();
        }
        nextPosition();
    }
}

bool Scanner::eof() {
    return getCurrentLexemType() == END_OF_FILE;
}

TypeLexeme Scanner::getCurrentLexemType() {
    return getCurrentNode()->getTypeLexem();
}

int Scanner::getCurrentLine() const {
    return currentLine;
}

void Scanner::nextPosition() {
    if (c == '\n') {
        currentLine++;
        currentLinePosition = 1;
    } else {
        currentLinePosition++;
    }
    currentPosition++;
    c = text[currentPosition];
    nc = text[currentPosition + 1];
}

int Scanner::getCurrentLinePosition() const {
    return currentLinePosition;
}

void Scanner::setCurrentLine(int i) {
    this->currentLine = i;
}

void Scanner::setCurrentLinePosition(int i) {
    this->currentLinePosition = i;
}
