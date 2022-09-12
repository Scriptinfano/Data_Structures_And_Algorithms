#include "DerivedArrayStack.h"
#include "ArrayStack.h"
#include "TwoStack.h"
#include "LinkedStack.h"
#include <iostream>

using namespace std;

class TestUtil {
public:
    static void testStackBasicFunc() {
        cout << "��һ�����ü̳�ǰ���ArrayList��ʵ�ֵ�ջ" << endl;
        DerivedArrayStack<int> stack(5);
        stack.push(12);
        stack.push(13);
        stack.push(52);
        while (!stack.empty()) {
            cout << stack.getTop() << endl;
            stack.pop();
        }

        cout << "�ڶ���ֱ��ʵ��ջ�Ĳ���" << endl;
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

    //FIXME �˺����ƺ����ڴ�й¶����ȴ����
    static void testStackMerge() {
        ArrayStack<int> stack(10);
        vector<int> vec = {1, 5, 2, 6, 3, 7, 8, 5, 4};
        stack.initializeStack(vec);

        ArrayStack<int> stack2(10);
        vector<int> vec2 = {1, 5, 5, 4};
        stack2.initializeStack(vec2);

        stack.merge(stack2);
        stack.output();

        //�ں�������֮��ִ��ArrayStack����������ʱ�������ظ��ͷ��ڴ�����⣬��ʱ�޷����
    }

    //TODO ΪTwoStack������д���Դ���
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
    TestUtil::testLinkedStack();//C++��ľ�̬��������ֱ��ͨ�������������޶���::ֱ�ӵ���


    return 0;
}

