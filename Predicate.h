#ifndef UNTITLED_PREDICATE_H
#define UNTITLED_PREDICATE_H
#include <string>
#include <vector>
#include <ostream>
#include <sstream>

using namespace std;

class Predicate {
private:
    string name;
    vector<string> parameters;
public:

    void setName(const string &name1) {
        this -> name = name1;
    }
    void addParameter(string param){
        parameters.push_back(param);
    }

     const vector<string> getParameters() const {
        return parameters;
    }

    string toString() const {
        stringstream out;
        out << name << "(";
        for(size_t i = 0; i <parameters.size(); i++){
            out << parameters.at(i);
            if(i != parameters.size() - 1)
            out << ",";
            }
        out << ")";
        return out.str();
    }
};


#endif //UNTITLED_PREDICATE_H
