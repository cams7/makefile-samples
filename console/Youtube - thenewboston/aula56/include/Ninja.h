#ifndef NINJA_H
#define NINJA_H

#include "Enemy.h"


class Ninja : public Enemy
{
    public:
        Ninja();
        virtual ~Ninja();

        void attack();
    protected:

    private:
};

#endif // NINJA_H
