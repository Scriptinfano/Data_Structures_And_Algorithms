#pragma once

#include "../linearList/arrayAndVectorList/arrayList.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <iterator>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;


//����������
template<class T>
class chainList : public LinearList<T> {

    //����ģ�������Ԫģ�庯��ֱ�ӽ�����д���ඨ��֮��
    friend bool operator<(const chainList<T> &leftChain, const chainList<T> &rightChain) {
        char c;
        T t;
        if (typeid(t) != typeid(c))throw ExceptionSpace::IllegalParameterValue("ʹ��<�Ƚ���������ʱ�����ܱȽϳ���char�����������������");
        ChainNode<T> *it = leftChain.begin();
        ChainNode<T> *it2 = rightChain.begin();
        char *p = new char[leftChain.size()];
        char *p2 = new char[rightChain.size()];
        for (int i = 0; i < leftChain.size(); i++) {
            p[i] = leftChain.get(i);
        }
        for (int i = 0; i < rightChain.size(); i++) {
            p2[i] = rightChain.get(i);
        }
        int cmp = strcmp(p, p2);
        if (cmp < 0)return true;
        else return false;
    }

    friend void bubbleSort(chainList<T> *chain, int size) {
        for (int i = size; i > 1 && chain->bubble(i); i--);
    }

protected:
    void checkIndex(int theIndex, string actionType) const;

    ChainNode<T> *firstNode;//ָ�������һ���ڵ��ָ�룬������Ϊ��ʱ����ֵΪnullptr
    int listSize;//����ڵ����

public:


    //�������׽ڵ㣬����һ���ձ�
    chainList(ChainNode<T> *p = nullptr, int theListSize = 0) : firstNode(p), listSize(theListSize) {}

    //�����׽ڵ�
    chainList(const T &theElement, int theListSize = 1) : listSize(theListSize) {
        firstNode = new ChainNode<T>(theElement, nullptr);
    }

    chainList(const chainList<T> &theChainList);

    ~chainList();

    //ADT����
    virtual bool empty() const { return listSize == 0; }    //����Ƿ�Ϊ��
    virtual int size() const;                               //��������Ԫ�ظ���
    virtual T &get(const int &theIndex);                     //�õ�����ֵΪtheIndex��Ԫ��
    virtual int indexOf(const T &theElement) const;         //����Ԫ��theElement�״γ��ֵ�����ֵ
    virtual void erase(const int &theIndex);                       //ɾ������ΪtheIndex��Ԫ��
    virtual void insert(const int &theIndex, const T &theElement); //��ָ��λ�ò���Ԫ��
    virtual void output(ostream &out) const;                //��������е�����Ԫ��
    virtual void clear();                                   //��׼��������ӿڣ���ѡ��������ջ����߼����


private:
    //˽���ڲ��ӿڣ�
    void setSize(int newSize);//ʹ����ڵ��������newSize����newSizeС��ԭ��С����ɾ������Ԫ�أ�������ԭ��С�����κβ���

    ChainNode<T> *indexToAddress(int theIndex) const;//�������������ظ�����������Ľڵ�ĵ�ַ

    int indexOf(ChainNode<T> *pBegin, const T &theElement) const;    //���Ե�ַΪpBegin�Ľڵ㿪ʼ�����ң��ҵ���һ���ڵ�Ԫ����theElement�Ľڵ���

    int lastIndexOf(const T &theElement) const;//����ָ��Ԫ�������ֵ����������������򷵻�-1

    void swap(int indexA, int indexB);//����ָ�������������ڵ��Ԫ��

    bool bubble(int n);

    void physicalClear();//����ɾ������Ԫ�أ��ͷ���������ռ�

    void logicalClear();//�߼��������Ԫ�أ����洢�����׽ڵ�ĳ�Ա����ָ��firstNode��Ϊnullptr���ٽ�listSize��Ϊ0


public:

    //��������

    void push_back(const T &theElement);//�������β���¼�һ���ڵ�

    void set(int theIndex, const T &theElement);//�滻ָ��Ԫ��

    void removeRange(int beginIndex, int endIndex);//ɾ��ָ����Χ�ڵ�Ԫ��

    void swap(chainList<T> &theChain);//�������������е�Ԫ��

    void fromList(const arrayList<T> &theArray);//���������Ա�ת��Ϊ����

    arrayList<T> toList();//������ת��Ϊ�������Ա���ֱ�ӷ��ؽ��

    void leftShift(int offset);//�������е�Ԫ�������ƶ�offset��λ��

    void reverse();//ԭ�صߵ������е�Ԫ�أ��������κ��µĽڵ�ռ�

    void meld(chainList<T> &chainA,
              chainList<T> &chainB);//�������෽��meld()���ƣ��ϲ��������Ӧ��������a��b�Ľڵ�ռ䣬�ϲ�֮����������chainA��chainB�ǿձ�������ɾ�������������

    vector<chainList<T>> *split();//����������չ����a��b��a�а�������Ϊ������Ԫ�أ�b�а�������Ԫ�أ�a��b�Ĵ洢�ռ伴*this�Ĵ洢�ռ�

    void test();//��������˽�к����Ĺ��нӿ�

    void swapNode(int indexA, int indexB);//���������ڵ������

    void insertSort();//���ò������򷨶�����Ԫ�ؽ�������

    void selectionSort();

    void rankSort();

    void bubbleSort();


    //�������������
    T &operator[](int index);

    bool operator==(const chainList<T> &theChain);

    bool operator!=(const chainList<T> &theChain);

    //���������׽ڵ��ַ
    ChainNode<T> *begin() const;


};


template<class T>
void chainList<T>::checkIndex(int theIndex, string actionType) const {
//ȷ��������0��listSize-1֮��
    if (actionType == "insert") {
        if (theIndex < 0 || theIndex > this->size()) {
            ostringstream s;
            s << "����Ԫ��ʱ��";
            if (theIndex < 0)s << "����ֵ����<0" << endl;
            if (theIndex > listSize)s << "����ֵ����>����Ԫ�ظ���" << endl;
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
chainList<T>::chainList(const chainList<T> &theChainList) {
    listSize = theChainList.listSize;
    if (listSize == 0) {
        //����theChainListΪ�գ�����Ҫ���ƹ���
        firstNode = nullptr;
        return;
    }
    //�ȴ���ָ��ӹܱ����������ٿ�����һ��Ԫ�أ����ƶ�ԭ����ָ�룬����ָ��ӹ�Ŀ������Ȼ��ѭ������Ԫ��
    ChainNode<T> *sourceNode = theChainList.firstNode;//sourceNodeָ�򱻸���������׽ڵ�
    firstNode = new ChainNode<T>(sourceNode->element);//��ʼ��Ŀ�������׽ڵ㲢������Ԫ��
    sourceNode = sourceNode->next;//ָ�򱻸��������׽ڵ��ָ�����Ųһ���ڵ�
    ChainNode<T> *targetNode = firstNode;//����ָ��Ŀ�������׽ڵ��ָ��
    while (sourceNode != nullptr) {
        targetNode->next = new ChainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = nullptr;


}

template<class T>
chainList<T>::~chainList() {
    while (firstNode != nullptr) {
        ChainNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
    listSize = 0;
}

template<class T>
int chainList<T>::size() const {
    return listSize;
}

template<class T>
T &chainList<T>::get(const int &theIndex){
    checkIndex(theIndex, "get");
    ChainNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; i++) {
        currentNode = currentNode->next;
    }
    return currentNode->element;
}

template<class T>
int chainList<T>::indexOf(const T &theElement) const {
    ChainNode<T> *currentNode = firstNode;
    int index = 0;
    while (currentNode != nullptr && currentNode->element != theElement) {
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == nullptr)return -1;//����û���ҵ�
    else return index;//�ҵ���
}

template<class T>
void chainList<T>::erase(const int &theIndex) {
    checkIndex(theIndex, "erase");

    ChainNode<T> *deleteNode;
    if (theIndex == 0)//ɾ����Ԫ�صĽڵ�
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    } else {
        //�ñ����ķ�����ָ��pָ��Ҫɾ���ڵ��ǰ���ڵ�
        ChainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++) {
            p = p->next;
        }
        deleteNode = p->next;
        p->next = p->next->next;//��ǰ���ڵ�ֱ������Ҫɾ���ڵ�ĺ�̽ڵ�
    }
    listSize--;
    delete deleteNode;
}

template<class T>
void chainList<T>::insert(const int &theIndex, const T &theElement) {
    checkIndex(theIndex, "insert");
    if (theIndex == 0)//�ڱ�ͷ�����½ڵ�
    {
        firstNode = new ChainNode<T>(theElement, firstNode);

    } else {
        ChainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++) {
            p = p->next;
        }
        p->next = new ChainNode<T>(theElement, p->next);

    }
    listSize++;
}

template<class T>
void chainList<T>::output(ostream &out) const {
    for (ChainNode<T> *currentNode = firstNode; currentNode != nullptr; currentNode = currentNode->next) {
        out << currentNode->element << " ";
    }
}

template<class T>
void chainList<T>::setSize(int newSize) {
    if (newSize < 0)throw IllegalParameterValue("����void chainList<T>::setSize(int newSize)����ʱ���������ݴ���newSize����С��0");
    if (newSize < listSize) {
        //ɾ������Ԫ��
        ChainNode<T> *p = firstNode;
        ChainNode<T> *j = p->next;
        //��ʱpָ��Ľڵ���jָ��Ľڵ��ǰ���ڵ�
        for (int i = 0; i < newSize; i++) {
            j = j->next;
            p = p->next;
        }
        //p��j��ǰ�棬��ʱjָ��Ľڵ��Լ�֮������нڵ���Ҫɾ���Ľڵ�
        p->next = nullptr;

        ChainNode<T> *deleteNode = j;
        ChainNode<T> *currentNode = deleteNode;

        int count = 0;//��¼ɾ���ڵ������
        while (currentNode != nullptr) {
            currentNode = currentNode->next;
            delete deleteNode;
            deleteNode = currentNode;
            count++;
        }
        listSize -= count;

    } else {
        throw IllegalParameterValue("����void chainList<T>::setSize(int newSize)����ʱ���������ݴ���newSize���ô���ԭ��С");
    }

}

template<class T>
void chainList<T>::push_back(const T &theElement) {
    ChainNode<T> *newNode = new ChainNode<T>(theElement, nullptr);
    if (listSize == 0)firstNode = newNode;
    else {
        ChainNode<T> *p = firstNode;
        for (int i = 0; i < listSize - 1; i++) {
            p = p->next;
        }
        p->next = newNode;
    }
    listSize++;
}

template<class T>
void chainList<T>::set(int theIndex, const T &theElement) {
    checkIndex(theIndex, "replace");
    this->get(theIndex) = theElement;
}

template<class T>
void chainList<T>::removeRange(int beginIndex, int endIndex) {
    if (beginIndex >= 0 && beginIndex < endIndex && endIndex <= listSize - 1) {
        ChainNode<T> *pBegin = firstNode, *pEnd = firstNode;
        for (int i = 0; i < beginIndex - 1; i++)
            pBegin = pBegin->next;
        for (int i = 0; i < endIndex - 1; i++)
            pEnd = pEnd->next;
        ChainNode<T> *p = pBegin->next, *j = pEnd->next;
        ChainNode<T> *deleteNode = nullptr;
        int count = 0;
        pBegin->next = j->next;

        while (p != j->next) {
            deleteNode = p;
            p = p->next;
            delete deleteNode;
            count++;
        }
        listSize -= count;
    } else {
        throw IllegalParameterValue("ʹ��removeRange����ʱ������������");

    }
}

template<class T>
int chainList<T>::lastIndexOf(const T &theElement) const {
    ChainNode<T> *p = firstNode;
    int lastIndex = 0;
    int finalIndex = 0;

    while (p != nullptr) {
        finalIndex = lastIndex;
        lastIndex = indexOf(p, theElement);
        p = indexToAddress(lastIndex);
        if (p != nullptr)p = p->next;
    }
    return finalIndex;
}

template<class T>
int chainList<T>::indexOf(ChainNode<T> *pBegin, const T &theElement) const {
    //���Ե�ַΪpBegin�Ľڵ㿪ʼ�����ң��ҵ���һ���ڵ�Ԫ����theElement�Ľڵ���
    ChainNode<T> *currentNode = pBegin;
    int index = 0;
    ChainNode<T> *p = firstNode;
    while (p != currentNode) {
        p = p->next;
        index++;
    }

    while (currentNode != nullptr && currentNode->element != theElement) {
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == nullptr)return -1;//����û���ҵ�
    else return index;//�ҵ���

}

template<class T>
ChainNode<T> *chainList<T>::indexToAddress(int theIndex) const {
    if (theIndex >= listSize || theIndex < 0)return nullptr;
    int index = 0;
    ChainNode<T> *p = firstNode;
    while (index != theIndex) {
        p = p->next;
        index++;
    }
    return p;
}

template<class T>
T &chainList<T>::operator[](int index) {
    ChainNode<T> *p = firstNode;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    return p->element;

}

template<class T>
bool chainList<T>::operator==(const chainList<T> &theChain) {
    ChainNode<T> *p = firstNode, *p2 = theChain.begin();
    if (listSize != theChain.size())return false;
    else {
        while (p != nullptr && p2 != nullptr) {
            if (p->element != p2->element)return false;
            p = p->next;
            p2 = p2->next;
        }
        return true;
    }
}

template<class T>
ChainNode<T> *chainList<T>::begin() const {
    return firstNode;
}

template<class T>
bool chainList<T>::operator!=(const chainList<T> &theChain) {
    return !(*this == theChain);
}

template<class T>
void chainList<T>::swap(chainList<T> &theChain) {
    int selfListSize = this->size();
    int otherListSize = theChain.size();

    ChainNode<T> *temp = firstNode;
    firstNode = theChain.firstNode;
    theChain.firstNode = temp;

    listSize = otherListSize;
    theChain.setSize(selfListSize);

}

template<class T>
void chainList<T>::fromList(const arrayList<T> &theArray) {
    for (int i = 0; i < theArray.size(); i++)
        this->push_back(theArray.get(i));
}

template<class T>
arrayList<T> chainList<T>::toList() {
    arrayList<T> array(this->size());
    for (int i = 0; i < this->size(); i++)
        array.push_back(this->get(i));

    return array;
}

template<class T>
void chainList<T>::leftShift(int offset) {
    int newSize = listSize - offset;
    ChainNode<T> *p = firstNode;
    for (int i = 0; i < offset; i++)
        p = p->next;
    ChainNode<T> *temp = new ChainNode<T>(p->element, nullptr);
    ChainNode<T> *j = temp;

    for (int i = 0; i < newSize - 1; i++) {
        j->next = new ChainNode<T>(p->next->element, nullptr);
        j = j->next;
        p = p->next;
    }
    firstNode = temp;
    listSize = newSize;


}

template<class T>
void chainList<T>::reverse() {
    ChainNode<T> *p = firstNode;
    ChainNode<T> *j = firstNode->next;
    ChainNode<T> *temp = nullptr;
    while (j != nullptr) {
        temp = j->next;
        j->next = p;
        p = j;
        j = temp;
    }
    firstNode->next = nullptr;
    firstNode = p;
}

template<class T>
void chainList<T>::meld(chainList<T> &chainA, chainList<T> &chainB) {
    if (chainA.size() == 0 && chainB.size() == 0)return;
    ChainNode<T> *p = chainA.begin();
    ChainNode<T> *j = chainB.begin();
    ChainNode<T> *t = nullptr;
    ChainNode<T> *c = nullptr;
    ChainNode<T> *temp = nullptr;
    ChainNode<T> *temp2 = nullptr;
    do {
        temp = p->next;
        t = p;
        p = p->next;
        temp2 = j->next;
        c = j;
        j = j->next;
        t->next = c;
        c->next = temp;
    } while (temp != nullptr && temp2 != nullptr);
    if (temp == nullptr && temp2 != nullptr)
        c->next = temp2;
    firstNode = chainA.begin();
    listSize = chainA.size() + chainB.size();
    chainA.logicalClear();
    chainB.logicalClear();

}

template<class T>
void chainList<T>::physicalClear() {
    ChainNode<T> *deleteNode = firstNode;
    ChainNode<T> *p = firstNode;
    while (p != nullptr) {
        deleteNode = p;
        p = p->next;
        delete deleteNode;
    }
    firstNode = nullptr;
    listSize = 0;
}

template<class T>
void chainList<T>::logicalClear() {
    firstNode = nullptr;
    listSize = 0;
}

template<class T>
void chainList<T>::swap(int indexA, int indexB) {
    checkIndex(indexA, "replace");
    checkIndex(indexB, "replace");
    T temp;
    temp = this->get(indexA);
    this->get(indexA) = this->get(indexB);
    this->get(indexB) = temp;
}

template<class T>
vector<chainList<T>> *chainList<T>::split() {
    auto *p = new vector<chainList<T>>;
    if (this->size() < 2)return nullptr;
    if (this->size() == 2) {
        chainList<T> c1(firstNode, 1);
        ChainNode<T> *secondNode = firstNode->next;
        firstNode->next = nullptr;
        chainList<T> c2(secondNode, 1);
        secondNode->next = nullptr;
        c1.set(0, this->get(0));
        c2.set(0, this->get(1));
        p->push_back(c1);
        p->push_back(c2);
        firstNode = nullptr;
        listSize = 0;
        return p;
    }
    //Ԫ�ظ������ڵ���3�ģ�Ҫ����һ�׽����㷨������������Ϊż���ģ�����Ϊ0��Ԫ�ز��ö�����Ҳ��������Ϊ2��Ԫ�ؿ�ʼ������������Ϊż����Ԫ����ǰ�ţ�����{7��6��8��9��2}��Ϊ{7��8��2��6��9}
    int i = 1;
    int x = 2;
    while (true) {
        if (x + 1 <= listSize)//������������ľ�ִ��swap()����
        {
            this->swap(i, x);
        } else break;
        i++;
        x += 2;
    }

    chainList<T> c1(firstNode, i);//����Ϊi�Ľڵ�֮ǰ�����нڵ����c1
    chainList<T> c2(this->indexToAddress(i), listSize - i);
    this->indexToAddress(i - 1)->next = nullptr;

    p->push_back(c1);
    p->push_back(c2);

    firstNode = nullptr;
    listSize = 0;
    return p;


}

template<class T>
void chainList<T>::test() {

    this->swap(1, 2);

}

template<class T>
void chainList<T>::insertSort() {
    for (int i = 1; i < this->size(); i++) {
        T t = this->get(i);
        int j;
        for (j = i - 1; j >= 0 && t < this->get(j); j--) {
            this->get(j + 1) = this->get(j);
        }
        this->get(j + 1) = t;
    }
}

template<class T>
bool chainList<T>::bubble(int n) {
    bool swapped = false;
    for (int i = 0; i < n; i++) {
        if (this->get(i) > this->get(i + 1)) {
            this->swapNode(i, i + 1);
            swapped = true;
        }
    }
    return swapped;
}

template<class T>
void chainList<T>::selectionSort() {
    bool sorted = false;
    for (int size = this->size(); !sorted && (size > 1); size--) {
        int indexOfMax = 0;
        sorted = true;
        for (int i = 1; i < size; i++) {
            if (this->get(indexOfMax) <= this->get(i))
                indexOfMax = i;
            else sorted = false;
        }
        this->swap(this->get(indexOfMax), this->get(size - 1));
    }
}

template<class T>
void chainList<T>::rankSort() {
    int *countArray = new int[this->size()];
    for (int i = 0; i < this->size(); i++)countArray[i] = 0;
    for (int i = 0; i < this->size(); i++) {
        countArray[this->get(i)]++;
    }
    int index = 0;
    for (int i = 0; i < this->size(); i++) {
        if (countArray[i] != 0) {
            for (int j = 0; j < countArray[i]; j++) {
                this->get(index) = i;
                index++;
            }
        }
    }
}

template<class T>
void chainList<T>::swapNode(int indexA, int indexB) {
    checkIndex(indexA, "replace");
    checkIndex(indexB, "replace");
    T temp;
    temp = this->get(indexA);
    this->get(indexA) = this->get(indexB);
    this->get(indexB) = temp;
}

template<class T>
void chainList<T>::bubbleSort() {
    for (int i = this->size(); i > 1 && this->bubble(i); i--);
}

template<class T>
void chainList<T>::clear() {
    this->physicalClear();
}

//ȫ�ֺ������������������ʹ��cout<<���������������Ԫ��
template<class T>
ostream &operator<<(ostream &out, const chainList<T> &theNode) {
    theNode.output(out);
    return out;
}

//������ת��Ϊ�������Ա�Ҫ��ʹ��chainList��get()������size()��������arrayList��insert����
template<class T>
void chainToArray(const chainList<T> &theChain, arrayList<T> &theArray) {
    theArray.reserve(theChain.size());
    for (int i = 0; i < theChain.size(); i++) {
        theArray.push_back(theChain.get(i));
    }
}


//��չchainList��������������extendedLinearList�������Ĺ���
