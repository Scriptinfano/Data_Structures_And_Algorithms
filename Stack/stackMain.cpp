#include "DerivedArrayStack.h"
#include "ArrayStack.h"
#include <iostream>

using namespace std;
class TestUtil {
public:
    static void testStackBasicFunc() {
        cout << "第一个采用继承前面的ArrayList类实现的栈" << endl;
        DerivedArrayStack<int> stack(5);
        stack.push(12);
        stack.push(13);
        stack.push(52);
        while (!stack.empty()) {
            cout << stack.getTop() << endl;
            stack.pop();
        }

        cout << "第二个直接实现栈的操作" << endl;
        ArrayStack<int> stack2(5);
        stack2.push(13);
        stack2.push(14);
        stack2.push(151);
        stack2.push(143);
        while (!stack2.empty()) {
            cout << stack2.getTop() << endl;
            stack2.pop();
        }

    }
};
int main() {
    TestUtil util;
    util.testStackBasicFunc();

    return 0;
}

