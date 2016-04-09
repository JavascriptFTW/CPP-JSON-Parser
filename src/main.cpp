#include <iostream>
#include <string.h>

#include "Lexer.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Please supply a path to a JSON file." << endl;
        return 1;
    }
    
    Lexer l(argv[1]);
    Lexeme lex;
    while (!!strncmp(lex.type, "EOF", strlen("EOF"))) {
        l.getNextLexeme(&lex);
    }
    
    return 0;
}
