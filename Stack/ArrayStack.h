/*
 * 通过实现接口的方式来实现栈结构*/
#pragma once

#include "StackADT.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\globalFunctionSpace.h"

using namespace GlobalSpace;
using namespace ::StackExceptionSpace;

//TODO 完成可初始化接口的设计之后实现该接口，实现初始化录入数据操作
template<class T>
class ArrayStack : public StackADT<T>, public StackExtendFunctionInterface<T> {
    friend void GlobalSpace::changeLength1D(T *&a, int oldLength, int newLength);

private:
    int stackTop;//代表栈顶元素在整个栈中的索引，注意这个索引是从0开始的
    int stackLength;//栈容量
    T *stack;//元素数组

    //该函数确保该类重写基类的纯虚函数，使得该类不为抽象基类，下面的函数不需要写任何实现不需要在任何地方调用
    virtual void pureVirtual() override {}

public:
    //构造函数与析构函数
    ArrayStack(const int &initialCapacity) {
        if (initialCapacity < 1) {
            ostringstream message;
            message << "初始容量必须大于0";
            throw IllegalParameterValue(message.str());//str()将字符串流中的数据复制到string对象中并返回
        }
        stackLength = initialCapacity;
        stack = new T[stackLength];
        stackTop = -1;
    }

    ~ArrayStack() {
        delete[]stack;
    }

    //实现接口
    void initializeStack(const vector<T> &array) override {
        //if (array.size() > stackLength)throw InvalidStackInitializeException();
        if (array.empty())return;
        for (T element: array) {
            this->push(element);
        }
    }

    bool empty() const override {
        return stackTop == -1;
    }

    int size() const override {
        return stackTop + 1;
    }

    T getTop() const override {
        if (stackTop == -1)
            throw StackEmptyException();
        return stack[stackTop];
    }

    T &top() override {
        if (stackTop == -1)
            throw StackEmptyException();
        return stack[stackTop];
    }

    void pop() override {
        if (stackTop == -1)throw StackEmptyException();
        if (stackTop < (stackLength / 4)) {
            //当栈中元素减少到原来的四分之一以下的时候，栈的容量应该减少到当前容量的一半
            changeLength1D(stack, stackLength, stackLength / 2);
        }
        stack[stackTop--].~T();
    }

    void push(const T &theElement) override {

        if (stackTop == stackLength - 1) {
            changeLength1D(stack, stackLength, 2 * stackLength);
            stackLength *= 2;
        }
        //在栈顶插入元素
        stack[++stackTop] = theElement;//stackTop代表栈顶元素的索引，所以应该先加1得到栈顶元素上面一个位置的索引
    }

    ArrayStack<T> *split() override {
        if (empty())throw StackEmptyException();
        int half = size() / 2;
        T *temp = new T[half];
        for (int i = 0; i < half; i++) {
            temp[i] = this->getTop();
            this->pop();
        }
        auto newStack = new ArrayStack(half);
        for (int i = half - 1; i > -1; i--) {
            newStack->push(temp[i]);
        }
        delete[]temp;
        return newStack;
    }

    void merge(StackExtendFunctionInterface<T> &theStack) override {
        //将两个栈合并，不改变第二个栈中元素的相对顺序
        ArrayStack<T> &secondStack = dynamic_cast<ArrayStack<T> &>(theStack);
        changeLength1D(stack, stackLength, secondStack.size());
        auto temp = new ArrayStack(secondStack.size());
        int i = 0;
        while (!secondStack.empty()) {
            temp->push(secondStack.getTop());
            secondStack.pop();
        }
        while (!temp->empty()) {
            this->push(temp->getTop());
            temp->pop();
        }
        delete temp;
    }

};