//定义所有线性表（包括链表）的抽象基类
#pragma once

template<class T>
class LinearList {
public:
    virtual ~LinearList() {}                                 //空的虚析构函数
    virtual bool empty() const = 0;                          //检测容器是否为空
    virtual int size() const = 0;                            //返回容器中元素的数量
    virtual int indexOf(const T &theElement) const = 0;      //传入对象的引用，返回该对象在容器中的索引值
    virtual T get(const int &index) const = 0;                     //返回索引值为index的对象
    virtual void erase(const int &index) = 0;                       //删除索引为index的对象
    virtual void insert(const int &index, const T &theElement) = 0; //在索引index处的后一个位置插入元素
    virtual void output(std::ostream &out) const = 0;        //输出元素
    virtual void clear() = 0;

};

//临时链表抽象基类，仅作测试使用
class TempLinearList {
public:
    virtual ~TempLinearList() = default;                                 //空的虚析构函数
    [[nodiscard]] virtual bool empty() const = 0;                          //检测容器是否为空
    [[nodiscard]] virtual int indexOf(const int &theElement) const = 0;      //传入对象的引用，返回该对象在容器中的索引值
    [[nodiscard]] virtual int getElement(const int &index) const = 0;                     //返回索引值为index的对象
    virtual void erase(const int &index) = 0;                       //删除索引为index的对象
    virtual void insert(const int &index, const int &theElement) = 0; //在索引index处的后一个位置插入元素
    virtual void output() const = 0;        //输出元素
    virtual void clear() = 0;

};

//为开发extendedChain类定义抽象基类，此抽象基类私有派生自
template<class T>
class extendedLinearList : private LinearList<T> {
public:
    virtual ~extendedLinearList() {}

    virtual void push_back(const T &theElement) = 0;

};
