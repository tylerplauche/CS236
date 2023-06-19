
#ifndef LAB1_SCANNER_H
#define LAB1_SCANNER_H
#include <string>
#include <vector>
#include <iostream>
#include "Token.h"



using namespace std;

class Scanner {
private:
    string input;
    vector<Token> tokenVector;

public:
    Scanner(const string& input) : input(input) { }
    void print() {
        for (size_t i = 0; i < tokenVector.size(); i++){
            cout << tokenVector.at(i).toString();
        }
        cout << "Total Tokens = " << tokenVector.size() << endl;
    }
    int singleLineComment(){
        int size = 1;
        for(size_t i = 1; i < input.size(); i++){

            if (input.at(i) == '\n'){
                return size;
            }
            size++;
        }
        return size;
    }
    int handleString(int& line, TokenType& type, bool& undefinedString){
        int size = 1;
        for(size_t i = 1; i < input.size(); i++){
            if (input.at(i) == '\n'){
                line++;
            }
            if (input.at(i) == '\''){
                return size + 1;
            }
            size++;
        }
        type = UNDEFINED;
        undefinedString = true;
        return size;
    }
    void scanTokens() {
        int line = 1;
        int size = 0;
        bool undefinedString = false;
        int temp = 0;
        while(input.size() > 0) {
            while (isspace(input.at(0))) {
                if (input.at(0) == '\n'){
                    line++;
                }

                input = input.substr(1);
                if(input.empty()) {
                    break;
                }
            }
            TokenType type = COMMA;
            if(input.empty()) {
                break;
            }
            switch (input.at(0)) {
                // LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, PERIOD, Q_MARK, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES
                case ',':
                    type = COMMA;
                    size = 1;
                    break;
                case '(':
                    type = LEFT_PAREN;
                    size = 1;
                    break;
                case ')':
                    type = RIGHT_PAREN;
                    size = 1;
                    break;
                case ':':
                    type = COLON;
                    size = 1;
                    if(input.at(1) == '-'){
                        type = COLON_DASH;
                        size = 2;
                    }
                    break;
                case '.':
                    type = PERIOD;
                  size = 1;
                    break;
                case '?':
                    type = Q_MARK;
                    size = 1;
                    break;
                case '*':
                    type = MULTIPLY;
                    size = 1;
                    break;
                case '+':
                    type = ADD;
                    size = 1;
                    break;
                case '#':
                    type =  COMMENT;
                    size = singleLineComment();
                    break;
                case '\'': {
                    type = STRING;
                    temp = line;
                    size = handleString(line, type, undefinedString);
                    break;
                }
                default:
                    if(isalpha(input.at(0))){
                        type = ID;
                        size = 1;
                        while (isalnum(input.at(size))){
                            size++;
                        }
                        string idString = input.substr(0,size);
                        if (idString == "Schemes"){
                            type = SCHEMES;
                        }
                        else if (idString == "Facts"){
                            type = FACTS;
                        }
                        else if (idString == "Queries"){
                            type = QUERIES;
                        }
                        else if (idString == "Rules"){
                            type = RULES;
                        }
                    }
                    else {
                        type = UNDEFINED;
                        size = 1;
                    }
                    break;



            }
            string value = input.substr(0, size);
            input = input.substr(size);
            Token t = Token(type, value, line);
            if(undefinedString) {
                t = Token(type, value, temp);
            }
            tokenVector.push_back(t);
        }
        Token eofToken = Token(END_OF_FILE, "", line);
        tokenVector.push_back(eofToken);
    }

    vector<Token> getTokenVector() const {
        return tokenVector;
    }

};


#endif //LAB1_SCANNER_H
