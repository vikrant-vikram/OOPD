
#include <string>
using namespace std;
class Line {
private:
    string lineName;

public:
    Line(const string& name) : lineName(name) {}

    string getLineName() const {
        return lineName;
    }
};
