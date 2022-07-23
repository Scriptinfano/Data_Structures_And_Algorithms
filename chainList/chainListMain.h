#pragma once

#include"D:\ClionProjects\Data_Structures_And_Algorithms\virtualBaseClassLinearList.h"
#include<sstream>
#include<iostream>
#include<string>
#include <iterator>

using namespace std;

//定义异常类
class illegalParameterValue {
private:
    string message;

public:
    illegalParameterValue() : message("非法实参传入") {}

    illegalParameterValue(string theMessage) { message = theMessage; }

    void outPutMessage() const { cout << message << endl; }
};


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
protected:
    void checkIndex(int theIndex, string actionType) const;

    chainNode<T> *firstNode;//指向链表第一个节点的指针，当链表为空时，此值为nullptr
    int listSize;//链表节点个数

public:
    chainList(int initialCapacity = 10);

    chainList(const chainList<T> &theChainList);

    ~chainList();

    //ADT方法
    bool empty() const { return listSize == 0; }    //检测是否为空
    int size() const;                               //返回容器元素个数
    T &get(int theIndex) const;                     //得到索引值为theIndex的元素
    int indexOf(const T &theElement) const;         //返回元素theElement首次出现的索引值
    void erase(int theIndex);                       //删除索引为theIndex的元素
    void insert(int theIndex, const T &theElement); //在指定位置插入元素
    void output(ostream &out) const;
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
chainList<T>::chainList(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "初始容量=" << initialCapacity << "，此值必须大于0";
        throw illegalParameterValue(s.str());

    }
    firstNode = nullptr;
    listSize = 0;
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
ostream &operator<<(ostream &out, const chainList<T> &theNode) {
    theNode.output(out);
    return out;
}




//定义前向迭代器
template<class T>
class forward_iterator {
protected:
    chainNode<T> *node;
public:
    //向前迭代器必须的typedef定义语句
    typedef forward_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;

    //构造函数
    forward_iterator(chainNode<T>*theNode=nullptr)
    {
        node=theNode;
    }
    //解引用操作符
    T &operator*()const{return node->element;}
    T*operator->()const{return &(node->element);}

    //迭代器加法操作

};
