#include "Lexer.hpp"
#include <iostream>
#include <fstream>

using namespace std;

Lexer::Lexer(char const* filePath) : file(filePath) {
    index = 0;
};

Lexeme Lexer::getNextLexeme(Lexeme *dest) {
    Lexeme lex;
    
    if (!loadChar()) {
        lex.type = "EOF";
        lex.start = index;
        lex.end = index;
        *dest = lex;
        return lex;
    }
    
    lex.start = index;
    
    lex.type = "MISSING_NO";
    
    lex.end = index;
    
    *dest = lex;
    return lex;
}

bool Lexer::loadChar() {
    ++index;
    return file >> noskipws >> curChar;
}
