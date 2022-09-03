#include "DerivedArrayStack.h"
#include "ArrayStack.h"
#include <iostream>

using namespace std;

int main() {
    cout<<"第一个采用继承前面的ArrayList类实现的栈（有性能损失）"<<endl;
    DerivedArrayStack<int> stack(5);
    stack.push(12);
    stack.push(13);
    stack.push(52);
    while (!stack.empty()) {
        cout << stack.getTop() << endl;
        stack.pop();
    }
    cout<<"第二个直接采用内部数组实现的栈"<<endl;
    ArrayStack<int> stack2(5);
    stack2.push(13);
    stack2.push(14);
    stack2.push(151);
    stack2.push(143);
    while (!stack2.empty()) {
        cout << stack2.getTop() << endl;
        stack2.pop();
    }


    return 0;
}