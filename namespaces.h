#include <iostream>
using namespace std;

namespace ExceptionSpace {
    class IllegalParameterValue {
    private:
        string message;

    public:
        IllegalParameterValue() : message("�Ƿ�ʵ�δ���") {}

        IllegalParameterValue(string theMessage) { message = theMessage; }

        void OutMessage() const { cout << message << endl; }
    };

}
