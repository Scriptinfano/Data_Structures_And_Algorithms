#include <iostream>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\arrayAndVectorList\globalFunction.h"

//全局模板函数在使用的文件前必须要前向声明
template<class T>
void chainToArray(const chainList<T> &theChain, arrayList<T> &theArray);

int main() {
    extendedChainList<int> chain;
    chain.push_back(12);
    chain.push_back(43);
/*
    chain.push_back(73);
    chain.push_back(62);
    chain.push_back(568);
*/
    extendedChainList<int> chainB;
    chainB.push_back(14);
    chainB.push_back(26);
    chainB.push_back(29);
/*
    chainB.push_back(265);
    chainB.push_back(321);
*/
    extendedChainList<int> chainC;
    chainC.meld(chain, chainB);
    cout << chainC;


    //chain.leftShift(2);
    //chain.reverse();

/*
    arrayList<int> array(chain.toList());
    cout<<array;
*/

/*

    array.push_back(12);
    array.push_back(12);
    array.push_back(12);
    array.push_back(12);
    array.push_back(12);
    array.push_back(12);
*/


    //cout<<array.capacity();
    //chain.fromList(array);
    //chainToArray<int>(chain,array);
    //cout << chain;



    return 0;
}
