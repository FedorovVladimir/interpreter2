//
// Created by vladimir on 10.06.2020.
//

#include "Scanner.h"

#include <utility>
#include <cstring>
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
}

Node *Scanner::next() {
    swapGarbageSymbols();
    swapComment();
    swapGarbageSymbols();

    if (currentPosition == text.length()) {
        return new Node(END_OF_FILE);
    }

    // , ; ( ) { } * % /
    int indexOneSymbols = oneSymbols.find(text[currentPosition]);
    if (0 <= indexOneSymbols && indexOneSymbols < oneSymbols.length()) {
        currentPosition++;
        return new Node(oneLexemes[indexOneSymbols]);
    }

    // | || & && + ++ - -- = ==
    int indexDoubleSymbols1 = doubleSymbols.find(text[currentPosition]);
    if (0 <= indexDoubleSymbols1 && indexDoubleSymbols1 < doubleSymbols.length()) {
        currentPosition++;
        int indexDoubleSymbols2 = doubleSymbols.find(text[currentPosition]);
        if (0 <= indexDoubleSymbols2 && indexDoubleSymbols2 < doubleSymbols.length()) {
            currentPosition++;
            return new Node(doubleLexemes[indexDoubleSymbols2 + 1]);
        } else {
            return new Node(doubleLexemes[indexDoubleSymbols1]);
        }
    }

    // !=
    if (text[currentPosition] == '!') {
        currentPosition++;
        if (text[currentPosition] == '=') {
            currentPosition++;
            return new Node(NOT_EQUAL);
        } else {
            return new Node(ERROR);
        }
    }

    // >> >= > << <= <
    int index1 = s1.find(text[currentPosition]);
    if (0 <= index1 && index1 < s1.length()) {
        currentPosition++;
        int index2 = s2.find(text[currentPosition]);
        int index3 = s3.find(text[currentPosition]);
        if (0 <= index2 && index2 < s2.length()) {
            currentPosition++;
            return new Node(l2[index2]);
        } else if (0 <= index3 && index3 < s3.length()) {
            currentPosition++;
            return new Node(l3[index3]);
        } else
            return new Node(l1[index1]);
    }

    // id
    if (isalpha(text[currentPosition])) {
        string s;
        s += text[currentPosition++];
        while (isdigit(text[currentPosition]) || isalpha(text[currentPosition])) {
            s += text[currentPosition++];
        }
        for (int i = 0; i < countWords; i++) {
            if (s == stringWord[i]) {
                return new Node(lexemeWord[i]);
            }
        }
        return new Node(ID, "", s);
    }

    if (!isdigit(text[currentPosition]) && text[currentPosition] != '.') {
        return new Node(ERROR);
    }

    string s;
    if (isdigit(text[currentPosition])) {
        s += text[currentPosition++];
        while (isdigit(text[currentPosition])) {
            s += text[currentPosition++];
        }
        if (text[currentPosition] == '.') {
            s += text[currentPosition++];
            goto N1;
        } else if (text[currentPosition] == 'E' || text[currentPosition] == 'e') {
            s += text[currentPosition++];
            goto N2;
        }
        return new Node(CONST_INT, s);
    }
    if (text[currentPosition] == '.') {
        s += text[currentPosition++];
        if (isdigit(text[currentPosition])) {
            s += text[currentPosition++];
            goto N1;
        }
        return new Node(POINT, s);
    }
    N1:
    while (isdigit(text[currentPosition])) {
        s += text[currentPosition++];
    }
    if (text[currentPosition] == 'E' || text[currentPosition] == 'e') {
        s += text[currentPosition++];
        goto N2;
    }
    return new Node(CONST_DOUBLE, s);
    N2:
    if (text[currentPosition] == '+' || text[currentPosition] == '-') {
        s += text[currentPosition++];
        if (isdigit(text[currentPosition])) {
            s += text[currentPosition++];
            goto N3;
        } else {
            return new Node(ERROR);
        }
    }
    N3:
    while (isdigit(text[currentPosition])) {
        s += text[currentPosition++];
    }

    char *value = new char[s.length() + 1];
    strcpy(value, s.c_str());
    char *str = strtok(value, "Ee");
    double valueDouble = atof(str);
    str = strtok(nullptr, "Ee");
    valueDouble *= pow(10, atoi(str));
    return new Node(CONST_DOUBLE, to_string(valueDouble));
}

Node *Scanner::getCurrentNode() {
    int i = getCurrentPosition();
    Node *pNode = next();
    setCurrentPosition(i);
    return pNode;
}

int Scanner::getCurrentPosition() const {
    return currentPosition;
}

void Scanner::setCurrentPosition(const int position) {
    this->currentPosition = position;
}

Node *Scanner::getNextNode() {
    int i = getCurrentPosition();
    next();
    Node *pNode = next();
    setCurrentPosition(i);
    return pNode;
}

void Scanner::swapGarbageSymbols() {
    while (text[currentPosition] == ' ' ||
           text[currentPosition] == '\n' ||
           text[currentPosition] == '\t' ||
           text[currentPosition] == '\r') {
        currentPosition++;
    }
}

void Scanner::swapComment() {
    if (text[currentPosition] == '/' && text[currentPosition + 1] == '/') {
        currentPosition += 2;
        while (text[currentPosition] != '\n') {
            currentPosition++;
        }
        currentPosition++;
    }
}
