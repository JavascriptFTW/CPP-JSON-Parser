#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "Lexer.hpp"

using namespace std;

Lexer::Lexer(char const* filePath) : file(filePath) {
    index = 0;
};

void Lexer::getNextLexeme(Lexeme *lex) {
    lex->start = index;
    
    // If we've reached the end of the file (i.e. we can't load any more
    // characters).
    if (!loadChar()) {
        lex->type = "EOF";
        lex->end = index;
        lex->raw = "";
        return;
    }
    
    // Default to just setting the raw to the current character as that's
    // the behavior of the majority of tokens.
    lex->raw = current;
    
    switch (current) {
        case '{':
            lex->type = "OpenBrace";
            break;
        case '}':
            lex->type = "CloseBrace";
            break;
        case '"':
            lexString(lex);
            break;
        case '[':
            lex->type = "OpenBracket";
            break;
        case ']':
            lex->type = "CloseBracket";
            break;
        case ':':
            lex->type = "Colon";
            break;
        case ',':
            lex->type = "Comma";
            break;
        default:
            if (current >= '0' && current <= '9' || current == '-' ||
                current == '+') {
                lexNumber(lex);
            } else if (current == 't' && matchesKeyword("rue")) {
                lex->type = "Keyword";
                lex->raw = "true";
            } else if (current == 'f' && matchesKeyword("alse")) {
                lex->type = "Keyword";
                lex->raw = "false";
            } else if (current == 'n' && matchesKeyword("ull")) {
                lex->type = "Keyword";
                lex->raw = "null";
            } else {
                lex->type = "Unknown";
            }
    }
    
    lex->end = index;
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
        lex->raw += current;
    }
    lex->raw += current;
}

void Lexer::lexNumber(Lexeme *lex) {
    lex->type = "Number";
    // Skip the first character as it was taken care of in getNextLexeme()
    loadCharWS();
    eatNumberPart(lex);
    if (current == 'e' || current == 'E') {
        lex->raw += current;
        loadCharWS();
        eatNumberPart(lex);
    }
}

void Lexer::eatNumberPart(Lexeme *lex) {
    do {
        lex->raw += current;
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
