#ifndef STANKFIRST_H
#define STANKFIRST_H


class StankFirst
{
    public:
        StankFirst(int);
        virtual ~StankFirst();

        void printCrap();
    protected:

    private:
        int number;

    friend void stinkysFriend(StankFirst&);
};

#endif // STANKFIRST_H
