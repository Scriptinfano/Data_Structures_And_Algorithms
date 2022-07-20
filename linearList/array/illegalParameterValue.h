#pragma once
#include<iostream>
#include<string>
using namespace std;

class illegalParameterValue {
private:
    string message;

public:
    illegalParameterValue() : message("非法实参传入") {}

    illegalParameterValue(string theMessage) { message = theMessage; }

    void outPutMessage() const { cout << message << endl; }
};
