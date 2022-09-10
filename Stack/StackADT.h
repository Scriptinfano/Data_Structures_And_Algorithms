//
// Created by Mingxiang on 2022/9/3.
//
#pragma once

template<class T>
class StackADT {
public :
    virtual ~StackADT() =default;

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual T getTop() const = 0;

    virtual T &top() = 0;

    virtual void pop() = 0;

    virtual void push(const T &theElement) = 0;

    virtual void initializeStack(const vector<T> &array) = 0;

};

//扩充栈类方法的接口
template<class T>
class StackExtendFunctionInterface {
public:
    virtual ~StackExtendFunctionInterface() =default;
    virtual StackExtendFunctionInterface *split() = 0;//将栈分裂成两个栈，第一个栈包含从栈底开始的一半元素，第二个包含剩余的元素，函数返回第二个栈的指针
    virtual void merge(StackExtendFunctionInterface &theStack) = 0;//将两个栈合并，将第二个栈的所有元素置于第一个栈的顶部，不改变第二个栈中元素的相对顺序
};

