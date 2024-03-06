%{
#include <iostream>
using namespace std;
%}

%option noyywrap

DIGIT [0-9]
LETTER [a-zA-Z]
IDENTIFIER {LETTER}({LETTER}|{DIGIT})*
WHITESPACE [ \t\r\n]

%%

{WHITESPACE}    ;

"//"(.*)     ;


"/*"([^*]|(\*+[^*/]))*"*"+"/"    ;


{IDENTIFIER}    {
                    cout << "IDENTIFIER ";
                }


{DIGIT}+        {
                    cout << "NUMBER ";
                }

.               {
                    cout << "SYMBOL ";
                }

%%

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (inputFile == nullptr) {
        cerr << "Error: Cannot open input file" << endl;
        return 1;
    }

    yyin = inputFile;

    yylex();

    fclose(inputFile);

    return 0;
}
