#pragma once

#include <algorithm>
#include "QueueADT.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"

using namespace ExceptionSpace::QueueExceptionSpace;
using namespace std;

/**
 * 初始化队列时，空队列的queueFront=queueBack=0
 * 当插入新元素时，尾指针queueBack+1
 * 当队头元素出队列时，头指针queueFront+1
 * 在非空队列中，头指针始终指向队头元素，而尾指针始终指向队尾元素的下一个位置*/
template<class T>
class ArrayQueue : public queue<T> {
private:
    T *queueArray;//队列的数组表示
    int queueLength;//队列的长度
    int queueFront;//表示队首
    int queueBack;//表示队尾
    int queueSize;//队列中的元素个数

public:
    ArrayQueue(int initialCapacity) {
        queueArray = new T[initialCapacity];
        queueLength = initialCapacity;
        queueFront = 0;
        queueBack = 0;
        queueSize = 0;
    }

    ~ArrayQueue() {
        delete[]queueArray;
    }

    ArrayQueue(const ArrayQueue<T> &theQueue) {
        queueArray = new T[theQueue.queueLength];
        std::copy(begin(theQueue.queueArray), end(theQueue.queueArray), begin(queueArray));
        queueBack = theQueue.queueBack;
        queueFront = theQueue.queueFront;
        queueSize = theQueue.queueSize;
    }


    //ADT

    /* 解决循环队列的队空和队满的状态判断有三种方法
     * 1、少用一个元素空间，即以队尾指针rear+1==front时认为队满，此时队满的条件如下：(rear+1)%MaxQueueSize==front；队空的条件：rear==front
     * 2、设置一个标志位，假设标志位为tag，初始时置tag=0，每当入队操作成功时置tag=1，每当出队操作成功时置tag=0；队空条件：rear==front&&tag==0 队满条件：rear==front&&tag=1
     * 3、设置一个计数器记录队列中元素的个数，假设计数器为count，初始时count=0；每当入队操作成功时count+1；每当出队操作成功时count-1；此时队空的条件：count==0 队满的条件：count>0&&rear==front
     */
    bool empty() const override {
        return queueSize == 0;
    }

    int size() const override {
        //return (queueBack - queueFront + queueLength) % queueLength;//循环队列计算元素个数的公式，这个公式只能计算rear和front不相等时的元素个数，一旦rear==front时无法计算
        return queueSize;
    }

    T front() override {
        if (empty()) {
            throw QueueEmptyException();
        }
        return queueArray[queueFront];
    }

    //直接删除队头元素
    void pop() override {
        if (empty()) {
            throw QueueEmptyException();
        }
        queueArray[queueFront].~T();
        queueFront = (queueFront + 1) % queueLength;
        queueSize--;
    }

    //在删除队头元素之后，返回被删除的队头元素的值
    T pop_catch() override {
        T backUp = queueArray[queueFront];
        pop();
        return backUp;
    }

    //普通的push，如果达到了最大的容量则不能加入元素
    void push(const T &theElement) override {
        if (queueSize > 0 && queueBack == queueFront) {
            //if的条件判断还可以写为queueSize==queueLength
            throw QueueFullException();
        }
        queueArray[queueBack] = theElement;
        queueBack = (queueBack + 1) % queueLength;
        queueSize++;
    }

    //可以增大队列长度，无限向队尾增加元素的push，每一次空间不够的时候，就会申请二倍于原空间的新空间
    void push_infinite(const T &theElement) {
        if ((queueBack + 1) % queueLength == queueFront) {
            //需要增加数组的长度
            T *newQueue = new T[2 * queueLength];
            if (queueBack > queueFront) {
                //队列中的元素没有形成环，也就是将环形队列展开之后，数组中的所有元素紧挨在一起，中间没有空的
                //将front指向的元素直到rear指向的元素之前的元素全部复制到新数组中
                std::copy(queueArray + queueFront, queueArray + (queueBack - 1 > 0 ? queueBack : queueLength), newQueue);
                queueFront = 0;
                queueBack = queueBack - queueFront;
            } else {
                //队列中的元素形成了环
                std::copy(queueArray + queueFront, queueArray + queueLength, newQueue);
                std::copy(queueArray, queueArray + queueBack, newQueue + (queueLength - queueFront));
                queueFront = 0;
                queueBack = queueLength - (queueFront - queueBack);
            }
            queueArray=newQueue;
            queueLength *= 2;
        }
        queueArray[queueBack] = theElement;
        queueBack = (queueBack + 1) % queueLength;
        queueSize++;
    }

    //返回当前队列容量
    int capacity()const{
        return queueLength;
    }
};