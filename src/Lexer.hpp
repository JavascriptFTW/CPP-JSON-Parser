#ifndef __LEXER_H_
#define __LEXER_H_

#include <fstream>

using namespace std;

// No one using Lexemes will not want the Lexer class and vice-versa so just
// put them in the same file.
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
        char current;
        fstream file;
        int index;
        bool loadChar();
        bool loadCharWS();
        bool isEmpty(char ch);
        void lexString(Lexeme *lex);
        void lexNumber(Lexeme *lex);
        void eatNumberPart();
        bool matchesKeyword(char const* keyword);
};

#endif
