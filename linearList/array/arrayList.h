//
// Created by USER on 20/07/2022.
//
#pragma once

#include<iostream>
#include<sstream>
#include <iterator>//�����������
#include "myIterator.h"
#include "globalFunction.h"
#include"illegalParameterValue.h"

using namespace std;

template<class T>
class linerList {
public:
    virtual ~linerList() {}                                  //�յ�����������
    virtual bool empty() const = 0;                          //��������Ƿ�Ϊ��
    virtual int size() const = 0;                            //����������Ԫ�ص�����
    virtual T &get(int index) const = 0;                     //��������ֵΪindex�Ķ���
    virtual int indexOf(const T &theElement) const = 0;      //�����������ã����ظö����������е�����ֵ
    virtual void erase(int index) = 0;                       //ɾ������Ϊindex�Ķ���
    virtual void insert(int index, const T &theElement) = 0; //������index���ĺ�һ��λ�ò���Ԫ��
    virtual void output(std::ostream &out) const = 0;             //���Ԫ��
};

//�̳ж�̬��������������
template<class T>
class arrayList : public linerList<T> {
public:
    arrayList(int initialCapacity = 10, int extraSize = 0);

    arrayList(const arrayList<T> &); //��������
    ~arrayList() { delete[] element; }

    // ADT������ʵ�ֻ���Ĵ��麯����
    bool empty() const { return listSize == 0; }    //����Ƿ�Ϊ��
    int size() const { return listSize; }           //����������С
    T &get(int theIndex) const;                     //�õ�����ֵΪtheIndex��Ԫ��
    int indexOf(const T &theElement) const;         //����Ԫ�ص�����ֵ
    void erase(int theIndex);                       //ɾ������ΪtheIndex��Ԫ��
    void insert(int theIndex, const T &theElement); //��ָ��λ�ò���Ԫ��
    void output(std::ostream &out) const;

    //��������
    int capacity() const { return arrayLength; }

    void trimToSize();

    void setSize(int newSize);

    T &operator[](int i) const;

    bool operator==(arrayList<T> &array);

    bool operator!=(arrayList<T> &array);

    T *begin() { return element; }//������Ԫ�ص�ַ

    T *end() { return element + listSize; }//�������һ��Ԫ�غ����λ��

protected:
    void checkIndex(int theIndex, std::string actionType) const;

    T *element;      //�洢���Ա�Ԫ�ص�һά����
    int arrayLength; //���鳤�ȣ��൱������������
    int listSize;    //����Ԫ�صĸ���
    int m_extraSize;
};
//
// Created by USER on 20/07/2022.
//



//���캯��ʵ��
template<class T>
arrayList<T>::arrayList(int initialCapacity, int extraSize) {
    if (initialCapacity < 1) {
        ostringstream s;
        s << "��ʼ����=" << initialCapacity << "����ֵ����>0" << endl;
        throw illegalParameterValue(s.str()); // ostringstream�������str()�᷵��һ����ʱ��string����
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
    if (extraSize > initialCapacity)
        m_extraSize = extraSize;
    else m_extraSize = 0;
}

//�������캯��ʵ��
template<class T>
arrayList<T>::arrayList(const arrayList<T> &theList) {
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    m_extraSize = theList.m_extraSize;
    copy(theList.element, theList.element + listSize, element); //��һ�͵ڶ���������ԭ�������ʼ��ַ�����һ��Ԫ�صĵ�ַ����Ҫ���Ƶ����䣬���һ��������ճ���ĵ�ַ
}

//ȷ��������ָ����Χ��
template<class T>
void arrayList<T>::checkIndex(int theIndex, string actionType) const {
    //ȷ��������0��listsize-1֮��
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex >= arrayLength || theIndex > listSize) {
            ostringstream s;
            s << "����Ԫ��ʱ��";
            if (theIndex < 0)s << "����ֵ����<0" << endl;
            if (theIndex >= arrayLength)s << "����ֵ����>=�����С" << endl;
            if (theIndex > listSize)s << "����ֵ����>����Ԫ�ظ���" << endl;
            throw illegalParameterValue(s.str());
        }
    } else if (actionType == "erase" || actionType == "get") {
        if (theIndex >= listSize) {
            ostringstream s;
            if (actionType == "erase")
                s << "ɾ��Ԫ��ʱ������ֵ����>=listsize" << endl;
            else s << "��ȡԪ��ʱ������ֵ����>=listsize" << endl;
            throw illegalParameterValue(s.str());
        }
    } else {
        ostringstream s;
        s << "checkIndex�ڶ����������벻��ȷ��δָ����ȷ�Ĳ�������" << endl;
        throw illegalParameterValue(s.str());
    }

}


//����ָ��������Ԫ��
template<class T>
T &arrayList<T>::get(int theIndex) const {
    checkIndex(theIndex, "get");
    return element[theIndex];
}

//����ָ��Ԫ�ص���������Ԫ�ز������򷵻�-1
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
        return -1;//����û���ŵ����Ԫ��
    */
    int theIndex = (int) (find(element, element + listSize, theElement) -
                          element); // find�ĵ�һ�͵ڶ��������ǵ�ַ��ǲ������䣬�����������ǲ��ҵ�Ŀ��Ԫ�أ�������������Ԫ�صĵ�ַ����ȥ��ʼ��ַ�󼴸�Ԫ�ص�������δ�ҵ������������һ��Ԫ��֮���λ��
    if (theIndex == listSize)
        return -1; //����û���ҵ�
    else
        return theIndex;
}

//ɾ��ָ��Ԫ�أ���������>=listsize
template<class T>
void arrayList<T>::erase(int theIndex) {
    checkIndex(theIndex, "erase");
    copy(element + theIndex + 1, element + listSize,
         element + theIndex); //��׼�㷨����copy()�ĵ�һ�ڶ���������Ҫ����Ԫ�ص���ʼλ�ú���ֹλ�ã�������������Ŀ��������Ŀ���ַ
    element[--listSize].~T(); //�����ƶ�Ԫ�ػᵼ������ĩβ���һ��δ�������Ŀռ䣬���Ա�������������Ӧ���͵��������������ͷ�
}

//��ָ��λ�ò���ָ������Ԫ��
template<class T>
void arrayList<T>::insert(int theIndex, const T &theElement) {
    checkIndex(theIndex, "insert");        //�ȼ������ֵ�Ƿ����
    if (listSize == arrayLength) //�����Ѿ����ˣ����鳤����Ҫ�������ٲ����µ�Ԫ��
    {
        if (m_extraSize == 0) {
            //���ù��캯��ʱ�����extraSize�ȳ�ʼ����С����δ�������Ĳ�����ִ�б�������������ִ�а��û�ָ�������������С�Ĳ���
            changeLength1D(element, arrayLength, 2 * arrayLength);
            arrayLength *= 2;
        } else {
            changeLength1D(element, arrayLength, m_extraSize);
            arrayLength = m_extraSize;
        }
    }
    copy_backward(element + theIndex, element + listSize,
                  element + listSize + 1); //��ָ�������ڵ�Ԫ�����Ų��ֱ��������ĩλ��������������ĵ�ַ��ͬΪֹ
    element[theIndex] = theElement;
    listSize++;
}

//�����������������������е�����Ԫ�أ��м�ķָ����ǡ� ��
template<class T>
void arrayList<T>::output(ostream &out) const {
    ostream_iterator<T> pout(out, " ");      //��������������봫�뺯�����������������������÷ָ���
    copy(element, element + listSize, pout); // copy�ĵ�����������������������������������������һ�����ͣ��Ǿͱ�������<<�����
    /*������������ ostream_iterator<T>pout(cout, " ")
    ͨ��������������Խ�Ҫ���������д�뵽ָ�������С�
    cout�Ǳ�׼������������������ͨ�������������������ﵽ��ָ���������뵽ָ������Ŀ��
    ������������ɿ���һ��ָ���������ָ�롣ͨ�����ָ����԰Ѷ���д��������С�
    copy (v.begin(),v.end(),output);//ͨ����������output��������ָ�������ڵ�Ԫ�طŵ�cout�����
    ostream_iterator<int> output(cout ,"*");//�ŵ��������ʱ��ÿ��һ����������ĩβ���һ��*
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
//��������
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

//��ʹ����������������������ݷ��뵽ָ�������ʱ��������<<�����
template<class T>
ostream &operator<<(ostream &out, const arrayList<T> &x) {
    x.output(out);
    return out;
}


