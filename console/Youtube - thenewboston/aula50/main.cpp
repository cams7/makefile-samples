#include "Sally.h"

#include <iostream>

using namespace std;

int main()
{
    Sally a(55);
    Sally b(13);
    Sally c = a + b;
    Sally d = a - b;
    Sally e = a * b;
    Sally f = a / b;
    Sally g = a % b;

    cout << a.getNumber() << " + " << b.getNumber() << " = " << c.getNumber() << endl;
    cout << a.getNumber() << " - " << b.getNumber() << " = " << d.getNumber() << endl;
    cout << a.getNumber() << " * " << b.getNumber() << " = " << e.getNumber() << endl;
    cout << a.getNumber() << " / " << b.getNumber() << " = " << f.getNumber() << endl;
    cout << a.getNumber() << " % " << b.getNumber() << " = " << g.getNumber() << endl;

    return 0;
}
