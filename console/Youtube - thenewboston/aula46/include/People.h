#ifndef PEOPLE_H
#define PEOPLE_H

#include "Birthday.h"

#include <string>
using namespace std;

class People
{
    public:
        People(string, Birthday&);
        virtual ~People();

        void printInfo();
    protected:

    private:
        string name;
        Birthday& birthday;
};

#endif // PEOPLE_H
