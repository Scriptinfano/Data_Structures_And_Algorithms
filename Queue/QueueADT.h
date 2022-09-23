//定义队列的抽象数据类型：队列（队尾插入队首删除）
#pragma once

template<class T>
class queue {
public:
    virtual ~queue() {}

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual T &front() = 0;

    virtual void pop() = 0;

    virtual T top()=0;

    virtual void push(const T &theElement) = 0;
};