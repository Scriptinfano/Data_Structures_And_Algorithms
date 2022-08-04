#pragma once
#include<iostream>
using namespace std;
#include"chainListMain.h"


template<class T>
class extendedChainList : public extendedLinearList<T>, public chainList<T> {

protected:
    ChainNode<T> *lastNode;//这是一个指向链表尾节点的指针，在调用push_back()函数时可以更快地将元素插入到链表尾部

public:
    //构造函数与拷贝构造函数

    extendedChainList(ChainNode<T> *p = nullptr, int theSize = 0) : chainList<T>(p, theSize) {
        lastNode = chainList<T>::firstNode;
    }

    extendedChainList(const extendedChainList<T> &c) : chainList<T>(c) {
        ChainNode<T> *p = chainList<T>::firstNode;
        while (p->next != nullptr)
            p = p->next;
        lastNode = p;
    }

    //ADT方法
    bool empty() const { return chainList<T>::listSize == 0; }

    int size() const { return chainList<T>::listSize; }

    T &get(const int &theIndex) const { return chainList<T>::get(theIndex); }

    int indexOf(const T &theElement) const { return chainList<T>::indexOf(theElement); }

    void erase(const int &theIndex);

    void insert(const int &theIndex, const T &theElement);

    void clear();

    void push_back(const T &theElement);

    void output(ostream &out) const { chainList<T>::output(out); }

    void circularShift(int theOffset);

    //其他函数
    void zero() {
        chainList<T>::firstNode = nullptr;
        chainList<T>::listSize = 0;
    }

    void meld(const extendedChainList<T> &chainA, const extendedChainList<T> &chainB);

    vector<extendedChainList<T>> *split();

};

template<class T>
void extendedChainList<T>::erase(const int &theIndex) {
    chainList<T>::checkIndex(theIndex, "erase");

    ChainNode<T> *deleteNode;
    if (theIndex == 0)//删除头节点
    {
        deleteNode = chainList<T>::firstNode;
        chainList<T>::firstNode = chainList<T>::firstNode->next;
    } else {
        //找到要删除节点的前驱节点
        ChainNode<T> *p = chainList<T>::firstNode;
        for (int i = 0; i < theIndex - 1; i++) {
            p = p->next;
        }
        deleteNode = p->next;
        p->next = p->next->next;
        //若要删除的节点是最后一个节点，则将最后一个节点的前一个节点作为最后一个节点
        if (deleteNode == lastNode)
            lastNode = p;
    }
    chainList<T>::listSize--;
    delete deleteNode;
}

template<class T>
void extendedChainList<T>::insert(const int &theIndex, const T &theElement) {
    chainList<T>::checkIndex(theIndex, "insert");

    //在头节点之前插入节点
    if (theIndex == 0) {
        chainList<T>::firstNode = new ChainNode<T>(theElement, chainList<T>::firstNode);
        if (chainList<T>::listSize == 0)lastNode = chainList<T>::firstNode;
    } else {
        //找到要插入节点的前驱节点
        ChainNode<T> *p = chainList<T>::firstNode;
        for (int i = 0; i < chainList<T>::listSize - 1; i++)
            p = p->next;
        p->next = new ChainNode<T>(theElement, p->next);
        if (chainList<T>::listSize == theIndex) {
            //说明是在最后一个节点之后插入节点，相当于在末尾新增节点
            lastNode = p->next;
        }
    }
    chainList<T>::listSize++;
}

template<class T>
void extendedChainList<T>::clear() {
    while (chainList<T>::firstNode != nullptr) {
        ChainNode<T> *nextNode = chainList<T>::firstNode->next;
        delete chainList<T>::firstNode;
        chainList<T>::firstNode = nextNode;
    }
    chainList<T>::listSize = 0;

}

template<class T>
void extendedChainList<T>::push_back(const T &theElement) {
    ChainNode<T> *newNode = new ChainNode<T>(theElement, nullptr);
    if (chainList<T>::firstNode == nullptr) {
        //整个链表是空的情况
        chainList<T>::firstNode = lastNode = newNode;
    } else {
        lastNode->next = newNode;
        lastNode = newNode;
    }
    chainList<T>::listSize++;
}

template<class T>
void extendedChainList<T>::meld(const extendedChainList<T> &chainA, const extendedChainList<T> &chainB) {
    ChainNode<T> *p = chainA.firstNode;
    ChainNode<T> *j = chainB.firstNode;
    ChainNode<T> *k = nullptr;
    while (!(p == nullptr || j == nullptr)) {
        this->push_back(p->element);
        p = p->next;
        this->push_back(j->element);
        j = j->next;

    }

    //此时如果两个链表长度不相等，则一个指针是nullptr，另一个指针指向的节点及之后的所有节点都是要插入目标链表的，目标链表即调用该函数的对象
    if (j == nullptr && p != nullptr) {
        //chainA链表剩下的全部插入
        while (p != nullptr) {
            this->push_back(p->element);
            p = p->next;
        }
    } else if (j != nullptr && p == nullptr) {
        //chainB链表剩下的全部插入
        while (j != nullptr) {
            this->push_back(j->element);
            j = j->next;
        }

    } else {
        //j和p都是nullptr，说明两个链表的长度一样，不需要做任何后续的补全工作
        chainList<T>::listSize = chainA.listSize;
        lastNode = j;
        return;
    }
    chainList<T>::listSize = chainA.listSize + chainB.listSize;
    k = chainList<T>::firstNode;
    while (k->next != nullptr)
        k = k->next;
    lastNode = k;
}

template<class T>
vector<extendedChainList<T>> *extendedChainList<T>::split() {
    auto *targetVector = new vector<extendedChainList<T>>;
    if (this->size() == 0)return nullptr;
    extendedChainList<T> oddChain;//存放索引为奇数的节点
    extendedChainList<T> evenChain;//存放索引为偶数的节点
    for (int i = 0; i < this->size(); i++) {
        if ((i % 2) != 0)//索引为奇数时
        {
            oddChain.push_back(this->get(i));
        } else {
            //索引为偶数时
            evenChain.push_back(this->get(i));
        }
    }
    targetVector->push_back(oddChain);
    targetVector->push_back(evenChain);
    return targetVector;
}

template<class T>
void extendedChainList<T>::circularShift(int theOffset) {
    queue<T> temp;
    int netOffset = theOffset % chainList<T>::listSize;
    for (int i = 0; i < netOffset; i++) {
        temp.push(this->get(0));
        this->erase(0);
        this->push_back(temp.front());
        temp.pop();
    }
}


//全局模板函数，假设T类型的数据定义了比较运算符，且输入的两个链表chainA和chainB都是有序链表
template<class T>
extendedChainList<T> merge(extendedChainList<T> &chainA, extendedChainList<T> &chainB) {
    vector<T> temp;
    for (int i = 0; i < chainA.size(); i++) {
        temp.push_back(chainA.get(i));
    }
    for (int i = 0; i < chainB.size(); i++) {
        temp.push_back(chainB.get(i));
    }
    sort(temp.begin(), temp.end());
    extendedChainList<T> targetChain;
    for (int i = 0; i < temp.size(); i++) {
        targetChain.push_back(temp.at(i));
    }
    return targetChain;
}

