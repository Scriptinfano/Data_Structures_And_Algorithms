#include <iostream>

using namespace std;

class person {
    int a;
public:
    person(int param) : a(param) {}

    ~person() { cout << "person的析构函数调用"; }
};

void test() {

    auto temp = new person(12);
    delete temp;

}

int main() {
    test();
    return 0;
}
