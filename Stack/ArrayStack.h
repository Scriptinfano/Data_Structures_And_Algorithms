/*
 * 通过实现接口的方式来实现栈结构*/
#pragma once

#include "StackADT.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\globalFunctionSpace.h"

using namespace GlobalSpace;

template<class T>
class ArrayStack : public StackADT<T> {
private:
    int stackTop;//代表栈顶元素在整个栈中的索引，注意这个索引是从0开始的
    int arrayLength;//栈容量
    T *stack;//元素数组

public:
    //构造函数与析构函数
    ArrayStack(const int &initialCapacity) {
        if (initialCapacity < 1) {
            ostringstream message;
            message << "初始容量必须大于0";
            throw IllegalParameterValue(message.str());//str()将字符串流中的数据复制到string对象中并返回
        }
        arrayLength = initialCapacity;
        stack = new T[arrayLength];
        stackTop = -1;
    }

    ~ArrayStack() {
        delete[]stack;
    }

    //实现接口
    void initializeStack(const vector<T> &array) override {
        //if (array.size() > arrayLength)throw InvalidStackInitializeException();
        if(array.empty())return;
        for(T element:array){
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
        stack[stackTop--].~T();

    }

    void push(const T &theElement) override {

        if (stackTop == arrayLength - 1) {
            changeLength1D(stack, arrayLength, 2 * arrayLength);
            arrayLength *= 2;
        }
        //在栈顶插入元素
        stack[++stackTop] = theElement;//stackTop代表栈顶元素的索引，所以应该先加1得到栈顶元素上面一个位置的索引
    }
};