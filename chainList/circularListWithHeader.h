#pragma once

#include "chainListMain.h"
#include "extendedChainList.h"

using namespace std;


//ӵ��ͷ�ڵ��ѭ�������࣬ͷ�ڵ�������򲻴洢���ݣ�ͷ�ڵ����һ���ڵ����ʵ�ʴ洢���ݵĽڵ㣬�ұ���Ϊ�׽ڵ�
template<class T>
class circularListWithHeader : public chainList<T> {
    /*
     * void checkIndex(int theIndex, string actionType) const;��������ౣ��һ��
     * */
public:

    typedef chainNode<T> *pointer;
    typedef chainNode<T> node;
    pointer &header = chainList<T>::firstNode;//�û����е��׽ڵ��ַ��Ϊѭ������ͷ�ڵ��ַ�������˴����������������������
    int &listSize = chainList<T>::listSize;

    //����ͷ�ڵ㣬�����ձ�ͷ�ڵ��в��洢�κ����ݣ���ָ���򱣴������ַ
    circularListWithHeader(pointer p = nullptr, int theListSize = 0) : chainList<T>(p, theListSize) {
        header = new node;
        header->next = header;
    }

    //����ֱ�ӹ����׽ڵ�Ĺ��캯��
    circularListWithHeader(const T &theElement, int theListSize = 1) : chainList<T>(nullptr, theListSize) {
        header = new node;
        header->next = new node(theElement, header);
    }

    circularListWithHeader(const circularListWithHeader<T> &theChainList);

    ~circularListWithHeader();

    //���½���ʾ��Ҫ��д��ADT����
    T &get(int theIndex) const;//currentNode����ֱ�ӵ���firstNode->next
    int indexOf(const T &theElement) const;

    void erase(int theIndex);

    void insert(int theIndex, const T &theElement);

    void output(ostream &out) const;

    //��������
    void push_back(const T &theElement);

    void set(int theIndex, const T &theElement);//�滻ָ��Ԫ��

    void removeRange(int beginIndex, int endIndex);//ɾ��ָ����Χ�ڵ�Ԫ��

    void swap(chainList<T> &theChain);//�������������е�Ԫ��

    void fromList(const arrayList<T> &theArray);//���������Ա�ת��Ϊ����

    arrayList<T> toList();//������ת��Ϊ�������Ա���ֱ�ӷ��ؽ��

    void leftShift(int offset);//�������е�Ԫ�������ƶ�offset��λ��

    void reverse();//ԭ�صߵ������е�Ԫ�أ��������κ��µĽڵ�ռ�

    void meld(chainList<T> &chainA,
              chainList<T> &chainB);//�������෽��meld()���ƣ��ϲ��������Ӧ��������a��b�Ľڵ�ռ䣬�ϲ�֮����������chainA��chainB�ǿձ�������ɾ�������������

    void physicalClear();//����ɾ������Ԫ�أ��ͷ���������ռ�

    void logicalClear();//�߼��������Ԫ�أ����洢�����׽ڵ�ĳ�Ա����ָ��firstNode��Ϊnullptr���ٽ�listSize��Ϊ0

    vector<chainList<T>> *split();//����������չ����a��b��a�а�������Ϊ������Ԫ�أ�b�а�������Ԫ�أ�a��b�Ĵ洢�ռ伴*this�Ĵ洢�ռ�

    void test();//��������˽�к����Ĺ��нӿ�

    void swapNode(int indexA, int indexB);//���������ڵ������

    void insertSort();//���ò������򷨶�����Ԫ�ؽ�������

    void selectionSort();

    void rankSort();

    void bubbleSort();


private:
    void setSize(int newSize);

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
    while (p != header) {
        pointer nextNode = p->next;
        delete p;
        p = nextNode;
    }
    delete p;
    listSize = 0;
}

template<class T>
T &circularListWithHeader<T>::get(int theIndex) const {
    chainList<T>::checkIndex(theIndex, "get");
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
    chainList<T>::checkIndex(theIndex, "erase");
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
    chainList<T>::checkIndex(theIndex, "insert");
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
    chainList<T>::checkIndex(theIndex,"replace");
    this->get(theIndex)=theElement;
}

template<class T>
void circularListWithHeader<T>::removeRange(int beginIndex, int endIndex) {
if(beginIndex>=0&&beginIndex<endIndex&&endIndex<=listSize-1)
{
    pointer pBegin=header->next,pEnd=header->next;
    for(int i=0;i<beginIndex-1;i++)
        pBegin=pBegin->next;
    for(int i=0;i< endIndex-1;i++)
        pEnd=pEnd->next;
    pointer p=pBegin->next,j=pEnd->next,deleteNode= nullptr;
    int count=0;
    while(p!=j->next)
    {
        deleteNode=p;
        p=p->next;
        delete deleteNode;
        count++;
    }


}
}

template<class T>
void circularListWithHeader<T>::swap(chainList<T> &theChain) {
}

template<class T>
void circularListWithHeader<T>::fromList(const arrayList<T> &theArray) {
}

template<class T>
arrayList<T> circularListWithHeader<T>::toList() {
}

template<class T>
void circularListWithHeader<T>::leftShift(int offset) {
}

template<class T>
void circularListWithHeader<T>::reverse() {
}

template<class T>
void circularListWithHeader<T>::meld(chainList<T> &chainA, chainList<T> &chainB) {
}

template<class T>
void circularListWithHeader<T>::physicalClear() {
}

template<class T>
void circularListWithHeader<T>::logicalClear() {
}

template<class T>
vector<chainList<T>> *circularListWithHeader<T>::split() {
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
