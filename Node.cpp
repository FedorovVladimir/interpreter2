//
// Created by vladimir on 10.06.2020.
//

#include <sstream>
#include "Node.h"

using namespace std;

Node::Node(TypeLexeme typeLexeme) {
    this->typeLexeme = typeLexeme;
    this->valueInteger = 0;
    this->valueDouble = 0;
}

TypeLexeme Node::getTypeLexem() {
    return this->typeLexeme;
}

string Node::toString() {
    stringstream s;
    switch (this->typeLexeme) {
        case IF:
            s << "IF";
            break;
        case ELSE:
            s << "ELSE";
            break;
        case VOID:
            s << "VOID";
            break;
        case INT:
            s << "INT";
            break;
        case DOUBLE:
            s << "DOUBLE";
            break;
        case MAIN:
            s << "MAIN";
            break;
        case STRUCT:
            s << "STRUCT";
            break;
        case ID:
            s << "ID" << " " << name;
            break;
        case CONST_INT:
            s << "CONST_INT" << " " << valueInteger;
            break;
        case CONST_DOUBLE:
            s << "CONST_DOUBLE" << " " << valueDouble;
            break;
        case PLUS:
            s << "PLUS";
            break;
        case MINUS:
            s << "MINUS";
            break;
        case DIV:
            s << "DIV";
            break;
        case MOD:
            s << "MOD";
            break;
        case MUL:
            s << "MUL";
            break;
        case INC:
            s << "INC";
            break;
        case DEC:
            s << "DEC";
            break;
        case AND:
            s << "AND";
            break;
        case AND_AND:
            s << "AND_AND";
            break;
        case OR:
            s << "OR";
            break;
        case OR_OR:
            s << "OR_OR";
            break;
        case LARGER_LARGER:
            s << "LARGER_LARGER";
            break;
        case LESS_LESS:
            s << "LESS_LESS";
            break;
        case LESS:
            s << "LESS";
            break;
        case LARGER:
            s << "LARGER";
            break;
        case LESS_EQUAL:
            s << "LESS_EQUAL";
            break;
        case LARGER_EQUAL:
            s << "LARGER_EQAL";
            break;
        case EQUAL:
            s << "EQUAL";
            break;
        case NOT_EQUAL:
            s << "NOT_EQUAL";
            break;
        case SAVE:
            s << "SAVE";
            break;
        case POINT_COMMA:
            s << "POINT_COMMA";
            break;
        case OPEN_KRUGLAY_SKOBKA:
            s << "OPEN_KRUGLAY_SKOBKA";
            break;
        case CLOSE_KRUGLAY_SKOBKA:
            s << "CLOSE_KRUGLAY_SKOBKA";
            break;
        case OPEN_FIGURNAY_SKOBKA:
            s << "OPEN_FIGURNAY_SKOBKA";
            break;
        case CLOSE_FIGURNAY_SKOBKA:
            s << "CLOSE_FIGURNAY_SKOBKA";
            break;
        case COMMA:
            s << "COMMA";
            break;
        case POINT:
            s << "POINT";
            break;
        case END_OF_FILE:
            s << "END_OF_FILE";
            break;
        case ERROR:
            s << "ERROR";
            break;
        case EMPTY:
            s << "EMPTY";
            break;
        case FUNCTION:
            s << "FUNCTION" << " " << name;
            break;
    }
    return s.str();
}

Node::Node(TypeLexeme typeLexeme, const string &text, const string &name) {
    this->typeLexeme = typeLexeme;
    this->valueDouble = 0;

    if (typeLexeme == CONST_INT || typeLexeme == INT) {
        valueInteger = stoi(text);
    }

    this->name = name;

    if (typeLexeme == CONST_DOUBLE || typeLexeme == DOUBLE) {
        valueDouble = stof(text);
    }
}

string Node::getName() {
    return name;
}
