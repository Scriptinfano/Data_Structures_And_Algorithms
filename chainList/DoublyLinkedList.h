#pragma once

#include <iostream>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\virtualBaseClassLinearList.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\namespaces.h"
#include<sstream>
#include<vector>

using namespace std;
using ExceptionSpace::IllegalParameterValue;

template<class T>
class DoublyLinkedList : public LinearList<T> {

    //当全局友元函数的参数有类名时，根据参数查找规则可直接将友元函数的定义写在类内，类外无需声明
    friend ostream &operator<<(ostream &out, const DoublyLinkedList<T> &theChain) {
        theChain.output(out);
        return out;
    }

public://别名
    typedef DoublyNode<T> *NodePointer;
    typedef DoublyNode<T> Node;
    typedef DoublyLinkedList<T> DoublyList;
    typedef DoublyLinkedList<T> *DoublyPointer;
private://私有成员变量
    NodePointer nodeHeader;
    int listSize;
public://访问私有数据成员的公有接口

    void setHeader(const NodePointer &thePointer) { nodeHeader = thePointer; }

    void setSize(const int &theSize) { listSize = theSize; }

    NodePointer getHeader() const { return nodeHeader; }

public://构造，析构，拷贝构造

    //默认构造，创建空表
    explicit DoublyLinkedList(NodePointer p = new Node) {
        nodeHeader = p;
        nodeHeader->setNext(nullptr);
        nodeHeader->setPrevious(nullptr);
        listSize = 0;
    }

    //构造有首节点的双向循环链表
    explicit DoublyLinkedList(const T &theElement, NodePointer p = new Node) {
        nodeHeader = p;
        auto newNode = new Node(nodeHeader, theElement, nodeHeader);
        nodeHeader->setPrevious(newNode);
        nodeHeader->setNext(newNode);
        listSize = 1;
    }

    DoublyLinkedList(const DoublyList &theDoublyList) {
        if (listSize == 0) {
            nodeHeader = new Node;
            nodeHeader->setNext(nullptr);
            nodeHeader->setPrevious(nullptr);
            listSize = 0;
        } else {
            listSize = theDoublyList.size();
            nodeHeader = new Node;
            NodePointer sourceNode = theDoublyList.getHeader()->getNext();
            nodeHeader->setNext(new Node(nodeHeader, sourceNode->getElement(), nodeHeader));
            sourceNode = sourceNode->getNext();
            NodePointer targetNode = nodeHeader->getNext();
            NodePointer tempPointer = nullptr;
            while (sourceNode != theDoublyList.getHeader()) {
                targetNode->setNext(new Node(targetNode, sourceNode->getElement(), nodeHeader));
                targetNode = targetNode->getNext();
                tempPointer = sourceNode;
                sourceNode = sourceNode->getNext();
            }
            nodeHeader->setPrevious(tempPointer);
        }
    }


    ~DoublyLinkedList() {
        NodePointer p = nodeHeader->getNext();
        NodePointer deleteNode = nullptr;
        while (p != nodeHeader) {
            deleteNode = p;
            p = p->getNext();
            delete deleteNode;
        }
        delete nodeHeader;
    }

public://公有用户接口函数
    //基础操作接口
    T &get(const int &theIndex);                     //currentNode可以直接等于firstNode->next
    int indexOf(const T &theElement) const;               //返回元素对应的索引
    bool empty() const { return listSize == 0; }          //检测容器是否为空
    int size() const { return listSize; }                 //返回容器中元素的数量
    void clear();                                         //清空容器
    void erase(const int &theIndex);                      //删除索引为index的元素
    void insert(const int &theIndex, const T &theElement);//在索引为index的位置上插入元素
    void output(ostream &out) const;                      //输出容器中所有元素

    //特殊操作接口
    void set(const int &theIndex, const T &theElement);   //替换指定元素

    T at(const int &theIndex);//以值的形式返回某节点元素的值

    void push_back(const T &theElement);//向容器中添加一个元素

    void removeRange(const int &beginIndex, const int &endIndex);//删除指定范围内的元素

    void swapContainer(DoublyLinkedList<T> &theChain);//交换两个链表中的元素

    void swapElement(const int &indexA, const int &indexB);//交换两个节点的数据

    void leftShift(const int &offset);//将链表中的元素向左移动offset个位置

    void reverse();//原地颠倒链表中的元素，不分配任何新的节点空间

    void meld(DoublyLinkedList<T> &theChain);//将传入的链表合并到调用函数的链表中，并将传入的链表置空

    vector<DoublyLinkedList<T>> *split();//生成两个扩展链表a和b，a中包含索引为奇数的元素，b中包含其余元素，a和b的存储空间即*this的存储空间

    void test();//用来测试私有函数的公有接口

    void insertSort();//利用插入排序法对链表元素进行排列

    void selectionSort();//利用选择排序对容器中的元素排序

    void bubbleSort();//利用冒泡排序对元素排序

    void overwriteErase(const int &theIndex);//删除theNode指向的节点，将theNode节点的后继节点的数据往前挪一位，并删除后继节点

public://重载为成员函数的运算符重载函数
    T &operator[](const int &theIndex);


private://私有内部接口

    DoublyNode<T> &getNode(const int &theIndex) const;

    void setNode(const int &theIndex, const T &theElement, const NodePointer &thePrevious, const NodePointer &theNext);

    void logicalClear();

    void checkIndex(int theIndex, std::string actionType) const;

    DoublyNode<T> *indexToAddress(const int &theIndex) const;

    bool bubble(const int &n);
};

template<class T>
T &DoublyLinkedList<T>::get(const int &theIndex) {
    checkIndex(theIndex, "get");
    NodePointer p = nodeHeader->getNext();
    for (int i = 0; i < theIndex; i++) {
        p = p->getNext();
    }
    return p->theElement();
}

template<class T>
int DoublyLinkedList<T>::indexOf(const T &theElement) const {
    NodePointer p = nodeHeader->getNext();
    int i = 0;
    while (p != nodeHeader) {
        if (p->getElement() == theElement) { return i; }
        p = p->getNext();
        i++;
    }
    return -1;
}

template<class T>
void DoublyLinkedList<T>::clear() {
    NodePointer p = nodeHeader->getNext();
    NodePointer deleteNode;
    while (p != nodeHeader) {
        deleteNode = p;
        p = p->getNext();
        delete deleteNode;
    }
    nodeHeader->setNext(nullptr);
    nodeHeader->setPrevious(nullptr);
    listSize = 0;
}

template<class T>
void DoublyLinkedList<T>::erase(const int &theIndex) {
    checkIndex(theIndex, "erase");
    NodePointer deleteNode;
    if (theIndex == 0 && listSize == 1) {
        deleteNode = nodeHeader->getNext();
        nodeHeader->setNext(nullptr);
        nodeHeader->setPrevious(nullptr);
    } else if (theIndex == 0 && listSize > 1) {
        deleteNode = nodeHeader->getNext();
        NodePointer nextNode = nodeHeader->getNext()->getNext();
        nodeHeader->setNext(nextNode);
        nextNode->setPrevious(nodeHeader);
    } else {
        DoublyNode theNode = this->getNode(theIndex);
        theNode.getPrevious()->setNext(theNode.getNext());
        theNode.getNext()->setPrevious(theNode.getPrevious());
        deleteNode = &theNode;
    }
    listSize--;
    delete deleteNode;
}

template<class T>
void DoublyLinkedList<T>::insert(const int &theIndex, const T &theElement) {
    checkIndex(theIndex, "insert");
    NodePointer previousNode = this->getNode(theIndex).getPrevious();
    NodePointer nextNode = previousNode->getNext();
    NodePointer newNode = new Node(previousNode, theElement, nextNode);
    previousNode->setNext(newNode);
    nextNode->setPrevious(newNode);
}

template<class T>
void DoublyLinkedList<T>::output(ostream &out) const {
    if (nodeHeader->getNext() == nullptr) {
        cout << "当前链表为空，无法输出" << endl;
    }else{
        NodePointer p = nodeHeader->getNext();
        for (int i = 0; i < listSize; i++) {
            out << p->getElement() << " ";
            p = p->getNext();
        }
        cout << endl;
    }
}

template<class T>
void DoublyLinkedList<T>::push_back(const T &theElement) {
    NodePointer newNode;
    if (listSize == 0) {
        newNode = new Node(nodeHeader, theElement, nodeHeader);
        nodeHeader->setNext(newNode);
    } else {
        NodePointer lastNode = nodeHeader->getPrevious();
        newNode = new Node(lastNode, theElement, nodeHeader);
        lastNode->setNext(newNode);

    }
    nodeHeader->setPrevious(newNode);
    listSize++;

}

template<class T>
void DoublyLinkedList<T>::set(const int &theIndex, const T &theElement) {
    this->get(theIndex) = theElement;
}

template<class T>
void DoublyLinkedList<T>::removeRange(const int &beginIndex, const int &endIndex) {

}

template<class T>
void DoublyLinkedList<T>::swapContainer(DoublyLinkedList<T> &theChain) {

}

template<class T>
void DoublyLinkedList<T>::swapElement(const int &indexA, const int &indexB) {

}

template<class T>
void DoublyLinkedList<T>::leftShift(const int &offset) {

}

template<class T>
void DoublyLinkedList<T>::reverse() {

}

template<class T>
void DoublyLinkedList<T>::meld(DoublyLinkedList<T> &theChain) {

}

template<class T>
vector<DoublyLinkedList<T>> *DoublyLinkedList<T>::split() {
    return nullptr;
}

template<class T>
void DoublyLinkedList<T>::test() {

}

template<class T>
void DoublyLinkedList<T>::insertSort() {

}

template<class T>
void DoublyLinkedList<T>::selectionSort() {

}

template<class T>
void DoublyLinkedList<T>::bubbleSort() {

}

template<class T>
void DoublyLinkedList<T>::overwriteErase(const int &theIndex) {

}

template<class T>
DoublyNode<T> &DoublyLinkedList<T>::getNode(const int &theIndex) const {
    NodePointer p = nodeHeader->getNext();
    for (int i = 0; i < theIndex; i++) {
        p = p->getNext();
    }
    return *p;
}

template<class T>
void
DoublyLinkedList<T>::setNode(const int &theIndex, const T &theElement, DoublyLinkedList::NodePointer const &thePrevious,
                             DoublyLinkedList::NodePointer const &theNext) {

}

template<class T>
void DoublyLinkedList<T>::logicalClear() {

}

template<class T>
void DoublyLinkedList<T>::checkIndex(int theIndex, std::string actionType) const {
    //确保索引在窒执行特殊操作时，索引在正确的范围内
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex > this->size()) {
            ostringstream s;
            s << "插入元素时，";
            if (theIndex < 0)s << "索引值不得<0" << endl;
            if (theIndex > this->size())s << "索引值不得>数组元素个数" << endl;
            throw ExceptionSpace::IllegalParameterValue(s.str());
        }
    } else if (actionType == "erase" || actionType == "get" || actionType == "replace") {
        if (!(theIndex >= 0&&theIndex<this->size())) {
            ostringstream s;
            if(theIndex>=this->size())
            {
                if (actionType == "erase")
                    s << "删除元素时，索引值不得>=listSize" << endl;
                else if (actionType == "replace")s << "替换元素时，索引值不得>=listSize" << endl;
                else if (actionType == "get")s << "获取元素时，索引值不得>=listSize" << endl;
            }else{
                if (actionType == "erase")
                    s << "删除元素时，索引值不得<0" << endl;
                else if (actionType == "replace")s << "替换元素时，索引值不得<0" << endl;
                else if (actionType == "get")s << "获取元素时，索引值不得<0" << endl;
            }
            throw ExceptionSpace::IllegalParameterValue(s.str());
        }
    } else {
        ostringstream s;
        s << "checkIndex第二个参数传入不正确，未指定正确的操作类型" << endl;
        throw ExceptionSpace::IllegalParameterValue(s.str());
    }

}

template<class T>
DoublyNode<T> *DoublyLinkedList<T>::indexToAddress(const int &theIndex) const {
    return nullptr;
}

template<class T>
bool DoublyLinkedList<T>::bubble(const int &n) {
    return false;
}

template<class T>
T DoublyLinkedList<T>::at(const int &theIndex) {
    checkIndex(theIndex, "get");
    NodePointer p = nodeHeader->getNext();
    for (int i = 0; i < theIndex; i++) {
        p = p->getNext();
    }
    return p->getElement();
}

template<class T>
T &DoublyLinkedList<T>::operator[](const int &theIndex) {
    return this->get(theIndex);
}
