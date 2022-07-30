#pragma once

#include "chainListMain.h"
#include "extendedChainList.h"

using namespace std;


//拥有头节点的循环链表类，头节点的数据域不存储数据，头节点的下一个节点才是实际存储数据的节点，且被称为首节点
template<class T>
class circularListWithHeader : public chainList<T> {
    /*
     * void checkIndex(int theIndex, string actionType) const;代码与基类保持一致
     * */
public:

    typedef chainNode<T> *pointer;
    typedef chainNode<T> node;
    pointer &header = chainList<T>::firstNode;//用基类中的首节点地址作为循环链表头节点地址变量，此处给变量起个别名方便引用
    int &listSize = chainList<T>::listSize;

    //构造头节点，建立空表，头节点中不存储任何数据，其指针域保存自身地址
    circularListWithHeader(pointer p = nullptr, int theListSize = 0) : chainList<T>(p, theListSize) {
        header = new node;
        header->next = header;
    }

    //可以直接构造首节点的构造函数
    circularListWithHeader(const T &theElement, int theListSize = 1) : chainList<T>(nullptr, theListSize) {
        header = new node;
        header->next = new node(theElement, header);
    }

    circularListWithHeader(const circularListWithHeader<T> &theChainList);

    ~circularListWithHeader();

    //以下仅显示需要重写的ADT函数
    T &get(int theIndex) const;//currentNode可以直接等于firstNode->next
    int indexOf(const T &theElement) const;

    void erase(int theIndex);

    void insert(int theIndex, const T &theElement);

    void output(ostream &out) const;

    //其他函数
    void push_back(const T &theElement);

    void set(int theIndex, const T &theElement);//替换指定元素

    void removeRange(int beginIndex, int endIndex);//删除指定范围内的元素

    void swap(chainList<T> &theChain);//交换两个链表中的元素

    void fromList(const arrayList<T> &theArray);//将数组线性表转换为链表

    arrayList<T> toList();//将自身转换为数组线性表，并直接返回结果

    void leftShift(int offset);//将链表中的元素向左移动offset个位置

    void reverse();//原地颠倒链表中的元素，不分配任何新的节点空间

    void meld(chainList<T> &chainA,
              chainList<T> &chainB);//与派生类方法meld()类似，合并后的链表应该是链表a和b的节点空间，合并之后输入链表chainA和chainB是空表，会物理删除输入的两个表

    void physicalClear();//物理删除链表元素，释放所有链表空间

    void logicalClear();//逻辑清空链表元素，将存储链表首节点的成员变量指针firstNode置为nullptr，再将listSize置为0

    vector<chainList<T>> *split();//生成两个扩展链表a和b，a中包含索引为奇数的元素，b中包含其余元素，a和b的存储空间即*this的存储空间

    void test();//用来测试私有函数的公有接口

    void swapNode(int indexA, int indexB);//交换两个节点的数据

    void insertSort();//利用插入排序法对链表元素进行排列

    void selectionSort();

    void rankSort();

    void bubbleSort();


private:
    void setSize(int newSize);

protected:

};

template<class T>
circularListWithHeader<T>::circularListWithHeader(const circularListWithHeader<T> &theChainList) {
    this->setSize(theChainList.size());
    if (this->size() == 0) {
        //链表theChainList为空，不需要复制构造
        header = new node;
        header->next = header;
    } else {
        header = new node;
        pointer sourceNode = theChainList.begin()->next;
        header->next = new node(theChainList.begin()->next->element);
        sourceNode = sourceNode->next;
        pointer targetNode = header->next;
        while (sourceNode != theChainList.begin()) {
            targetNode->next = new node(sourceNode->element);
            targetNode = targetNode->next;
            sourceNode = sourceNode->next;
        }
        targetNode->next = header;
    }
}

template<class T>
circularListWithHeader<T>::~circularListWithHeader() {
    pointer p = header->next;
    while (p != header) {
        pointer nextNode = p->next;
        delete p;
        p = nextNode;
    }
    delete p;
    listSize = 0;
}

template<class T>
T &circularListWithHeader<T>::get(int theIndex) const {
    chainList<T>::checkIndex(theIndex, "get");
    pointer currentNode = header->next;
    for (int i = 0; i < theIndex; i++) {
        currentNode = currentNode->next;
    }
    return currentNode->element;

}

template<class T>
int circularListWithHeader<T>::indexOf(const T &theElement) const {
    pointer currentNode = header->next;
    int index = 0;
    while (currentNode->element != theElement) {
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == header) {
        return -1;
    } else return index;

}

template<class T>
void circularListWithHeader<T>::erase(int theIndex) {
    chainList<T>::checkIndex(theIndex, "erase");
    pointer deleteNode;
    if (theIndex == 0 && listSize == 1) {
        deleteNode = header->next;
        header->next = header;
    } else if (theIndex == 0 && listSize > 1) {
        deleteNode = header->next;
        header->next = header->next->next;
    } else {
        pointer p = header->next;
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
void circularListWithHeader<T>::insert(int theIndex, const T &theElement) {
    chainList<T>::checkIndex(theIndex, "insert");
    if (theIndex == 0) {
        if (listSize == 0)
            header->next = new node(theElement, header);
        else header->next = new node(theElement, header->next);
    } else {
        pointer p = header->next;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        p->next = new node(theElement, p->next);
    }
    listSize++;
}

template<class T>
void circularListWithHeader<T>::output(ostream &out) const {
    for (pointer currentNode = header->next; currentNode != header; currentNode = currentNode->next) {
        out << currentNode->element << " ";
    }
}

template<class T>
void circularListWithHeader<T>::setSize(int newSize) {
    if (newSize < this->size() && newSize > 0) {
        pointer p = header->next;
        pointer j = p->next;
        for (int i = 0; i < newSize; i++) {
            j = j->next;
            p = p->next;
        }
        p->next = header;
        chainNode<T> *deleteNode = j;
        chainNode<T> *currentNode = deleteNode;
        int count = 0;//记录删除节点的数量
        while (currentNode != header) {
            currentNode = currentNode->next;
            delete deleteNode;
            deleteNode = currentNode;
            count++;

        }
        listSize -= count;
    } else {
        throw illegalParameterValue("调用void chainList<T>::setSize(int newSize)函数时，参数传递错误");
    }
}

template<class T>
void circularListWithHeader<T>::push_back(const T &theElement) {
    pointer newNode = new node(theElement, header);
    if (listSize == 0)header->next = newNode;
    else {
        pointer p = header->next;
        for (int i = 0; i < listSize - 1; i++) {
            p = p->next;
        }
        p->next = newNode;
    }
    listSize++;
}

template<class T>
void circularListWithHeader<T>::set(int theIndex, const T &theElement) {
    chainList<T>::checkIndex(theIndex,"replace");
    this->get(theIndex)=theElement;
}

template<class T>
void circularListWithHeader<T>::removeRange(int beginIndex, int endIndex) {
if(beginIndex>=0&&beginIndex<endIndex&&endIndex<=listSize-1)
{
    pointer pBegin=header->next,pEnd=header->next;
    for(int i=0;i<beginIndex-1;i++)
        pBegin=pBegin->next;
    for(int i=0;i< endIndex-1;i++)
        pEnd=pEnd->next;
    pointer p=pBegin->next,j=pEnd->next,deleteNode= nullptr;
    int count=0;
    while(p!=j->next)
    {
        deleteNode=p;
        p=p->next;
        delete deleteNode;
        count++;
    }


}
}

template<class T>
void circularListWithHeader<T>::swap(chainList<T> &theChain) {
}

template<class T>
void circularListWithHeader<T>::fromList(const arrayList<T> &theArray) {
}

template<class T>
arrayList<T> circularListWithHeader<T>::toList() {
}

template<class T>
void circularListWithHeader<T>::leftShift(int offset) {
}

template<class T>
void circularListWithHeader<T>::reverse() {
}

template<class T>
void circularListWithHeader<T>::meld(chainList<T> &chainA, chainList<T> &chainB) {
}

template<class T>
void circularListWithHeader<T>::physicalClear() {
}

template<class T>
void circularListWithHeader<T>::logicalClear() {
}

template<class T>
vector<chainList<T>> *circularListWithHeader<T>::split() {
}

template<class T>
void circularListWithHeader<T>::test() {
}

template<class T>
void circularListWithHeader<T>::swapNode(int indexA, int indexB) {
}

template<class T>
void circularListWithHeader<T>::insertSort() {
}

template<class T>
void circularListWithHeader<T>::selectionSort() {
}

template<class T>
void circularListWithHeader<T>::rankSort() {
}

template<class T>
void circularListWithHeader<T>::bubbleSort() {
}
