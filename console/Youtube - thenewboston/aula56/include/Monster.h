#ifndef MONSTER_H
#define MONSTER_H

#include "Enemy.h"


class Monster : public Enemy
{
    public:
        Monster();
        virtual ~Monster();

        void attack();
    protected:

    private:
};

#endif // MONSTER_H
