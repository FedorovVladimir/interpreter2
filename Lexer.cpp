//
// Created by vladimir on 10.06.2020.
//

#include "Lexer.h"

Lexer::Lexer(Scanner *scanner) {
    this->scanner = scanner;
    this->root = new Node(EMPTY);
    this->currentNode = this->root;
    addNode(new Node(FUNCTION, "", "print"));
    addNode(new Node(FUNCTION, "", "scan"));
}

void Lexer::start() {
    while (!scanner->eof()) {
        if (scanner->getCurrentLexemType() == INT ||
            scanner->getCurrentLexemType() == DOUBLE) {
            variableOpisanie();
        } else if (scanner->getCurrentLexemType() == VOID) {
            mainFunctionOpisanie();
        } else if (scanner->getCurrentLexemType() == STRUCT) {
            structOpisanie();
        } else {
            logErr("I don't know: " + scanner->getCurrentNode()->toString());
        }
    }
}

void Lexer::addNode(Node *node) {
    currentNode->left = node;
    node->parent = currentNode;
    currentNode = currentNode->left;
}

void Lexer::logErr(const string &text) {
    cout << "Error: " << text << "." << endl;
    exit(1);
}

void Lexer::variableOpisanie() {
    scanner->next(); // type
    logInfo("Var: " + scanner->getCurrentNode()->toString());
    expected(ID, "ID");
    expected(POINT_COMMA, "POINT_COMMA");
}

void Lexer::mainFunctionOpisanie() {
    scanner->next(); // void
    expected(MAIN, "MAIN");
    expected(OPEN_KRUGLAY_SKOBKA, "OPEN_KRUGLAY_SKOBKA");
    expected(CLOSE_KRUGLAY_SKOBKA, "CLOSE_KRUGLAY_SKOBKA");
    while (scanner->getCurrentLexemType() == IF ||
           scanner->getCurrentLexemType() == INT ||
           scanner->getCurrentLexemType() == DOUBLE ||
           scanner->getCurrentLexemType() == ID) {
        if (scanner->getCurrentLexemType() == INT ||
            scanner->getCurrentLexemType() == DOUBLE) {
            variableOpisanie();
        } else if (scanner->getCurrentLexemType() == IF) {
            ifOpisanie();
        } else if (scanner->getCurrentLexemType() == ID) {
            saveOpisanie();
        }
    }
    expected(OPEN_FIGURNAY_SKOBKA, "OPEN_FIGURNAY_SKOBKA");
    expected(CLOSE_FIGURNAY_SKOBKA, "CLOSE_FIGURNAY_SKOBKA");
    exit(1);
}

void Lexer::structOpisanie() {
    scanner->next(); // struct
    logInfo("Struct: " + scanner->getCurrentNode()->toString());
    expected(ID, "ID");
    expected(OPEN_FIGURNAY_SKOBKA, "OPEN_FIGURNAY_SKOBKA");
    while (scanner->getCurrentLexemType() == INT ||
           scanner->getCurrentLexemType() == DOUBLE) {
        variableOpisanie();
    }
    expected(CLOSE_FIGURNAY_SKOBKA, "CLOSE_FIGURNAY_SKOBKA");
    expected(POINT_COMMA, "POINT_COMMA");
}

void Lexer::expected(TypeLexeme typeLexeme, const string &text) const {
    if (scanner->getCurrentLexemType() == typeLexeme) {
        scanner->next();
    } else {
        string err;
        err.append("expected " + text + " but found ")
                .append(scanner->getCurrentNode()->toString())
                .append(". Line: ")
                .append(to_string(scanner->getCurrentLine()))
                .append(" Position: ")
                .append(to_string(scanner->getCurrentLinePosition()));
        logErr(err);
    }
}

void Lexer::logInfo(const string &text) {
    cout << "Info: " << text << "." << endl;
}

void Lexer::ifOpisanie() {
    logInfo("ifOpisanie");
}

void Lexer::saveOpisanie() {
    logInfo("saveOpisanie");
}
