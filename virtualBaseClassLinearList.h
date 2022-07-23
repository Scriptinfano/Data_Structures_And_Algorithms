#pragma once

template<class T>
class linearList {
public:
    virtual ~linearList() {}                                  //空的虚析构函数
    virtual bool empty() const = 0;                          //检测容器是否为空
    virtual int size() const = 0;                            //返回容器中元素的数量
    virtual T &get(int index) const = 0;                     //返回索引值为index的对象
    virtual int indexOf(const T &theElement) const = 0;      //传入对象的引用，返回该对象在容器中的索引值
    virtual void erase(int index) = 0;                       //删除索引为index的对象
    virtual void insert(int index, const T &theElement) = 0; //在索引index处的后一个位置插入元素
    virtual void output(std::ostream &out) const = 0;        //输出元素
};

//为开发extendedChain类定义抽象基类，此抽象基类私有派生自
template<class T>
class extendedLinearList : private linearList<T> {
public:
    virtual ~extendedLinearList() {}

    virtual void clear() = 0;

    virtual void push_back(const T &theElement) = 0;

};
