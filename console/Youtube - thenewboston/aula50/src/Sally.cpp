#include "Sally.h"

#include <iostream>
using namespace std;

Sally::Sally():
    number(0)
{
    cout << "Create Sally" << endl;
}

Sally::Sally(double number):
    number(number)
{
    cout << "Create Sally with param: number = " << number << endl;
}

Sally::~Sally()
{
    cout << "Destroy Sally" << endl;
}


Sally Sally::operator+(Sally& sally){
    Sally newSally;
    newSally.number = this->number + sally.number;
    return newSally;
}

Sally Sally::operator-(Sally& sally){
    Sally newSally;
    newSally.number = this->number - sally.number;
    return newSally;
}

Sally Sally::operator*(Sally& sally){
    Sally newSally;
    newSally.number = this->number * sally.number;
    return newSally;
}

Sally Sally::operator/(Sally& sally){
    Sally newSally;
    newSally.number = this->number / sally.number;
    return newSally;
}

Sally Sally::operator%(Sally& sally){
    Sally newSally;
    newSally.number = (int)this->number % (int)sally.number;
    return newSally;
}

double Sally::getNumber(){
    return number;
}
