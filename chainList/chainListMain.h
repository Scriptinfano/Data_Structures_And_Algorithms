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
    void output(ostream &out) const;

    //��������
    void setSize(int newSize);//ʹ����ڵ��������newSize����newSizeС��ԭ��С����ɾ������Ԫ�أ�������ԭ��С�����κβ���

    void push_back(const T &theElement);

    void set(int theIndex, const T &theElement);//�滻ָ��Ԫ��

    void removeRange(int beginIndex, int endIndex);//ɾ��ָ����Χ�ڵ�Ԫ��
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
        chainNode<T>*pBegin=firstNode,*pEnd=firstNode;
        for(int i=0;i<beginIndex-1;i++)
            pBegin=pBegin->next;
        for(int i=0;i<endIndex-1;i++)
            pEnd=pEnd->next;
        chainNode<T>*p=pBegin->next,*j=pEnd->next;
        chainNode<T>*deleteNode= nullptr;
        int count=0;
        while(p!=j->next)
        {
            deleteNode=p;
            p=p->next;
            delete deleteNode;
            count++;
        }
        pBegin->next=pEnd->next->next;
        listSize-=count;
    } else {
        throw illegalParameterValue("ʹ��removeRange����ʱ������������");

    }
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
