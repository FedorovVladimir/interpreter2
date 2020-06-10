#include <iostream>
#include <fstream>
#include "Scanner.h"
#include "Lexer.h"

using namespace std;

string readCodeFromFile(const string &filePath) {
    string text;

    // открываем файл
    ifstream fin(filePath); // открыли файл для чтения

    // проверка файла
    if (!fin) {
        cout << "File " << filePath << " not found!" << endl;
        exit(0);
    }

    // чтение файла
    char buffer[80];
    while (!fin.eof()) {
        fin.getline(buffer, 80);
        text.append(buffer).append("\n");
    }

    // закрываем файл
    fin.close();

    return text;
}

int main() {
    // читаем файл кода
    string text = readCodeFromFile("/home/vladimir/CLionProjects/interpreter/code/code.soda");

    // создаем сканер
    auto *scanner = new Scanner(text);

//    while (!scanner->eof()) {
//        cout << scanner->getCurrentNode()->toString() << endl;
//        scanner->next();
//    }

    // создаем лексер
    auto *lexer = new Lexer(scanner);
    lexer->start();

    return 0;
}
