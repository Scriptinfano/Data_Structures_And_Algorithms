#pragma once
#include<iostream>
using namespace std;
#include"chainListMain.h"


template<class T>
class extendedChainList : public extendedLinearList<T>, public chainList<T> {

protected:
    ChainNode<T> *lastNode;//����һ��ָ������β�ڵ��ָ�룬�ڵ���push_back()����ʱ���Ը���ؽ�Ԫ�ز��뵽����β��

public:
    //���캯���뿽�����캯��

    extendedChainList(ChainNode<T> *p = nullptr, int theSize = 0) : chainList<T>(p, theSize) {
        lastNode = chainList<T>::firstNode;
    }

    extendedChainList(const extendedChainList<T> &c) : chainList<T>(c) {
        ChainNode<T> *p = chainList<T>::firstNode;
        while (p->next != nullptr)
            p = p->next;
        lastNode = p;
    }

    //ADT����
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

    //��������
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
    if (theIndex == 0)//ɾ��ͷ�ڵ�
    {
        deleteNode = chainList<T>::firstNode;
        chainList<T>::firstNode = chainList<T>::firstNode->next;
    } else {
        //�ҵ�Ҫɾ���ڵ��ǰ���ڵ�
        ChainNode<T> *p = chainList<T>::firstNode;
        for (int i = 0; i < theIndex - 1; i++) {
            p = p->next;
        }
        deleteNode = p->next;
        p->next = p->next->next;
        //��Ҫɾ���Ľڵ������һ���ڵ㣬�����һ���ڵ��ǰһ���ڵ���Ϊ���һ���ڵ�
        if (deleteNode == lastNode)
            lastNode = p;
    }
    chainList<T>::listSize--;
    delete deleteNode;
}

template<class T>
void extendedChainList<T>::insert(const int &theIndex, const T &theElement) {
    chainList<T>::checkIndex(theIndex, "insert");

    //��ͷ�ڵ�֮ǰ����ڵ�
    if (theIndex == 0) {
        chainList<T>::firstNode = new ChainNode<T>(theElement, chainList<T>::firstNode);
        if (chainList<T>::listSize == 0)lastNode = chainList<T>::firstNode;
    } else {
        //�ҵ�Ҫ����ڵ��ǰ���ڵ�
        ChainNode<T> *p = chainList<T>::firstNode;
        for (int i = 0; i < chainList<T>::listSize - 1; i++)
            p = p->next;
        p->next = new ChainNode<T>(theElement, p->next);
        if (chainList<T>::listSize == theIndex) {
            //˵���������һ���ڵ�֮�����ڵ㣬�൱����ĩβ�����ڵ�
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
        //���������ǿյ����
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

    //��ʱ������������Ȳ���ȣ���һ��ָ����nullptr����һ��ָ��ָ��Ľڵ㼰֮������нڵ㶼��Ҫ����Ŀ������ģ�Ŀ���������øú����Ķ���
    if (j == nullptr && p != nullptr) {
        //chainA����ʣ�µ�ȫ������
        while (p != nullptr) {
            this->push_back(p->element);
            p = p->next;
        }
    } else if (j != nullptr && p == nullptr) {
        //chainB����ʣ�µ�ȫ������
        while (j != nullptr) {
            this->push_back(j->element);
            j = j->next;
        }

    } else {
        //j��p����nullptr��˵����������ĳ���һ��������Ҫ���κκ����Ĳ�ȫ����
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
    extendedChainList<T> oddChain;//�������Ϊ�����Ľڵ�
    extendedChainList<T> evenChain;//�������Ϊż���Ľڵ�
    for (int i = 0; i < this->size(); i++) {
        if ((i % 2) != 0)//����Ϊ����ʱ
        {
            oddChain.push_back(this->get(i));
        } else {
            //����Ϊż��ʱ
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


//ȫ��ģ�庯��������T���͵����ݶ����˱Ƚ�����������������������chainA��chainB������������
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

