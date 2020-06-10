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
    logInfo("variableOpisanie");
}

void Lexer::mainFunctionOpisanie() {
    logInfo("mainFunctionOpisanie");
}

void Lexer::structOpisanie() {
    logInfo("structOpisanie");
}

void Lexer::logInfo(const string &text) {
    cout << "Info: " << text << "." << endl;
}
