//
// Created by USER on 20/07/2022.
//
#pragma once

#include<iostream>
#include<sstream>
#include <iterator>//�����������
#include <vector>
#include "myIterator.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\virtualBaseClassLinearList.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\namespaces.h"

using ExceptionSpace::IllegalParameterValue;

//ȫ��ģ�庯����������ͨ�����о�����ʵ�����ſ�ʹ��
void initializeTemplateFunction() {

    //������������ã�������ʵ����ģ�庯��
    int *p= nullptr;
    int oldLength=0;
    int newLength=0;
    GlobalSpace::changeLength1D<int>(p,oldLength,newLength);
}

using namespace std;

//�̳ж�̬��������������
template<class T>
class arrayList : public LinearList<T> {
protected:
    void checkIndex(int theIndex, std::string actionType) const;


    int arrayLength; //���鳤�ȣ��൱������������
    int listSize;    //����Ԫ�صĸ���

    T *element;      //�洢���Ա�Ԫ�ص�һά����
    int m_extraSize;

public:
    //���캯�����������캯������������
    arrayList(int initialCapacity = 10, int extraSize = 0);//���캯��
    arrayList(const arrayList<T> &); //��������
    ~arrayList() { delete[] element; }//��������

    // ADT������ʵ�ֻ���Ĵ��麯����
    virtual bool empty() const { return listSize == 0; }    //����Ƿ�Ϊ��
    virtual int size() const;                               //��������Ԫ�ظ���
    virtual T &get(const int &index) const;                     //��������ֵΪindex�Ķ���
    virtual int indexOf(const T &theElement) const;         //����Ԫ�ص�����ֵ
    virtual void erase(const int &index);                       //ɾ������Ϊindex�Ķ���
    virtual void insert(const int &index, const T &theElement); //������index���ĺ�һ��λ�ò���Ԫ��
    virtual void output(std::ostream &out) const;           //������������������Ԫ��

    //���������Ա����

    void trimToSize();//���������Ŀռ�ü�����ʹ�������С����Ԫ������

    void setCapacity(int newCapacity);//����ı�������С������С������Ԫ�ظ���ʱ����Ԫ�ر�ɾ��

    void reserve(int newCapacity);//������ı�������С������������������ı�Ϊ��ǰ������ָ�������еĽϴ�ֵ

    void push_back(const T theElement);//���������¼�һ�����ݣ�������������������

    void pop_back();//ɾ��������β��Ԫ��

    void swap(arrayList<T> &array);//��������������Ԫ��

    int capacity() const { return arrayLength; }//������������

    void clear();//�������������Ԫ��

    void setSize(int newSize);//����ָ����ֵ���������ڲ�ͳ��Ԫ�ظ����ĺ���

    void set(int theIndex, const T &theElement);//��ָ��Ԫ���滻ָ������ֵ��Ԫ��

    int lastIndexOf(const T &theElement);//����ָ��Ԫ��������ʱ����������Ԫ�ز������򷵻�-1

    void reverse();//ԭ�ط�ת����Ԫ��

    void leftShift(int offset);//�����Ա��Ԫ�������ƶ�offset��λ��

    void removeRange(int beginIndex, int endIndex);//�Ƴ�������Χ�ڵ�Ԫ��

    void circularShift(int offset);//ѭ���ƶ����Ա��ڵ�Ԫ�أ���˳ʱ�뷽���ƶ�

    void half();//��һ��Ԫ��ɾ��һ��Ԫ��

    void meld(const arrayList<T> &arrayA,
              const arrayList<T> &arrayB);//���øú�������������ذ���arrayOne��arrayTwo��Ԫ�أ���arrayOne�ĵ�0��Ԫ�ؿ�ʼ����һ�����Ԫ��ȡ������һ����ʣ�µ�Ԫ�طŵ��±���

    void merge(arrayList<T> &listA, arrayList<T> &listB);//��������������Ա�ϲ���һ����������Ա�

    void split(arrayList<T> &listA, arrayList<T> &listB);//�����ú����Ķ���������Ϊż����Ԫ�ط���listA��������Ϊ������Ԫ�ط���listB

    //������Ϊ��Ա�������ص����������
    bool operator==(arrayList<T> &array);

    T &operator[](int i) const;

    bool operator!=(arrayList<T> &array);

    bool operator<(arrayList<T> &array);

    //������Ԫ�ص�ַĩԪ�غ�̵�ַ�ĺ���
    T *begin() const { return element; }//������Ԫ�ص�ַ

    T *end() const { return element + listSize; }//�������һ��Ԫ�غ����λ��

    //�����Զ���������ĺ��������������ֱ𷵻�ָ����Ԫ�صĵ�������ָ��ĩԪ�غ��λ�õĵ�����
    mystd::iterator<T> it_begin() const;

    mystd::iterator<T> it_end() const;


};

//���캯��ʵ��
template<class T>
arrayList<T>::arrayList(int initialCapacity, int extraSize) {
    if (initialCapacity < 1) {
        ostringstream s;
        s << "��ʼ����=" << initialCapacity << "����ֵ����>0" << endl;
        throw IllegalParameterValue(s.str()); // ostringstream�������str()�᷵��һ����ʱ��string����
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

    if (listSize == 0) {// replace with arrayList of length 1
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
//��������
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
    for (; *it == *it2; ++it, ++it2)
        if (*it == '\0')return false;
    return ((*it) < (*it2)) ? true : false;
}

template<class T>
void arrayList<T>::push_back(const T theElement) {
    if (listSize + 1 > arrayLength) {
        //ִ�б�������֮��Ԫ����ӵ����һ��Ԫ�صĺ���
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
    int selfSize = this->listSize;
    int arraySize = array.size();

    if (this->listSize > array.capacity()) {
        //����array���ٽ���Ԫ��
        array.setCapacity(2 * array.capacity());
    }
    if (array.size() > this->arrayLength) {
        //�����Լ����ٽ���Ԫ��
        this->setCapacity(2 * arrayLength);
    }
    //�����������if��䲻���㣬˵�����ཻ��Ԫ��ʱ���Է����������ݵ����Լ���Ԫ�ظ���������Ҫ����ĳ��������С
    int tempCapacity = max(this->arrayLength, array.capacity());
    arrayList<T> temp(
            tempCapacity);//��ʱ�Ѿ�ָ����temp������ֵ��ע�����temp����insert()��push_back()������Ԫ�أ������ڲ�ͳ��Ԫ�ظ����ĳ�Ա����listSize�ǲ���ı�ģ������ֶ��ı��ڲ���Ա����listSize��ֵ
    copy(this->begin(), this->end(), temp.begin());

    //����temp�ڲ���Ԫ�ظ�������Ȼ�޷���tempִ��begin��end���������Ԫ�غ�β��Ԫ�صĵ�ַ

    temp.setSize(selfSize);
    this->clear();

    copy(array.begin(), array.end(), this->begin());
    array.clear();
    copy(temp.begin(), temp.end(), array.begin());

    //����Ԫ��֮���������������ͳ��Ԫ�ظ����ĳ�Ա������ֵ
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
    checkIndex(theIndex, "replace");//��������Ƿ����ĳ������Ҫ�����������׳��쳣��ֹ����
    element[theIndex] = theElement;

}

template<class T>
void arrayList<T>::removeRange(int beginIndex, int endIndex) {
    //�ȼ�����������Ƿ�Ϸ�
    if (beginIndex >= 0 && beginIndex < endIndex && endIndex <= listSize - 1) {
        //ֻ�������������������������Ȧ���ķ�Χ֮�ڲ���Ԫ�أ�ע��������������ȣ�Ҳ����˵�ú���Ҫ����ɾ������Ԫ��
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
        throw IllegalParameterValue("ʹ��removeRange����ʱ������������");
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
//ȷ��������0��listsize-1֮��
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex >= this->capacity() || theIndex > this->size()) {
            ostringstream s;
            s << "����Ԫ��ʱ��";
            if (theIndex < 0)s << "����ֵ����<0" << endl;
            if (theIndex >= this->capacity())s << "����ֵ����>=�����С" << endl;
            if (theIndex > this->size())s << "����ֵ����>����Ԫ�ظ���" << endl;
            throw IllegalParameterValue(s.str());
        }
    } else if (actionType == "erase" || actionType == "get" || actionType == "replace") {
        if (theIndex >= this->size()) {
            ostringstream s;
            if (actionType == "erase")
                s << "ɾ��Ԫ��ʱ������ֵ����>=listSize" << endl;
            else if (actionType == "replace")s << "�滻Ԫ��ʱ������ֵ����>=listSize" << endl;
            else if (actionType == "get")s << "��ȡԪ��ʱ������ֵ����>=listSize" << endl;
            throw IllegalParameterValue(s.str());
        }
    } else {
        ostringstream s;
        s << "checkIndex�ڶ����������벻��ȷ��δָ����ȷ�Ĳ�������" << endl;
        throw IllegalParameterValue(s.str());
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
    int netOffset = 0;//��ƫ��������offset>listSize����netOffset=offSet%listSize
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
        //�������Ԫ��һ������˵������Ҫ����һ�����Ԫ�طŽ��±�
        return;

    } else if (indexA == listSizeA) {
        //����2�����±�
        while (indexB < listSizeB) {
            temp[tempIndex] = arrayB[indexB];
            tempIndex++;
            indexB++;
        }
    } else {
        //indexB==listSizeTwo�����������1�����±�
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
            //��ʱ��������ż��
            listA.push_back(element[i]);
        } else {
            //��ʱ������������
            listB.push_back(element[i]);
        }
    }

}

template<class T>
T &arrayList<T>::get(const int &index) const {
    checkIndex(index, "get");
    return element[index];

}

template<class T>
void arrayList<T>::erase(const int &index) {
    checkIndex(index, "erase");
    copy(element + index + 1, element + listSize,
         element + index); //��׼�㷨����copy()�ĵ�һ�ڶ���������Ҫ����Ԫ�ص���ʼλ�ú���ֹλ�ã�������������Ŀ��������Ŀ���ַ
    if (listSize - 1 < (arrayLength / 4)) {
        //�����Ա�Ԫ�ظ����������Ա�������1/4����ʱ�����������飬����ΪarrayLength/2��Ȼ���ϱ��Ԫ�ظ��ƹ�ȥ
        T *temp = new T[arrayLength / 2];
        copy(this->begin(), this->end(), temp);
        delete[]element;
        element = temp;
        listSize--;
        arrayLength = arrayLength / 2;
        return;
    }
    element[--listSize].~T(); //�����ƶ�Ԫ�ػᵼ������ĩβ���һ��δ�������Ŀռ䣬���Ա�������������Ӧ���͵��������������ͷ�

}

template<class T>
void arrayList<T>::insert(const int &index, const T &theElement) {
    checkIndex(index, "insert");        //�ȼ������ֵ�Ƿ����
    if (listSize == arrayLength) //�����Ѿ����ˣ����鳤����Ҫ�������ٲ����µ�Ԫ��
    {
        if (m_extraSize == 0) {
            //���ù��캯��ʱ�����extraSize�ȳ�ʼ����С����δ�������Ĳ�����ִ�б�������������ִ�а��û�ָ�������������С�Ĳ���
            GlobalSpace::changeLength1D<T>(element, arrayLength, 2 * arrayLength);
            arrayLength *= 2;
        } else {
            GlobalSpace::changeLength1D<T>(element, arrayLength, m_extraSize);
            arrayLength = m_extraSize;
        }
    }
    copy_backward(element + index, element + listSize,
                  element + listSize + 1); //��ָ�������ڵ�Ԫ�����Ų��ֱ��������ĩλ��������������ĵ�ַ��ͬΪֹ
    element[index] = theElement;
    listSize++;

}


//��ʹ����������������������ݷ��뵽ָ�������ʱ��������<<�����
template<class T>
ostream &operator<<(ostream &out, const arrayList<T> &x) {
    x.output(out);
    return out;
}

//��vector<>������Ϊ�ײ�洢�ṹ��ģ��������

template<class T>
class vectorList : public LinearList<T> {
protected:
    void checkIndex(int theIndex, string actionType) const;

    vector<T> *element;
public:
    //���캯�����������캯������������
    vectorList(int initialCapacity = 10);

    vectorList(const vectorList<T> &theVectorList);

    ~vectorList() { delete element; }

    //ADT����
    virtual bool empty() const { return element->empty(); }     //�ж������Ƿ�Ϊ��
    virtual int size() const { return (int) element->size(); }  //��������Ԫ�ظ���
    virtual int indexOf(const T &theElement) const;             //����ָ��Ԫ�ص�����
    virtual T &get(const int &index) const;                     //��������ֵΪindex�Ķ���
    virtual void erase(const int &index);                       //ɾ������Ϊindex�Ķ���
    virtual void insert(const int &index, const T &theElement); //������index���ĺ�һ��λ�ò���Ԫ��
    virtual void output(ostream &out) const;                    //�������Ԫ��

    //���ӵķ���
    int capacity() const { return (int) element->capacity(); }

    //���Ա����ʼ�ͽ���λ�õĵ�����
    //�����ȶ���һ�����ͱ���������ʹ�ã����ص��������͵�ʱ����дһ����
    typedef typename vector<T>::iterator iterator;//��Ϊģ�����Ͷ������ʱҪ��typedef֮�����typename��typedef�����˴������͵ı�����typename���߱�����std::vector<T>::iterator��һ�����Ͷ�����һ����Ա�������ʹ��iterator��Ϊvector<T>::iterator�ı���

    iterator begin() { return element->begin(); }

    iterator end() { return element->end(); }
};

template<class T>
vectorList<T>::vectorList(int initialCapacity) {
    if (initialCapacity < 1) {
        ostringstream s;
        s << "��ʼ����=" << initialCapacity << "����ֵ����>0";
        throw IllegalParameterValue(s.str());
    }
    element = new vector<T>;//����vector����
    element->reserve(initialCapacity);//��������

}

template<class T>
vectorList<T>::vectorList(const vectorList<T> &theVectorList) {
    element = new vector<T>(*theVectorList.element);//�ڶ�������һ��vector���������������еĶ�������ʼ�����������еĶ��󼴴��뺯����vectorList�����ڲ���vector����
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
void vectorList<T>::output(ostream &out) const {
    for (typename vector<T>::iterator it = this->element->begin(); it != this->element->end(); it++) {
        out << *it < " ";
    }
}

template<class T>
void vectorList<T>::checkIndex(int theIndex, string actionType) const {
//ȷ��������0��listsize-1֮��
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex >= this->capacity() || theIndex > this->size()) {
            ostringstream s;
            s << "����Ԫ��ʱ��";
            if (theIndex < 0)s << "����ֵ����<0" << endl;
            if (theIndex >= this->capacity())s << "����ֵ����>=�����С" << endl;
            if (theIndex > this->size())s << "����ֵ����>����Ԫ�ظ���" << endl;
            throw IllegalParameterValue(s.str());
        }
    } else if (actionType == "erase" || actionType == "get" || actionType == "replace") {
        if (theIndex >= this->size()) {
            ostringstream s;
            if (actionType == "erase")
                s << "ɾ��Ԫ��ʱ������ֵ����>=listSize" << endl;
            else if (actionType == "replace")s << "�滻Ԫ��ʱ������ֵ����>=listSize" << endl;
            else if (actionType == "get")s << "��ȡԪ��ʱ������ֵ����>=listSize" << endl;
            throw IllegalParameterValue(s.str());
        }
    } else {
        ostringstream s;
        s << "checkIndex�ڶ����������벻��ȷ��δָ����ȷ�Ĳ�������" << endl;
        throw IllegalParameterValue(s.str());
    }

}

template<class T>
T &vectorList<T>::get(const int &index) const {
    return element->at(index);//����������Ҫ�����ڲ���vector��������ִ��at����ʱ�׳��쳣

}

template<class T>
void vectorList<T>::erase(const int &index) {
//vector���õ�erase����������ϸ���׳��쳣����������������ʱ����������ָ����һ�������ڵ�Ԫ��ʱ��������쳣�˳��������ڴ�������ǰҪ�����Ϸ���
    checkIndex(index, std::string());
    element->erase(begin() + index);//STL����vector�ĺ���erase()�Ĳ����ǵ���������˼��ɾ��������ָ������ݣ�ע�ⲻ�Ǵ�������

}

template<class T>
void vectorList<T>::insert(const int &index, const T &theElement) {
    checkIndex(index, std::string());
    element->insert(begin() + index, theElement);

}

