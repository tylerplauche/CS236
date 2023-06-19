
#ifndef LAB1_TOKEN_H
#define LAB1_TOKEN_H
#include <string>
#include <iostream>
#include <sstream>


using namespace std;
enum TokenType {
    COMMA, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, PERIOD, Q_MARK, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, END_OF_FILE, ID, STRING, COMMENT,UNDEFINED
};
class Token {
private:
    TokenType type;
    string tokenValue;
    int lineNum;

public:
    string getValue() const {
        return tokenValue;
    }

    Token(TokenType type, string tokenValue,int lineNum) : type(type), tokenValue(tokenValue), lineNum(lineNum){ }


    string toString() const {
        stringstream out;
        out << "(" << typeName(type) << "," << "\"" << tokenValue << "\"" << "," << lineNum << ")" << endl;
        return out.str();
    }

    TokenType getType() const {
        return type;
    }

    string typeName(TokenType type1) const {
        switch (type1) {
            case COMMA:
                return "COMMA";
            case LEFT_PAREN:
                return "LEFT_PAREN";
            case RIGHT_PAREN:
                return "RIGHT_PAREN";
            case COLON:
                return "COLON";
            case COLON_DASH:
                return "COLON_DASH";
            case PERIOD:
                return "PERIOD";
            case Q_MARK:
                return "Q_MARK";
            case MULTIPLY:
                return "MULTIPLY";
            case ADD:
                return "ADD";
            case SCHEMES:
                return "SCHEMES";
            case FACTS:
                return "FACTS";
            case RULES:
                return "RULES";
            case QUERIES:
                return "QUERIES";
            case ID:
                return "ID";
            case STRING:
                return "STRING";
            case COMMENT:
                return "COMMENT";
            case UNDEFINED:
                return "UNDEFINED";
            case END_OF_FILE:
                return "EOF";
            default: return "error";

        }
    }




};


#endif //LAB1_TOKEN_H
