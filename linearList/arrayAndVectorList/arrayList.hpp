#pragma once

#include<iostream>
#include<sstream>
#include <iterator>
#include <vector>
#include "myIterator.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\globalFunctionSpace.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\BaseLinearList.h"
using namespace ExceptionSpace::ArrayListExceptionSpace;

void initializeTemplateFunction() {
    int *p = nullptr;
    int oldLength = 0;
    int newLength = 0;
    GlobalSpace::changeLength1D<int>(p, oldLength, newLength);
}

using namespace std;

template<class T>
class arrayList : public LinearList<T> {
protected:
    void checkIndex(const int &theIndex, const string &actionType) const;

    int arrayLength; //数组长度
    int listSize;    //数组元素个数

    T *element;//存储线性表元素的一维数组
    int m_extraSize;

public:
    arrayList(int initialCapacity = 10, int extraSize = 0) {
        if (initialCapacity < 1) {
            ostringstream s;
            s << "初始容量=" << initialCapacity << "此值必须>0" << endl;
            throw IllegalParameterException(s.str());
        }
        arrayLength = initialCapacity;
        element = new T[arrayLength];
        listSize = 0;
        if (extraSize > initialCapacity)
            m_extraSize = extraSize;
        else m_extraSize = 0;
    }


    arrayList(const arrayList<T> &theList) {
        arrayLength = theList.arrayLength;
        listSize = theList.listSize;
        element = new T[arrayLength];
        m_extraSize = theList.m_extraSize;
        copy(theList.element, theList.element + listSize, element);
    }


    ~arrayList() { delete[] element; }

    //ADT方法
    virtual bool empty() const { return listSize == 0; }

    virtual int size() const;

    virtual T get(const int &index) const;

    virtual int indexOf(const T &theElement) const;

    virtual void erase(const int &index);

    virtual void insert(const int &index, const T &theElement);

    virtual void output(std::ostream &out) const;

    //常规接口

    T& getSelf(const int &theIndex){
        checkIndex(theIndex, "get");
        return element[theIndex];
    }

    void trimToSize();//将数组多余的空间裁剪掉，使得数组大小等于元素数量

    void setCapacity(int newCapacity);//任意改变容器大小函数，小于数组元素个数时多余元素被删除

    void reserve(int newCapacity);//改变容器大小函数，将数组的容量改变为当前容量和指定容量中的较大值

    void push_back(const T theElement);//向容器中新加一个数据，若超出容量则倍增数组

    void pop_back();//删除容器的尾部元素

    void swap(arrayList<T> &array);//交换两个容器的元素

    int capacity() const { return arrayLength; }//返回容器容量

    void clear();//清空容器的所有元素

    void setSize(int newSize);//根据指定的值更新容器内部统计元素个数的函数

    void set(int theIndex, const T &theElement);//用指定元素替换指定索引值的元素

    void set(mystd::iterator<T> &iter, const T &theElement);//重载上面的set函数，利用传入的自定义迭代器实现元素替换

    int lastIndexOf(const T &theElement);//返回指定元素最后出现时的索引，若元素不存在则返回-1

    void reverse();//原地反转数组元素

    void leftShift(int offset);//将线性表的元素向左移动offset个位置

    void removeRange(int beginIndex, int endIndex);//移除索引范围内的元素

    void removeRange(const mystd::iterator<T> &iter_begin, const mystd::iterator<T> &iter_end);//重载上面的removeRange函数，利用自定义迭代器标记范围，删除范围之内的元素

    void circularShift(int offset);//循环移动线性表内的元素，按顺时针方向移动

    void half();//隔一个元素删除一个元素

    void meld(const arrayList<T> &arrayA, const arrayList<T> &arrayB);//调用该函数的容器交替地包含arrayOne和arrayTwo的元素，从arrayOne的第0个元素开始，若一个表的元素取完则将另一个表剩下的元素放到新表中

    void merge(arrayList<T> &listA, arrayList<T> &listB);//将两个无序的线性表合并成一个有序的线性表

    void split(arrayList<T> &listA, arrayList<T> &listB);//将调用函数的对象中索引为偶数的元素放入listA，将索引为奇数的元素放入listB

    T *address(const int &theIndex) const;//其他作为成员函数重载的运算符函数

    bool operator==(arrayList<T> &array);//判断是否相等

    T &operator[](int i) const;//得到索引为i的元素的引用

    bool operator!=(arrayList<T> &array);//判断元素是否不相等

    bool operator<(arrayList<T> &array);//从左往右分别遍历两个容器，若出现第一个容器的元素比第二个容器中同位置的元素小的情况则返回true否则返回false

    //返回首元素地址末元素后继地址的函数
    T *begin() const { return element; }//返回首元素地址

    T *end() const { return element + listSize; }//返回最后一个元素后面的位置

    //返回自定义迭代器的函数，两个函数分别返回指向首元素的迭代器和指向末元素后继位置的迭代器
    mystd::iterator<T> it_begin() const;

    mystd::iterator<T> it_end() const;


};


template<class T>
int arrayList<T>::indexOf(const T &theElement) const {
    int theIndex = (int) (find(element, element + listSize, theElement) - element);
    if (theIndex == listSize)
        return -1;
    else
        return theIndex;
}

template<class T>
void arrayList<T>::output(ostream &out) const {
    if(empty())throw ArrayListEmptyException();
    ostream_iterator<T> pout(out, " ");
    copy(element, element + listSize, pout);
}

template<class T>
void arrayList<T>::trimToSize() {
    if (arrayLength == listSize)
        return;

    if (listSize == 0) {
        delete[] element;
        element = new T[1];
        arrayLength = 1;
        return;
    }

    GlobalSpace::changeLength1D<T>(element, arrayLength, listSize);
    arrayLength = listSize;

}

template<class T>
void arrayList<T>::setCapacity(int newCapacity) {
    if (newCapacity == listSize) {
        trimToSize();
    }
    if (newCapacity < listSize) {
        GlobalSpace::changeLength1D<T>(element, arrayLength, newCapacity);
        arrayLength = listSize = newCapacity;
    }
    if (newCapacity > listSize) {
        GlobalSpace::changeLength1D<T>(element, arrayLength, newCapacity);
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
    for (; *it == *it2; ++it, ++it2) {
        if ((*it) == '\0' || (*it2) == '\0')return false;
        if ((*it) < (*it2))return true;
    }
}

template<class T>
void arrayList<T>::push_back(const T theElement) {
    if (listSize + 1 > arrayLength) {
        GlobalSpace::changeLength1D<T>(element, arrayLength, 2 * arrayLength);
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
    //交换第一个容器和第二个容器的元素值

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
    arrayList<T> temp(tempCapacity);
    //此时已经指定了temp的容量值，注意除非temp调用insert()和push_back()来插入元素，否则内部统计元素个数的成员变量listSize是不会改变的，必须手动改变内部成员变量listSize的值
    copy(this->begin(), this->end(), temp.begin());

    //更新temp内部的元素个数，不然无法对temp执行begin和end操作获得首元素和尾部元素的地址
    temp.setSize(selfSize);
    this->clear();//清除第一个容器的元素

    copy(array.begin(), array.end(), this->begin());//将第二个容器的元素拷贝到第一个容器中
    array.clear();//将第二个容器清空
    copy(temp.begin(), temp.end(), array.begin());//再将第一个容器中的元素拷贝到第二个容器中

    //手动更改两个容器统计元素个数的值，因为自动更新元素个数值只会在调用insert和push_back()时发生
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
    checkIndex(theIndex, "replace");
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
        delete[]element;
        element = temp;
        arrayLength = newLength;
        listSize = newLength;

    } else {
        throw IllegalParameterException("使用removeRange函数时索引传入有误");
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
void arrayList<T>::checkIndex(const int &theIndex, const string &actionType) const {
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex >= this->capacity() || theIndex > this->size()) {
            ostringstream s;
            s << "插入元素时，";
            if (theIndex < 0)s << "索引值不得<0" << endl;
            if (theIndex >= this->capacity())s << "索引值不得>=数组大小" << endl;
            if (theIndex > this->size())s << "索引值不得>数组元素个数" << endl;
            throw IllegalParameterException(s.str());
        }
    } else if (actionType == "erase" || actionType == "get" || actionType == "replace") {
        if (theIndex >= this->size()) {
            ostringstream s;
            if (actionType == "erase")
                s << "删除元素时，索引值不得>=listSize" << endl;
            else if (actionType == "replace")s << "替换元素时，索引值不得>=listSize" << endl;
            else if (actionType == "get")s << "获取元素时，索引值不得>=listSize" << endl;
            throw IllegalParameterException(s.str());
        }
    } else {
        ostringstream s;
        s << "checkIndex第二个参数传入不正确，未指定正确的操作类型" << endl;
        throw IllegalParameterException(s.str());
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
void arrayList<T>::meld(const arrayList<T> &arrayA, const arrayList<T> &arrayB) {
    int listSizeA = arrayA.size(), listSizeB = arrayB.size();
    T *temp = new T[listSizeA + listSizeB];
    int tempIndex = 0, indexA = 0, indexB = 0;
    while (!(indexA == listSizeA || indexB == listSizeB)) {
        temp[tempIndex] = arrayA[indexA];
        tempIndex++;
        indexA++;
        temp[tempIndex] = arrayB[indexB];
        tempIndex++;
        indexB++;
    }
    if (indexA == listSizeA && indexB == listSizeB) {
        //两个表的元素一样长，说明不需要将另一个表的元素放进新表
        return;

    } else if (indexA == listSizeA) {
        //将表2放入新表
        while (indexB < listSizeB) {
            temp[tempIndex] = arrayB[indexB];
            tempIndex++;
            indexB++;
        }
    } else {
        //indexB==listSizeTwo的情况，将表1放入新表
        while (indexA < listSizeA) {
            temp[tempIndex] = arrayA[indexA];
            tempIndex++;
            indexA++;

        }
    }
    listSize = listSizeA + listSizeB;
    arrayLength = listSizeA + listSizeB;
    delete[]element;
    element = temp;


}

template<class T>
void arrayList<T>::merge(arrayList<T> &listA, arrayList<T> &listB) {
    int listSizeOne = listA.size(), listSizeTwo = listB.size();
    int sumListSize = listSizeOne + listSizeTwo;
    T *temp = new T[listSizeOne + listSizeTwo];
    copy(listA.begin(), listA.end(), temp);
    copy(listB.begin(), listB.end(), temp + listSizeOne);
    sort(temp, temp + sumListSize);
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
    for (int i = 0; i < listSize; i++) {
        if (i % 2 == 0) {
            listA.push_back(element[i]);
        } else {
            listB.push_back(element[i]);
        }
    }

}

template<class T>
T arrayList<T>::get(const int &index) const {
    checkIndex(index, "get");
    return element[index];

}

template<class T>
void arrayList<T>::erase(const int &index) {
    checkIndex(index, "erase");
    copy(element + index + 1, element + listSize, element + index);
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

template<class T>
void arrayList<T>::insert(const int &index, const T &theElement) {
    checkIndex(index, "insert");
    if (listSize == arrayLength) //数组已经满了，数组长度需要倍增后再插入新的元素
    {
        if (m_extraSize == 0) {
            //调用构造函数时传入的extraSize比初始容量小或者未传入额外的参数则执行倍增操作，否则执行按用户指定的增加数组大小的操作
            GlobalSpace::changeLength1D<T>(element, arrayLength, 2 * arrayLength);
            arrayLength *= 2;
        } else {
            GlobalSpace::changeLength1D<T>(element, arrayLength, m_extraSize);
            arrayLength = m_extraSize;
        }
    }
    copy_backward(element + index, element + listSize, element + listSize + 1); //将指定区间内的元素向后挪，直到该区间末位置与第三个参数的地址相同为止
    element[index] = theElement;
    listSize++;

}

template<class T>
void arrayList<T>::set(mystd::iterator<T> &iter, const T &theElement) {
    if (iter < mystd::iterator<T>(begin()) || iter > mystd::iterator<T>(end()))
        throw IteratorOutOfBounds();
    *iter = theElement;
}

template<class T>
void arrayList<T>::removeRange(const mystd::iterator<T> &iter_begin, const mystd::iterator<T> &iter_end) {
    if (iter_begin >= mystd::iterator<T>(begin()) && iter_begin < iter_end && iter_end < mystd::iterator<T>(end())) {
        ptrdiff_t distance = iter_end - iter_begin;

        int newLength = listSize - (distance + 1);
        T *temp = new T[newLength];
        mystd::iterator<T> iter(begin());
        mystd::iterator<T> iter2(end());
        int i = 0;
        while (iter != iter_begin) {
            temp[i++] = *iter;
            iter++;
        }
        iter += (distance + 1);
        while (iter != iter2) {
            temp[i++] = *iter;
            iter++;
        }
        delete[]element;
        element = temp;
        arrayLength = newLength;
        listSize = newLength;
    } else throw IteratorOutOfBounds();
}

template<class T>
T *arrayList<T>::address(const int &theIndex) const {
    checkIndex(theIndex, "get");
    return &element[theIndex];
}

template<class T>
ostream &operator<<(ostream &out, const arrayList<T> &x) {
    x.output(out);
    return out;
}

//以vector<>容器作为底层存储结构的模板链表类
template<class T>
class vectorList : public LinearList<T> {
protected:
    void checkIndex(int theIndex, string actionType) const
    {
        if (actionType == "insert") {
            if (theIndex < 0 || theIndex >= this->capacity() || theIndex > this->size()) {
                ostringstream s;
                s << "插入元素时";
                if (theIndex < 0)s << "索引值不得<0" << endl;
                if (theIndex >= this->capacity())s << "索引值不得>=数组大小" << endl;
                if (theIndex > this->size())s << "索引值不得>数组元素个数" << endl;
                throw IllegalParameterException(s.str());
            }
        } else if (actionType == "erase" || actionType == "get" || actionType == "replace") {
            if (theIndex >= this->size()) {
                ostringstream s;
                if (actionType == "erase")
                    s << "删除元素时，索引值不得>=数组元素个数" << endl;
                else if (actionType == "replace")s << "替换数组元素时，索引值不得>=数组元素个数" << endl;
                else if (actionType == "get")s << "获取元素时，索引值不得>=数组元素个数" << endl;
                throw IllegalParameterException(s.str());
            }
        } else {
            ostringstream s;
            s << "调用checkIndex()时，第二个参数传入不正确，未指定正确的操作类型" << endl;
            throw IllegalParameterException(s.str());
        }
    }

    vector<T> *element;
public:
    //构造函数，拷贝构造函数，析构函数接口

    //构造函数
    vectorList(int initialCapacity = 10) {
        if (initialCapacity < 1) {
            ostringstream s;
            s << "初始容量=" << initialCapacity << "，此值必须>0";
            throw IllegalParameterException(s.str());
        }
        element = new vector<T>;
        element->reserve(initialCapacity);//调用reserve()为容器分配容量

    }

    vectorList(const vectorList<T> &theVectorList) {
        element = new vector<T>(*(theVectorList.element));//调用vector容器的拷贝构造函数完成拷贝
    }

    //析构函数
    ~vectorList() { delete element; }

    //ADT接口
    virtual bool empty() const {
        return element->empty();
    }

    //返回容器元素的个数
    virtual int size() const {
        return element->size();
    }

    //传入对象的引用，返回该对象在容器中的索引值
    virtual int indexOf(const T &theElement) const {
        for (int i = 0; i < element->size(); i++) {
            if (theElement == element[i])
                return i;
        }
        return -1;
    }

    //返回索引值为index的对象
    virtual T get(const int &index) const {
        //若索引不合要求，则内部的vector容器会在执行at函数时抛出异常
        return element->at(index);
    }

    //删除索引为index的对象
    virtual void erase(const int &index)
    {
        checkIndex(index, "erase");
        element->erase(begin() + index);//erase可接受一个指向要删除元素的迭代器，begin()向后走index步正好指向要删除的元素
    }

    //在索引index处的后一个位置插入元素
    virtual void insert(const int &index, const T &theElement) {
        checkIndex(index, std::string());
        element->insert(begin() + index, theElement);
    }

    //输出元素
    virtual void output(std::ostream &out) const {
        for (typename vector<T>::iterator it = this->element->begin(); it != this->element->end(); it++) {
            out << *it < " ";
        }
    }

    //清空容器元素
    virtual void clear() {
        element->clear();
    }

    //常规接口
    int capacity() const { return (int) element->capacity(); }

    //返回线性表的起始和结束位置的迭代器的接口，下面先定义一个类型别名，方便使用，返回迭代器类型的时候不用写一长串
    //在为模板类型定义别名时要再typedef之后加上typename，typedef创建了存在类型的别名，typename告诉编译器std::vector<T>::iterator是一个类型而不是一个成员，此语句使得iterator成为vector<T>::iterator的别名
    typedef typename vector<T>::iterator iterator;

    //返回起始迭代器
    iterator begin() { return element->begin(); }

    //返回终止迭代器
    iterator end() { return element->end(); }
};
