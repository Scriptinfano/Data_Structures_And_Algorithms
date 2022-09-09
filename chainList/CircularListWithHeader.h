//�����ͷ�ڵ�Ļ�������
#pragma once

#include<vector>
#include<sstream>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\BaseLinearList.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\chainList\ChainNode.h"
using namespace std;
using ExceptionSpace::IllegalParameterValue;

//��ͷ���Ļ�������
template<class T>
class CircularListWithHeader : public LinearList<T> {
public:
    typedef ChainNode<T> *NodePointer;
    typedef ChainNode<T> Node;

    typedef CircularListWithHeader<T> CircularList;
    typedef CircularListWithHeader<T> *CircularPointer;

private:
    NodePointer nodeHeader;//ͷ�ڵ�ָ��
    int listSize;//�ڵ����

public:
    //�������׽ڵ�ֻ����ͷ�ڵ�Ĺ��캯��
    explicit CircularListWithHeader() : listSize(0) {
        nodeHeader = new Node(nodeHeader);
    }

    //�����׽ڵ�Ĺ��캯������ָ���׽ڵ��Ԫ��ֵ��ͷ�ڵ�ĵ�ַ
    explicit CircularListWithHeader(const T &theElement, NodePointer p = new Node) : nodeHeader(p), listSize(1) {
        nodeHeader->next = new Node(theElement, nodeHeader);
    }

    //ָ��ͷ�ڵ���׽ڵ��ַ�Ĺ��캯��������Ҫ�׽ڵ�Ԫ��ֵʱʹ��
    explicit CircularListWithHeader(const T &theElement, NodePointer header, NodePointer headNode = new Node) : nodeHeader(header), listSize(1) {
        nodeHeader->next = headNode;
        headNode->element = theElement;
        headNode->next = nodeHeader;
    }

    //ָ��ͷ�ڵ���׽ڵ��ַ�Ĺ��캯�����ڲ���Ҫ�ṩ�׽��Ԫ��ֵʱʹ��
    explicit CircularListWithHeader(NodePointer header, NodePointer headNode) : nodeHeader(header), listSize(1) {
        nodeHeader->next = headNode;
        headNode->next = nodeHeader;
    }

    //ֻ��Ҫָ���׽ڵ�Ĺ��캯��
    explicit CircularListWithHeader(NodePointer headNode) {
        nodeHeader = new Node(headNode);
        headNode->next = nodeHeader;
        listSize = 1;
    }

    //�������newSize���ڵ������Ȼ�����������Ԫ�ض���ΪtheElement
    CircularListWithHeader(const T theElement, const int &newSize) {
        nodeHeader = new Node;
        NodePointer p = nodeHeader;
        for (int i = 0; i < newSize; i++) {
            p->next = new Node(theElement, nodeHeader);
            p = p->next;
        }
        listSize = newSize;
    }

    //�������캯��
    CircularListWithHeader(const CircularListWithHeader<T> &theChainList) {
        if (theChainList.size() == 0) {
            //����theChainListΪ�գ�����Ҫ���ƹ���
            nodeHeader = new Node;
            nodeHeader->next = nodeHeader;
            listSize = 0;
        } else {
            listSize = theChainList.size();
            nodeHeader = new Node;
            NodePointer sourceNode = &(theChainList.getNode(0));//sourceNodeָ�򱻿���������׽ڵ�
            nodeHeader->next = new Node(sourceNode->element, nodeHeader);
            sourceNode = sourceNode->next;
            NodePointer targetNode = nodeHeader->next;
            while (sourceNode != theChainList.nodeHeader) {
                targetNode->next = new Node(sourceNode->element, nodeHeader);
                targetNode = targetNode->next;
                sourceNode = sourceNode->next;
            }
        }
    }

    //��������
    ~CircularListWithHeader() {
        NodePointer p = nodeHeader->next;
        NodePointer deleteNode = nullptr;
        while (p != nodeHeader) {
            deleteNode = p;
            p = p->next;
            delete deleteNode;
        }
        delete nodeHeader;
    }


    //ADT����

    //�õ�ָ������ֵ�Ľڵ��е�Ԫ��ֵ
    virtual T get(const int &theIndex) const {
        checkIndex(theIndex, "get");
        NodePointer currentNode = nodeHeader->next;
        for (int i = 0; i < theIndex; i++) {
            currentNode = currentNode->next;
        }
        return currentNode->element;
    }

    //�õ���һ���ڵ�Ԫ��ֵ����theElement�Ľڵ������ֵ
    virtual int indexOf(const T &theElement) const {
        NodePointer currentNode = nodeHeader->next;
        int index = 0;
        while (currentNode->element != theElement) {
            currentNode = currentNode->next;
            index++;
        }
        if (currentNode == nodeHeader) {
            return -1;
        } else return index;
    }

    //�ж������Ƿ�Ϊ��
    [[nodiscard]] virtual bool empty() const {
        return this->listSize == 0;
    }

    //����������Ԫ�صĸ���
    [[nodiscard]] virtual int size() const {
        return listSize;
    }

    //������������еĽڵ�
    virtual void clear() {
        NodePointer p = nodeHeader->next;
        nodeHeader->next = nodeHeader;
        NodePointer deleteNode;
        while (p != nodeHeader) {
            deleteNode = p;
            p = p->next;
            delete deleteNode;
        }
        listSize = 0;
    }

    //ɾ��ָ�������Ľڵ�
    virtual void erase(const int &theIndex) {
        checkIndex(theIndex, "erase");
        NodePointer deleteNode;
        if (theIndex == 0 && listSize == 1) {
            deleteNode = nodeHeader->next;
            nodeHeader->next = nodeHeader;
        } else if (theIndex == 0 && listSize > 1) {
            deleteNode = nodeHeader->next;
            nodeHeader->next = nodeHeader->next->next;
        } else {
            NodePointer p = nodeHeader->next;
            for (int i = 0; i < theIndex - 1; i++)
                p = p->next;
            deleteNode = p->next;
            p->next = p->next->next;
        }
        listSize--;
        delete deleteNode;

    }

    //��ָ�������Ľڵ�֮ǰ����ڵ�
    virtual void insert(const int &theIndex, const T &theElement) {
        checkIndex(theIndex, "insert");
        if (theIndex == 0) {
            if (listSize == 0)
                nodeHeader->next = new Node(theElement, nodeHeader);
            else nodeHeader->next = new Node(theElement, nodeHeader->next);
        } else {
            NodePointer p = nodeHeader->next;
            for (int i = 0; i < theIndex - 1; i++)
                p = p->next;
            p->next = new Node(theElement, p->next);
        }
        listSize++;

    }

    //������нڵ�Ԫ��ֵ
    virtual void output(ostream &out) const {
        if (listSize == 0) {
            cout << "��ǰ����Ϊ�գ��޷����" << endl;
            return;
        }
        for (NodePointer currentNode = nodeHeader->next; currentNode != nodeHeader; currentNode = currentNode->next) {
            out << currentNode->element << " ";
        }

    }

    //����ӿ�

    NodePointer getHeader() { return nodeHeader; }

    void push_back(const T &theElement) {
        NodePointer newNode = new Node(theElement, nodeHeader);
        if (listSize == 0)nodeHeader->next = newNode;
        else {
            NodePointer p = nodeHeader->next;
            for (int i = 0; i < listSize - 1; i++) {
                p = p->next;
            }
            p->next = newNode;
        }
        listSize++;


    }

    //��ָ�������Ľڵ��Ԫ��ֵ��ΪtheElement
    void setElement(const int &theIndex, const T &theElement) {
        checkIndex(theIndex, "replace");
        this->setElement(theIndex,theElement);
    }

    //�Ƴ�����ָ������֮�������Ԫ��
    void removeRange(const int &beginIndex, const int &endIndex) {
        if (beginIndex >= 0 && beginIndex < endIndex && endIndex <= listSize - 1) {
            NodePointer pBegin = nodeHeader->next, pEnd = nodeHeader->next;
            for (int i = 0; i < beginIndex - 1; i++)
                pBegin = pBegin->next;
            for (int i = 0; i < endIndex - 1; i++)
                pEnd = pEnd->next;
            NodePointer p = pBegin->next, j = pEnd->next, deleteNode = nullptr;
            int count = endIndex - beginIndex + 1;
            pBegin->next = j->next;
            j->next = nullptr;
            while (p != nullptr) {
                deleteNode = p;
                p = p->next;
                delete deleteNode;
            }

            listSize -= count;
        } else {
            throw ExceptionSpace::IllegalParameterValue("removeRange(const int &beginIndex, const int &endIndex)�������ݴ���");
        }

    }

    //�������������нڵ�
    void swapContainer(CircularListWithHeader<T> &theChain) {
        int tempSize = listSize;
        listSize = theChain.listSize;
        theChain.listSize = tempSize;

        NodePointer tempHeader;
        tempHeader = nodeHeader;
        nodeHeader = theChain.nodeHeader;
        theChain.nodeHeader = tempHeader;
    }

    //����ָ�������������ڵ��Ԫ��ֵ
    void swapElement(const int &indexA, const int &indexB) {
        checkIndex(indexA, "replace");
        checkIndex(indexB, "replace");
        T temp = this->get(indexA);
        this->setElement(indexA,this->get(indexB));
        this->setElement(indexB,temp);

    }

    //��Ԫ�����������ƶ�
    void leftShift(const int &offset) {
        NodePointer p = nodeHeader->next;
        NodePointer j = nodeHeader->next;
        for (int i = 0; i < offset - 1; i++) {
            p = p->next;
        }
        nodeHeader->next = p->next;
        p->next = nullptr;
        NodePointer deleteNode;
        while (j != nullptr) {
            deleteNode = j;
            j = j->next;
            delete deleteNode;
        }
        listSize -= offset;

    }

    //��ת����Ԫ��
    void reverse() {
        NodePointer p = nodeHeader->next;
        NodePointer first = p;
        NodePointer j = p->next;
        NodePointer temp = nullptr;
        while (j != nodeHeader) {
            temp = j->next;
            j->next = p;
            p = j;
            j = temp;
        }
        nodeHeader->next = p;
        first->next = nodeHeader;

    }

    //����������������Ԫ�ؽ��������øú����������У��Ҳ������µĿռ䣬����߼�ɾ���������������
    void meld(CircularListWithHeader<T> &chainA, CircularListWithHeader<T> &chainB) {
        if (chainA.size() == 0 && chainB.size() == 0)return;

        NodePointer p = &chainA.getNode(0);
        NodePointer j = &chainB.getNode(0);
        NodePointer aBegin = chainA.getHeader();
        NodePointer bBegin = chainB.getHeader();

        while (p->next != aBegin) {
            p = p->next;
        }
        p->next = nullptr;
        while (j->next != bBegin) {
            j = j->next;
        }
        j->next = nullptr;

        p = aBegin->next;
        j = bBegin->next;
        NodePointer t, c, temp, temp2;
        t = c = temp = temp2 = nullptr;

        do {
            temp = p->next;
            t = p;
            p = p->next;
            temp2 = j->next;
            c = j;
            j = j->next;
            t->next = c;
            c->next = temp;
        } while (temp != nullptr && temp2 != nullptr);
        if (temp == nullptr && temp2 != nullptr)
            c->next = temp2;

        nodeHeader = aBegin;
        NodePointer begin = nodeHeader;
        while (begin->next != nullptr) {
            begin = begin->next;
        }
        begin->next = nodeHeader;

        listSize = chainA.size() + chainB.size();
        chainA.logicalClear();
        chainB.logicalClear();

    }

    //����������չ����a��b��a�а���c������Ϊ������Ԫ�أ�b�а���c�������Ԫ�أ�����������ܸı�c�е��ڴ�ṹ
    vector<CircularListWithHeader<T>> *split() {
        auto p = new vector<CircularListWithHeader<T>>;

        //���ȴ��������������
        if (this->size() < 2)return nullptr;//������Ԫ��С��2ʱֱ�ӷ��ؿ�ָ��
        if (this->size() == 2) {
            auto p1 = this->indexToAddress(0);
            auto p2 = this->indexToAddress(1);
            CircularListWithHeader c1(p1), c2(p2);
            p->push_back(c1);
            p->push_back(c2);
            this->logicalClear();
            return p;
        }

        //���������㷨�������������Ϊż����Ԫ����ǰ�ᣬʹ�������һ�𣬶�����Ϊ������Ԫ�ؽ����Ե���������֮��
        //������������㷨�Ὣ����������{2, 7, 8, 9, 3, 5, 4, 6, 1}��Ϊ{2, 8, 3, 4, 1, 6, 5, 9, 7}
        for (int x = 1; x + 1 <= listSize - 1; x++) {
            int i = x;
            while (i + 1 <= listSize - 1) {
                this->swapElement(i, i + 1);
                i += 2;
            }
        }

        int sizeA, sizeB;//sizeA������Ϊż����Ԫ�صĸ�����sizeB������Ϊ������Ԫ�صĸ���
        if (listSize % 2 == 0) { sizeA = listSize / 2; }
        else { sizeA = (listSize / 2) + 1; }
        sizeB = listSize - sizeA;

        //������������Ϊż����Ԫ�ض���ǰ�棬��������Ϊ������Ԫ�ض��ں��棨ע���ʱ���������ǵ���֮����Ҫ��ת��
        //��ָ��ֱ𻮶�����ֵΪż��������������εĿ�ʼ��ĩβ
        NodePointer beginA = nodeHeader->next;//ָ������Ϊż�������еĵ�һ��Ԫ��
        NodePointer endA = this->indexToAddress(sizeA - 1);
        NodePointer beginB = this->indexToAddress(sizeA);//ָ������Ϊ���������е����һ��Ԫ��
        NodePointer endB = this->indexToAddress(listSize - 1);//ָ������Ϊ���������еĵ�һ��Ԫ��

        //��ż������Ԫ��ƴ�����´�����������
        CircularListWithHeader listA;//����ż�����е�����
        NodePointer beginListA = listA.getHeader();
        beginListA->next = beginA;
        endA->next = beginListA;

        //����������Ԫ��ƴ�����´�����������
        CircularListWithHeader listB;
        NodePointer beginListB = listB.getHeader();
        beginListB->next = beginB;
        endB->next = beginListB;

        //��תlistB
        listB.reverse();

        p->push_back(listA);
        p->push_back(listB);
        return p;

    }

    void test() {
        cout << "���޲��Դ���" << endl;
    }

    //���ղ����������������е�Ԫ��
    void insertSort() {

        for (int i = 1; i < this->size(); i++) {
            T t = this->get(i);
            int j = i - 1;
            while (j >= 0 && t < this->get(j)) {
                this->setElement(j + 1, this->get(j));
                j--;
            }
            this->setElement(j + 1, t);
        }

    }

    //����ѡ�����򷨶������е�Ԫ�ؽ�������
    void selectionSort() {
        for (int i = 0; i < this->size() - 1; i++) {
            int tempMin = i;
            for (int j = i + 1; j < this->size(); j++) {
                if (this->get(j) < this->get(tempMin))
                    tempMin = j;
            }
            this->swapElement(tempMin, i);
        }
    }

    //����ð�����򷨶������е�Ԫ�ؽ�������
    void bubbleSort() {
        for (int i = this->size(); i > 1 && this->bubble(i); i--);

    }

    //�ø��ǵķ�ʽɾ�������е�ĳһ������ڵ�
    void overwriteErase(const int &theIndex) {
        /*
         * Ҫɾ�������е�һ���ڵ㣬�Ȱѵڶ����ڵ��Ԫ��ֵ���ǵ���һ���ڵ㣬Ȼ��ѵڶ����ڵ�ɾ���ﵽ��
         * ɾ����һ���ڵ��Ŀ��
         * */
        checkIndex(theIndex, "erase");
        NodePointer theNode = this->indexToAddress(theIndex);
        theNode->element = theNode->next->element;
        NodePointer deleteNode = theNode->next;
        theNode->next = theNode->next->next;
        delete deleteNode;
    }

private:

    //����ָ�������Ľڵ�����
    ChainNode<T> &getNode(const int &theIndex)const {
        NodePointer p = nodeHeader->next;
        for (int i = 0; i < theIndex; i++) {
            p = p->next;
        }
        return *p;
    }

    //��ָ��������Ԫ��ֵ��ΪtheElement��������ָ������Ϊ�����ĵ�ַ
    void setNode(const int &theIndex, const T &theElement, NodePointer &theNext) {
        this->getNode(theIndex).element = theElement;
        this->getNode(theIndex).next = theNext;

    }

    //�߼����������Ԫ�أ�ʵ�ʿռ䲢δ�ͷ�
    void logicalClear() {
        nodeHeader->next = nodeHeader;
        listSize = 0;
    }

    //ǿ���趨����Ԫ�ظ��������������Ԫ�ظ�������ԭ������Ԫ�ظ�������Ҫɾ���κ�Ԫ��
    //��������Ԫ�ظ���С�ڵ�ǰ����Ԫ�ظ�������ɾ�����������ڵ�
    void setSize(int newSize) {
        if (newSize < this->size() && newSize > 0) {
            NodePointer p = nodeHeader->next;
            NodePointer j = p->next;
            for (int i = 0; i < newSize - 1; i++) {
                j = j->next;
                p = p->next;
            }
            p->next = nodeHeader;
            //��ʱjָ��Ľڵ㼰��֮������нڵ㶼��Ҫɾ���Ľڵ�
            ChainNode<T> *deleteNode = j;
            ChainNode<T> *currentNode = deleteNode;
            int count = 0;//��¼ɾ���ڵ������
            while (currentNode != nodeHeader) {
                currentNode = currentNode->next;
                delete deleteNode;
                deleteNode = currentNode;
                count++;
            }
            listSize -= count;
        } else {
            //������ĺ��油���½ڵ㣬�����½ڵ��ֵ����Ϊ0
            int newListSize = newSize - listSize;
            CircularListWithHeader circularList = new CircularListWithHeader<T>(0, newListSize);
            this->getNode(listSize - 1).next = circularList.indexToAddress(0);
            circularList.getNode(newListSize - 1).next = nodeHeader;
            listSize += newListSize;
            delete circularList.getHeader();
        }

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
            if (theIndex >= this->size()) {
                ostringstream s;
                if (actionType == "erase")
                    s << "ɾ��Ԫ��ʱ������ֵ����>=listSize" << endl;
                else if (actionType == "replace")s << "�滻Ԫ��ʱ������ֵ����>=listSize" << endl;
                else if (actionType == "get")s << "��ȡԪ��ʱ������ֵ����>=listSize" << endl;
                throw ExceptionSpace::IllegalParameterValue(s.str());
            }
        } else {
            ostringstream s;
            s << "checkIndex�ڶ����������벻��ȷ��δָ����ȷ�Ĳ�������" << endl;
            throw ExceptionSpace::IllegalParameterValue(s.str());
        }
    }

    ChainNode<T> *indexToAddress(const int &theIndex) const {
        NodePointer p = nodeHeader->next;
        for (int i = 0; i < theIndex; i++)
            p = p->next;
        return p;

    }

    bool bubble(const int &n) {
        bool sorted = false;
        for (int i = 0; i < n; i++) {
            if (this->get(i) > this->get(i + 1)) {
                this->swapElement(i, i + 1);
                sorted = true;
            }
        }
        return sorted;

    }

    void addNode(const NodePointer &p) {
        p->next = nodeHeader;
        this->getNode(listSize - 1).next = p;
        listSize++;
    }

};

template<class T>
ostream &operator<<(ostream &out, const CircularListWithHeader<T> &chain) {
    chain.output(out);
    return out;
}
