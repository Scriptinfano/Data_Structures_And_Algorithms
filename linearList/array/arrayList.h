//
// Created by USER on 20/07/2022.
//
#pragma once

#include<iostream>
#include<sstream>
#include <iterator>//输出流迭代器
#include "myIterator.h"
#include "globalFunction.h"
#include"illegalParameterValue.h"

using namespace std;

template<class T>
class linerList {
public:
    virtual ~linerList() {}                                  //空的虚析构函数
    virtual bool empty() const = 0;                          //检测容器是否为空
    virtual int size() const = 0;                            //返回容器中元素的数量
    virtual T &get(int index) const = 0;                     //返回索引值为index的对象
    virtual int indexOf(const T &theElement) const = 0;      //传入对象的引用，返回该对象在容器中的索引值
    virtual void erase(int index) = 0;                       //删除索引为index的对象
    virtual void insert(int index, const T &theElement) = 0; //在索引index处的后一个位置插入元素
    virtual void output(std::ostream &out) const = 0;             //输出元素
};

//继承动态数组基类的派生类
template<class T>
class arrayList : public linerList<T> {
public:
    arrayList(int initialCapacity = 10, int extraSize = 0);

    arrayList(const arrayList<T> &); //拷贝构造
    ~arrayList() { delete[] element; }

    // ADT方法（实现基类的纯虚函数）
    bool empty() const { return listSize == 0; }    //检测是否为空
    int size() const { return listSize; }           //返回容器大小
    T &get(int theIndex) const;                     //得到索引值为theIndex的元素
    int indexOf(const T &theElement) const;         //返回元素的索引值
    void erase(int theIndex);                       //删除索引为theIndex的元素
    void insert(int theIndex, const T &theElement); //在指定位置插入元素
    void output(std::ostream &out) const;

    //其他方法
    int capacity() const { return arrayLength; }

    void trimToSize();

    void setSize(int newSize);

    T &operator[](int i) const;

    bool operator==(arrayList<T> &array);

    bool operator!=(arrayList<T> &array);

    T *begin() { return element; }//返回首元素地址

    T *end() { return element + listSize; }//返回最后一个元素后面的位置

protected:
    void checkIndex(int theIndex, std::string actionType) const;

    T *element;      //存储线性表元素的一维数组
    int arrayLength; //数组长度，相当于容器的容量
    int listSize;    //数组元素的个数
    int m_extraSize;
};
//
// Created by USER on 20/07/2022.
//



//构造函数实现
template<class T>
arrayList<T>::arrayList(int initialCapacity, int extraSize) {
    if (initialCapacity < 1) {
        ostringstream s;
        s << "初始容量=" << initialCapacity << "，此值必须>0" << endl;
        throw illegalParameterValue(s.str()); // ostringstream对象调用str()会返回一个临时的string对象
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
    if (extraSize > initialCapacity)
        m_extraSize = extraSize;
    else m_extraSize = 0;
}

//拷贝构造函数实现
template<class T>
arrayList<T>::arrayList(const arrayList<T> &theList) {
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    m_extraSize = theList.m_extraSize;
    copy(theList.element, theList.element + listSize, element); //第一和第二个参数是原数组的起始地址和最后一个元素的地址，即要复制的区间，最后一个参数是粘贴的地址
}

//确保索引在指定范围内
template<class T>
void arrayList<T>::checkIndex(int theIndex, string actionType) const {
    //确保索引在0到listsize-1之间
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex >= arrayLength || theIndex > listSize) {
            ostringstream s;
            s << "插入元素时，";
            if (theIndex < 0)s << "索引值不得<0" << endl;
            if (theIndex >= arrayLength)s << "索引值不得>=数组大小" << endl;
            if (theIndex > listSize)s << "索引值不得>数组元素个数" << endl;
            throw illegalParameterValue(s.str());
        }
    } else if (actionType == "erase" || actionType == "get") {
        if (theIndex >= listSize) {
            ostringstream s;
            if (actionType == "erase")
                s << "删除元素时，索引值不得>=listsize" << endl;
            else s << "获取元素时，索引值不得>=listsize" << endl;
            throw illegalParameterValue(s.str());
        }
    } else {
        ostringstream s;
        s << "checkIndex第二个参数传入不正确，未指定正确的操作类型" << endl;
        throw illegalParameterValue(s.str());
    }

}


//返回指定索引的元素
template<class T>
T &arrayList<T>::get(int theIndex) const {
    checkIndex(theIndex, "get");
    return element[theIndex];
}

//返回指定元素的索引，若元素不存在则返回-1
template<class T>
int arrayList<T>::indexOf(const T &theElement) const {
    /*
        T const *p = element;
        for (int i = 0; i < listSize; i++)
        {
            if(*p==theElement)
                return i;
            else p++;
        }
        return -1;//代表并没有着调相关元素
    */
    int theIndex = (int) (find(element, element + listSize, theElement) -
                          element); // find的第一和第二个参数是地址标记查找区间，第三个参数是查找的目标元素，函数返回所找元素的地址，减去起始地址后即该元素的索引，未找到返回容器最后一个元素之后的位置
    if (theIndex == listSize)
        return -1; //代表没有找到
    else
        return theIndex;
}

//删除指定元素，索引不得>=listsize
template<class T>
void arrayList<T>::erase(int theIndex) {
    checkIndex(theIndex, "erase");
    copy(element + theIndex + 1, element + listSize,
         element + theIndex); //标准算法函数copy()的第一第二个参数是要复制元素的起始位置和终止位置，第三个参数是目标容器的目标地址
    element[--listSize].~T(); //由于移动元素会导致数组末尾多出一个未存放运算的空间，所以必须主动调用相应类型的析构函数将其释放
}

//在指定位置插入指定的新元素
template<class T>
void arrayList<T>::insert(int theIndex, const T &theElement) {
    checkIndex(theIndex, "insert");        //先检查索引值是否合理
    if (listSize == arrayLength) //数组已经满了，数组长度需要倍增后再插入新的元素
    {
        if (m_extraSize == 0) {
            //调用构造函数时传入的extraSize比初始容量小或者未传入额外的参数则执行倍增操作，否则执行按用户指定的增加数组大小的操作
            changeLength1D(element, arrayLength, 2 * arrayLength);
            arrayLength *= 2;
        } else {
            changeLength1D(element, arrayLength, m_extraSize);
            arrayLength = m_extraSize;
        }
    }
    copy_backward(element + theIndex, element + listSize,
                  element + listSize + 1); //将指定区间内的元素向后挪，直到该区间末位置与第三个参数的地址相同为止
    element[theIndex] = theElement;
    listSize++;
}

//利用输出流迭代器输出数组中的所有元素，中间的分隔符是“ ”
template<class T>
void arrayList<T>::output(ostream &out) const {
    ostream_iterator<T> pout(out, " ");      //将输出流迭代器与传入函数的输出流对象关联，并设置分隔符
    copy(element, element + listSize, pout); // copy的第三个参数是输出迭代器，如果输出迭代器输出的是一个泛型，那就必须重载<<运算符
    /*详解输出迭代器 ostream_iterator<T>pout(cout, " ")
    通过输出迭代器可以将要输入的数据写入到指定的流中。
    cout是标准输出流对象，输出迭代器通过和输出流对象关联，达到将指定数据输入到指定流的目的
    输出流迭代器可看作一个指向输出流的指针。通过这个指针可以把东西写到输出流中。
    copy (v.begin(),v.end(),output);//通过流迭代器output将容器中指定区间内的元素放到cout输出流
    ostream_iterator<int> output(cout ,"*");//放到输出流的时候，每放一个整数，就末尾添加一个*
    */
}

template<class T>
void arrayList<T>::trimToSize() {
    if (arrayLength == listSize)
        return;

    if (listSize == 0) {// replace with array of length 1
        delete[] element;
        element = new T[1];
        arrayLength = 1;
        return;
    }

    changeLength1D(element, arrayLength, listSize);
    arrayLength = listSize;

}

template<class T>
void arrayList<T>::setSize(int newSize) {
    if (newSize == listSize) {
        trimToSize();
    }
    if (newSize < listSize) {
//两个都变
        changeLength1D(element, arrayLength, newSize);
        arrayLength = listSize = newSize;
    }
    if (newSize > listSize) {
        changeLength1D(element, arrayLength, newSize);
        arrayLength = newSize;
    }
}

template<class T>
T &arrayList<T>::operator[](int i) const {
    return this->get(i);
}

template<class T>
bool arrayList<T>::operator==(arrayList<T> &array) {
    if (this->size() != array.size())return false;
    int i = 0;

    for (mystd::iterator<T> it(this->begin()); it != this->end(); ++it) {
        if (*it != array[i])
            return false;
        i++;
    }
    return true;
}

template<class T>
bool arrayList<T>::operator!=(arrayList<T> &array) {
    if ((*this) == array)return false;
    else return true;
}

//当使用输出流迭代器将泛型数据放入到指定输出流时必须重载<<运算符
template<class T>
ostream &operator<<(ostream &out, const arrayList<T> &x) {
    x.output(out);
    return out;
}


