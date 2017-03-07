#ifndef WINDOW_H
#define WINDOW_H

#include "Screen.h"

class Window : public Screen
{
    public:
        Window(int, int, int, char);
        virtual ~Window();

        Screen& display();
    protected:

    private:
        int origin;
};

#endif // WINDOW_H
