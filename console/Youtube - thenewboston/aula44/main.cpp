#include "Sally.h"

#include <iostream>

using namespace std;

int main()
{
    Sally sally;
    sally.printShiz();
    sally.printShiz2();
    sally.print();

    Sally* sallyPointer = &sally;
    sallyPointer->printShiz();
    sallyPointer->printShiz2();
    sallyPointer->print();

    const Sally SALLY2;
    SALLY2.printShiz2();

    Sally sally3(10,15);
    sally3.print();

    Sally* sally4 = new Sally(29, 34);
    sally4->print();

    cout << "Hello world!" << endl;
    return 0;
}
