#include <iostream>
#include"myIterator.h"//�Զ��������
#include "illegalParameterValue.h"//�쳣�ඨ��
#include "arrayList.h"

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
