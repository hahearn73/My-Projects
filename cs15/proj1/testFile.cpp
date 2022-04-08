#include <iostream> 
using namespace std;

bool isNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

int main() {
    string input;
    int n; // used to add new datum(n) to stack
    while (true) {
        
    }
    return 0;
}