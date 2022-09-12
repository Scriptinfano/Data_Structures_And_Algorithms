#include "DerivedArrayStack.h"
#include "ArrayStack.h"
#include "TwoStack.h"
#include "LinkedStack.h"
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

    static void testStackSplit() {
        ArrayStack<int> stack(10);
        vector<int> vec = {1, 5, 2, 6, 3, 7, 8, 5, 4};
        stack.initializeStack(vec);
        auto result = stack.split();
        result->output();

    }

    //FIXME 此函数似乎有内存泄露问题等待解决
    static void testStackMerge() {
        ArrayStack<int> stack(10);
        vector<int> vec = {1, 5, 2, 6, 3, 7, 8, 5, 4};
        stack.initializeStack(vec);

        ArrayStack<int> stack2(10);
        vector<int> vec2 = {1, 5, 5, 4};
        stack2.initializeStack(vec2);

        stack.merge(stack2);
        stack.output();

        //在函数结束之后执行ArrayStack的析构函数时可能有重复释放内存的问题，暂时无法解决
    }

    //TODO 为TwoStack容器编写测试代码
    static void testTwoStack() {
        TwoStack<int> twoStack(20);
        twoStack.push(12);
    }
    static void testLinkedStack(){
        LinkedStack<int>linkStack;
        linkStack.push(12);
        linkStack.push(41);
        linkStack.push(78);
        linkStack.output();
    }
};

int main() {
    TestUtil::testLinkedStack();//C++类的静态函数可以直接通过类名加类名限定符::直接调用


    return 0;
}

