//基于数组实现的双端队列
#pragma once

#include "abstractDeque.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"
#include <iostream>

using namespace ExceptionSpace::DequeExceptionSpace;

//数组实现的双端队列
template<class T>
class MyArrayDeque : public MyAbstractDeque<T> {
private:
    int head;
    int rear;
    int capacity;
    T *dequeArray;
public:
    explicit MyArrayDeque(int theCapacity) : capacity(theCapacity) {
        head = 0;
        rear = 1;
        dequeArray = new T[theCapacity];
    }

    MyArrayDeque(const MyArrayDeque &theDeque) {
        head = theDeque.head;
        rear = theDeque.rear;
        capacity = theDeque.capacity;
        dequeArray = new T[capacity];
        std::copy(dequeArray, theDeque.dequeArray, theDeque.dequeArray + capacity - 1);
    }

    bool empty() override {
        if ((head + 1) % capacity == rear)
            return true;
        else return false;
    }

    int size() override {
        return (rear - head - 1 + capacity) % capacity;
    }

    T &front() override {
        if (empty())throw DequeEmptyException();
        return dequeArray[(head + 1) % capacity];
    }

    T &back() override {
        if (empty())throw DequeEmptyException();
        return dequeArray[(rear - 1 + capacity) % capacity];
    }

    void push_back(T &theElement) override {
        if (size() == capacity)throw DequeFullException();
        dequeArray[rear] = theElement;
        rear = (rear + 1) % capacity;

    }

    void push_front(T &theElement) override {
        if (size() == capacity)throw DequeFullException();
        dequeArray[head] = theElement;
        head = (head - 1 + capacity) % capacity;
    }

    void pop_front() override {
        if (empty())throw DequeEmptyException();
        head = (head + 1) % capacity;
    }

    void pop_back() override {
        if (empty())throw DequeEmptyException();
        rear = (rear - 1 + capacity) % capacity;
    }

    void clear() override {
        head = 0;
        rear = 1;
        delete[]dequeArray;
        dequeArray = new T[capacity];
    }
};
