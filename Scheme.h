#include <string>
#include <vector>
using namespace std;
class Scheme : public vector<string> {

public:

    Scheme(vector<string> names) : vector<string>(names) { }

};