#ifndef DAUGHTER_H
#define DAUGHTER_H

#include "People.h"
#include "Mother.h"

class Daughter : public People
{
    public:
        Daughter(string);
        Daughter(string, Mother&);
        virtual ~Daughter();

        Mother* getMother();

    protected:

    private:
        Mother* mother;
};

#endif // DAUGHTER_H
