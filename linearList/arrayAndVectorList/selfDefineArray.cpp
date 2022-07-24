#include <iostream>
#include"myIterator.h"//自定义迭代器
#include "illegalParameterValue.h"//异常类定义
#include "arrayList.hpp"

using namespace std;


void test01();

int main() {
    //创建两个容量为100的线性表
    /*
        linearList*x=(linearList)new arrayList<int>(100);
        arrayList<double>y(100);

        arrayList<char>z;
        arrayList<double>w(y);//拷贝构造一个线性表
    */
    try {
        test01();
    }
    catch (const illegalParameterValue &except) {
        cerr << "触发异常，详细信息如下" << endl;
        except.outPutMessage();
    }

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
    //sort(array.begin(),array.end());//sort函数要求传入的迭代器支持随机访问


    cout << array2 << endl;
    cout << array3;
}
