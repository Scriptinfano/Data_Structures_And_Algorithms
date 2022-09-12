//
// Created by Mingxiang on 2022/9/11.
//

#pragma once

#include "StackADT.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"
#include <vector>

using namespace ExceptionSpace::StackExceptionSpace;

template<class T>
class TwoStack : public StackADT<T> {
private:
    T *array;
    int top1;//指向前栈栈顶
    int top2;//指向后栈栈顶
    int capacity;//栈的容量
public:
    explicit TwoStack(const int &initialCapacity) {
        capacity = initialCapacity;
        array = new T[capacity];
        for (int i = 0; i < capacity; i++) {
            array[i] = 0;
        }
        top1 = -1;
        top2 = capacity;
    }


    ~TwoStack() override {
        delete[]array;
    }

    //判断双栈是否都为空
    [[nodiscard]] bool empty() const override {
        return top1 == -1 && top2 == capacity;
    }

    //返回双栈中元素的个数
    [[nodiscard]] int size() const override {
        return top1 + 1 + (capacity - top2);
    }

    //返回前栈栈顶元素的值
    T getTop() const override {
        if (top1 == -1)throw StackEmptyException("返回前栈元素时，前栈为空");
        return array[top1];
    }

    //返回前栈栈顶元素的引用
    T &top() override {
        if (top1 == -1)throw StackEmptyException("返回前栈元素时，前栈为空");
        return array[top1];
    }

    //返回后栈栈顶元素的值
    T getTop_back() const {
        if (top2 == capacity)throw StackEmptyException("返回后栈栈顶元素时，后栈为空");
        return array[top2];
    }

    //返回后栈栈顶元素的引用
    T &top_back() const {
        if (top2 == capacity)throw StackEmptyException("返回后栈栈顶元素时，后栈为空");
        return array[top2];
    }

    //弹出前栈栈顶元素
    void pop() override {
        if (top1 == -1)throw StackEmptyException("弹出前栈栈顶元素时，前栈为空，无法弹出");
        array[top1--] = 0;
    }

    //弹出后栈栈顶元素
    void pop_back() {
        if (top2 == capacity)throw StackEmptyException("弹出前栈栈顶元素时，前栈为空，无法弹出");
        array[top2++] = 0;
    }

    //在前栈栈顶放入元素
    void push(const T &theElement) override {
        if (full())throw StackFullException();
        array[++top1] = theElement;

    }

    //在后栈栈顶放入元素
    void push_back(const T &theElement) {
        if (full())throw StackFullException();
        array[--top2] = theElement;

    }

    //按照两个栈的插入顺序输出两个栈的元素
    void output() override {
        if(empty())throw StackEmptyException();
        cout << "前栈元素：";
        for (int i = 0; i < top1 + 1; i++) {
            cout << array[i] << " ";
        }
        cout << endl << "后栈元素：";
        for (int i = capacity; i > top2 - 1; i--) {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    //判断两个栈是否已满
    bool full() {
        if (top1 + 1 == top2)return true;
        return false;
    }
};
