#ifndef SALLY_H
#define SALLY_H


class Sally
{
    public:
        Sally();
        Sally(double);
        virtual ~Sally();

        double getNumber();

        Sally operator+(Sally&);
        Sally operator-(Sally&);
        Sally operator*(Sally&);
        Sally operator/(Sally&);
        Sally operator%(Sally&);
    protected:

    private:
        double number;
};

#endif // SALLY_H
