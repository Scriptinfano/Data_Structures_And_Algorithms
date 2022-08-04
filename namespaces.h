#include <iostream>
using namespace std;

namespace ExceptionSpace {
    class IllegalParameterValue {
    private:
        string message;

    public:
        IllegalParameterValue() : message("非法实参传入") {}

        IllegalParameterValue(string theMessage) { message = theMessage; }

        void OutMessage() const { cout << message << endl; }
    };

}
