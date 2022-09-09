#pragma once
//本头文件定义各种链表的节点，因为不同的链表需要不同的节点

#include <iostream>

using namespace std;

template<class T>
class ChainNode {
public:
    T element;//链表节点的数据域
    ChainNode<T> *next;//链表节点的指针域

    //数据域未知，指针域明确的构造函数
    ChainNode() = default;

    ChainNode(ChainNode<T> *theNext) : element(*(new T)), next(theNext) {}

    //指定数据域和指针域的标准构造函数
    ChainNode(const T &theElement, ChainNode<T> *theNext = nullptr) : element(theElement), next(theNext) {}

};

class Node {
    using NodePointer = Node *;
public:
    int data;
    Node *next;

    Node(const int &data, Node *theNext) {
        this->data = data;
        next = theNext;
    }

    Node(Node *theNext) {
        next = theNext;
    }
};

using NodePointer = Node *;

//定义双向循环链表节点
template<class T>
class DoublyNode {
public://别名
    using pointer = DoublyNode<T> *;
    using node = DoublyNode<T>;
private://私有成员
    T element;
    pointer previous;
    pointer next;
public://构造与析构与拷贝构造函数
    DoublyNode(const pointer &thePrevious, const T &theElement, const pointer &theNext) : previous(thePrevious), element(theElement), next(theNext) {}

    DoublyNode() = default;

    DoublyNode(const node &theNode) {
        const pointer thePrevious = theNode.getPrevious();
        const T theElement = theNode.getElement();
        const pointer theNext = theNode.getNext();
        this->set(thePrevious, theElement, theNext);
    }

public://公有接口
    void setPrevious(const pointer &thePrevious) { previous = thePrevious; }

    void setNext(const pointer &theNext) { next = theNext; }

    void setElement(const T &theElement) { element = theElement; }

    void set(const pointer &thePrevious, const T &theElement, const pointer &theNext) {
        next = theNext;
        element = theElement;
        previous = thePrevious;
    }

    //以值的方式返回成员
    pointer getNext() const { return next; }

    pointer getPrevious() const { return previous; }

    T getElement() const { return element; }

    //以引用的方式返回成员
    pointer &theNext() { return next; }

    pointer &thePrevious() { return previous; }

    T &theElement() { return element; }

};

