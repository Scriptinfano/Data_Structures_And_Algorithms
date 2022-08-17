#include <iostream>
#include"myIterator.h"//自定义迭代器
#include "arrayList.hpp"
using namespace std;


void test01();

int main() {
    setbuf(stdout, nullptr);
    try{
        test01();
    }catch(const outOfBounds& theException){
        cerr<<theException.what();
    }catch(const IllegalParameterValue& theException){
        cerr<<theException.what();
    }

    return 0;
}

void test01() {

    arrayList<int> array(5);
    array.push_back(12);
    array.push_back(23);//
    array.push_back(123);
    array.push_back(42);//
    array.push_back(89);

    mystd::iterator<int>iter_begin(array.address(1));
    mystd::iterator<int>iter_end(array.address(3));

    array.removeRange(iter_begin,iter_end);
    cout<<array;
}
