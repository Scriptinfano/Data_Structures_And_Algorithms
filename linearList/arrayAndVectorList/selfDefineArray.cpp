#include <iostream>
#include"myIterator.h"//�Զ��������
#include "illegalParameterValue.h"//�쳣�ඨ��
#include "arrayList.hpp"

using namespace std;


void test01();

int main() {
    //������������Ϊ100�����Ա�
    /*
        linerList*x=(linerList)new arrayList<int>(100);
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

    arrayList<int>array(5);
    array.push_back(12);
    array.push_back(23);
    array.push_back(123);
    array.reverse();
    cout<<array;

}
