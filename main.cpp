#include <iostream>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\linearList\arrayAndVectorList\arrayList.hpp"

using namespace std;

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

void test1() {
    stringstream transformer;

    int nonZeroSize = 3;
    string str;
    for (int i = 0; i < nonZeroSize; i++) {
        int row;
        int column;
        double value;

        while (true) {
            cout << "输入第" << i + 1 << "个元素的行标：";
            getline(cin, str);
            cout << "显示刚刚输入的字符串：" << str << endl;
            transformer << str;
            transformer >> row;
            cout << "显示转换后的数据:" << row << endl;
            transformer.clear();
            transformer.sync();

            cout << "输入第" << i + 1 << "个元素的列标：";
            getline(cin, str);
            cout << "显示刚刚输入的字符串：" << str << endl;
            transformer << str;
            transformer >> column;
            cout << "显示转换后的数据:" << column << endl;
            transformer.clear();
            transformer.sync();

            cout << "输入第" << i + 1 << "个元素的值：";
            getline(cin, str);
            cout << "显示刚刚输入的字符串：" << str << endl;
            transformer << str;
            transformer >> value;
            cout << "显示转换后的数据:" << value << endl;
            transformer.clear();
            transformer.sync();

            if (row == 0 || column == 0 || value == 0) {
                cout << "输入的三个数据中有一个或多个不合法不合法，请重新输入" << endl;
                continue;
            } else break;
        }
    }

}

int main() {


    return 0;
}
