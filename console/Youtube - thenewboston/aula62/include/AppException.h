#ifndef APPEXCEPTION_H
#define APPEXCEPTION_H

#include <string>
using namespace std;

class AppException
{
    public:
        AppException(string, unsigned int);
        virtual ~AppException();

        string getMessage();
        unsigned int getCode();
    protected:

    private:
        string message;
        unsigned int code;
};

#endif // APPEXCEPTION_H
