#include<iostream>
#include"circularListWithHeader.h"
#include"extendedChainList.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\arrayAndVectorList\globalFunction.h"
#include<ctime>

//ȫ��ģ�庯����ʹ�õ��ļ�ǰ����Ҫǰ������
template<class T>
void chainToArray(const chainList<T> &theChain, arrayList<T> &theArray);


void test21();//extendedChainList<T>::split��������
void test22();

void test23();

void test27_3();//���Լ�������
void testRemoveRange();

int main() {
    testRemoveRange();

    return 0;
}

void test21() {
    srand((unsigned int) time(0));
    extendedChainList<int> chain;
    int max = 100, min = 0;
    int randNumber = 0;

    for (int i = 0; i < 10; i++) {
        randNumber = rand() % (max - min + 1) + min;
        chain.push_back(randNumber);
    }
    cout << "ԭʼ����" << endl;
    cout << chain << endl;
    cout << "�����" << endl;
    vector<extendedChainList<int>> *p = chain.split();
    if (p == nullptr)cout << "chainΪ��" << endl;
    cout << p->at(0) << endl;
    cout << p->at(1) << endl;

}

void test22() {
    chainList<int> chain;
    chain.push_back(7);
    chain.push_back(3);
    chain.push_back(9);
    chain.push_back(8);
    chain.push_back(2);
    chain.push_back(6);

    vector<chainList<int>> *p = chain.split();
    cout << p->at(0) << endl;
}

void test23() {
    extendedChainList<int> chain;
    chain.push_back(7);
    chain.push_back(3);
    chain.push_back(9);
    chain.push_back(8);
    chain.push_back(2);
    chain.push_back(6);
    chain.circularShift(8);
    cout << chain;
}

void test27_3() {
    chainList<int> chain;

    chain.push_back(7);
    chain.push_back(3);
    chain.push_back(9);
    chain.push_back(8);
    chain.push_back(2);
    chain.push_back(6);

    chain.rankSort();

    cout << chain;

}

void testRemoveRange() {
    circularListWithHeader<int> circular;
    circular.push_back(7);
    circular.push_back(9);
    circular.push_back(8);
    circular.push_back(2);
    circular.push_back(6);
    circular.push_back(5);

    circular.removeRange(2, 4);

    cout<<circular;

}
