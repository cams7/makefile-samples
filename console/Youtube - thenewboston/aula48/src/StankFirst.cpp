#include "StankFirst.h"

#include <iostream>
using namespace std;

StankFirst::StankFirst(int number):
    number(number)
{
    cout << "Create StankFirst" << endl;
}

StankFirst::~StankFirst()
{
    cout << "Destroy StankFirst" << endl;
}

void StankFirst::printCrap(){
    cout << "number: " << number << endl;
    cout << "this->number: " << this->number << endl;
    cout << "(*this).number " << (*this).number << endl;
}
