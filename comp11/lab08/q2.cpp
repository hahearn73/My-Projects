// Harry Ahearn

#include <iostream>
using namespace std;

// this outputs: "9 16 9 16"
int main() {
        int m, n;
        int *p1, *p2;

        p1 = &m;
        p2 = &n;
        *p1 = 8;
        *p2 = (*p1)++;
        *p2 += *p2;

        cout << m << " " << n << " " << *p1 << " " << *p2 << endl;

    return 0;
}