#include <iostream>
#include"myIterator.h"//�Զ��������
#include "illegalParameterValue.h"//�쳣�ඨ��
#include "arrayList.hpp"

using namespace std;


void test01();

int main() {
    //������������Ϊ100�����Ա�
    /*
        linearList*x=(linearList)new arrayList<int>(100);
        arrayList<double>y(100);

        arrayList<char>z;
        arrayList<double>w(y);//��������һ�����Ա�
    */
    try {
        test01();
    }
    catch (const illegalParameterValue &except) {
        cerr << "�����쳣����ϸ��Ϣ����" << endl;
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
    //sort(array.begin(),array.end());//sort����Ҫ����ĵ�����֧���������


    cout << array2 << endl;
    cout << array3;
}
