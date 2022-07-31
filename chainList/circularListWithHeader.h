#pragma once

#include<vector>
#include<sstream>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\virtualBaseClassLinearList.h"

using namespace std;


class illegalParameterValue {
private:
    string message;

public:
    illegalParameterValue() : message("非法实参传入") {}

    illegalParameterValue(string theMessage) { message = theMessage; }

    void outPutMessage() const { cout << message << endl; }
};


//拥有头节点的循环链表类，头节点的数据域不存储数据，头节点的下一个节点才是实际存储数据的节点，且被称为首节点


template<class T>
class circularListWithHeader : public linearList<T> {
    /*
     * void checkIndex(int theIndex, string actionType) const;代码与基类保持一致
     * */

public:

    //节点及节点指针别名
    typedef chainNode<T> *pointer;
    typedef chainNode<T> node;


    pointer header;//用基类中的首节点地址作为循环链表头节点地址变量，此处给变量起个别名方便引用
    int listSize;

    //构造头节点，建立空表，头节点中不存储任何数据，其指针域保存自身地址
    circularListWithHeader(pointer p = nullptr, int theListSize = 0) {
        header = new node;
        header->next = header;
    }

    //可以直接构造首节点的构造函数
    circularListWithHeader(const T &theElement, int theListSize = 1) {
        header = new node;
        header->next = new node(theElement, header);
    }

    //拷贝构造函数
    circularListWithHeader(const circularListWithHeader<T> &theChainList);

    //析构函数
    ~circularListWithHeader();


    //ADT函数
    virtual T &get(int theIndex) const;//currentNode可以直接等于firstNode->next
    virtual int indexOf(const T &theElement) const;

    virtual bool empty() const;                          //检测容器是否为空
    virtual int size() const;                            //返回容器中元素的数量
    virtual void clear();

    virtual void erase(int theIndex);

    virtual void insert(int theIndex, const T &theElement);

    virtual void output(ostream &out) const;

    //其他函数
    void push_back(const T &theElement);

    void set(int theIndex, const T &theElement);//替换指定元素

    void removeRange(int beginIndex, int endIndex);//删除指定范围内的元素

    void swap(circularListWithHeader<T> &theChain);//交换两个链表中的元素

    void fromList(const circularListWithHeader<T> &theChain);//将数组线性表转换为链表

    void leftShift(int offset);//将链表中的元素向左移动offset个位置

    void reverse();//原地颠倒链表中的元素，不分配任何新的节点空间

    void meld(circularListWithHeader<T> &chainA,
              circularListWithHeader<T> &chainB);//与派生类方法meld()类似，合并后的链表应该是链表a和b的节点空间，合并之后输入链表chainA和chainB是空表，会物理删除输入的两个表

    void physicalClear();//物理删除链表元素，释放所有链表空间

    void logicalClear();//逻辑清空链表元素，将存储链表首节点的成员变量指针firstNode置为nullptr，再将listSize置为0

    vector<circularListWithHeader<T>> *split();//生成两个扩展链表a和b，a中包含索引为奇数的元素，b中包含其余元素，a和b的存储空间即*this的存储空间

    void test();//用来测试私有函数的公有接口

    void swapNode(int indexA, int indexB);//交换两个节点的数据

    void insertSort();//利用插入排序法对链表元素进行排列

    void selectionSort();

    void rankSort();

    void bubbleSort();


private:
    void setSize(int newSize);

    void checkIndex(int theIndex, std::string actionType) const;


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
    header->next = header;
    pointer deleteNode = nullptr;
    while (p != header) {
        deleteNode = p;
        p = p->next;
        delete deleteNode;
    }
    listSize = 0;
}

template<class T>
T &circularListWithHeader<T>::get(int theIndex) const {
    checkIndex(theIndex, "get");
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
    checkIndex(theIndex, "erase");
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
    checkIndex(theIndex, "insert");
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
    checkIndex(theIndex, "replace");
    this->get(theIndex) = theElement;
}

template<class T>
void circularListWithHeader<T>::removeRange(int beginIndex, int endIndex) {
    if (beginIndex >= 0 && beginIndex < endIndex && endIndex <= listSize - 1) {
        pointer pBegin = header->next, pEnd = header->next;
        for (int i = 0; i < beginIndex - 1; i++)
            pBegin = pBegin->next;
        for (int i = 0; i < endIndex - 1; i++)
            pEnd = pEnd->next;
        pointer p = pBegin->next, j = pEnd->next, deleteNode = nullptr;
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
        throw illegalParameterValue("使用removeRange函数时索引传入有误");
    }
}

template<class T>
void circularListWithHeader<T>::swap(circularListWithHeader<T> &theChain) {
}

template<class T>
void circularListWithHeader<T>::leftShift(int offset) {
}

template<class T>
void circularListWithHeader<T>::reverse() {
}

template<class T>
void circularListWithHeader<T>::meld(circularListWithHeader<T> &chainA, circularListWithHeader<T> &chainB) {
}

template<class T>
void circularListWithHeader<T>::physicalClear() {
}

template<class T>
void circularListWithHeader<T>::logicalClear() {
}

template<class T>
vector<circularListWithHeader<T>> *
circularListWithHeader<T>::split()//生成两个扩展链表a和b，a中包含索引为奇数的元素，b中包含其余元素，a和b的存储空间即*this的存储空间
{

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

template<class T>
bool circularListWithHeader<T>::empty() const {
    return listSize == 0;
}

template<class T>
int circularListWithHeader<T>::size() const {
    return listSize;
}

template<class T>
void circularListWithHeader<T>::clear() {
    this->~circularListWithHeader();
}


//全局模板函数
template<class T>
ostream &operator<<(ostream &out, const circularListWithHeader<T> &chain) {
    chain.output(out);
    return out;
}

template<class T>
void circularListWithHeader<T>::checkIndex(int theIndex, std::string actionType) const {
//确保索引在0到listsize-1之间
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex > this->size()) {
            ostringstream s;
            s << "插入元素时，";
            if (theIndex < 0)s << "索引值不得<0" << endl;
            if (theIndex > this->size())s << "索引值不得>数组元素个数" << endl;
            throw illegalParameterValue(s.str());
        }
    } else if (actionType == "erase" || actionType == "get" || actionType == "replace") {
        if (theIndex >= this->size()) {
            ostringstream s;
            if (actionType == "erase")
                s << "删除元素时，索引值不得>=listSize" << endl;
            else if (actionType == "replace")s << "替换元素时，索引值不得>=listSize" << endl;
            else if (actionType == "get")s << "获取元素时，索引值不得>=listSize" << endl;
            throw illegalParameterValue(s.str());
        }
    } else {
        ostringstream s;
        s << "checkIndex第二个参数传入不正确，未指定正确的操作类型" << endl;
        throw illegalParameterValue(s.str());
    }
}
