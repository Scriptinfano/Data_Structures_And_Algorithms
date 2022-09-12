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

    int arrayLength; //���鳤��
    int listSize;    //����Ԫ�ظ���

    T *element;//�洢���Ա�Ԫ�ص�һά����
    int m_extraSize;

public:
    arrayList(int initialCapacity = 10, int extraSize = 0) {
        if (initialCapacity < 1) {
            ostringstream s;
            s << "��ʼ����=" << initialCapacity << "��ֵ����>0" << endl;
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

    //ADT����
    virtual bool empty() const { return listSize == 0; }

    virtual int size() const;

    virtual T get(const int &index) const;

    virtual int indexOf(const T &theElement) const;

    virtual void erase(const int &index);

    virtual void insert(const int &index, const T &theElement);

    virtual void output(std::ostream &out) const;

    //����ӿ�

    T& getSelf(const int &theIndex){
        checkIndex(theIndex, "get");
        return element[theIndex];
    }

    void trimToSize();//���������Ŀռ�ü�����ʹ�������С����Ԫ������

    void setCapacity(int newCapacity);//����ı�������С������С������Ԫ�ظ���ʱ����Ԫ�ر�ɾ��

    void reserve(int newCapacity);//�ı�������С������������������ı�Ϊ��ǰ������ָ�������еĽϴ�ֵ

    void push_back(const T theElement);//���������¼�һ�����ݣ�������������������

    void pop_back();//ɾ��������β��Ԫ��

    void swap(arrayList<T> &array);//��������������Ԫ��

    int capacity() const { return arrayLength; }//������������

    void clear();//�������������Ԫ��

    void setSize(int newSize);//����ָ����ֵ���������ڲ�ͳ��Ԫ�ظ����ĺ���

    void set(int theIndex, const T &theElement);//��ָ��Ԫ���滻ָ������ֵ��Ԫ��

    void set(mystd::iterator<T> &iter, const T &theElement);//���������set���������ô�����Զ��������ʵ��Ԫ���滻

    int lastIndexOf(const T &theElement);//����ָ��Ԫ��������ʱ����������Ԫ�ز������򷵻�-1

    void reverse();//ԭ�ط�ת����Ԫ��

    void leftShift(int offset);//�����Ա��Ԫ�������ƶ�offset��λ��

    void removeRange(int beginIndex, int endIndex);//�Ƴ�������Χ�ڵ�Ԫ��

    void removeRange(const mystd::iterator<T> &iter_begin, const mystd::iterator<T> &iter_end);//���������removeRange�����������Զ����������Ƿ�Χ��ɾ����Χ֮�ڵ�Ԫ��

    void circularShift(int offset);//ѭ���ƶ����Ա��ڵ�Ԫ�أ���˳ʱ�뷽���ƶ�

    void half();//��һ��Ԫ��ɾ��һ��Ԫ��

    void meld(const arrayList<T> &arrayA, const arrayList<T> &arrayB);//���øú�������������ذ���arrayOne��arrayTwo��Ԫ�أ���arrayOne�ĵ�0��Ԫ�ؿ�ʼ����һ�����Ԫ��ȡ������һ����ʣ�µ�Ԫ�طŵ��±���

    void merge(arrayList<T> &listA, arrayList<T> &listB);//��������������Ա�ϲ���һ����������Ա�

    void split(arrayList<T> &listA, arrayList<T> &listB);//�����ú����Ķ���������Ϊż����Ԫ�ط���listA��������Ϊ������Ԫ�ط���listB

    T *address(const int &theIndex) const;//������Ϊ��Ա�������ص����������

    bool operator==(arrayList<T> &array);//�ж��Ƿ����

    T &operator[](int i) const;//�õ�����Ϊi��Ԫ�ص�����

    bool operator!=(arrayList<T> &array);//�ж�Ԫ���Ƿ����

    bool operator<(arrayList<T> &array);//�������ҷֱ�������������������ֵ�һ��������Ԫ�رȵڶ���������ͬλ�õ�Ԫ��С������򷵻�true���򷵻�false

    //������Ԫ�ص�ַĩԪ�غ�̵�ַ�ĺ���
    T *begin() const { return element; }//������Ԫ�ص�ַ

    T *end() const { return element + listSize; }//�������һ��Ԫ�غ����λ��

    //�����Զ���������ĺ��������������ֱ𷵻�ָ����Ԫ�صĵ�������ָ��ĩԪ�غ��λ�õĵ�����
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
    //������һ�������͵ڶ���������Ԫ��ֵ

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
    arrayList<T> temp(tempCapacity);
    //��ʱ�Ѿ�ָ����temp������ֵ��ע�����temp����insert()��push_back()������Ԫ�أ������ڲ�ͳ��Ԫ�ظ����ĳ�Ա����listSize�ǲ���ı�ģ������ֶ��ı��ڲ���Ա����listSize��ֵ
    copy(this->begin(), this->end(), temp.begin());

    //����temp�ڲ���Ԫ�ظ�������Ȼ�޷���tempִ��begin��end���������Ԫ�غ�β��Ԫ�صĵ�ַ
    temp.setSize(selfSize);
    this->clear();//�����һ��������Ԫ��

    copy(array.begin(), array.end(), this->begin());//���ڶ���������Ԫ�ؿ�������һ��������
    array.clear();//���ڶ����������
    copy(temp.begin(), temp.end(), array.begin());//�ٽ���һ�������е�Ԫ�ؿ������ڶ���������

    //�ֶ�������������ͳ��Ԫ�ظ�����ֵ����Ϊ�Զ�����Ԫ�ظ���ֵֻ���ڵ���insert��push_back()ʱ����
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
        delete[]element;
        element = temp;
        arrayLength = newLength;
        listSize = newLength;

    } else {
        throw IllegalParameterException("ʹ��removeRange����ʱ������������");
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
            s << "����Ԫ��ʱ��";
            if (theIndex < 0)s << "����ֵ����<0" << endl;
            if (theIndex >= this->capacity())s << "����ֵ����>=�����С" << endl;
            if (theIndex > this->size())s << "����ֵ����>����Ԫ�ظ���" << endl;
            throw IllegalParameterException(s.str());
        }
    } else if (actionType == "erase" || actionType == "get" || actionType == "replace") {
        if (theIndex >= this->size()) {
            ostringstream s;
            if (actionType == "erase")
                s << "ɾ��Ԫ��ʱ������ֵ����>=listSize" << endl;
            else if (actionType == "replace")s << "�滻Ԫ��ʱ������ֵ����>=listSize" << endl;
            else if (actionType == "get")s << "��ȡԪ��ʱ������ֵ����>=listSize" << endl;
            throw IllegalParameterException(s.str());
        }
    } else {
        ostringstream s;
        s << "checkIndex�ڶ����������벻��ȷ��δָ����ȷ�Ĳ�������" << endl;
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
    checkIndex(index, "insert");
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
    copy_backward(element + index, element + listSize, element + listSize + 1); //��ָ�������ڵ�Ԫ�����Ų��ֱ��������ĩλ��������������ĵ�ַ��ͬΪֹ
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

//��vector<>������Ϊ�ײ�洢�ṹ��ģ��������
template<class T>
class vectorList : public LinearList<T> {
protected:
    void checkIndex(int theIndex, string actionType) const
    {
        if (actionType == "insert") {
            if (theIndex < 0 || theIndex >= this->capacity() || theIndex > this->size()) {
                ostringstream s;
                s << "����Ԫ��ʱ";
                if (theIndex < 0)s << "����ֵ����<0" << endl;
                if (theIndex >= this->capacity())s << "����ֵ����>=�����С" << endl;
                if (theIndex > this->size())s << "����ֵ����>����Ԫ�ظ���" << endl;
                throw IllegalParameterException(s.str());
            }
        } else if (actionType == "erase" || actionType == "get" || actionType == "replace") {
            if (theIndex >= this->size()) {
                ostringstream s;
                if (actionType == "erase")
                    s << "ɾ��Ԫ��ʱ������ֵ����>=����Ԫ�ظ���" << endl;
                else if (actionType == "replace")s << "�滻����Ԫ��ʱ������ֵ����>=����Ԫ�ظ���" << endl;
                else if (actionType == "get")s << "��ȡԪ��ʱ������ֵ����>=����Ԫ�ظ���" << endl;
                throw IllegalParameterException(s.str());
            }
        } else {
            ostringstream s;
            s << "����checkIndex()ʱ���ڶ����������벻��ȷ��δָ����ȷ�Ĳ�������" << endl;
            throw IllegalParameterException(s.str());
        }
    }

    vector<T> *element;
public:
    //���캯�����������캯�������������ӿ�

    //���캯��
    vectorList(int initialCapacity = 10) {
        if (initialCapacity < 1) {
            ostringstream s;
            s << "��ʼ����=" << initialCapacity << "����ֵ����>0";
            throw IllegalParameterException(s.str());
        }
        element = new vector<T>;
        element->reserve(initialCapacity);//����reserve()Ϊ������������

    }

    vectorList(const vectorList<T> &theVectorList) {
        element = new vector<T>(*(theVectorList.element));//����vector�����Ŀ������캯����ɿ���
    }

    //��������
    ~vectorList() { delete element; }

    //ADT�ӿ�
    virtual bool empty() const {
        return element->empty();
    }

    //��������Ԫ�صĸ���
    virtual int size() const {
        return element->size();
    }

    //�����������ã����ظö����������е�����ֵ
    virtual int indexOf(const T &theElement) const {
        for (int i = 0; i < element->size(); i++) {
            if (theElement == element[i])
                return i;
        }
        return -1;
    }

    //��������ֵΪindex�Ķ���
    virtual T get(const int &index) const {
        //����������Ҫ�����ڲ���vector��������ִ��at����ʱ�׳��쳣
        return element->at(index);
    }

    //ɾ������Ϊindex�Ķ���
    virtual void erase(const int &index)
    {
        checkIndex(index, "erase");
        element->erase(begin() + index);//erase�ɽ���һ��ָ��Ҫɾ��Ԫ�صĵ�������begin()�����index������ָ��Ҫɾ����Ԫ��
    }

    //������index���ĺ�һ��λ�ò���Ԫ��
    virtual void insert(const int &index, const T &theElement) {
        checkIndex(index, std::string());
        element->insert(begin() + index, theElement);
    }

    //���Ԫ��
    virtual void output(std::ostream &out) const {
        for (typename vector<T>::iterator it = this->element->begin(); it != this->element->end(); it++) {
            out << *it < " ";
        }
    }

    //�������Ԫ��
    virtual void clear() {
        element->clear();
    }

    //����ӿ�
    int capacity() const { return (int) element->capacity(); }

    //�������Ա����ʼ�ͽ���λ�õĵ������Ľӿڣ������ȶ���һ�����ͱ���������ʹ�ã����ص��������͵�ʱ����дһ����
    //��Ϊģ�����Ͷ������ʱҪ��typedef֮�����typename��typedef�����˴������͵ı�����typename���߱�����std::vector<T>::iterator��һ�����Ͷ�����һ����Ա�������ʹ��iterator��Ϊvector<T>::iterator�ı���
    typedef typename vector<T>::iterator iterator;

    //������ʼ������
    iterator begin() { return element->begin(); }

    //������ֹ������
    iterator end() { return element->end(); }
};
