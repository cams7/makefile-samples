#ifndef BASICMATH_H
#define BASICMATH_H

template<class F, class S>
class BasicMath
{
    public:
        BasicMath(F, S);
        virtual ~BasicMath();

        double sum();
        double sub();
        double mult();
        double div();
    protected:

    private:
        F first;
        S secound;
};

#include "../src/BasicMath.cpp"
#endif // BASICMATH_H
