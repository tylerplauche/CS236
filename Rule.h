//
// Created by BYU Rental on 2/5/2022.
//

#ifndef UNTITLED_RULE_H
#define UNTITLED_RULE_H


#include "Predicate.h"

class Rule {
private:
    Predicate headPredicate;
    vector<Predicate> bodyPredicates;
public:
    void setHeadPredicate(const Predicate &headPredicate1) {
        this -> headPredicate = headPredicate1;
    }
    void addPredicate(Predicate body){
        bodyPredicates.push_back(body);
    }

    string toString() const {
        stringstream out;
        out << headPredicate.toString() << " :- ";
        for(size_t i = 0; i <bodyPredicates.size(); i++){
            out << bodyPredicates.at(i).toString();
            if(i != bodyPredicates.size() - 1)
                out << ",";
        }
        out << ".";
        return out.str();
    }
};


#endif //UNTITLED_RULE_H
