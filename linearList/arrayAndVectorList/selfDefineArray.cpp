#include <iostream>
#include"myIterator.h"//�Զ��������
#include "arrayList.hpp"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\namespaces.h"
using namespace std;
using ExceptionSpace::IllegalParameterValue;


void test01();

int main() {
    //������������Ϊ100�����Ա�
    /*
        LinearList*x=(LinearList)new arrayList<int>(100);
        arrayList<double>y(100);

        arrayList<char>z;
        arrayList<double>w(y);//��������һ�����Ա�
    */
    try {
        test01();
    }
    catch (const IllegalParameterValue &exception) {
        cerr << "�����쳣����ϸ��Ϣ����" << endl;
        exception.OutMessage();
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
    //sort(array.begin(),array.end());
    // sort����Ҫ����ĵ�����֧���������


    cout << array2 << endl;
    cout << array3;
}
