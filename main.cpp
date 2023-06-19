#include <iostream>
#include <fstream>
#include <sstream>
#include "Scanner.h"
#include "Parser.h"
#include "Relation.h"

using namespace std;
int main(int argc, char* argv[]) {
    //check input
    if (argc < 2)
    {
        cerr << "Please provide name of input file";

    }

    ifstream in(argv[1]);
    if (!in.is_open())
    {
        cerr << "Unable to open " << argv[1] << " for input";
        //return 1;
    }
    ostringstream os;
    os << in.rdbuf();
    string fileString = os.str();

    Scanner s = Scanner(fileString);
    s.scanTokens();


    Parser p = Parser(s.getTokenVector());
    try {
        p.datalogProgram();
    }
    catch(Token s){
        cout << "Failure!" << endl << "  " << s.toString();
    }
    vector<string> names = { "ID", "Name", "Major" };

    Scheme scheme(names);

    Relation relation("student", scheme);

    vector<string> values[] = {
            {"'42'", "'Ann'", "'CS'"},
            {"'32'", "'Bob'", "'CS'"},
            {"'64'", "'Ned'", "'EE'"},
            {"'16'", "'Jim'", "'EE'"},
    };

    for (auto& value : values) {
        Tuple tuple(value);
        cout << tuple.toString(scheme) << endl;
        relation.addTuple(tuple);
    }

    cout << "relation:" << endl;
    cout << relation.toString();

    Relation result = relation.select(2, "'CS'");

    cout << "select Major='CS' result:" << endl;
    cout << result.toString();
}