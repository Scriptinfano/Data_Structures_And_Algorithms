#pragma once

#include"D:\ClionProjects\Data_Structures_And_Algorithms\virtualBaseClassLinearList.h"
#include<sstream>
#include<iostream>
#include<string>
#include <iterator>
#include <string.h>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\arrayAndVectorList\illegalParameterValue.h"
#include"D:\ClionProjects\Data_Structures_And_Algorithms\linearList\arrayAndVectorList\arrayList.hpp"

using namespace std;

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

    //����ģ�������Ԫģ�庯��ֱ�ӽ�����д���ඨ��֮��
    friend bool operator<(const chainList<T> &leftChain, const chainList<T> &rightChain) {
        char c;
        T t;
        if (typeid(t) != typeid(c))throw illegalParameterValue("ʹ��<�Ƚ���������ʱ�����ܱȽϳ���char�����������������");
        chainNode<T> *it = leftChain.begin();
        chainNode<T> *it2 = rightChain.begin();
        char *p = new char[leftChain.size()];
        char *p2 = new char[rightChain.size()];
        for (int i = 0; i < leftChain.size(); i++) {
            p[i] = leftChain.get(i);
        }
        for (int i = 0; i < rightChain.size(); i++) {
            p2[i] = rightChain.get(i);
        }
        int cmp = strcmp(p, p2);
        if (cmp < 0)return true;
        else return false;
    }

protected:
    void checkIndex(int theIndex, string actionType) const;

    chainNode<T> *firstNode;//ָ�������һ���ڵ��ָ�룬������Ϊ��ʱ����ֵΪnullptr
    int listSize;//����ڵ����

public:
    chainList();//��������Ϊ�ײ����ݽṹ����������ָ������

    chainList(const chainList<T> &theChainList);

    ~chainList();

    //ADT����
    bool empty() const { return listSize == 0; }    //����Ƿ�Ϊ��
    int size() const;                               //��������Ԫ�ظ���
    T &get(int theIndex) const;                     //�õ�����ֵΪtheIndex��Ԫ��
    int indexOf(const T &theElement) const;         //����Ԫ��theElement�״γ��ֵ�����ֵ
    void erase(int theIndex);                       //ɾ������ΪtheIndex��Ԫ��
    void insert(int theIndex, const T &theElement); //��ָ��λ�ò���Ԫ��
    void output(ostream &out) const;                //��������е�����Ԫ��


    //��������
    void setSize(int newSize);//ʹ����ڵ��������newSize����newSizeС��ԭ��С����ɾ������Ԫ�أ�������ԭ��С�����κβ���

    void push_back(const T &theElement);//�������β���¼�һ���ڵ�

    void set(int theIndex, const T &theElement);//�滻ָ��Ԫ��

    void removeRange(int beginIndex, int endIndex);//ɾ��ָ����Χ�ڵ�Ԫ��

    chainNode<T> *indexToAddress(int theIndex) const;//�������������ظ�����������Ľڵ�ĵ�ַ

    int indexOf(chainNode<T> *pBegin, const T &theElement) const;    //���Ե�ַΪpBegin�Ľڵ㿪ʼ�����ң��ҵ���һ���ڵ�Ԫ����theElement�Ľڵ���

    int lastIndexOf(const T &theElement) const;//����ָ��Ԫ�������ֵ����������������򷵻�-1

    void swap(chainList<T> &theChain);//�������������е�Ԫ��

    void fromList(const arrayList<T> &theArray);//���������Ա�ת��Ϊ����

    arrayList<T> toList();//������ת��Ϊ�������Ա���ֱ�ӷ��ؽ��

    //�������������
    T &operator[](int index);

    bool operator==(const chainList<T> &theChain);

    bool operator!=(const chainList<T> &theChain);

    //���������׽ڵ��ַ
    chainNode<T> *begin() const;

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
chainList<T>::chainList() {
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
void chainList<T>::setSize(int newSize) {
    if (newSize < listSize) {
        //ɾ������Ԫ��
        chainNode<T> *p = firstNode;
        for (int i = 0; i < newSize - 1; i++)
            p = p->next;
        //��ʱpָ��Ľڵ��֮������нڵ㶼��Ҫɾ���Ľڵ�
        chainNode<T> *deleteNode = p->next;
        p->next = nullptr;
        chainNode<T> *currentNode = deleteNode;

        int count = 0;
        while (currentNode != nullptr) {
            currentNode = currentNode->next;
            delete deleteNode;
            deleteNode = currentNode;
            count++;
        }
        listSize -= count;

    } else {
        return;
    }

}

template<class T>
void chainList<T>::push_back(const T &theElement) {
    chainNode<T> *newNode = new chainNode<T>(theElement, nullptr);
    if (listSize == 0)firstNode = newNode;
    else {
        chainNode<T> *p = firstNode;
        for (int i = 0; i < listSize - 1; i++) {
            p = p->next;
        }
        p->next = newNode;
    }
    listSize++;
}

template<class T>
void chainList<T>::set(int theIndex, const T &theElement) {
    checkIndex(theIndex, "replace");
    this->get(theIndex) = theElement;
}

template<class T>
void chainList<T>::removeRange(int beginIndex, int endIndex) {
    if (beginIndex >= 0 && beginIndex < endIndex && endIndex <= listSize - 1) {
        chainNode<T> *pBegin = firstNode, *pEnd = firstNode;
        for (int i = 0; i < beginIndex - 1; i++)
            pBegin = pBegin->next;
        for (int i = 0; i < endIndex - 1; i++)
            pEnd = pEnd->next;
        chainNode<T> *p = pBegin->next, *j = pEnd->next;
        chainNode<T> *deleteNode = nullptr;
        int count = 0;
        while (p != j->next) {
            deleteNode = p;
            p = p->next;
            delete deleteNode;
            count++;
        }
        pBegin->next = pEnd->next->next;
        listSize -= count;
    } else {
        throw illegalParameterValue("ʹ��removeRange����ʱ������������");

    }
}

template<class T>
int chainList<T>::lastIndexOf(const T &theElement) const {
    chainNode<T> *p = firstNode;
    int lastIndex = 0;
    int finalIndex = 0;

    while (p != nullptr) {
        finalIndex = lastIndex;
        lastIndex = indexOf(p, theElement);
        p = indexToAddress(lastIndex);
        if (p != nullptr)p = p->next;
    }
    return finalIndex;
}

template<class T>
int chainList<T>::indexOf(chainNode<T> *pBegin, const T &theElement) const {
    //���Ե�ַΪpBegin�Ľڵ㿪ʼ�����ң��ҵ���һ���ڵ�Ԫ����theElement�Ľڵ���
    chainNode<T> *currentNode = pBegin;
    int index = 0;
    chainNode<T> *p = firstNode;
    while (p != currentNode) {
        p = p->next;
        index++;
    }

    while (currentNode != nullptr && currentNode->element != theElement) {
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == nullptr)return -1;//����û���ҵ�
    else return index;//�ҵ���

}

template<class T>
chainNode<T> *chainList<T>::indexToAddress(int theIndex) const {
    if (theIndex >= listSize || theIndex < 0)return nullptr;
    int index = 0;
    chainNode<T> *p = firstNode;
    while (index != theIndex) {
        p = p->next;
        index++;
    }
    return p;
}

template<class T>
T &chainList<T>::operator[](int index) {
    chainNode<T> *p = firstNode;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    return p->element;

}

template<class T>
bool chainList<T>::operator==(const chainList<T> &theChain) {
    chainNode<T> *p = firstNode, *p2 = theChain.begin();
    if (listSize != theChain.size())return false;
    else {
        while (p != nullptr && p2 != nullptr) {
            if (p->element != p2->element)return false;
            p = p->next;
            p2 = p2->next;
        }
        return true;
    }
}

template<class T>
chainNode<T> *chainList<T>::begin() const {
    return firstNode;
}

template<class T>
bool chainList<T>::operator!=(const chainList<T> &theChain) {
    return !(*this == theChain);
}

template<class T>
void chainList<T>::swap(chainList<T> &theChain) {
    int selfListSize = this->size();
    int otherListSize = theChain.size();

    chainNode<T> *temp = firstNode;
    firstNode = theChain.firstNode;
    theChain.firstNode = temp;

    listSize = otherListSize;
    theChain.setSize(selfListSize);

}

template<class T>
void chainList<T>::fromList(const arrayList<T> &theArray) {
    for (int i = 0; i < theArray.size(); i++)
        this->push_back(theArray.get(i));
}

template<class T>
arrayList<T> chainList<T>::toList() {
    arrayList<T>array(this->size());
    for(int i=0;i<this->size();i++)
    array.push_back(this->get(i));

    return array;
}


template<class T>
ostream &operator<<(ostream &out, const chainList<T> &theNode) {
    theNode.output(out);
    return out;
}

//��չchainList��������������extendedLinearList�������Ĺ���
template<class T>
class extendedChainList : public extendedLinearList<T>, public chainList<T> {

protected:
    chainNode<T> *lastNode;//����һ��ָ������β�ڵ��ָ�룬�ڵ���push_back()����ʱ���Ը���ؽ�Ԫ�ز��뵽����β��

public:
    //���캯���뿽�����캯��

    extendedChainList(int initialCapacity = 10) : chainList<T>(initialCapacity) {}

    extendedChainList(const extendedChainList<T> &c) : chainList<T>(c) {}

    //ADT����
    bool empty() const { return chainList<T>::listSize == 0; }

    int size() const { return chainList<T>::listSize; }

    T &get(int theIndex) const { return chainList<T>::get(theIndex); }

    int indexOf(const T &theElement) const { return chainList<T>::indexOf(theElement); }

    void erase(int theIndex);

    void insert(int theIndex, const T &theElement);

    void clear();

    void push_back(const T &theElement);

    void output(ostream &out) const { chainList<T>::output(out); }

    //��������
    void zero() {
        chainList<T>::firstNode = nullptr;
        chainList<T>::listSize = 0;
    }

};

template<class T>
void extendedChainList<T>::erase(int theIndex) {
    chainList<T>::checkIndex(theIndex, "erase");

    chainNode<T> *deleteNode;
    if (theIndex == 0)//ɾ��ͷ�ڵ�
    {
        deleteNode = chainList<T>::firstNode;
        chainList<T>::firstNode = chainList<T>::firstNode->next;
    } else {
        //�ҵ�Ҫɾ���ڵ��ǰ���ڵ�
        chainNode<T> *p = chainList<T>::firstNode;
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
void extendedChainList<T>::insert(int theIndex, const T &theElement) {
    chainList<T>::checkIndex(theIndex, "insert");

    //��ͷ�ڵ�֮ǰ����ڵ�
    if (theIndex == 0) {
        chainList<T>::firstNode = new chainNode<T>(theElement, chainList<T>::firstNode);
        if (chainList<T>::listSize == 0)lastNode = chainList<T>::firstNode;
    } else {
        //�ҵ�Ҫ����ڵ��ǰ���ڵ�
        chainList<T> *p = chainList<T>::firstNode;
        for (int i = 0; i < chainList<T>::listSize - 1; i++)
            p = p->next;
        p->next = new chainNode<T>(theElement, p->next);
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
        chainNode<T> *nextNode = chainList<T>::firstNode->next;
        delete chainList<T>::firstNode;
        chainList<T>::firstNode = nextNode;
    }
    chainList<T>::listSize = 0;

}

template<class T>
void extendedChainList<T>::push_back(const T &theElement) {
    chainNode<T> *newNode = new chainNode<T>(theElement, nullptr);
    if (chainList<T>::firstNode == nullptr) {
        //���������ǿյ����
        chainList<T>::firstNode = lastNode = newNode;
    } else {
        lastNode->next = newNode;
        lastNode = newNode;
    }
    chainList<T>::listSize++;
}
