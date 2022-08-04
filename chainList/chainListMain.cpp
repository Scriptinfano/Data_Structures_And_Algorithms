#include<iostream>
#include "CircularListWithHeader.h"
#include "extendedChainList.h"
#include "chainListMain.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\arrayAndVectorList\globalFunction.h"
#include<ctime>

//全局模板函数在使用的文件前必须要前向声明
template<class T>
void chainToArray(const chainList<T> &theChain, arrayList<T> &theArray);

void testExtendedChainListSplit();

void testCircularReverse();

void testCircularShift();

void testCircularMeld();

void testChainListRankSort();

void testCircularListWithHeaderRemoveRange();

void testCircularSplit();

void testCircularListWithHeaderLeftShift();

void testCircularSwapContainer();

void testCircularInsertSort();


int main() {
    //setbuf(stdout, NULL);


    return 0;
}

void testExtendedChainListSplit() {
    srand((unsigned int) time(0));
    extendedChainList<int> chain;
    int max = 100, min = 0;
    int randNumber = 0;

    for (int i = 0; i < 10; i++) {
        randNumber = rand() % (max - min + 1) + min;
        chain.push_back(randNumber);
    }
    cout << "原始链表：" << endl;
    cout << chain << endl;
    cout << "分离后：" << endl;
    vector<extendedChainList<int>> *p = chain.split();
    if (p == nullptr)cout << "chain为空" << endl;
    cout << p->at(0) << endl;
    cout << p->at(1) << endl;

}

void testCircularShift() {
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

void testChainListRankSort() {
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

void testCircularListWithHeaderRemoveRange() {
    CircularListWithHeader<int> circular;
    circular.push_back(7);
    circular.push_back(9);
    circular.push_back(8);
    circular.push_back(2);
    circular.push_back(6);
    circular.push_back(5);

    circular.removeRange(2, 4);

    cout << circular;

}

void testCircularListWithHeaderLeftShift() {
    CircularListWithHeader<int> circular;
    circular.push_back(7);
    circular.push_back(9);
    circular.push_back(8);
    circular.push_back(2);
    circular.push_back(6);
    circular.push_back(5);

    circular.leftShift(2);
    cout << circular;

}

void testCircularSwapContainer() {
    CircularListWithHeader<int> circular;
    circular.push_back(7);
    circular.push_back(9);
    circular.push_back(8);
    circular.push_back(2);
    circular.push_back(6);
    circular.push_back(5);

    CircularListWithHeader<int> circular2;
    circular2.push_back(5);
    circular2.push_back(4);
    circular2.push_back(6);
    circular2.push_back(2);
    circular2.push_back(8);
    circular2.push_back(6);

    circular.swapContainer(circular2);
    cout << circular << endl;
    cout << circular2 << endl;


}

void testCircularReverse() {
    CircularListWithHeader<int> circular;
    circular.push_back(7);
    circular.push_back(9);
    circular.push_back(8);
    circular.push_back(2);
    circular.push_back(6);
    circular.push_back(5);
    circular.reverse();
    cout << circular;

}

void testCircularMeld() {

    CircularListWithHeader<int> chain;
    CircularListWithHeader<int> chain2;
    CircularListWithHeader<int> chain3;


    chain.push_back(12);
    chain.push_back(13);
    chain.push_back(14);
    chain.push_back(1);
    chain.push_back(126);
    chain.push_back(123);
    chain.push_back(75);

    chain2.push_back(7);
    chain2.push_back(9);
    chain2.push_back(8);
    chain2.push_back(2);

    chain3.meld(chain, chain2);

    cout << chain3;

}

void testCircularSplit() {

    //元素数为奇数的情况
    CircularListWithHeader<int> chain;

    chain.push_back(12);
    chain.push_back(13);
    chain.push_back(14);
    chain.push_back(1);
    chain.push_back(126);
    chain.push_back(123);
    chain.push_back(75);

    //元素数为偶数的情况
    CircularListWithHeader<int> chain2;
    chain2.push_back(41);
    chain2.push_back(254);
    chain2.push_back(36);
    chain2.push_back(2365);
    chain2.push_back(736);
    chain2.push_back(2693);
    chain2.push_back(856);
    chain2.push_back(417);

    vector<CircularListWithHeader<int>> *p = chain.split();
    for (int i = 0; i < p->size(); i++) {
        cout << p->at(i) << endl;
    }


}

void testCircularInsertSort()
{
    CircularListWithHeader<int> chain;

    chain.push_back(12);
    chain.push_back(13);
    chain.push_back(14);
    chain.push_back(1);
    chain.push_back(126);
    chain.push_back(123);
    chain.push_back(75);

    chain.insertSort();
    cout<<chain;

}