#pragma once

#include<vector>
#include<sstream>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\virtualBaseClassLinearList.h"

using namespace std;


class illegalParameterValue {
private:
    string message;

public:
    illegalParameterValue() : message("�Ƿ�ʵ�δ���") {}

    illegalParameterValue(string theMessage) { message = theMessage; }

    void outPutMessage() const { cout << message << endl; }
};


//ӵ��ͷ�ڵ��ѭ�������࣬ͷ�ڵ�������򲻴洢���ݣ�ͷ�ڵ����һ���ڵ����ʵ�ʴ洢���ݵĽڵ㣬�ұ���Ϊ�׽ڵ�


template<class T>
class circularListWithHeader : public linearList<T> {
    /*
     * void checkIndex(int theIndex, string actionType) const;��������ౣ��һ��
     * */

public:

    //�ڵ㼰�ڵ�ָ�����
    typedef chainNode<T> *pointer;
    typedef chainNode<T> node;


    pointer header;//�û����е��׽ڵ��ַ��Ϊѭ������ͷ�ڵ��ַ�������˴����������������������
    int listSize;

    //����ͷ�ڵ㣬�����ձ�ͷ�ڵ��в��洢�κ����ݣ���ָ���򱣴������ַ
    circularListWithHeader(pointer p = nullptr, int theListSize = 0) {
        header = new node;
        header->next = header;
    }

    //����ֱ�ӹ����׽ڵ�Ĺ��캯��
    circularListWithHeader(const T &theElement, int theListSize = 1) {
        header = new node;
        header->next = new node(theElement, header);
    }

    //�������캯��
    circularListWithHeader(const circularListWithHeader<T> &theChainList);

    //��������
    ~circularListWithHeader();


    //ADT����
    virtual T &get(int theIndex) const;//currentNode����ֱ�ӵ���firstNode->next
    virtual int indexOf(const T &theElement) const;

    virtual bool empty() const;                          //��������Ƿ�Ϊ��
    virtual int size() const;                            //����������Ԫ�ص�����
    virtual void clear();

    virtual void erase(int theIndex);

    virtual void insert(int theIndex, const T &theElement);

    virtual void output(ostream &out) const;

    //��������
    void push_back(const T &theElement);

    void set(int theIndex, const T &theElement);//�滻ָ��Ԫ��

    void removeRange(int beginIndex, int endIndex);//ɾ��ָ����Χ�ڵ�Ԫ��

    void swap(circularListWithHeader<T> &theChain);//�������������е�Ԫ��

    void fromList(const circularListWithHeader<T> &theChain);//���������Ա�ת��Ϊ����

    void leftShift(int offset);//�������е�Ԫ�������ƶ�offset��λ��

    void reverse();//ԭ�صߵ������е�Ԫ�أ��������κ��µĽڵ�ռ�

    void meld(circularListWithHeader<T> &chainA,
              circularListWithHeader<T> &chainB);//�������෽��meld()���ƣ��ϲ��������Ӧ��������a��b�Ľڵ�ռ䣬�ϲ�֮����������chainA��chainB�ǿձ�������ɾ�������������

    void physicalClear();//����ɾ������Ԫ�أ��ͷ���������ռ�

    void logicalClear();//�߼��������Ԫ�أ����洢�����׽ڵ�ĳ�Ա����ָ��firstNode��Ϊnullptr���ٽ�listSize��Ϊ0

    vector<circularListWithHeader<T>> *split();//����������չ����a��b��a�а�������Ϊ������Ԫ�أ�b�а�������Ԫ�أ�a��b�Ĵ洢�ռ伴*this�Ĵ洢�ռ�

    void test();//��������˽�к����Ĺ��нӿ�

    void swapNode(int indexA, int indexB);//���������ڵ������

    void insertSort();//���ò������򷨶�����Ԫ�ؽ�������

    void selectionSort();

    void rankSort();

    void bubbleSort();


private:
    void setSize(int newSize);

    void checkIndex(int theIndex, std::string actionType) const;


protected:

};

template<class T>
circularListWithHeader<T>::circularListWithHeader(const circularListWithHeader<T> &theChainList) {
    this->setSize(theChainList.size());
    if (this->size() == 0) {
        //����theChainListΪ�գ�����Ҫ���ƹ���
        header = new node;
        header->next = header;
    } else {
        header = new node;
        pointer sourceNode = theChainList.begin()->next;
        header->next = new node(theChainList.begin()->next->element);
        sourceNode = sourceNode->next;
        pointer targetNode = header->next;
        while (sourceNode != theChainList.begin()) {
            targetNode->next = new node(sourceNode->element);
            targetNode = targetNode->next;
            sourceNode = sourceNode->next;
        }
        targetNode->next = header;
    }
}

template<class T>
circularListWithHeader<T>::~circularListWithHeader() {
    pointer p = header->next;
    header->next = header;
    pointer deleteNode = nullptr;
    while (p != header) {
        deleteNode = p;
        p = p->next;
        delete deleteNode;
    }
    listSize = 0;
}

template<class T>
T &circularListWithHeader<T>::get(int theIndex) const {
    checkIndex(theIndex, "get");
    pointer currentNode = header->next;
    for (int i = 0; i < theIndex; i++) {
        currentNode = currentNode->next;
    }
    return currentNode->element;

}

template<class T>
int circularListWithHeader<T>::indexOf(const T &theElement) const {
    pointer currentNode = header->next;
    int index = 0;
    while (currentNode->element != theElement) {
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == header) {
        return -1;
    } else return index;

}

template<class T>
void circularListWithHeader<T>::erase(int theIndex) {
    checkIndex(theIndex, "erase");
    pointer deleteNode;
    if (theIndex == 0 && listSize == 1) {
        deleteNode = header->next;
        header->next = header;
    } else if (theIndex == 0 && listSize > 1) {
        deleteNode = header->next;
        header->next = header->next->next;
    } else {
        pointer p = header->next;
        //�ҵ�Ҫɾ���ڵ��ǰ���ڵ�
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        deleteNode = p->next;
        p->next = p->next->next;
    }
    listSize--;
    delete deleteNode;
}

template<class T>
void circularListWithHeader<T>::insert(int theIndex, const T &theElement) {
    checkIndex(theIndex, "insert");
    if (theIndex == 0) {
        if (listSize == 0)
            header->next = new node(theElement, header);
        else header->next = new node(theElement, header->next);
    } else {
        pointer p = header->next;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        p->next = new node(theElement, p->next);
    }
    listSize++;
}

template<class T>
void circularListWithHeader<T>::output(ostream &out) const {
    for (pointer currentNode = header->next; currentNode != header; currentNode = currentNode->next) {
        out << currentNode->element << " ";
    }
}

template<class T>
void circularListWithHeader<T>::setSize(int newSize) {
    if (newSize < this->size() && newSize > 0) {
        pointer p = header->next;
        pointer j = p->next;
        for (int i = 0; i < newSize; i++) {
            j = j->next;
            p = p->next;
        }
        p->next = header;
        chainNode<T> *deleteNode = j;
        chainNode<T> *currentNode = deleteNode;
        int count = 0;//��¼ɾ���ڵ������
        while (currentNode != header) {
            currentNode = currentNode->next;
            delete deleteNode;
            deleteNode = currentNode;
            count++;

        }
        listSize -= count;
    } else {
        throw illegalParameterValue("����void chainList<T>::setSize(int newSize)����ʱ���������ݴ���");
    }
}

template<class T>
void circularListWithHeader<T>::push_back(const T &theElement) {
    pointer newNode = new node(theElement, header);
    if (listSize == 0)header->next = newNode;
    else {
        pointer p = header->next;
        for (int i = 0; i < listSize - 1; i++) {
            p = p->next;
        }
        p->next = newNode;
    }
    listSize++;
}

template<class T>
void circularListWithHeader<T>::set(int theIndex, const T &theElement) {
    checkIndex(theIndex, "replace");
    this->get(theIndex) = theElement;
}

template<class T>
void circularListWithHeader<T>::removeRange(int beginIndex, int endIndex) {
    if (beginIndex >= 0 && beginIndex < endIndex && endIndex <= listSize - 1) {
        pointer pBegin = header->next, pEnd = header->next;
        for (int i = 0; i < beginIndex - 1; i++)
            pBegin = pBegin->next;
        for (int i = 0; i < endIndex - 1; i++)
            pEnd = pEnd->next;
        pointer p = pBegin->next, j = pEnd->next, deleteNode = nullptr;
        int count = endIndex - beginIndex + 1;
        pBegin->next = j->next;
        j->next = nullptr;
        while (p != nullptr) {
            deleteNode = p;
            p = p->next;
            delete deleteNode;
        }

        listSize -= count;
    } else {
        throw illegalParameterValue("ʹ��removeRange����ʱ������������");
    }
}

template<class T>
void circularListWithHeader<T>::swap(circularListWithHeader<T> &theChain) {
}

template<class T>
void circularListWithHeader<T>::leftShift(int offset) {
}

template<class T>
void circularListWithHeader<T>::reverse() {
}

template<class T>
void circularListWithHeader<T>::meld(circularListWithHeader<T> &chainA, circularListWithHeader<T> &chainB) {
}

template<class T>
void circularListWithHeader<T>::physicalClear() {
}

template<class T>
void circularListWithHeader<T>::logicalClear() {
}

template<class T>
vector<circularListWithHeader<T>> *
circularListWithHeader<T>::split()//����������չ����a��b��a�а�������Ϊ������Ԫ�أ�b�а�������Ԫ�أ�a��b�Ĵ洢�ռ伴*this�Ĵ洢�ռ�
{

}

template<class T>
void circularListWithHeader<T>::test() {
}

template<class T>
void circularListWithHeader<T>::swapNode(int indexA, int indexB) {
}

template<class T>
void circularListWithHeader<T>::insertSort() {
}

template<class T>
void circularListWithHeader<T>::selectionSort() {
}

template<class T>
void circularListWithHeader<T>::rankSort() {
}

template<class T>
void circularListWithHeader<T>::bubbleSort() {
}

template<class T>
bool circularListWithHeader<T>::empty() const {
    return listSize == 0;
}

template<class T>
int circularListWithHeader<T>::size() const {
    return listSize;
}

template<class T>
void circularListWithHeader<T>::clear() {
    this->~circularListWithHeader();
}


//ȫ��ģ�庯��
template<class T>
ostream &operator<<(ostream &out, const circularListWithHeader<T> &chain) {
    chain.output(out);
    return out;
}

template<class T>
void circularListWithHeader<T>::checkIndex(int theIndex, std::string actionType) const {
//ȷ��������0��listsize-1֮��
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex > this->size()) {
            ostringstream s;
            s << "����Ԫ��ʱ��";
            if (theIndex < 0)s << "����ֵ����<0" << endl;
            if (theIndex > this->size())s << "����ֵ����>����Ԫ�ظ���" << endl;
            throw illegalParameterValue(s.str());
        }
    } else if (actionType == "erase" || actionType == "get" || actionType == "replace") {
        if (theIndex >= this->size()) {
            ostringstream s;
            if (actionType == "erase")
                s << "ɾ��Ԫ��ʱ������ֵ����>=listSize" << endl;
            else if (actionType == "replace")s << "�滻Ԫ��ʱ������ֵ����>=listSize" << endl;
            else if (actionType == "get")s << "��ȡԪ��ʱ������ֵ����>=listSize" << endl;
            throw illegalParameterValue(s.str());
        }
    } else {
        ostringstream s;
        s << "checkIndex�ڶ����������벻��ȷ��δָ����ȷ�Ĳ�������" << endl;
        throw illegalParameterValue(s.str());
    }
}
