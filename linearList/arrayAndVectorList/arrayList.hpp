//
// Created by USER on 20/07/2022.
//
#pragma once

#include<iostream>
#include<sstream>
#include <iterator>//输出流迭代器
#include <vector>
#include "myIterator.h"
#include "globalFunction.h"
#include"illegalParameterValue.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\virtualBaseClassLinearList.h"

using namespace std;

//继承动态数组基类的派生类
template<class T>
class arrayList : public linearList<T> {
protected:
    void checkIndex(int theIndex, std::string actionType) const;


    int arrayLength; //数组长度，相当于容器的容量
    int listSize;    //数组元素的个数

    T *element;      //存储线性表元素的一维数组
    int m_extraSize;

public:
    //构造函数、拷贝构造函数、析构函数
    arrayList(int initialCapacity = 10, int extraSize = 0);//构造函数
    arrayList(const arrayList<T> &); //拷贝构造
    ~arrayList() { delete[] element; }//析构函数

    // ADT方法（实现基类的纯虚函数）
    bool empty() const { return listSize == 0; }    //检测是否为空
    int size() const;                               //返回容器元素个数
    T &get(int theIndex) const;                     //得到索引值为theIndex的元素
    int indexOf(const T &theElement) const;         //返回元素的索引值
    void erase(int theIndex);                       //删除索引为theIndex的元素
    void insert(int theIndex, const T &theElement); //在指定位置插入元素
    void output(std::ostream &out) const;           //输出流迭代器输出所有元素

    //其他常规成员函数

    void trimToSize();//将数组多余的空间裁剪掉，使得数组大小等于元素数量

    void setCapacity(int newCapacity);//任意改变容器大小函数，小于数组元素个数时多余元素被删除

    void reserve(int newCapacity);//非任意改变容器大小函数，将数组的容量改变为当前容量和指定容量中的较大值

    void push_back(const T theElement);//向容器中新加一个数据，若超出容量则倍增数组

    void pop_back();//删除容器的尾部元素

    void swap(arrayList<T> &array);//交换两个容器的元素

    int capacity() const { return arrayLength; }//返回容器容量

    void clear();//清空容器的所有元素

    void setSize(int newSize);//根据指定的值更新容器内部统计元素个数的函数

    void set(int theIndex, const T &theElement);//用指定元素替换指定索引值的元素

    int lastIndexOf(const T &theElement);//返回指定元素最后出现时的索引，若元素不存在则返回-1

    void reverse();//原地反转数组元素

    void leftShift(int offset);//将线性表的元素向左移动offset个位置

    void removeRange(int beginIndex, int endIndex);//移除索引范围内的元素

    void circularShift(int offset);//循环移动线性表内的元素，按顺时针方向移动

    void half();//隔一个元素删除一个元素

    void meld(const arrayList<T> &arrayOne,
              const arrayList<T> &arrayTwo);//调用该函数的容器交替地包含arrayOne和arrayTwo的元素，从arrayOne的第0个元素开始，若一个表的元素取完则将另一个表剩下的元素放到新表中

    void merge(arrayList<T> &listA, arrayList<T> &listB);//将两个无序的线性表合并成一个有序的线性表

    void split(arrayList<T> &listA, arrayList<T> &listB);//将调用函数的对象中索引为偶数的元素放入listA，将索引为奇数的元素放入listB

    //其他作为成员函数重载的运算符函数
    bool operator==(arrayList<T> &array);

    T &operator[](int i) const;

    bool operator!=(arrayList<T> &array);

    bool operator<(arrayList<T> &array);

    //返回首元素地址末元素后继地址的函数
    T *begin() const { return element; }//返回首元素地址

    T *end() const { return element + listSize; }//返回最后一个元素后面的位置

    //返回自定义迭代器的函数，两个函数分别返回指向首元素的迭代器和指向末元素后继位置的迭代器
    mystd::iterator<T> it_begin() const;

    mystd::iterator<T> it_end() const;


};

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
    if (listSize - 1 < (arrayLength / 4)) {
        //若线性表元素个数降至线性表容量的1/4以下时，创建新数组，长度为arrayLength/2，然后将老表的元素复制过去
        T *temp = new T[arrayLength / 2];
        copy(this->begin(), this->end(), temp);
        delete[]element;
        element = temp;
        listSize--;
        arrayLength = arrayLength / 2;
        return;
    }
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

    if (listSize == 0) {// replace with arrayList of length 1
        delete[] element;
        element = new T[1];
        arrayLength = 1;
        return;
    }

    changeLength1D(element, arrayLength, listSize);
    arrayLength = listSize;

}

template<class T>
void arrayList<T>::setCapacity(int newCapacity) {
    if (newCapacity == listSize) {
        trimToSize();
    }
    if (newCapacity < listSize) {
//两个都变
        changeLength1D(element, arrayLength, newCapacity);
        arrayLength = listSize = newCapacity;
    }
    if (newCapacity > listSize) {
        changeLength1D(element, arrayLength, newCapacity);
        arrayLength = newCapacity;
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

template<class T>
bool arrayList<T>::operator<(arrayList<T> &array) {
    mystd::iterator<T> it = this->begin();
    mystd::iterator<T> it2 = array.begin();
    for (; *it == *it2; ++it, ++it2)
        if (*it == '\0')return false;
    return ((*it) < (*it2)) ? true : false;
}

template<class T>
void arrayList<T>::push_back(const T theElement) {
    if (listSize + 1 > arrayLength) {
        //执行倍增操作之后将元素添加到最后一个元素的后面
        changeLength1D(element, arrayLength, 2 * arrayLength);
        element[listSize] = theElement;
        listSize++;
        arrayLength = 2 * arrayLength;
        return;
    }
    element[listSize] = theElement;
    listSize++;

}

template<class T>
void arrayList<T>::pop_back() {
    element[--listSize].~T();

}

template<class T>
void arrayList<T>::swap(arrayList<T> &array) {
    int selfSize = this->listSize;
    int arraySize = array.size();

    if (this->listSize > array.capacity()) {
        //倍增array后再交换元素
        array.setCapacity(2 * array.capacity());
    }
    if (array.size() > this->arrayLength) {
        //倍增自己后再交换元素
        this->setCapacity(2 * arrayLength);
    }
    //如果上面两个if语句不满足，说明互相交换元素时，对方的容器都容得下自己的元素个数，不需要倍增某个容器大小
    int tempCapacity = max(this->arrayLength, array.capacity());
    arrayList<T> temp(
            tempCapacity);//此时已经指定了temp的容量值，注意除非temp调用insert()和push_back()来插入元素，否则内部统计元素个数的成员变量listSize是不会改变的，必须手动改变内部成员变量listSize的值
    copy(this->begin(), this->end(), temp.begin());

    //更新temp内部的元素个数，不然无法对temp执行begin和end操作获得首元素和尾部元素的地址

    temp.setSize(selfSize);
    this->clear();

    copy(array.begin(), array.end(), this->begin());
    array.clear();
    copy(temp.begin(), temp.end(), array.begin());

    //交换元素之后更新两个容器中统计元素个数的成员变量的值
    this->listSize = arraySize;
    array.setSize(selfSize);
}

template<class T>
void arrayList<T>::clear() {
    delete[]element;
    element = new T[arrayLength];
    listSize = 0;
}

template<class T>
void arrayList<T>::reserve(int newCapacity) {
    int finalCapacity = max(arrayLength, newCapacity);
    this->setCapacity(finalCapacity);
}

template<class T>
int arrayList<T>::size() const {
    return listSize;
}

template<class T>
void arrayList<T>::setSize(int newSize) {
    listSize = newSize;
}

template<class T>
void arrayList<T>::set(int theIndex, const T &theElement) {
    checkIndex(theIndex, "replace");//检查索引是否符合某操作的要求，若不符合抛出异常终止程序
    element[theIndex] = theElement;

}

template<class T>
void arrayList<T>::removeRange(int beginIndex, int endIndex) {
    //先检查两个索引是否合法
    if (beginIndex >= 0 && beginIndex < endIndex && endIndex <= listSize - 1) {
        //只有满足这个条件，两个索引所圈定的范围之内才有元素，注意两个索引不相等，也就是说该函数要至少删除两个元素
        int newLength = listSize - (endIndex - beginIndex + 1);
        T *temp = new T[newLength];
        int i = 0;
        for (; i < beginIndex; i++) {
            temp[i] = element[i];
        }
        for (int x = endIndex + 1; x < listSize; x++) {
            temp[i] = element[x];
        }
        element = temp;
        arrayLength = newLength;
        listSize = newLength;

    } else {
        throw illegalParameterValue("使用removeRange函数时索引传入有误");
    }
}

template<class T>
int arrayList<T>::lastIndexOf(const T &theElement) {
    for (int i = listSize - 1; i >= 0; i--) {
        if (theElement == element[i])return i;
    }
    return -1;
}

template<class T>
void arrayList<T>::reverse() {
    T temp;
    for (int i = 0, x = listSize - 1; x >= i; i++, x--) {
        temp = element[i];
        element[i] = element[x];
        element[x] = temp;
    }

}

template<class T>
void arrayList<T>::checkIndex(int theIndex, std::string actionType) const {
//确保索引在0到listsize-1之间
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex >= this->capacity() || theIndex > this->size()) {
            ostringstream s;
            s << "插入元素时，";
            if (theIndex < 0)s << "索引值不得<0" << endl;
            if (theIndex >= this->capacity())s << "索引值不得>=数组大小" << endl;
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

template<class T>
void arrayList<T>::leftShift(int offset) {
    T *target = new T[listSize];
    copy(element + offset, element + listSize, target);
    listSize -= offset;
    delete[]element;
    element = target;
}

template<class T>
void arrayList<T>::circularShift(int offset) {
    int netOffset = 0;//净偏移量，若offset>listSize，则netOffset=offSet%listSize
    if (offset > listSize)netOffset = offset % listSize; else netOffset = offset;
    T *temp = new T[listSize];
    copy(element + netOffset, element + listSize, temp);
    copy(element, element + netOffset, temp + (listSize - netOffset));
    delete[]element;
    element = temp;
}

template<class T>
void arrayList<T>::half() {
    int i = 0, x = 0;
    if (i >= listSize - 1)return;
    int newSize = (listSize / 2) + (listSize % 2);
    T *temp = new T[newSize];
    while (i <= listSize - 1) {

        temp[x] = element[i];
        i += 2;
        x++;
    }
    listSize = arrayLength = newSize;

    delete[]element;
    element = temp;
}

template<class T>
void arrayList<T>::meld(const arrayList<T> &arrayOne, const arrayList<T> &arrayTwo) {
    int listSizeOne = arrayOne.size(), listSizeTwo = arrayTwo.size();
    T *temp = new T[listSizeOne + listSizeTwo];
    int tempIndex = 0, oneIndex = 0, twoIndex = 0;
    while (!(oneIndex == listSizeOne || twoIndex == listSizeTwo)) {
        temp[tempIndex] = arrayOne[oneIndex];
        tempIndex++;
        oneIndex++;
        temp[tempIndex] = arrayTwo[twoIndex];
        tempIndex++;
        twoIndex++;
    }
    if (oneIndex == listSizeOne && twoIndex == listSizeTwo) {
        //两个表的元素一样长，说明不需要将另一个表的元素放进新表
        return;

    } else if (oneIndex == listSizeOne) {
        //将表2放入新表
        while (twoIndex < listSizeTwo) {
            temp[tempIndex] = arrayTwo[twoIndex];
            tempIndex++;
            twoIndex++;
        }
    } else {
        //twoIndex==listSizeTwo的情况，将表1放入新表
        while (oneIndex < listSizeOne) {
            temp[tempIndex] = arrayOne[oneIndex];
            tempIndex++;
            oneIndex++;

        }
    }
    listSize = listSizeOne + listSizeTwo;
    arrayLength = listSizeOne + listSizeTwo;
    delete[]element;
    element = temp;


}

template<class T>
void arrayList<T>::merge(arrayList<T> &listA, arrayList<T> &listB) {
    int listSizeOne = listA.size(), listSizeTwo = listB.size();
    int sumListSize=listSizeOne+listSizeTwo;
    T *temp = new T[listSizeOne + listSizeTwo];
    copy(listA.begin(), listA.end(), temp);
    copy(listB.begin(), listB.end(), temp + listSizeOne);
    sort(temp, temp+sumListSize);
    delete[]element;
    element = temp;
    listSize = arrayLength = listSizeOne + listSizeTwo;
}

template<class T>
mystd::iterator<T> arrayList<T>::it_begin() const {
    return mystd::iterator<T>(begin());
}

template<class T>
mystd::iterator<T> arrayList<T>::it_end() const {
    return mystd::iterator<T>(end());
}

template<class T>
void arrayList<T>::split(arrayList<T> &listA, arrayList<T> &listB) {
    for(int i=0;i<listSize;i++)
    {
        if(i%2==0)
        {
            //此时的索引是偶数
            listA.push_back(element[i]);
        }else
        {
            //此时的索引是奇数
            listB.push_back(element[i]);
        }
    }

}


//当使用输出流迭代器将泛型数据放入到指定输出流时必须重载<<运算符
template<class T>
ostream &operator<<(ostream &out, const arrayList<T> &x) {
    x.output(out);
    return out;
}

//以vector<>容器作为底层存储结构的模板链表类

template<class T>
class vectorList : public linearList<T> {
protected:
    void checkIndex(int theIndex, string actionType) const;

    vector<T> *element;
public:
    //构造函数，拷贝构造函数，析构函数
    vectorList(int initialCapacity = 10);

    vectorList(const vectorList<T> &theVectorList);

    ~vectorList() { delete element; }

    //ADT方法
    bool empty() const { return element->empty(); }

    int size() const { return (int) element->size(); }

    T &get(int theIndex) const;

    int indexOf(const T &theElement) const;

    void erase(int theIndex);

    void insert(int theIndex, const T &theElement);

    void output(ostream &out) const;

    //增加的方法
    int capacity() const { return (int) element->capacity(); }

    //线性表的起始和结束位置的迭代器
    //下面先定义一个类型别名，方便使用，返回迭代器类型的时候不用写一长串
    typedef typename vector<T>::iterator iterator;//在为模板类型定义别名时要再typedef之后加上typename，typedef创建了存在类型的别名，typename告诉编译器std::vector<T>::iterator是一个类型而不是一个成员，此语句使得iterator成为vector<T>::iterator的别名

    iterator begin() { return element->begin(); }

    iterator end() { return element->end(); }
};

template<class T>
vectorList<T>::vectorList(int initialCapacity) {
    if (initialCapacity < 1) {
        ostringstream s;
        s << "初始容量=" << initialCapacity << "，此值必须>0";
        throw illegalParameterValue(s.str());
    }
    element = new vector<T>;//创建vector容器
    element->reserve(initialCapacity);//增加容量

}

template<class T>
vectorList<T>::vectorList(const vectorList<T> &theVectorList) {
    element = new vector<T>(*theVectorList.element);//在堆区创建一个vector容器，并用括号中的对象来初始化它，括号中的对象即传入函数的vectorList对象内部的vector容器
}

template<class T>
T &vectorList<T>::get(int theIndex) const {
    return element->at(theIndex);//若索引不合要求，则内部的vector容器会在执行at函数时抛出异常
}

template<class T>
int vectorList<T>::indexOf(const T &theElement) const {
    for (int i = 0; i < element->size(); i++) {
        if (theElement == element[i])
            return i;
    }
    return -1;
}

template<class T>
void vectorList<T>::erase(int theIndex) {
//vector内置的erase函数不能详细的抛出异常，当传入错误的索引时，即迭代器指向了一个不存在的元素时，程序会异常退出，所以在传入索引前要检查其合法性
    checkIndex(theIndex, std::string());
    element->erase(begin() + theIndex);//STL容器vector的函数erase()的参数是迭代器，意思是删除迭代器指向的数据，注意不是传递索引
}

template<class T>
void vectorList<T>::insert(int theIndex, const T &theElement) {
    checkIndex(theIndex, std::string());
    element->insert(begin() + theIndex, theElement);
}

template<class T>
void vectorList<T>::output(ostream &out) const {
for(typename vector<T>::iterator it=this->element->begin();it!=this->element->end();it++)
{
    out<<*it<" ";
}
}

template<class T>
void vectorList<T>::checkIndex(int theIndex, string actionType) const {
//确保索引在0到listsize-1之间
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex >= this->capacity() || theIndex > this->size()) {
            ostringstream s;
            s << "插入元素时，";
            if (theIndex < 0)s << "索引值不得<0" << endl;
            if (theIndex >= this->capacity())s << "索引值不得>=数组大小" << endl;
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

