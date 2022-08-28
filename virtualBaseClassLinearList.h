#pragma once

//定义链表节点类
template<class T>
class ChainNode {
public:
    T element;//链表节点的数据域
    ChainNode<T> *next;//链表节点的指针域

    //数据域未知，指针域明确的构造函数
    ChainNode() = default;

    ChainNode(ChainNode<T> *theNext) : element(*(new T)), next(theNext) {}

    //指定数据域和指针域的标准构造函数
    ChainNode(const T &theElement, ChainNode<T> *theNext = nullptr) : element(theElement), next(theNext) {}

};

//定义双向循环链表节点
template<class T>
class DoublyNode {
public://别名
    using pointer = DoublyNode<T> *;
    using node = DoublyNode<T>;
private://私有成员
    T element;
    pointer previous;
    pointer next;
public://构造与析构与拷贝构造函数
    DoublyNode(const pointer&thePrevious,const T&theElement,const pointer &theNext):previous(thePrevious),element(theElement),next(theNext){}
    DoublyNode()=default;
    DoublyNode(const node&theNode){
        const pointer thePrevious=theNode.getPrevious();
        const T theElement=theNode.getElement();
        const pointer theNext=theNode.getNext();
        this->set(thePrevious, theElement, theNext);
    }
public://公有接口
    void setPrevious(const pointer &thePrevious){ previous=thePrevious;}
    void setNext(const pointer &theNext){next=theNext;}
    void setElement(const T&theElement){element=theElement;}
    void set(const pointer &thePrevious, const T &theElement, const pointer &theNext)
    {
        next=theNext;
        element=theElement;
        previous=thePrevious;
    }
    //以值的方式返回成员
    pointer getNext()const{return next;}
    pointer getPrevious()const{return previous;}
    T getElement()const{return element;}

    //以引用的方式返回成员
    pointer &theNext(){return next;}
    pointer &thePrevious(){return previous;}
    T& theElement(){return element;}

};

//定义所有链表的抽象基类
template<class T>
class LinearList {
public:
    virtual ~LinearList() {}                                 //空的虚析构函数
    virtual bool empty() const = 0;                          //检测容器是否为空
    virtual int size() const = 0;                            //返回容器中元素的数量
    virtual int indexOf(const T &theElement) const = 0;      //传入对象的引用，返回该对象在容器中的索引值
    virtual T get(const int &index)const= 0;                     //返回索引值为index的对象
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
