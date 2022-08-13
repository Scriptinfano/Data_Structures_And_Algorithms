#pragma once

#include "../linearList/arrayAndVectorList/arrayList.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <iterator>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;


//定义链表类
template<class T>
class chainList : public LinearList<T> {

    //定义模板类的友元模板函数直接将定义写在类定义之内
    friend bool operator<(const chainList<T> &leftChain, const chainList<T> &rightChain) {
        char c;
        T t;
        if (typeid(t) != typeid(c))throw ExceptionSpace::IllegalParameterValue("使用<比较两个链表时，不能比较除了char类型以外的数据类型");
        ChainNode<T> *it = leftChain.begin();
        ChainNode<T> *it2 = rightChain.begin();
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

    friend void bubbleSort(chainList<T> *chain, int size) {
        for (int i = size; i > 1 && chain->bubble(i); i--);
    }

protected:
    void checkIndex(int theIndex, string actionType) const;

    ChainNode<T> *firstNode;//指向链表第一个节点的指针，当链表为空时，此值为nullptr
    int listSize;//链表节点个数

public:


    //不构造首节点，创建一个空表
    chainList(ChainNode<T> *p = nullptr, int theListSize = 0) : firstNode(p), listSize(theListSize) {}

    //构造首节点
    chainList(const T &theElement, int theListSize = 1) : listSize(theListSize) {
        firstNode = new ChainNode<T>(theElement, nullptr);
    }

    chainList(const chainList<T> &theChainList);

    ~chainList();

    //ADT方法
    virtual bool empty() const { return listSize == 0; }    //检测是否为空
    virtual int size() const;                               //返回容器元素个数
    virtual T &get(const int &theIndex);                     //得到索引值为theIndex的元素
    virtual int indexOf(const T &theElement) const;         //返回元素theElement首次出现的索引值
    virtual void erase(const int &theIndex);                       //删除索引为theIndex的元素
    virtual void insert(const int &theIndex, const T &theElement); //在指定位置插入元素
    virtual void output(ostream &out) const;                //输出链表中的所有元素
    virtual void clear();                                   //标准清空容器接口，可选择物理清空还是逻辑清空


private:
    //私有内部接口：
    void setSize(int newSize);//使链表节点个数等于newSize，若newSize小于原大小，则删除多余元素，若大于原大小则不做任何操作

    ChainNode<T> *indexToAddress(int theIndex) const;//给出索引，返回该索引所代表的节点的地址

    int indexOf(ChainNode<T> *pBegin, const T &theElement) const;    //从以地址为pBegin的节点开始向后查找，找到第一个节点元素是theElement的节点编号

    int lastIndexOf(const T &theElement) const;//返回指定元素最后出现的索引，若不存在则返回-1

    void swap(int indexA, int indexB);//交换指定索引的两个节点的元素

    bool bubble(int n);

    void physicalClear();//物理删除链表元素，释放所有链表空间

    void logicalClear();//逻辑清空链表元素，将存储链表首节点的成员变量指针firstNode置为nullptr，再将listSize置为0


public:

    //其他函数

    void push_back(const T &theElement);//向链表的尾部新加一个节点

    void set(int theIndex, const T &theElement);//替换指定元素

    void removeRange(int beginIndex, int endIndex);//删除指定范围内的元素

    void swap(chainList<T> &theChain);//交换两个链表中的元素

    void fromList(const arrayList<T> &theArray);//将数组线性表转换为链表

    arrayList<T> toList();//将自身转换为数组线性表，并直接返回结果

    void leftShift(int offset);//将链表中的元素向左移动offset个位置

    void reverse();//原地颠倒链表中的元素，不分配任何新的节点空间

    void meld(chainList<T> &chainA,
              chainList<T> &chainB);//与派生类方法meld()类似，合并后的链表应该是链表a和b的节点空间，合并之后输入链表chainA和chainB是空表，会物理删除输入的两个表

    vector<chainList<T>> *split();//生成两个扩展链表a和b，a中包含索引为奇数的元素，b中包含其余元素，a和b的存储空间即*this的存储空间

    void test();//用来测试私有函数的公有接口

    void swapNode(int indexA, int indexB);//交换两个节点的数据

    void insertSort();//利用插入排序法对链表元素进行排列

    void selectionSort();

    void rankSort();

    void bubbleSort();


    //重载运算符函数
    T &operator[](int index);

    bool operator==(const chainList<T> &theChain);

    bool operator!=(const chainList<T> &theChain);

    //返回链表首节点地址
    ChainNode<T> *begin() const;


};


template<class T>
void chainList<T>::checkIndex(int theIndex, string actionType) const {
//确保索引在0到listSize-1之间
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex > this->size()) {
            ostringstream s;
            s << "插入元素时，";
            if (theIndex < 0)s << "索引值不得<0" << endl;
            if (theIndex > listSize)s << "索引值不得>数组元素个数" << endl;
            throw IllegalParameterValue(s.str());
        }
    } else if (actionType == "erase" || actionType == "get" || actionType == "replace") {
        if (theIndex >= this->size()) {
            ostringstream s;
            if (actionType == "erase")
                s << "删除元素时，索引值不得>=listSize" << endl;
            else if (actionType == "replace")s << "替换元素时，索引值不得>=listSize" << endl;
            else if (actionType == "get")s << "获取元素时，索引值不得>=listSize" << endl;
            throw IllegalParameterValue(s.str());
        }
    } else {
        ostringstream s;
        s << "checkIndex第二个参数传入不正确，未指定正确的操作类型" << endl;
        throw IllegalParameterValue(s.str());
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
    ChainNode<T> *sourceNode = theChainList.firstNode;//sourceNode指向被复制链表的首节点
    firstNode = new ChainNode<T>(sourceNode->element);//初始化目标链表首节点并拷贝首元素
    sourceNode = sourceNode->next;//指向被复制链表首节点的指针向后挪一个节点
    ChainNode<T> *targetNode = firstNode;//创建指向目标链表首节点的指针
    while (sourceNode != nullptr) {
        targetNode->next = new ChainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = nullptr;


}

template<class T>
chainList<T>::~chainList() {
    while (firstNode != nullptr) {
        ChainNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
    listSize = 0;
}

template<class T>
int chainList<T>::size() const {
    return listSize;
}

template<class T>
T &chainList<T>::get(const int &theIndex){
    checkIndex(theIndex, "get");
    ChainNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; i++) {
        currentNode = currentNode->next;
    }
    return currentNode->element;
}

template<class T>
int chainList<T>::indexOf(const T &theElement) const {
    ChainNode<T> *currentNode = firstNode;
    int index = 0;
    while (currentNode != nullptr && currentNode->element != theElement) {
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == nullptr)return -1;//代表没有找到
    else return index;//找到了
}

template<class T>
void chainList<T>::erase(const int &theIndex) {
    checkIndex(theIndex, "erase");

    ChainNode<T> *deleteNode;
    if (theIndex == 0)//删除首元素的节点
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    } else {
        //用遍历的方法让指针p指向要删除节点的前驱节点
        ChainNode<T> *p = firstNode;
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
void chainList<T>::insert(const int &theIndex, const T &theElement) {
    checkIndex(theIndex, "insert");
    if (theIndex == 0)//在表头插入新节点
    {
        firstNode = new ChainNode<T>(theElement, firstNode);

    } else {
        ChainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++) {
            p = p->next;
        }
        p->next = new ChainNode<T>(theElement, p->next);

    }
    listSize++;
}

template<class T>
void chainList<T>::output(ostream &out) const {
    for (ChainNode<T> *currentNode = firstNode; currentNode != nullptr; currentNode = currentNode->next) {
        out << currentNode->element << " ";
    }
}

template<class T>
void chainList<T>::setSize(int newSize) {
    if (newSize < 0)throw IllegalParameterValue("调用void chainList<T>::setSize(int newSize)函数时，参数传递错误，newSize不得小于0");
    if (newSize < listSize) {
        //删除多于元素
        ChainNode<T> *p = firstNode;
        ChainNode<T> *j = p->next;
        //此时p指向的节点是j指向的节点的前驱节点
        for (int i = 0; i < newSize; i++) {
            j = j->next;
            p = p->next;
        }
        //p在j的前面，此时j指向的节点以及之后的所有节点是要删除的节点
        p->next = nullptr;

        ChainNode<T> *deleteNode = j;
        ChainNode<T> *currentNode = deleteNode;

        int count = 0;//记录删除节点的数量
        while (currentNode != nullptr) {
            currentNode = currentNode->next;
            delete deleteNode;
            deleteNode = currentNode;
            count++;
        }
        listSize -= count;

    } else {
        throw IllegalParameterValue("调用void chainList<T>::setSize(int newSize)函数时，参数传递错误，newSize不得大于原大小");
    }

}

template<class T>
void chainList<T>::push_back(const T &theElement) {
    ChainNode<T> *newNode = new ChainNode<T>(theElement, nullptr);
    if (listSize == 0)firstNode = newNode;
    else {
        ChainNode<T> *p = firstNode;
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
        ChainNode<T> *pBegin = firstNode, *pEnd = firstNode;
        for (int i = 0; i < beginIndex - 1; i++)
            pBegin = pBegin->next;
        for (int i = 0; i < endIndex - 1; i++)
            pEnd = pEnd->next;
        ChainNode<T> *p = pBegin->next, *j = pEnd->next;
        ChainNode<T> *deleteNode = nullptr;
        int count = 0;
        pBegin->next = j->next;

        while (p != j->next) {
            deleteNode = p;
            p = p->next;
            delete deleteNode;
            count++;
        }
        listSize -= count;
    } else {
        throw IllegalParameterValue("使用removeRange函数时索引传入有误");

    }
}

template<class T>
int chainList<T>::lastIndexOf(const T &theElement) const {
    ChainNode<T> *p = firstNode;
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
int chainList<T>::indexOf(ChainNode<T> *pBegin, const T &theElement) const {
    //从以地址为pBegin的节点开始向后查找，找到第一个节点元素是theElement的节点编号
    ChainNode<T> *currentNode = pBegin;
    int index = 0;
    ChainNode<T> *p = firstNode;
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
ChainNode<T> *chainList<T>::indexToAddress(int theIndex) const {
    if (theIndex >= listSize || theIndex < 0)return nullptr;
    int index = 0;
    ChainNode<T> *p = firstNode;
    while (index != theIndex) {
        p = p->next;
        index++;
    }
    return p;
}

template<class T>
T &chainList<T>::operator[](int index) {
    ChainNode<T> *p = firstNode;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    return p->element;

}

template<class T>
bool chainList<T>::operator==(const chainList<T> &theChain) {
    ChainNode<T> *p = firstNode, *p2 = theChain.begin();
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
ChainNode<T> *chainList<T>::begin() const {
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

    ChainNode<T> *temp = firstNode;
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
    ChainNode<T> *p = firstNode;
    for (int i = 0; i < offset; i++)
        p = p->next;
    ChainNode<T> *temp = new ChainNode<T>(p->element, nullptr);
    ChainNode<T> *j = temp;

    for (int i = 0; i < newSize - 1; i++) {
        j->next = new ChainNode<T>(p->next->element, nullptr);
        j = j->next;
        p = p->next;
    }
    firstNode = temp;
    listSize = newSize;


}

template<class T>
void chainList<T>::reverse() {
    ChainNode<T> *p = firstNode;
    ChainNode<T> *j = firstNode->next;
    ChainNode<T> *temp = nullptr;
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
    ChainNode<T> *p = chainA.begin();
    ChainNode<T> *j = chainB.begin();
    ChainNode<T> *t = nullptr;
    ChainNode<T> *c = nullptr;
    ChainNode<T> *temp = nullptr;
    ChainNode<T> *temp2 = nullptr;
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
    ChainNode<T> *deleteNode = firstNode;
    ChainNode<T> *p = firstNode;
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

template<class T>
void chainList<T>::swap(int indexA, int indexB) {
    checkIndex(indexA, "replace");
    checkIndex(indexB, "replace");
    T temp;
    temp = this->get(indexA);
    this->get(indexA) = this->get(indexB);
    this->get(indexB) = temp;
}

template<class T>
vector<chainList<T>> *chainList<T>::split() {
    auto *p = new vector<chainList<T>>;
    if (this->size() < 2)return nullptr;
    if (this->size() == 2) {
        chainList<T> c1(firstNode, 1);
        ChainNode<T> *secondNode = firstNode->next;
        firstNode->next = nullptr;
        chainList<T> c2(secondNode, 1);
        secondNode->next = nullptr;
        c1.set(0, this->get(0));
        c2.set(0, this->get(1));
        p->push_back(c1);
        p->push_back(c2);
        firstNode = nullptr;
        listSize = 0;
        return p;
    }
    //元素个数大于等于3的，要采用一套交换算法，将所有索引为偶数的（索引为0的元素不用动），也就是索引为2的元素开始往后所有索引为偶数的元素往前放，例如{7，6，8，9，2}变为{7，8，2，6，9}
    int i = 1;
    int x = 2;
    while (true) {
        if (x + 1 <= listSize)//满足这个条件的就执行swap()函数
        {
            this->swap(i, x);
        } else break;
        i++;
        x += 2;
    }

    chainList<T> c1(firstNode, i);//索引为i的节点之前的所有节点归属c1
    chainList<T> c2(this->indexToAddress(i), listSize - i);
    this->indexToAddress(i - 1)->next = nullptr;

    p->push_back(c1);
    p->push_back(c2);

    firstNode = nullptr;
    listSize = 0;
    return p;


}

template<class T>
void chainList<T>::test() {

    this->swap(1, 2);

}

template<class T>
void chainList<T>::insertSort() {
    for (int i = 1; i < this->size(); i++) {
        T t = this->get(i);
        int j;
        for (j = i - 1; j >= 0 && t < this->get(j); j--) {
            this->get(j + 1) = this->get(j);
        }
        this->get(j + 1) = t;
    }
}

template<class T>
bool chainList<T>::bubble(int n) {
    bool swapped = false;
    for (int i = 0; i < n; i++) {
        if (this->get(i) > this->get(i + 1)) {
            this->swapNode(i, i + 1);
            swapped = true;
        }
    }
    return swapped;
}

template<class T>
void chainList<T>::selectionSort() {
    bool sorted = false;
    for (int size = this->size(); !sorted && (size > 1); size--) {
        int indexOfMax = 0;
        sorted = true;
        for (int i = 1; i < size; i++) {
            if (this->get(indexOfMax) <= this->get(i))
                indexOfMax = i;
            else sorted = false;
        }
        this->swap(this->get(indexOfMax), this->get(size - 1));
    }
}

template<class T>
void chainList<T>::rankSort() {
    int *countArray = new int[this->size()];
    for (int i = 0; i < this->size(); i++)countArray[i] = 0;
    for (int i = 0; i < this->size(); i++) {
        countArray[this->get(i)]++;
    }
    int index = 0;
    for (int i = 0; i < this->size(); i++) {
        if (countArray[i] != 0) {
            for (int j = 0; j < countArray[i]; j++) {
                this->get(index) = i;
                index++;
            }
        }
    }
}

template<class T>
void chainList<T>::swapNode(int indexA, int indexB) {
    checkIndex(indexA, "replace");
    checkIndex(indexB, "replace");
    T temp;
    temp = this->get(indexA);
    this->get(indexA) = this->get(indexB);
    this->get(indexB) = temp;
}

template<class T>
void chainList<T>::bubbleSort() {
    for (int i = this->size(); i > 1 && this->bubble(i); i--);
}

template<class T>
void chainList<T>::clear() {
    this->physicalClear();
}

//全局函数，重载左移运算符使得cout<<对象名可输出链表元素
template<class T>
ostream &operator<<(ostream &out, const chainList<T> &theNode) {
    theNode.output(out);
    return out;
}

//将链表转换为数组线性表，要求使用chainList的get()方法和size()方法，类arrayList的insert方法
template<class T>
void chainToArray(const chainList<T> &theChain, arrayList<T> &theArray) {
    theArray.reserve(theChain.size());
    for (int i = 0; i < theChain.size(); i++) {
        theArray.push_back(theChain.get(i));
    }
}


//扩展chainList，以扩充抽象基类extendedLinearList中新增的功能
