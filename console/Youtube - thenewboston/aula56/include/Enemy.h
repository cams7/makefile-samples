#ifndef ENEMY_H
#define ENEMY_H


class Enemy
{
    public:
        Enemy();
        virtual ~Enemy();

        virtual void attack() = 0;
    protected:

    private:
};

#endif // ENEMY_H
