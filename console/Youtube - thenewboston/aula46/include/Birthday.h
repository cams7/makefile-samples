#ifndef BIRTHDAY_H
#define BIRTHDAY_H

class Birthday
{
    public:
        Birthday(unsigned int, unsigned int, unsigned int);
        virtual ~Birthday();

        void printDate();

    protected:

    private:
        unsigned int year;
        unsigned int month;
        unsigned int day;
};

#endif // BIRTHDAY_H
