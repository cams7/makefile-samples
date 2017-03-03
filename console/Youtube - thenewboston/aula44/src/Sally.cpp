#include "Sally.h"
#include <iostream>

using namespace std;

Sally::Sally(): regVar(0), CONST_VAR(0)
{
    cout << "I'm constructor of Sally" << endl;
}

Sally::Sally(int x, int y): regVar(x), CONST_VAR(y)
{
    cout << "I'm constructor of Sally with parameters: x = " << x << ", y = " << y << endl;
}

Sally::~Sally()
{
    cout << "I'm destructor of Sally" << endl;
}

void Sally::printShiz(){
    cout << "I'm regular function" << endl;
}

void Sally::printShiz2() const{
    cout << "I'm const function" << endl;
}

void Sally::print(){
    cout << "regVar: " << regVar << ", CONST_VAR: " << CONST_VAR << endl;
}
