#include <iostream>
#include"myIterator.h"//自定义迭代器
#include "illegalParameterValue.h"//异常类定义
#include "arrayList.h"

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
    arrayList<char> intArray(10);
    intArray.insert(0, 'f');
    intArray.insert(1, 'g');
    intArray.insert(2, 'd');
    /*
    for (mystd::iterator<char> it(intArray.begin()); it != intArray.end(); ++it) {
        cout << *it << " ";
    }
    */
    /*
    intArray[0]='q';
    cout<<intArray[0];
    intArray[1]=intArray[0];
    cout<<intArray[1];
    */
    arrayList<char> intArray2(10);
    intArray.insert(0, 'f');
    intArray.insert(1, 'g');
    intArray.insert(2, 'd');
    bool judge = intArray != intArray;
    cout << boolalpha << judge;

}
