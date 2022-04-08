// Harry Ahearn

#include <iostream>
using namespace std;

int f(int *z);

int main() // prints out -1 0
{
    int    m = 5, n;

    n = f(&m);

    cout << m << " " << n << endl;

    return 0;
}

int f(int *z)
{
    if ( *z <= 0 )
        return *z + 1;

    *z -= 2;

    return f(z);
}