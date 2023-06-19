#ifndef UNTITLED_DATALOG_H
#define UNTITLED_DATALOG_H
#include <vector>
#include "Predicate.h"
#include "Rule.h"
#include <sstream>
#include <set>

class Datalog {
public:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    set<string> domain;
    void addScheme(Predicate pred){
        schemes.push_back(pred);
    }
    void addFact(Predicate pred){
        facts.push_back(pred);
    }
    void addQuery(Predicate pred){
        queries.push_back(pred);
    }
    void addRule(Rule rule){
        rules.push_back(rule);
    }

    string toString() {
        stringstream out;
        out << "Schemes(" << schemes.size() << "):" << endl;
        for(size_t i = 0; i <schemes.size() ; i++){
            out << "  " << schemes.at(i).toString() << endl;
        }
        out << "Facts(" << facts.size() << "):" << endl;
        for(size_t i = 0; i <facts.size() ; i++){
            out << "  " << facts.at(i).toString() << "." << endl;
            vector<string> parameters = facts.at(i).getParameters();
            for(size_t k = 0; k < parameters.size() ; k++){
                string param = parameters.at(k);
                domain.insert(param);
            }
        }
        out << "Rules(" << rules.size() << "):" << endl;
        for(size_t i = 0; i <rules.size() ; i++){
            out << "  " << rules.at(i).toString() << endl;
        }
        out << "Queries(" << queries.size() << "):" << endl;
        for(size_t i = 0; i <queries.size() ; i++){
            out << "  " << queries.at(i).toString() << "?" << endl;
        }
        out << "Domain(" << domain.size() << "):" << endl;

        for (string x :  domain){
            out << "  " << x << endl;

        }
        return out.str();
    }

};


#endif //UNTITLED_DATALOG_H
