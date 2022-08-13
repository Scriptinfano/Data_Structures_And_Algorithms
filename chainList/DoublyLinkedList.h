#pragma once

#include <iostream>
#include "../virtualBaseClassLinearList.h"
#include "../namespaces.h"
#include<sstream>
#include<vector>

using namespace std;
using ExceptionSpace::IllegalParameterValue;

template<class T>
class DoublyLinkedList : public LinearList<T> {

    //��ȫ����Ԫ�����Ĳ���������ʱ�����ݲ������ҹ����ֱ�ӽ���Ԫ�����Ķ���д�����ڣ�������������
    friend ostream &operator<<(ostream &out, const DoublyLinkedList<T> &theChain) {
        theChain.output(out);
        return out;
    }

public://����
    typedef DoublyNode<T> *NodePointer;
    typedef DoublyNode<T> Node;
    typedef DoublyLinkedList<T> DoublyList;
    typedef DoublyLinkedList<T> *DoublyPointer;
private://˽�г�Ա����
    NodePointer nodeHeader;
    int listSize;
public://����˽�����ݳ�Ա�Ĺ��нӿ�

    void setHeader(const NodePointer &thePointer) { nodeHeader = thePointer; }

    void setSize(const int &theSize) { listSize = theSize; }

    NodePointer getHeader() const { return nodeHeader; }

public://���죬��������������

    //Ĭ�Ϲ��죬�����ձ�
    explicit DoublyLinkedList(NodePointer p = new Node) {
        nodeHeader = p;
        nodeHeader->setNext(nullptr);
        nodeHeader->setPrevious(nullptr);
        listSize = 0;
    }

    //�������׽ڵ��˫��ѭ������
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
        if (listSize == 0) {
            delete nodeHeader;
        } else {
            NodePointer p = nodeHeader->getNext();
            NodePointer deleteNode;
            while (p != nodeHeader) {
                deleteNode = p;
                p = p->getNext();
                delete deleteNode;
            }
            delete nodeHeader;
        }
    }

public://�����û��ӿں���
    //���������ӿ�
    T &get(const int &theIndex);                     //currentNode����ֱ�ӵ���firstNode->next
    int indexOf(const T &theElement) const;               //����Ԫ�ض�Ӧ������
    bool empty() const { return listSize == 0; }          //��������Ƿ�Ϊ��
    int size() const { return listSize; }                 //����������Ԫ�ص�����
    void clear();                                         //�������
    void erase(const int &theIndex);                      //ɾ������Ϊindex��Ԫ��
    void insert(const int &theIndex, const T &theElement);//������Ϊindex��λ���ϲ���Ԫ��
    void output(ostream &out) const;                      //�������������Ԫ��

    //��������ӿ�
    void set(const int &theIndex, const T &theElement);   //�滻ָ��Ԫ��

    T at(const int &theIndex) const;//��ֵ����ʽ����ĳ�ڵ�Ԫ�ص�ֵ

    void push_back(const T &theElement);//�����������һ��Ԫ��

    void removeRange(const int &beginIndex, const int &endIndex);//ɾ��ָ����Χ�ڵ�Ԫ��

    void swapContainer(DoublyLinkedList<T> &theChain);//�������������е�Ԫ��

    void swapElement(const int &indexA, const int &indexB);//���������ڵ������

    void leftShift(const int &offset);//�����������ƶ�������߳�ȥ��Ԫ�ػ���ұ߽���

    void reverse();//ԭ�صߵ������е�Ԫ�أ��������κ��µĽڵ�ռ�

    void meld(DoublyLinkedList<T> &theChain);//�����������ϲ������ú����������У���������������ÿ�

    vector<DoublyLinkedList<T>> *split();//����������չ����a��b��a�а�������Ϊ������Ԫ�أ�b�а�������Ԫ�أ�a��b�Ĵ洢�ռ伴*this�Ĵ洢�ռ�

    void test();//��������˽�к����Ĺ��нӿ�

    void insertSort();//���ò������򷨶�����Ԫ�ؽ�������

    void selectionSort();//����ѡ������������е�Ԫ������

    void bubbleSort();//����ð�������Ԫ������

    void overwriteErase(const int &theIndex);//ɾ��theNodeָ��Ľڵ㣬��theNode�ڵ�ĺ�̽ڵ��������ǰŲһλ����ɾ����̽ڵ�

    void pop_front();

public://����Ϊ��Ա��������������غ���
    T &operator[](const int &theIndex) const;


private://˽���ڲ��ӿ�

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
        throw IllegalParameterValue("��ǰ����Ϊ�գ��޷�ִ���������");
    } else {
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
    checkIndex(beginIndex, "get");
    checkIndex(endIndex, "get");
    NodePointer beginNode = &(this->getNode(beginIndex));
    NodePointer endNode = &(this->getNode(endIndex));
    NodePointer deleteNode;
    int count = 0;
    while (beginNode != endNode->getNext()) {
        deleteNode = beginNode;
        beginNode = beginNode->getNext();
        delete deleteNode;
        count++;
    }
    this->getNode(beginIndex).thePrevious()->setNext(this->getNode(endIndex).getNext());
    this->getNode(endIndex).theNext()->setPrevious(this->getNode(beginIndex).getPrevious());
    listSize -= count;
}

template<class T>
void DoublyLinkedList<T>::swapContainer(DoublyLinkedList<T> &theChain) {
    NodePointer sourceBegin = nodeHeader->getNext();
    NodePointer sourceEnd = nodeHeader->getPrevious();
    NodePointer targetHeader = theChain.getHeader();
    nodeHeader->setNext(targetHeader->getNext());
    nodeHeader->setPrevious(targetHeader->getPrevious());
    targetHeader->thePrevious()->setNext(nodeHeader);
    targetHeader->theNext()->setPrevious(nodeHeader);
    targetHeader->setNext(sourceBegin);
    targetHeader->setPrevious(sourceEnd);
    sourceBegin->setPrevious(targetHeader);
    sourceEnd->setNext(targetHeader);
}

template<class T>
void DoublyLinkedList<T>::swapElement(const int &indexA, const int &indexB) {
    checkIndex(indexA, "get");
    checkIndex(indexB, "get");
    T temp = this->getNode(indexA).getElement();
    this->getNode(indexA).setElement(this->getNode(indexB).getElement());
    this->getNode(indexB).setElement(temp);
}

template<class T>
void DoublyLinkedList<T>::leftShift(const int &offset) {
    if (offset < 0)throw ExceptionSpace::IllegalParameterValue("����leftshift()ʱƫ�������ݴ���");
    int netOffset = offset % listSize;
    for (int i = 0; i < netOffset; i++) {
        T temp = this->at(0);
        this->pop_front();
        this->push_back(temp);
    }

}

template<class T>
void DoublyLinkedList<T>::reverse() {
    NodePointer p = nodeHeader;
    NodePointer temp;
    do {
        temp = p->getNext();
        p->setNext(p->getPrevious());
        p->setPrevious(temp);
        p = p->getNext();
    } while (p != nodeHeader);
}

template<class T>
void DoublyLinkedList<T>::meld(DoublyLinkedList<T> &theChain) {
    int sizeA=this->size();
    int sizeB=theChain.size();

    if (this->size() == 0 && theChain.size() == 0)return;
    NodePointer p = nodeHeader->getNext();
    NodePointer j = theChain.getHeader()->getNext();

    while (p->getNext() != nodeHeader)p = p->getNext();
    while (j->getNext() != theChain.getHeader())j = j->getNext();
    p->setNext(nullptr);
    j->setNext(nullptr);

    p = nodeHeader->getNext();
    j = theChain.getHeader()->getNext();
    NodePointer t, c, temp, temp2;
    do {
        temp = p->getNext();
        t = p;
        p = p->getNext();
        temp2 = j->getNext();
        c = j;
        j = j->getNext();
        t->setNext(c);
        c->setNext(temp);
        p->setPrevious(c);
        c->setPrevious(t);
    } while (p->getNext() != nullptr && j->getNext() != nullptr);
    if(p->getNext()== nullptr&&j->getNext()!= nullptr)
    {
        p->setNext(j);
        j->setPrevious(p);
        while(j->getNext()!= nullptr)
        {
            j=j->getNext();
        }
        j->setNext(nodeHeader);
        nodeHeader->setPrevious(j);

    }else if(p->getNext()!= nullptr&&j->getNext()== nullptr)
    {
        temp=p->getNext();
        p->setNext(j);
        j->setPrevious(p);
        j->setNext(temp);
        temp->setPrevious(j);
        p=temp;
        while(p->getNext()!= nullptr)
        {
            p=p->getNext();
        }
        p->setNext(nodeHeader);
    }else if(p->getNext()== nullptr&&j->getNext()== nullptr){
        p->setNext(j);
        j->setPrevious(p);
        j->setNext(nodeHeader);
        nodeHeader->setPrevious(j);
    }else
    {
        throw IllegalParameterValue("δ���ǵ����������");
    }
    theChain.getHeader()->setNext(nullptr);
    theChain.getHeader()->setPrevious(nullptr);
    listSize+=sizeB;
    theChain.setSize(0);
}

template<class T>
vector<DoublyLinkedList<T>> *DoublyLinkedList<T>::split() {

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
    checkIndex(theIndex, "get");
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
    this->getNode(theIndex).set(thePrevious, theElement, theNext);
}

template<class T>
void DoublyLinkedList<T>::logicalClear() {
    nodeHeader->setNext(nullptr);
    nodeHeader->setPrevious(nullptr);
    listSize = 0;
}

template<class T>
void DoublyLinkedList<T>::checkIndex(int theIndex, std::string actionType) const {
    //ȷ����������ִ���������ʱ����������ȷ�ķ�Χ��
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex > this->size()) {
            ostringstream s;
            s << "����Ԫ��ʱ��";
            if (theIndex < 0)s << "����ֵ����<0" << endl;
            if (theIndex > this->size())s << "����ֵ����>����Ԫ�ظ���" << endl;
            throw ExceptionSpace::IllegalParameterValue(s.str());
        }
    } else if (actionType == "erase" || actionType == "get" || actionType == "replace") {
        if (this->size() == 0)throw ExceptionSpace::IllegalParameterValue("����Ϊ�գ��޷�������ִ��ɾ������ȡ���滻����");
        if (!(theIndex >= 0 && theIndex < this->size())) {
            ostringstream s;
            if (theIndex >= this->size()) {
                if (actionType == "erase")
                    s << "ɾ��Ԫ��ʱ������ֵ����>=listSize" << endl;
                else if (actionType == "replace")s << "�滻Ԫ��ʱ������ֵ����>=listSize" << endl;
                else if (actionType == "get")s << "��ȡԪ��ʱ������ֵ����>=listSize" << endl;
            } else {
                //theIndex<0�����
                if (actionType == "erase")
                    s << "ɾ��Ԫ��ʱ������ֵ����<0" << endl;
                else if (actionType == "replace")s << "�滻Ԫ��ʱ������ֵ����<0" << endl;
                else if (actionType == "get")s << "��ȡԪ��ʱ������ֵ����<0" << endl;
            }
            throw ExceptionSpace::IllegalParameterValue(s.str());
        }
    } else {
        ostringstream s;
        s << "checkIndex�ڶ����������벻��ȷ��δָ����ȷ�Ĳ�������" << endl;
        throw ExceptionSpace::IllegalParameterValue(s.str());
    }

}

template<class T>
DoublyNode<T> *DoublyLinkedList<T>::indexToAddress(const int &theIndex) const {
    checkIndex(theIndex, "get");
    return &(this->getNode(theIndex));
}

template<class T>
bool DoublyLinkedList<T>::bubble(const int &n) {
    return false;
}

template<class T>
T DoublyLinkedList<T>::at(const int &theIndex) const {
    checkIndex(theIndex, "get");
    NodePointer p = nodeHeader->getNext();
    for (int i = 0; i < theIndex; i++) {
        p = p->getNext();
    }
    return p->getElement();
}

template<class T>
T &DoublyLinkedList<T>::operator[](const int &theIndex) const {
    return this->get(theIndex);
}

template<class T>
void DoublyLinkedList<T>::pop_front() {
    this->erase(0);
}
