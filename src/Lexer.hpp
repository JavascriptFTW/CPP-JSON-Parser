#ifndef __LEXER_H_
#define __LEXER_H_

#include <fstream>

using namespace std;

struct Lexeme {
    char const* type;
    int start;
    int end;
};

class Lexer {
    public:
        Lexer(char const* filePath);
        Lexeme getNextLexeme(Lexeme *dest);
    private:
        fstream file;
        int index;
        char curChar;
        bool loadChar();
};

#endif
