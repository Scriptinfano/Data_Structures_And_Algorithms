#pragma once

#include"D:\ClionProjects\Data_Structures_And_Algorithms\virtualBaseClassLinearList.h"
#include<sstream>
#include<iostream>
#include<string>
#include <iterator>

using namespace std;

//�����쳣��
class illegalParameterValue {
private:
    string message;

public:
    illegalParameterValue() : message("�Ƿ�ʵ�δ���") {}

    illegalParameterValue(string theMessage) { message = theMessage; }

    void outPutMessage() const { cout << message << endl; }
};


//��������ڵ���
template<class T>
class chainNode {
public:
    T element;//����ڵ��������
    chainNode<T> *next;//����ڵ��ָ����

    //��Ա����
    chainNode() = default;

    chainNode(const T &theElement) { this->element = theElement; }

    chainNode(const T &theElement, chainNode<T> *theNext) {
        this->element = theElement;
        this->next = theNext;
    }
};

//����������
template<class T>
class chainList : public linearList<T> {
protected:
    void checkIndex(int theIndex, string actionType) const;

    chainNode<T> *firstNode;//ָ�������һ���ڵ��ָ�룬������Ϊ��ʱ����ֵΪnullptr
    int listSize;//����ڵ����

public:
    chainList(int initialCapacity = 10);

    chainList(const chainList<T> &theChainList);

    ~chainList();

    //ADT����
    bool empty() const { return listSize == 0; }    //����Ƿ�Ϊ��
    int size() const;                               //��������Ԫ�ظ���
    T &get(int theIndex) const;                     //�õ�����ֵΪtheIndex��Ԫ��
    int indexOf(const T &theElement) const;         //����Ԫ��theElement�״γ��ֵ�����ֵ
    void erase(int theIndex);                       //ɾ������ΪtheIndex��Ԫ��
    void insert(int theIndex, const T &theElement); //��ָ��λ�ò���Ԫ��
    void output(ostream &out) const;
};

template<class T>
void chainList<T>::checkIndex(int theIndex, string actionType) const {
//ȷ��������0��listsize-1֮��
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex > this->size()) {
            ostringstream s;
            s << "����Ԫ��ʱ��";
            if (theIndex < 0)s << "����ֵ����<0" << endl;
            if (theIndex > listSize)s << "����ֵ����>����Ԫ�ظ���" << endl;
            throw illegalParameterValue(s.str());
        }
    } else if (actionType == "erase" || actionType == "get" || actionType == "replace") {
        if (theIndex >= this->size()) {
            ostringstream s;
            if (actionType == "erase")
                s << "ɾ��Ԫ��ʱ������ֵ����>=listSize" << endl;
            else if (actionType == "replace")s << "�滻Ԫ��ʱ������ֵ����>=listSize" << endl;
            else if (actionType == "get")s << "��ȡԪ��ʱ������ֵ����>=listSize" << endl;
            throw illegalParameterValue(s.str());
        }
    } else {
        ostringstream s;
        s << "checkIndex�ڶ����������벻��ȷ��δָ����ȷ�Ĳ�������" << endl;
        throw illegalParameterValue(s.str());
    }


}

template<class T>
chainList<T>::chainList(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "��ʼ����=" << initialCapacity << "����ֵ�������0";
        throw illegalParameterValue(s.str());

    }
    firstNode = nullptr;
    listSize = 0;
}

template<class T>
chainList<T>::chainList(const chainList<T> &theChainList) {
    listSize = theChainList.listSize;
    if (listSize == 0) {
        //����theChainListΪ�գ�����Ҫ���ƹ���
        firstNode = nullptr;
        return;
    }
    //�ȴ���ָ��ӹܱ����������ٿ�����һ��Ԫ�أ����ƶ�ԭ����ָ�룬����ָ��ӹ�Ŀ������Ȼ��ѭ������Ԫ��
    chainNode<T> *sourceNode = theChainList.firstNode;//sourceNodeָ�򱻸���������׽ڵ�
    firstNode = new chainNode(sourceNode->element);//��ʼ��Ŀ�������׽ڵ㲢������Ԫ��
    sourceNode = sourceNode->next;//ָ�򱻸��������׽ڵ��ָ�����Ųһ���ڵ�
    chainNode<T> *targetNode = firstNode;//����ָ��Ŀ�������׽ڵ��ָ��
    while (sourceNode != nullptr) {
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = nullptr;


}

template<class T>
chainList<T>::~chainList() {
    while (firstNode != nullptr) {
        chainNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class T>
int chainList<T>::size() const {
    return listSize;
}

template<class T>
T &chainList<T>::get(int theIndex) const {
    checkIndex(theIndex, "get");
    chainNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; i++) {
        currentNode = currentNode->next;
    }
    return currentNode->element;
}

template<class T>
int chainList<T>::indexOf(const T &theElement) const {
    chainNode<T> *currentNode = firstNode;
    int index = 0;
    while (currentNode != nullptr && currentNode->element != theElement) {
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == nullptr)return -1;//����û���ҵ�
    else return index;//�ҵ���
}

template<class T>
void chainList<T>::erase(int theIndex) {
    checkIndex(theIndex, "erase");

    chainNode<T> *deleteNode;
    if (theIndex == 0)//ɾ����Ԫ�صĽڵ�
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    } else {
        //�ñ����ķ�����ָ��pָ��Ҫɾ���ڵ��ǰ���ڵ�
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++) {
            p = p->next;
        }
        deleteNode = p->next;
        p->next = p->next->next;//��ǰ���ڵ�ֱ������Ҫɾ���ڵ�ĺ�̽ڵ�
    }
    listSize--;
    delete deleteNode;
}

template<class T>
void chainList<T>::insert(int theIndex, const T &theElement) {
    checkIndex(theIndex, "insert");
    if (theIndex == 0)//�ڱ�ͷ�����½ڵ�
    {
        firstNode = new chainNode<T>(theElement, firstNode);

    } else {
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++) {
            p = p->next;
        }
        p->next = new chainNode<T>(theElement, p->next);

    }
    listSize++;
}

template<class T>
void chainList<T>::output(ostream &out) const {
    for (chainNode<T> *currentNode = firstNode; currentNode != nullptr; currentNode = currentNode->next) {
        out << currentNode->element << " ";
    }
}

template<class T>
ostream &operator<<(ostream &out, const chainList<T> &theNode) {
    theNode.output(out);
    return out;
}




//����ǰ�������
template<class T>
class forward_iterator {
protected:
    chainNode<T> *node;
public:
    //��ǰ�����������typedef�������
    typedef forward_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;

    //���캯��
    forward_iterator(chainNode<T>*theNode=nullptr)
    {
        node=theNode;
    }
    //�����ò�����
    T &operator*()const{return node->element;}
    T*operator->()const{return &(node->element);}

    //�������ӷ�����

};
