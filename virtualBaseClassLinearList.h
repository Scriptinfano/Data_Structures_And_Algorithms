#pragma once

//定义链表节点类
template<class T>
class ChainNode {
public:
    T element;//链表节点的数据域
    ChainNode<T> *next;//链表节点的指针域

    //数据域未知，指针域明确的构造函数
    ChainNode()=default;

    ChainNode(const ChainNode<T> *theNext) : element(new T),next(theNext) {}

    //指定数据域和指针域的标准构造函数
    ChainNode(const T &theElement,ChainNode<T> *theNext = nullptr) : element(theElement),next(theNext) {}

};

template<class T>
class LinearList {
public:
    virtual ~LinearList() {}                                 //空的虚析构函数
    virtual bool empty() const = 0;                          //检测容器是否为空
    virtual int size() const = 0;                            //返回容器中元素的数量
    virtual int indexOf(const T &theElement) const = 0;      //传入对象的引用，返回该对象在容器中的索引值
    virtual T &get(const int &index) const = 0;                     //返回索引值为index的对象
    virtual void erase(const int &index) = 0;                       //删除索引为index的对象
    virtual void insert(const int &index, const T &theElement) = 0; //在索引index处的后一个位置插入元素
    virtual void output(std::ostream &out) const = 0;        //输出元素
    virtual void clear() = 0;

};

//为开发extendedChain类定义抽象基类，此抽象基类私有派生自
template<class T>
class extendedLinearList : private LinearList<T> {
public:
    virtual ~extendedLinearList() {}

    virtual void push_back(const T &theElement) = 0;

};
