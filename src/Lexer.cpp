#include <iostream>
#include <fstream>
#include <string.h>

#include "Lexer.hpp"

using namespace std;

Lexer::Lexer(char const* filePath) : file(filePath) {
    index = 0;
};

Lexeme Lexer::getNextLexeme(Lexeme *dest) {
    Lexeme lex;
    
    lex.start = index;
    
    // If we've reached the end of the file (i.e. we can't load any more
    // characters).
    if (!loadChar()) {
        lex.type = "EOF";
        lex.start = index;
        lex.end = index;
        *dest = lex;
        return lex;
    }
    
    switch (current) {
        case '{':
            lex.type = "OpenBrace";
            break;
        case '}':
            lex.type = "CloseBrace";
            break;
        case '"':
            lexString(&lex);
            break;
        case '[':
            lex.type = "OpenBracket";
            break;
        case ']':
            lex.type = "CloseBracket";
            break;
        case ':':
            lex.type = "Colon";
            break;
        case ',':
            lex.type = "Comma";
            break;
        default:
            if (current >= '0' && current <= '9' || current == '-' ||
                current == '+') {
                lexNumber(&lex);
            } else if (current == 't' && matchesKeyword("rue")) {
                lex.type = "Keyword";
            } else if (current == 'f' && matchesKeyword("alse")) {
                lex.type = "Keyword";
            } else if (current == 'n' && matchesKeyword("ull")) {
                lex.type = "Keyword";
            } else {
                lex.type = "Unknown";
            }
    }
    
    lex.end = index;
    
    *dest = lex;
    return lex;
}

bool Lexer::loadChar() {
    bool noFileEnd;
    
    do {
        noFileEnd = loadCharWS();
    } while (noFileEnd && isEmpty(current));
    
    return noFileEnd;
}

bool Lexer::loadCharWS() {
    ++index;
    return file >> noskipws >> current;
}

bool Lexer::isEmpty(char ch) {
    return (ch == ' ' || ch == '\n' || ch == '\v' || ch == '\r' || ch == '\f' ||
        ch == '\t');
}

void Lexer::lexString(Lexeme *lex) {
    lex->type = "String";
    
    bool ignore = false;
    
    while (loadChar() && (current != '"' && !ignore)) {
        ignore = (current == '\\');
    }
}

void Lexer::lexNumber(Lexeme *lex) {
    lex->type = "Number";
    if (current == '-' || current == '+') {
        loadCharWS();
    }
    eatNumberPart();
    if (current == 'e' || current == 'E') {
        loadCharWS();
        eatNumberPart();
    }
}

void Lexer::eatNumberPart() {
    do {
        // TODO (Joshua): Add stuff to token raw value here.
    } while (loadCharWS() && ((current >= '0' && current <= '9') ||
        current == '.'));
}

bool Lexer::matchesKeyword(char const *keyword) {
    char ch;
    for (int i = 0; i < strlen(keyword); ++i) {
        ++index;
        if (!(file >> noskipws >> current) || current != keyword[i]) {
            return false;
        }
    }
    return true;
}
