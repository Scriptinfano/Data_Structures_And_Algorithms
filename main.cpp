#include <iostream>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\arrayAndVectorList\arrayList.hpp"

using namespace std;

void test2(){
    int result=-3%20;
    printf("%d",result);
}
template<class T>
class MatrixTerm {
private:
    int row;
    int column;
    T value;
public:
    MatrixTerm(int row, int column, T value) : row(row), column(column), value(value) {}

    MatrixTerm() = default;

    int getRow() const {
        return row;
    }

    int getColumn() const {
        return column;
    }

    T getValue() const {
        return value;
    }

    void setRow(int theRow) {
        this->row = theRow;
    }

    void setColumn(int theColumn) {
        this->column = theColumn;
    }

    void setValue(T theValue) {
        this->value = theValue;
    }
};

template<class T>
class Bag {
public:
    using value_type = T;
    T val;

    Bag(T value) : val(value) {}
};

template<class T>
class Box {
public:
    using value_type = T;
    T val;

    Box(T value) : val(value) {}
};

template<class T>
typename T::value_type unpack(T container) {
    return container.val;
}

int main() {

    test2();

    return 0;
}
void test1(){
    stringstream transformer;

    int nonZeroSize=3;
    string str;
    for (int i = 0; i < nonZeroSize; i++) {
        int row;
        int column;
        double value;

        while (true) {
            cout << "�����" << i + 1 << "��Ԫ�ص��б꣺";
            getline(cin, str);
            cout<<"��ʾ�ո�������ַ�����"<<str<<endl;
            transformer << str;
            transformer >> row;
            cout<<"��ʾת���������:"<<row<<endl;
            transformer.clear();
            transformer.sync();

            cout << "�����" << i + 1 << "��Ԫ�ص��б꣺";
            getline(cin, str);
            cout<<"��ʾ�ո�������ַ�����"<<str<<endl;
            transformer << str;
            transformer >> column;
            cout<<"��ʾת���������:"<<column<<endl;
            transformer.clear();
            transformer.sync();

            cout << "�����" << i + 1 << "��Ԫ�ص�ֵ��";
            getline(cin, str);
            cout<<"��ʾ�ո�������ַ�����"<<str<<endl;
            transformer << str;
            transformer >> value;
            cout<<"��ʾת���������:"<<value<<endl;
            transformer.clear();
            transformer.sync();

            if (row == 0||column==0||value==0) {
                cout << "�����������������һ���������Ϸ����Ϸ�������������" << endl;
                continue;
            } else break;
        }
    }
}
