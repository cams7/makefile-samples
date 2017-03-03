#ifndef SALLY_H
#define SALLY_H


class Sally
{
    public:
        Sally();
        Sally(int x, int y);
        /*virtual*/ ~Sally();

        void printShiz();
        void printShiz2() const;
        void print();

    protected:

    private:
        int regVar;
        const int CONST_VAR;
};

#endif // SALLY_H
