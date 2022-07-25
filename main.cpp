#include <iostream>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\arrayAndVectorList\globalFunction.h"

//全局模板函数在使用的文件前必须要前向声明
template<class T>
void chainToArray(const chainList<T> &theChain, arrayList<T> &theArray);

int main() {
    chainList<int> chain;
    chain.push_back(12);
    chain.push_back(43);
    chain.push_back(73);
    chain.push_back(62);
    chain.push_back(568);

    arrayList<int> array(chain.toList());
    cout<<array;

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
    //cout<<chain;

}
