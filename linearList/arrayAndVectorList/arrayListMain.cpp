#include <iostream>
#include"myIterator.h"//自定义迭代器
#include "arrayList.hpp"
using namespace std;


void test01();

int main() {
    return 0;
}

void test01() {

    arrayList<int> array(5);
    arrayList<int> array2;
    arrayList<int> array3;

    array.push_back(12);
    array.push_back(23);
    array.push_back(123);
    array.push_back(42);
    array.push_back(89);

    array.split(array2, array3);

    //array3.merge(array,array2);
    //array3.meld(array, array2);
    //sort(array.begin(),array.end());
    // sort函数要求传入的迭代器支持随机访问


    cout << array2 << endl;
    cout << array3;
}
