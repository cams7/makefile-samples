#include "BasicMath.h"

#include <iostream>
using namespace std;

int main()
{
    BasicMath<long, int> math1(151, 26);
    cout << "Sum: " << math1.sum() << endl;
    cout << "Subtract: " << math1.sub() << endl;
    cout << "Multiply: " << math1.mult() << endl;
    cout << "Divide: " << math1.div() << endl;

    cout << endl;
    BasicMath<double, float> math2(1578.45, 26.89);
    cout << "Sum: " << math2.sum() << endl;
    cout << "Subtract: " << math2.sub() << endl;
    cout << "Multiply: " << math2.mult() << endl;
    cout << "Divide: " << math2.div() << endl;

    return 0;
}
