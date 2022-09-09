
#pragma once

#include <iostream>
#include<sstream>
#include<vector>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\BaseLinearList.h"
#include "ChainNode.h"
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

    //����ָ��������Ԫ��ֵ
    T get(const int &theIndex) const {
        checkIndex(theIndex, "get");
        NodePointer p = nodeHeader->getNext();
        for (int i = 0; i < theIndex; i++) {
            p = p->getNext();
        }
        return p->getElement();

    }

    //����ָ��Ԫ��ֵ������ֵ
    int indexOf(const T &theElement) const {
        NodePointer p = nodeHeader->getNext();
        int i = 0;
        while (p != nodeHeader) {
            if (p->getElement() == theElement) { return i; }
            p = p->getNext();
            i++;
        }
        return -1;

    }

    //�ж������Ƿ�Ϊ��
    bool empty() const { return listSize == 0; }

    //����������Ԫ�صĸ���
    int size() const { return listSize; }

    //��������е�Ԫ��
    void clear() {
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

    //ɾ��ָ������ֵ��Ԫ��
    void erase(const int &theIndex) {
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

    //��ָ������ֵ��Ԫ��֮ǰ����ָ��Ԫ��
    void insert(const int &theIndex, const T &theElement) {
        checkIndex(theIndex, "insert");
        NodePointer previousNode = this->getNode(theIndex).getPrevious();
        NodePointer nextNode = previousNode->getNext();
        auto newNode = new Node(previousNode, theElement, nextNode);
        previousNode->setNext(newNode);
        nextNode->setPrevious(newNode);

    }

    //�������Ԫ��
    void output(ostream &out) const {
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

    void set(const int &theIndex, const T &theElement) {
        NodePointer p = nodeHeader;
        for (int i = 0; i < theIndex + 1; i++) {
            p->setNext(p->getNext());
        }
        p->setElement(theElement);

    }

    T at(const int &theIndex) const {
        checkIndex(theIndex, "get");
        NodePointer p = nodeHeader->getNext();
        for (int i = 0; i < theIndex; i++) {
            p = p->getNext();
        }
        return p->getElement();

    }

    void push_back(const T &theElement) {
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

    void removeRange(const int &beginIndex, const int &endIndex) {
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

    void swapContainer(DoublyLinkedList<T> &theChain) {
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

    void swapElement(const int &indexA, const int &indexB) {
        checkIndex(indexA, "get");
        checkIndex(indexB, "get");
        T temp = this->getNode(indexA).getElement();
        this->getNode(indexA).setElement(this->getNode(indexB).getElement());
        this->getNode(indexB).setElement(temp);

    }

    void leftShift(const int &offset) {
        if (offset < 0)throw ExceptionSpace::IllegalParameterValue("????leftshift()?????????????");
        int netOffset = offset % listSize;
        for (int i = 0; i < netOffset; i++) {
            T temp = this->at(0);
            this->pop_front();
            this->push_back(temp);
        }
    }

    void reverse() {
        NodePointer p = nodeHeader;
        NodePointer temp;
        do {
            temp = p->getNext();
            p->setNext(p->getPrevious());
            p->setPrevious(temp);
            p = p->getNext();
        } while (p != nodeHeader);

    }

    void meld(DoublyLinkedList<T> &theChain) {
        int sizeA = this->size();
        int sizeB = theChain.size();

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
        if (p->getNext() == nullptr && j->getNext() != nullptr) {
            p->setNext(j);
            j->setPrevious(p);
            while (j->getNext() != nullptr) {
                j = j->getNext();
            }
            j->setNext(nodeHeader);
            nodeHeader->setPrevious(j);

        } else if (p->getNext() != nullptr && j->getNext() == nullptr) {
            temp = p->getNext();
            p->setNext(j);
            j->setPrevious(p);
            j->setNext(temp);
            temp->setPrevious(j);
            p = temp;
            while (p->getNext() != nullptr) {
                p = p->getNext();
            }
            p->setNext(nodeHeader);
        } else if (p->getNext() == nullptr && j->getNext() == nullptr) {
            p->setNext(j);
            j->setPrevious(p);
            j->setNext(nodeHeader);
            nodeHeader->setPrevious(j);
        } else {
            throw IllegalParameterValue("�ڵ���meldʱ��δ���ǵ����������");
        }
        theChain.getHeader()->setNext(nullptr);
        theChain.getHeader()->setPrevious(nullptr);
        listSize += sizeB;
        theChain.setSize(0);

    }

    vector<DoublyLinkedList<T>> *split() {

    }

    void test() {

    }

    void insertSort() {

    }

    void selectionSort() {

    }

    void bubbleSort() {

    }

    void overwriteErase(const int &theIndex) {

    }

    void pop_front() {
        this->erase(0);

    }

public:
    T operator[](const int &theIndex) const {
        checkIndex(theIndex, "get");
        NodePointer p = nodeHeader->getNext();
        for (int i = 0; i < theIndex; i++) {
            p = p->getNext();
        }
        return p->getElement();
    }


private:

    DoublyNode<T> &getNode(const int &theIndex) const {
        checkIndex(theIndex, "get");
        NodePointer p = nodeHeader->getNext();
        for (int i = 0; i < theIndex; i++) {
            p = p->getNext();
        }
        return *p;

    }

    void setNode(const int &theIndex, const T &theElement, const NodePointer &thePrevious, const NodePointer &theNext) {
        this->getNode(theIndex).set(thePrevious, theElement, theNext);
    }

    void logicalClear() {
        nodeHeader->setNext(nullptr);
        nodeHeader->setPrevious(nullptr);
        listSize = 0;

    }

    void checkIndex(int theIndex, std::string actionType) const {
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

    DoublyNode<T> *indexToAddress(const int &theIndex) const {
        checkIndex(theIndex, "get");
        return &(this->getNode(theIndex));

    }

    bool bubble(const int &n) {

    }
};
