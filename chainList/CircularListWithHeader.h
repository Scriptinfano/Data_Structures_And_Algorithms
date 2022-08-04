#pragma once

#include<vector>
#include<sstream>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\virtualBaseClassLinearList.h"
#include "../namespaces.h"

using namespace std;
using ExceptionSpace::IllegalParameterValue;

//拥有头节点的循环链表类，头节点的数据域不存储数据，头节点的下一个节点才是实际存储数据的节点，且被称为首节点

template<class T>
class CircularListWithHeader : public LinearList<T> {
    /*
     * void checkIndex(int theIndex, string actionType) const;代码与基类保持一致
     * */

public:
    typedef ChainNode<T> *NodePointer;
    typedef ChainNode<T> Node;

    //节点及节点指针别名
    typedef CircularListWithHeader<T> CircularList;
    typedef CircularListWithHeader<T> *CircularPointer;

public://公有成员变量
    NodePointer nodeHeader;//用基类中的首节点地址作为循环链表头节点地址变量，此处给变量起个别名方便引用
    int listSize;

public://公有接口
    //构造头节点(可提供地址)，建立空表，头节点中不存储任何数据，其指针域保存自身地址
    CircularListWithHeader(NodePointer p = new Node, int theListSize = 0) : nodeHeader(p), listSize(theListSize) {
        if (theListSize > 0) {
            NodePointer begin = nodeHeader->next;
            for (int i = 0; i < theListSize - 1; i++)
                begin = begin->next;
            begin->next = nodeHeader;
        } else {
            nodeHeader->next = nodeHeader;
        }
    }

    //可以直接构造首节点的构造函数
    CircularListWithHeader(const T &theElement, NodePointer p = new Node) : nodeHeader(p), listSize(1) {
        nodeHeader->next = new Node(theElement, nodeHeader);
    }

    //拷贝构造函数
    CircularListWithHeader(const CircularListWithHeader<T> &theChainList);

    //析构函数
    ~CircularListWithHeader();


    //ADT函数
    virtual T &get(const int &theIndex) const;                    //currentNode可以直接等于firstNode->next
    virtual int indexOf(const T &theElement) const;        //返回元素对应的索引
    virtual bool empty() const;                            //检测容器是否为空
    virtual int size() const;                              //返回容器中元素的数量
    virtual void clear();                                  //请空容器
    virtual void erase(const int &theIndex);                      //删除索引为index的元素
    virtual void insert(const int &theIndex, const T &theElement);//在索引为index的位置上插入元素
    virtual void output(ostream &out) const;               //输出容器中所有元素

    //其他函数
    void push_back(const T &theElement);

    void set(const int &theIndex, const T &theElement);//替换指定元素

    void removeRange(const int &beginIndex, const int &endIndex);//删除指定范围内的元素

    void swapContainer(CircularListWithHeader<T> &theChain);//交换两个链表中的元素

    void swapElement(const int &indexA, const int &indexB);//交换两个节点的数据

    void leftShift(const int &offset);//将链表中的元素向左移动offset个位置

    void reverse();//原地颠倒链表中的元素，不分配任何新的节点空间

    void meld(CircularListWithHeader<T> &chainA,
              CircularListWithHeader<T> &chainB);//与派生类方法meld()类似，合并后的链表应该是链表a和b的节点空间，合并之后输入链表chainA和chainB是空表，会物理删除输入的两个表

    vector<CircularListWithHeader<T>> *split();//生成两个扩展链表a和b，a中包含索引为奇数的元素，b中包含其余元素，a和b的存储空间即*this的存储空间

    void test();//用来测试私有函数的公有接口

    void insertSort();//利用插入排序法对链表元素进行排列

    void selectionSort();

    void bubbleSort();

private:

    ChainNode<T> &getNode(const int &theIndex);

    void setNode(const int &theIndex, const T &theElement, NodePointer &theNext);//设置指定索引为Index的节点的数据域和指针域

    void logicalClear();//逻辑清空链表元素，将存储链表首节点的成员变量指针firstNode置为nullptr，再将listSize置为0

    void setSize(int newSize);

    void checkIndex(int theIndex, std::string actionType) const;

    ChainNode<T> *indexToAddress(const int &theIndex) const;

    bool bubble(const int &n);

protected:

};

template<class T>
CircularListWithHeader<T>::CircularListWithHeader(const CircularListWithHeader<T> &theChainList) {
    this->listSize = theChainList.size();
    if (this->size() == 0) {
        //链表theChainList为空，不需要复制构造
        nodeHeader = new Node;
        nodeHeader->next = nodeHeader;
    } else {
        nodeHeader = new Node;
        NodePointer sourceNode = theChainList.nodeHeader->next;
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

template<class T>
CircularListWithHeader<T>::~CircularListWithHeader() {
    NodePointer p = nodeHeader->next;
    NodePointer deleteNode = nullptr;
    while (p != nodeHeader) {
        deleteNode = p;
        p = p->next;
        delete deleteNode;
    }
    delete nodeHeader;
}

template<class T>
T &CircularListWithHeader<T>::get(const int &theIndex) const {
    checkIndex(theIndex, "get");
    NodePointer currentNode = nodeHeader->next;
    for (int i = 0; i < theIndex; i++) {
        currentNode = currentNode->next;
    }
    return currentNode->element;

}

template<class T>
int CircularListWithHeader<T>::indexOf(const T &theElement) const {
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

template<class T>
void CircularListWithHeader<T>::erase(const int &theIndex) {
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
        //找到要删除节点的前驱节点
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        deleteNode = p->next;
        p->next = p->next->next;
    }
    listSize--;
    delete deleteNode;
}

template<class T>
void CircularListWithHeader<T>::insert(const int &theIndex, const T &theElement) {
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

template<class T>
void CircularListWithHeader<T>::output(ostream &out) const {
    for (NodePointer currentNode = nodeHeader->next; currentNode != nodeHeader; currentNode = currentNode->next) {
        out << currentNode->element << " ";
    }

}

template<class T>
void CircularListWithHeader<T>::setSize(int newSize) {
    if (newSize < this->size() && newSize > 0) {
        NodePointer p = nodeHeader->next;
        NodePointer j = p->next;
        for (int i = 0; i < newSize; i++) {
            j = j->next;
            p = p->next;
        }
        p->next = nodeHeader;
        ChainNode<T> *deleteNode = j;
        ChainNode<T> *currentNode = deleteNode;
        int count = 0;//记录删除节点的数量
        while (currentNode != nodeHeader) {
            currentNode = currentNode->next;
            delete deleteNode;
            deleteNode = currentNode;
            count++;

        }
        listSize -= count;
    } else {
        throw IllegalParameterValue("调用void chainList<T>::setSize(int newSize)函数时，参数传递错误");
    }
}

template<class T>
void CircularListWithHeader<T>::push_back(const T &theElement) {
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

template<class T>
void CircularListWithHeader<T>::set(const int &theIndex, const T &theElement) {
    checkIndex(theIndex, "replace");
    this->get(theIndex) = theElement;
}

template<class T>
void CircularListWithHeader<T>::removeRange(const int &beginIndex, const int &endIndex) {
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
        throw ExceptionSpace::IllegalParameterValue("使用removeRange函数时索引传入有误");
    }
}

template<class T>
void CircularListWithHeader<T>::swapContainer(CircularListWithHeader<T> &theChain) {
    int tempSize = listSize;
    listSize = theChain.listSize;
    theChain.listSize = tempSize;

    NodePointer tempHeader;
    tempHeader = nodeHeader;
    nodeHeader = theChain.nodeHeader;
    theChain.nodeHeader = tempHeader;

}

template<class T>
void CircularListWithHeader<T>::leftShift(const int &offset) {
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

template<class T>
void CircularListWithHeader<T>::reverse() {
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

template<class T>
void CircularListWithHeader<T>::meld(CircularListWithHeader<T> &chainA, CircularListWithHeader<T> &chainB) {
    if (chainA.size() == 0 && chainB.size() == 0)return;

    NodePointer p = chainA.nodeHeader->next;
    NodePointer j = chainB.nodeHeader->next;
    NodePointer aBegin = chainA.nodeHeader;

    //先将循环链表变为单链表
    while (p->next != chainA.nodeHeader) {
        p = p->next;
    }
    p->next = nullptr;
    while (j->next != chainB.nodeHeader) {
        j = j->next;
    }
    j->next = nullptr;

    p = chainA.nodeHeader->next;
    j = chainB.nodeHeader->next;
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

template<class T>
void CircularListWithHeader<T>::logicalClear() {
    nodeHeader->next = nodeHeader;
    listSize = 0;
}

template<class T>
vector<CircularListWithHeader<T>> *
CircularListWithHeader<T>::split()//生成两个扩展链表a和b，a中包含索引为奇数的元素，b中包含其余元素，a和b的存储空间即*this的存储空间
{
    auto *p = new vector<CircularList>;

    //以下是两种特殊情况
    if (this->size() < 2)return nullptr;
    if (this->size() == 2) {
        CircularList c1, c2;
        c1.nodeHeader->next = nodeHeader->next;
        c2.nodeHeader->next = nodeHeader->next->next;
        c1.nodeHeader->next->next = c1.nodeHeader;
        c2.nodeHeader->next->next = c2.nodeHeader;
        p->push_back(c1);
        p->push_back(c2);
        this->logicalClear();
        return p;
    }
    for (int x = 1; x + 1 <= listSize - 1; x++) {
        int i = x;
        while (i + 1 <= listSize - 1) {
            this->swapElement(i, i + 1);
            i += 2;
        }
    }

    int sizeA, sizeB;
    if (listSize % 2 == 0) { sizeA = listSize / 2; }
    else { sizeA = (listSize / 2) + 1; }
    sizeB = listSize - sizeA;
    NodePointer beginA = nodeHeader->next;
    NodePointer endB = this->indexToAddress(sizeA);
    NodePointer beginB = this->indexToAddress(listSize - 1);

    CircularList listA(nodeHeader, sizeA);

    NodePointer b_nodeHeader = new Node;
    b_nodeHeader->next = endB;
    CircularList listB(b_nodeHeader, sizeB);

    listB.reverse();

    p->push_back(listA);
    p->push_back(listB);
    return p;
}

template<class T>
void CircularListWithHeader<T>::test() {
}

template<class T>
void CircularListWithHeader<T>::insertSort() {

    for (int i = 1; i < this->size(); i++) {
        T t = this->get(i);
        int j = i - 1;
        while (j >= 0 && t < this->get(j)) {
            this->get(j + 1) = this->get(j);
            j--;
        }
        this->get(j + 1) = t;
    }

}

template<class T>
void CircularListWithHeader<T>::selectionSort() {
    for(int i=0;i<this->size()-1;i++)
    {
        int tempMin=i;
        for(int j=i+1;j<this->size();j++)
        {
            if(this->get(j)<this->get(tempMin))
                tempMin=j;
        }
        this->swapElement(tempMin,i);
    }

}

template<class T>
void CircularListWithHeader<T>::bubbleSort() {
    for(int i=this->size();i>1&&this->bubble(i);i--);
}

template<class T>
bool CircularListWithHeader<T>::empty() const {
    return listSize == 0;
}

template<class T>
int CircularListWithHeader<T>::size() const {
    return listSize;
}

template<class T>
void CircularListWithHeader<T>::clear() {
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


//全局模板函数
template<class T>
ostream &operator<<(ostream &out, const CircularListWithHeader<T> &chain) {
    chain.output(out);
    return out;
}

template<class T>
void CircularListWithHeader<T>::checkIndex(int theIndex, std::string actionType) const {
//确保索引在0到listsize-1之间
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex > this->size()) {
            ostringstream s;
            s << "插入元素时，";
            if (theIndex < 0)s << "索引值不得<0" << endl;
            if (theIndex > this->size())s << "索引值不得>数组元素个数" << endl;
            throw ExceptionSpace::IllegalParameterValue(s.str());
        }
    } else if (actionType == "erase" || actionType == "get" || actionType == "replace") {
        if (theIndex >= this->size()) {
            ostringstream s;
            if (actionType == "erase")
                s << "删除元素时，索引值不得>=listSize" << endl;
            else if (actionType == "replace")s << "替换元素时，索引值不得>=listSize" << endl;
            else if (actionType == "get")s << "获取元素时，索引值不得>=listSize" << endl;
            throw ExceptionSpace::IllegalParameterValue(s.str());
        }
    } else {
        ostringstream s;
        s << "checkIndex第二个参数传入不正确，未指定正确的操作类型" << endl;
        throw ExceptionSpace::IllegalParameterValue(s.str());
    }
}

template<class T>
void CircularListWithHeader<T>::swapElement(const int &indexA, const int &indexB) {
    checkIndex(indexA, "replace");
    checkIndex(indexB, "replace");
    T temp = this->get(indexA);
    this->get(indexA) = this->get(indexB);
    this->get(indexB) = temp;
}

template<class T>
void CircularListWithHeader<T>::setNode(const int &theIndex, const T &theElement,
                                        CircularListWithHeader::NodePointer &theNext) {
    this->getNode(theIndex).element = theElement;
    this->getNode(theIndex).next = theNext;
}

template<class T>
ChainNode<T> &CircularListWithHeader<T>::getNode(const int &theIndex) {
    NodePointer p = nodeHeader->next;
    for (int i = 0; i < theIndex; i++) {
        p = p->next;
    }
    return *p;
}

template<class T>
ChainNode<T> *CircularListWithHeader<T>::indexToAddress(const int &theIndex) const {
    NodePointer p = nodeHeader->next;
    for (int i = 0; i < theIndex; i++)
        p = p->next;
    return p;
}

template<class T>
bool CircularListWithHeader<T>::bubble(const int &n) {
    bool sorted=false;
    for(int i=0;i<n;i++)
    {
        if(this->get(i)>this->get(i+1))
        {
            this->swapElement(i,i+1);
            sorted= true;
        }
    }
    return sorted;
}