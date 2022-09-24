//定义队列的抽象数据类型：队列（队尾插入队首删除）
#pragma once

template<class T>
class queue {
public:
    virtual ~queue() {}

    virtual bool empty() const = 0;//判断容器是否为空

    virtual int size() const = 0;//返回容器元素个数

    virtual T front() = 0;//返回队头元素

    virtual void pop() = 0;//直接删除队头元素

    virtual T pop_catch() = 0;//在删除队头元素后，返回被删除的队头元素的值

    virtual void push(const T &theElement) = 0;//向队尾添加元素
};

//TODO 为某个队列类实现这个接口
//为队列增加输入和输出功能
template<class T>
class ExtendedQueue{
public:
    virtual void userIn()=0;//输入一个队列
    virtual void output()=0;//输出一个队列

};

//支持特殊操作的队列接口
template<class T>
class SpecialOperationQueue{
    virtual void split()=0;//将一个队列分解成两个新队列，一个队列包括原队列的第1、3、5、...个元素，另一个队列包含其余元素
    virtual SpecialOperationQueue* merge(const SpecialOperationQueue<T>&theQueue)const =0;//将两个队列合并成一个新队列，从队列1开始，轮流从两个队列选择元素插入新队列，若某队列为空，则将另一个队列中的剩余元素插入新队列

};