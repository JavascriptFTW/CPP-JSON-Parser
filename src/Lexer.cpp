#include <iostream>
#include <fstream>

#include "Lexer.hpp"

using namespace std;

Lexer::Lexer(char const* filePath) : file(filePath) {
    index = 0;
};

Lexeme Lexer::getNextLexeme(Lexeme *dest) {
    char curChar;
    Lexeme lex;
    
    // If we've reached the end of the file (i.e. we can't load any more
    // characters).
    if (!loadChar(&curChar)) {
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

bool Lexer::loadChar(char *ch) {
    ++index;
    return file >> noskipws >> *ch;
}
