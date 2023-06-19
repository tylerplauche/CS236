#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H
#include <vector>
#include <iostream>
#include "Token.h"
#include "Parameter.h"
#include "Datalog.h"
using namespace std;
class Parser {
private:
    vector<Token> tokens;
    Datalog datalog;
public:
    Parser(const vector<Token>& tokens) : tokens(tokens) { }
    TokenType tokenType() const {
        return tokens.at(0).getType();
    }
    void advanceToken() {
        tokens.erase(tokens.begin());
    }
    void throwError() {
        throw tokens.at(0);
       // cout << "error" << endl;
    }
    string tokenValue() const{
        return tokens.at(0).getValue();
    }
    void match(TokenType t) {
        //cout << "match: " << t << endl;
        if(tokens.at(0).getType() == TokenType::COMMENT)
            advanceToken();
        if (tokenType() == t)
            advanceToken();
        else {

            throwError();
        }
    }
    void idList(Predicate &scheme) {
        if (tokenType() == COMMA) {
            match(COMMA);
            scheme.addParameter(tokenValue());
            match(ID);
            idList(scheme);
        } else {
            // lambda
        }
    }
    void stringList(Predicate &fact) {
        //COMMA STRING stringList | lambda
        if (tokenType() == COMMA) {
            match(COMMA);
            fact.addParameter(tokenValue());
            match(STRING);
            stringList(fact);
        } else {
            // lambda
        }
    }
    void parameterList(Predicate &pred) {
        //COMMA parameter parameterList
        if (tokenType() == COMMA) {
            match(COMMA);
            parameter(pred);
            parameterList(pred);
        }
        else {
            // lambda
        }
    }
    void predicateList(Rule &rule){

        if (tokenType() == COMMA) {
            match(COMMA);
            rule.addPredicate(predicate());
            predicateList(rule);
        }
        else {
            // lambda
        }
    }
    Predicate headPredicate() {
        Predicate head;
        head.setName(tokenValue());
        match(ID);
        match(LEFT_PAREN);
        head.addParameter(tokenValue());
        match(ID);
        idList(head);
        match(RIGHT_PAREN);
        return head;
    }
    Predicate predicate() {
        Predicate pred;
        pred.setName(tokenValue());
        match(ID);
        match(LEFT_PAREN);
        parameter(pred);
        parameterList(pred);
        match(RIGHT_PAREN);
        return pred;
    }
    void parameter(Predicate &pred) {
        if(tokenType() == STRING) {
            pred.addParameter(tokenValue());
            match(STRING);
        }
        else if (tokenType() == ID) {
            pred.addParameter(tokenValue());
            match(ID);
        }
        else {
            throwError();
        }
    }
    void scheme() {
        Predicate scheme;
        scheme.setName(tokenValue());
        match(ID);
        match(LEFT_PAREN);
        scheme.addParameter(tokenValue());
        match(ID);
        idList(scheme);
        match(RIGHT_PAREN);
        datalog.addScheme(scheme);

    }
    void fact(){
        Predicate fact;
        fact.setName(tokenValue());
        match(ID);
        match(LEFT_PAREN);
        fact.addParameter(tokenValue());
        match(STRING);
        stringList(fact);
        match(RIGHT_PAREN);
        match(PERIOD);
        datalog.addFact(fact);
    }
    void rule(){
        Rule rule;
        rule.setHeadPredicate(headPredicate());
        match(COLON_DASH);
        rule.addPredicate(predicate());
        predicateList(rule);
        match(PERIOD);
        datalog.addRule(rule);
    }
    void query(){
        Predicate query = predicate();
        match(Q_MARK);
        datalog.addQuery(query);
    }
    void schemeList() {
        if(tokenType() == ID) {
            scheme();
            schemeList();
        }
        else{
            //lambda
        }
    }
    void factList() {
        if(tokenType() == ID) {
            fact();
            factList();
        }
        else {
            //lambda
        }
    }
    void ruleList() {
        if(tokenType() != QUERIES) {
            rule();
            ruleList();
        }
        else {
            //lambda
        }
    }
    void queryList() {
        if(tokenType() != END_OF_FILE) {
            query();
            queryList();
        }
        else {
            //lambda
        }
    }
    void datalogProgram(){

        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();
        match(FACTS);
        match(COLON);
        factList();
        match(RULES);
        match(COLON);
        ruleList();
        match(QUERIES);
        match(COLON);
        query();
        queryList();
        match(END_OF_FILE);
        cout << "Success!" << endl;
        cout << datalog.toString();
    }



};


#endif //UNTITLED_PARSER_H
