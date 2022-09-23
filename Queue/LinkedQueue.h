//用链式存储结构实现队列
#pragma once

#include "QueueADT.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\chainList\ChainNode.h"

//不带头节点的链队列，不带头节点的链队列更简单
template<class T>
class LinkedQueue : public queue<T> {
    using Node = ChainNode<T>;
    using NodePointer = ChainNode<T> *;
private:
    NodePointer head;//队头指针
    NodePointer rear;//队尾指针
    int queueSize;
public:
    LinkedQueue() {
        head = nullptr;
        rear = nullptr;
        queueSize = 0;
    }

    ~LinkedQueue() {
        while (head != rear) {
            NodePointer deleteNode = head;
            head = head->next;
            delete deleteNode;
        }
        delete rear;//此时delete rear和delete head都是可以的，两个都指向同一个节点
    }

    LinkedQueue(const LinkedQueue<T> &theQueue) {
        if (theQueue.empty()) {
            head = nullptr;
            rear = nullptr;
            queueSize = 0;
        } else if (theQueue.rear == theQueue.head) {
            //链表中只有一个节点
            rear = new Node(theQueue.rear->element);
            head = rear;
            queueSize = 1;
        } else {
            //链表中有多个节点
            NodePointer p = theQueue.head;
            head = new Node(p->element);
            NodePointer j = head;
            while (p != theQueue.rear) {
                j->next = new Node(p->element);
                j = j->next;
                p = p->next;
            }
            j->next = new Node(p->element);
            rear = j->next;
            queueSize = theQueue.queueSize;
        }

    }

    bool empty() const override {
        return head == nullptr && rear == nullptr;
    }

    int size() const override {
        return queueSize;
    }

    T &front() override {
        if (empty()) {
            throw QueueEmptyException();
        }
        return head->element;
    }

    void pop() override {
        if (empty()) {
            throw QueueEmptyException();
        }
        if (size() == 1) {
            delete head;
            head = nullptr;
            rear = nullptr;
        } else {
            NodePointer deleteNode = head;
            head = head->next;
            delete deleteNode;
        }
        queueSize--;
    }

    T top() override {
        if (empty())throw QueueEmptyException();
        T backUp = head->element;
        pop();
        return backUp;
    }

    void push(const T &theElement) override {
        if (empty()) {
            rear = new Node(theElement);//第二个指针域的默认值就是nullptr
            head = rear;
        } else {
            rear->next = new Node(theElement);
        }
        queueSize++;
    }
};