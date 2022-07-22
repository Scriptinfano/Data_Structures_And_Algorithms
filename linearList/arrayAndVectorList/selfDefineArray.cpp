#include <iostream>
#include"myIterator.h"//自定义迭代器
#include "illegalParameterValue.h"//异常类定义
#include "arrayList.hpp"

using namespace std;


void test01();

int main() {
    //创建两个容量为100的线性表
    /*
        linerList*x=(linerList)new arrayList<int>(100);
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

    arrayList<int>array(5);
    array.push_back(12);
    array.push_back(23);
    array.push_back(123);
    array.reverse();
    cout<<array;

}
