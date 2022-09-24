/*
 * 对稀疏矩阵存储的一个应用，此头文件主要用来解决一个问题：超市采购问题，问题描述如下
 * 某超级市场正在开展一项关于顾客购物品种的综合研究。为此收集了1000个顾客的购物数据，这些数据
 * 组织成一个矩阵purchases，其中purchases(i,j)表示顾客j所购买的商品i的数量。假定该超市
 * 有10000种不同的商品，那么purchases将是一个10000*1000的矩阵。超级市场有一个10000*1的
 * 价格矩阵price，price(i)代表商品i的单价。矩阵spent=transpose(purchases)*price是一个
 * 1000*1的矩阵，它给出每个顾客所花费的购物资金
 *
 * 用单个线性表描述:
 * 按行主次序将无规则稀疏矩阵的非0元素映射到一个线性表中，为重建矩阵结构，必须记录每个非0元素的行号和列号，因此
 * 数组元素有三个域：row、col、value。定义结构将三个域作为成员变量*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

static stringstream transformer;//将全局变量限制在本文件中

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
class SparseMatrix {
    friend std::ostream &operator<<(ostream &out, SparseMatrix<T> &theMatrix) {
        out << "输出矩阵特征：rows=" << theMatrix.rows << " columns=" << theMatrix.columns << endl;
        out << "非0项元素个数=" << theMatrix.terms.size() << endl;
        for (auto item = theMatrix.terms.begin(); item != theMatrix.terms.end(); item++) {
            out << "a(" << (*item).getRow() << "," << (*item).getColumn() << ")=" << (*item).getValue() << endl;
        }
        return out;
    }

    friend std::istream &operator>>(istream &in, SparseMatrix<T> &theMatrix) {
        //验证元素是否按行主次序输入，每个元素的行号和列号是否有效，每个输入的元素是否非零
        int nonZeroSize = 0;
        string str;
        while (true) {
            cout << "输入非零元素的个数：";
            getline(in, str);
            transformer << str;
            transformer >> nonZeroSize;
            if (nonZeroSize == 0) {
                cout << "输入的数据不合法，请重新输入" << endl;
                continue;
            } else if(nonZeroSize>theMatrix.rows*theMatrix.columns){
                cout<<"非零元素的个数不得大于矩阵中的元素总数"<<endl;
            }else
                break;
        }
        for (int i = 0; i < nonZeroSize; i++) {
            int row;
            int column;
            T value;

            while (true) {
                cout << "输入第" << i + 1 << "个元素的行标：";
                getline(in, str);
                transformer << str;
                transformer >> row;
                transformer.clear();
                transformer.sync();

                cout << "输入第" << i + 1 << "个元素的列标：";
                getline(in, str);
                transformer << str;
                transformer >> column;
                transformer.clear();
                transformer.sync();

                cout << "输入第" << i + 1 << "个元素的值：";
                getline(in, str);
                transformer << str;
                transformer >> value;
                transformer.clear();
                transformer.sync();

                if (row == 0||column==0||value==0) {
                    cout << "输入的三个数据中有一个或多个不合法不合法，请重新输入" << endl;
                    continue;
                } else break;
            }
            theMatrix.terms.push_back(*(new MatrixTerm<T>(row, column, value)));
        }
        return in;
    }

public :
    SparseMatrix(int rows, int columns) : rows(rows), columns(columns) {}
//TODO 继续为SparseMatrix编写剩下的代码
    void transpose(SparseMatrix<T> &theMatrix) {

    }

    void add(SparseMatrix<T> &theMatrixA, SparseMatrix<T> &theMatrixB) {

    }

private:
    int rows;//矩阵的行数
    int columns;//矩阵的列数
    std::vector<MatrixTerm<T>> terms;//非0项表
};