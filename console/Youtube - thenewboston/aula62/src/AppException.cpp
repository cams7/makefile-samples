#include "AppException.h"

#include <iostream>
using namespace std;

AppException::AppException(string message, unsigned int code):
    message(message), code(code)
{
    cout << "Create AppException" << endl;
}

AppException::~AppException()
{
    cout << "Destroy AppException" << endl;
}

string AppException::getMessage() {
    return message;
}

unsigned int AppException::getCode(){
    return code;
}
