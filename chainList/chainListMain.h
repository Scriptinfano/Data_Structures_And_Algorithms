#pragma once

#include "D:\ClionProjects\Data_Structures_And_Algorithms\virtualBaseClassLinearList.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\arrayAndVectorList\illegalParameterValue.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\arrayAndVectorList\arrayList.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <iterator>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

//定义链表节点类
template<class T>
class chainNode {
public:
    T element;//链表节点的数据域
    chainNode<T> *next;//链表节点的指针域

    //成员函数
    chainNode() = default;

    chainNode(const T &theElement) { this->element = theElement; }

    chainNode(const T &theElement, chainNode<T> *theNext) {
        this->element = theElement;
        this->next = theNext;
    }
};

//定义链表类
template<class T>
class chainList : public linearList<T> {

    //定义模板类的友元模板函数直接将定义写在类定义之内
    friend bool operator<(const chainList<T> &leftChain, const chainList<T> &rightChain) {
        char c;
        T t;
        if (typeid(t) != typeid(c))throw illegalParameterValue("使用<比较两个链表时，不能比较除了char类型以外的数据类型");
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

    chainNode<T> *firstNode;//指向链表第一个节点的指针，当链表为空时，此值为nullptr
    int listSize;//链表节点个数

public:


    //不构造首节点，创建一个空表
    chainList(chainNode<T> *p = nullptr, int theListSize = 0) : firstNode(p),
                                                                listSize(theListSize) {};//以链表作为底层数据结构的容器无需指定容量

    //构造首节点
    chainList(const T &theElement, int theListSize = 1) : listSize(theListSize) {
        firstNode = new chainNode<T>(theElement, nullptr);
    }

    chainList(const chainList<T> &theChainList);

    ~chainList();

    //ADT方法
    bool empty() const { return listSize == 0; }    //检测是否为空
    int size() const;                               //返回容器元素个数
    T &get(int theIndex) const;                     //得到索引值为theIndex的元素
    int indexOf(const T &theElement) const;         //返回元素theElement首次出现的索引值
    void erase(int theIndex);                       //删除索引为theIndex的元素
    void insert(int theIndex, const T &theElement); //在指定位置插入元素
    void output(ostream &out) const;                //输出链表中的所有元素


    //其他函数
    void setSize(int newSize);//使链表节点个数等于newSize，若newSize小于原大小，则删除多余元素，若大于原大小则不做任何操作

    void push_back(const T &theElement);//向链表的尾部新加一个节点

    void set(int theIndex, const T &theElement);//替换指定元素

    void removeRange(int beginIndex, int endIndex);//删除指定范围内的元素

    chainNode<T> *indexToAddress(int theIndex) const;//给出索引，返回该索引所代表的节点的地址

    int indexOf(chainNode<T> *pBegin, const T &theElement) const;    //从以地址为pBegin的节点开始向后查找，找到第一个节点元素是theElement的节点编号

    int lastIndexOf(const T &theElement) const;//返回指定元素最后出现的索引，若不存在则返回-1

    void swap(chainList<T> &theChain);//交换两个链表中的元素

    void fromList(const arrayList<T> &theArray);//将数组线性表转换为链表

    arrayList<T> toList();//将自身转换为数组线性表，并直接返回结果

    void leftShift(int offset);//将链表中的元素向左移动offset个位置

    void reverse();//原地颠倒链表中的元素，不分配任何新的节点空间

    void meld(chainList<T> &chainA,
              chainList<T> &chainB);//与派生类方法meld()类似，合并后的链表应该是链表a和b的节点空间，合并之后输入链表chainA和chainB是空表，会物理删除输入的两个表

    void physicalClear();//物理删除链表元素，释放所有链表空间

    void logicalClear();//逻辑清空链表元素，将存储链表首节点的成员变量指针firstNode置为nullptr，再将listSize置为0



    //重载运算符函数
    T &operator[](int index);

    bool operator==(const chainList<T> &theChain);

    bool operator!=(const chainList<T> &theChain);

    //返回链表首节点地址
    chainNode<T> *begin() const;


};


template<class T>
void chainList<T>::checkIndex(int theIndex, string actionType) const {
//确保索引在0到listsize-1之间
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex > this->size()) {
            ostringstream s;
            s << "插入元素时，";
            if (theIndex < 0)s << "索引值不得<0" << endl;
            if (theIndex > listSize)s << "索引值不得>数组元素个数" << endl;
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


template<class T>
chainList<T>::chainList(const chainList<T> &theChainList) {
    listSize = theChainList.listSize;
    if (listSize == 0) {
        //链表theChainList为空，不需要复制构造
        firstNode = nullptr;
        return;
    }
    //先创建指针接管被复制链表，再拷贝第一个元素，再移动原链表指针，再用指针接管目标链表，然后循环拷贝元素
    chainNode<T> *sourceNode = theChainList.firstNode;//sourceNode指向被复制链表的首节点
    firstNode = new chainNode(sourceNode->element);//初始化目标链表首节点并拷贝首元素
    sourceNode = sourceNode->next;//指向被复制链表首节点的指针向后挪一个节点
    chainNode<T> *targetNode = firstNode;//创建指向目标链表首节点的指针
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
    if (currentNode == nullptr)return -1;//代表没有找到
    else return index;//找到了
}

template<class T>
void chainList<T>::erase(int theIndex) {
    checkIndex(theIndex, "erase");

    chainNode<T> *deleteNode;
    if (theIndex == 0)//删除首元素的节点
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    } else {
        //用遍历的方法让指针p指向要删除节点的前驱节点
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++) {
            p = p->next;
        }
        deleteNode = p->next;
        p->next = p->next->next;//让前驱节点直接连上要删除节点的后继节点
    }
    listSize--;
    delete deleteNode;
}

template<class T>
void chainList<T>::insert(int theIndex, const T &theElement) {
    checkIndex(theIndex, "insert");
    if (theIndex == 0)//在表头插入新节点
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
        //删除多于元素
        chainNode<T> *p = firstNode;
        for (int i = 0; i < newSize - 1; i++)
            p = p->next;
        //此时p指向的节点的之后的所有节点都是要删除的节点
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
        throw illegalParameterValue("使用removeRange函数时索引传入有误");

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
    //从以地址为pBegin的节点开始向后查找，找到第一个节点元素是theElement的节点编号
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
    if (currentNode == nullptr)return -1;//代表没有找到
    else return index;//找到了

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
    arrayList<T> array(this->size());
    for (int i = 0; i < this->size(); i++)
        array.push_back(this->get(i));

    return array;
}

template<class T>
void chainList<T>::leftShift(int offset) {
    int newSize = listSize - offset;
    chainNode<T> *p = firstNode;
    for (int i = 0; i < offset; i++)
        p = p->next;
    chainNode<T> *temp = new chainNode<T>(p->element, nullptr);
    chainNode<T> *j = temp;

    for (int i = 0; i < newSize - 1; i++) {
        j->next = new chainNode<T>(p->next->element, nullptr);
        j = j->next;
        p = p->next;
    }
    firstNode = temp;
    listSize = newSize;


}

template<class T>
void chainList<T>::reverse() {
    chainNode<T> *p = firstNode;
    chainNode<T> *j = firstNode->next;
    chainNode<T> *temp = nullptr;
    while (j != nullptr) {
        temp = j->next;
        j->next = p;
        p = j;
        j = temp;
    }
    firstNode->next = nullptr;
    firstNode = p;
}

template<class T>
void chainList<T>::meld(chainList<T> &chainA, chainList<T> &chainB) {
    if (chainA.size() == 0 && chainB.size() == 0)return;
    chainNode<T> *p = chainA.begin();
    chainNode<T> *j = chainB.begin();
    chainNode<T> *t = nullptr;
    chainNode<T> *c = nullptr;
    chainNode<T> *temp = nullptr;
    chainNode<T> *temp2 = nullptr;
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
    firstNode = chainA.begin();
    listSize = chainA.size() + chainB.size();
    chainA.logicalClear();
    chainB.logicalClear();

}

template<class T>
void chainList<T>::physicalClear() {
    chainNode<T> *deleteNode = firstNode;
    chainNode<T> *p = firstNode;
    while (p != nullptr) {
        deleteNode = p;
        p = p->next;
        delete deleteNode;
    }
    firstNode = nullptr;
    listSize = 0;
}

template<class T>
void chainList<T>::logicalClear() {
    firstNode = nullptr;
    listSize = 0;
}

//全局函数，重载左移运算符使得cout<<对象名可输出链表元素
template<class T>
ostream &operator<<(ostream &out, const chainList<T> &theNode) {
    theNode.output(out);
    return out;
}

//扩展chainList，以扩充抽象基类extendedLinearList中新增的功能
template<class T>
class extendedChainList : public extendedLinearList<T>, public chainList<T> {

protected:
    chainNode<T> *lastNode;//这是一个指向链表尾节点的指针，在调用push_back()函数时可以更快地将元素插入到链表尾部

public:
    //构造函数与拷贝构造函数

    extendedChainList(chainNode<T> *p = nullptr, int theSize = 0) : chainList<T>(p, theSize) {
        lastNode = chainList<T>::firstNode;
    }

    extendedChainList(const extendedChainList<T> &c) : chainList<T>(c) {
        chainNode<T> *p = chainList<T>::firstNode;
        while (p->next != nullptr)
            p = p->next;
        lastNode = p;
    }

    //ADT方法
    bool empty() const { return chainList<T>::listSize == 0; }

    int size() const { return chainList<T>::listSize; }

    T &get(int theIndex) const { return chainList<T>::get(theIndex); }

    int indexOf(const T &theElement) const { return chainList<T>::indexOf(theElement); }

    void erase(int theIndex);

    void insert(int theIndex, const T &theElement);

    void clear();

    void push_back(const T &theElement);

    void output(ostream &out) const { chainList<T>::output(out); }

    //其他函数
    void zero() {
        chainList<T>::firstNode = nullptr;
        chainList<T>::listSize = 0;
    }

    void meld(const extendedChainList<T> &chainA, const extendedChainList<T> &chainB);

    vector<extendedChainList<T>> *split();

};

template<class T>
void extendedChainList<T>::erase(int theIndex) {
    chainList<T>::checkIndex(theIndex, "erase");

    chainNode<T> *deleteNode;
    if (theIndex == 0)//删除头节点
    {
        deleteNode = chainList<T>::firstNode;
        chainList<T>::firstNode = chainList<T>::firstNode->next;
    } else {
        //找到要删除节点的前驱节点
        chainNode<T> *p = chainList<T>::firstNode;
        for (int i = 0; i < theIndex - 1; i++) {
            p = p->next;
        }
        deleteNode = p->next;
        p->next = p->next->next;
        //若要删除的节点是最后一个节点，则将最后一个节点的前一个节点作为最后一个节点
        if (deleteNode == lastNode)
            lastNode = p;
    }
    chainList<T>::listSize--;
    delete deleteNode;
}

template<class T>
void extendedChainList<T>::insert(int theIndex, const T &theElement) {
    chainList<T>::checkIndex(theIndex, "insert");

    //在头节点之前插入节点
    if (theIndex == 0) {
        chainList<T>::firstNode = new chainNode<T>(theElement, chainList<T>::firstNode);
        if (chainList<T>::listSize == 0)lastNode = chainList<T>::firstNode;
    } else {
        //找到要插入节点的前驱节点
        chainNode<T> *p = chainList<T>::firstNode;
        for (int i = 0; i < chainList<T>::listSize - 1; i++)
            p = p->next;
        p->next = new chainNode<T>(theElement, p->next);
        if (chainList<T>::listSize == theIndex) {
            //说明是在最后一个节点之后插入节点，相当于在末尾新增节点
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
        //整个链表是空的情况
        chainList<T>::firstNode = lastNode = newNode;
    } else {
        lastNode->next = newNode;
        lastNode = newNode;
    }
    chainList<T>::listSize++;
}

template<class T>
void extendedChainList<T>::meld(const extendedChainList<T> &chainA, const extendedChainList<T> &chainB) {
    chainNode<T> *p = chainA.firstNode;
    chainNode<T> *j = chainB.firstNode;
    chainNode<T> *k = nullptr;
    while (!(p == nullptr || j == nullptr)) {
        this->push_back(p->element);
        p = p->next;
        this->push_back(j->element);
        j = j->next;

    }

    //此时如果两个链表长度不相等，则一个指针是nullptr，另一个指针指向的节点及之后的所有节点都是要插入目标链表的，目标链表即调用该函数的对象
    if (j == nullptr && p != nullptr) {
        //chainA链表剩下的全部插入
        while (p != nullptr) {
            this->push_back(p->element);
            p = p->next;
        }
    } else if (j != nullptr && p == nullptr) {
        //chainB链表剩下的全部插入
        while (j != nullptr) {
            this->push_back(j->element);
            j = j->next;
        }

    } else {
        //j和p都是nullptr，说明两个链表的长度一样，不需要做任何后续的补全工作
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
    extendedChainList<T> oddChain;//存放索引为奇数的节点
    extendedChainList<T> evenChain;//存放索引为偶数的节点
    for (int i = 0; i < this->size(); i++) {
        if ((i % 2) != 0)//索引为奇数时
        {
            oddChain.push_back(this->get(i));
        } else {
            //索引为偶数时
            evenChain.push_back(this->get(i));
        }
    }
    targetVector->push_back(oddChain);
    targetVector->push_back(evenChain);
    return targetVector;
}


//全局模板函数，假设T类型的数据定义了比较运算符，且输入的两个链表chainA和chainB都是有序链表
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

