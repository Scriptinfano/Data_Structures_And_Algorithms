
#pragma once

//双端队列的抽象基类
template<class  T>
class MyAbstractDeque{
public:
    virtual bool empty()=0;
    virtual int size()=0;
    virtual T&front()=0;
    virtual T&back()=0;
    virtual void push_back(T&theElement)=0;
    virtual void push_front(T&theElement)=0;
    virtual void pop_front()=0;
    virtual void pop_back()=0;
    virtual void clear()=0;
};