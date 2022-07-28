#include <iostream>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\arrayAndVectorList\globalFunction.h"
#include<ctime>

//ȫ��ģ�庯����ʹ�õ��ļ�ǰ����Ҫǰ������
template<class T>
void chainToArray(const chainList<T> &theChain, arrayList<T> &theArray);


void test21();//extendedChainList<T>::split��������
void test22();

void test23();

int main() {

    test23();
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
