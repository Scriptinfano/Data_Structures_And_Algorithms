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

//扩充栈类方法的接口，接口中的方法可以选择实现
template<class T>
class StackExtendFunctionInterface {
private:
    //该抽象基类的功能可以选择实现重写，为了确保该类不能实例化对象，将下面的函数声明为纯虚函数，也就是说该类所代表的是一个不需要实现所有方法的接口
    virtual void pureVirtual()=0;//该函数没有任何实质作用，是一个可以让该类变为抽象基类的纯虚函数，在子类中空实现即可

public:
    virtual ~StackExtendFunctionInterface() =default;
    virtual StackExtendFunctionInterface *split(){}//将栈分裂成两个栈，第一个栈包含从栈底开始的一半元素，第二个包含剩余的元素，函数返回第二个栈的指针
    virtual void merge(StackExtendFunctionInterface &theStack){}//将两个栈合并，将第二个栈的所有元素置于第一个栈的顶部，不改变第二个栈中元素的相对顺序
};

