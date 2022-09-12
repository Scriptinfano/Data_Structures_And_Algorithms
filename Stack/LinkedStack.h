#pragma once

#include "StackADT.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\chainList\ChainNode.h"

using namespace ExceptionSpace::StackExceptionSpace;

/**
 * 用链表实现的栈，为了效率选择使用链表的左端作为栈的栈顶
 * 该栈没有头节点
 * */
template<class T>
class LinkedStack : public StackADT<T> {
private:
    NodePointer stackTop;//栈顶的指针
    int stackSize;
public:
    LinkedStack() {
        stackTop = nullptr;
        stackSize = 0;
    }

    ~LinkedStack() = default;

    bool empty() const override {
        return stackSize == 0 && stackTop == nullptr;
    }

    int size() const override {
        return stackSize;
    }

    T getTop() const override {
        if (empty())throw StackEmptyException();
        return stackTop->data;
    }

    T &top() override {
        if (empty())throw StackEmptyException();
        return stackTop->data;
    }

    void pop() override {
        if (empty())throw StackEmptyException();
        NodePointer deleteNode = stackTop;
        stackTop = stackTop->next;
        delete deleteNode;
        stackSize--;
    }

    void push(const T &theElement) override {
        NodePointer newNode = nullptr;
        if (empty()) {
            newNode = new Node(theElement, nullptr);//确保第一个节点的指针域为nullptr，以后每次采用头插法插入节点
        } else newNode = new Node(theElement, stackTop);
        stackTop = newNode;
        stackSize++;
    }

    void output() override {
        if (empty())throw StackEmptyException("栈中没有元素，无法输出内容");
        NodePointer p = stackTop;
        while (p != nullptr) {
            cout << p->data << " ";
            p = p->next;
        }
        cout<<endl;
    }
};