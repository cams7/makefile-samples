#ifndef PEOPLE_H
#define PEOPLE_H

#include <string>
using namespace std;

class People
{
    public:
        People(string);
        virtual ~People();

        void sayName();

        string getName();
    protected:

    private:
        string name;
};

#endif // PEOPLE_H
