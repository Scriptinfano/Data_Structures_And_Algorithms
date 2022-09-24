/*
 * ��ϡ�����洢��һ��Ӧ�ã���ͷ�ļ���Ҫ�������һ�����⣺���вɹ����⣬������������
 * ĳ�����г����ڿ�չһ����ڹ˿͹���Ʒ�ֵ��ۺ��о���Ϊ���ռ���1000���˿͵Ĺ������ݣ���Щ����
 * ��֯��һ������purchases������purchases(i,j)��ʾ�˿�j���������Ʒi���������ٶ��ó���
 * ��10000�ֲ�ͬ����Ʒ����ôpurchases����һ��10000*1000�ľ��󡣳����г���һ��10000*1��
 * �۸����price��price(i)������Ʒi�ĵ��ۡ�����spent=transpose(purchases)*price��һ��
 * 1000*1�ľ���������ÿ���˿������ѵĹ����ʽ�
 *
 * �õ������Ա�����:
 * �����������޹���ϡ�����ķ�0Ԫ��ӳ�䵽һ�����Ա��У�Ϊ�ؽ�����ṹ�������¼ÿ����0Ԫ�ص��кź��кţ����
 * ����Ԫ����������row��col��value������ṹ����������Ϊ��Ա����*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

static stringstream transformer;//��ȫ�ֱ��������ڱ��ļ���

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
        out << "�������������rows=" << theMatrix.rows << " columns=" << theMatrix.columns << endl;
        out << "��0��Ԫ�ظ���=" << theMatrix.terms.size() << endl;
        for (auto item = theMatrix.terms.begin(); item != theMatrix.terms.end(); item++) {
            out << "a(" << (*item).getRow() << "," << (*item).getColumn() << ")=" << (*item).getValue() << endl;
        }
        return out;
    }

    friend std::istream &operator>>(istream &in, SparseMatrix<T> &theMatrix) {
        //��֤Ԫ���Ƿ������������룬ÿ��Ԫ�ص��кź��к��Ƿ���Ч��ÿ�������Ԫ���Ƿ����
        int nonZeroSize = 0;
        string str;
        while (true) {
            cout << "�������Ԫ�صĸ�����";
            getline(in, str);
            transformer << str;
            transformer >> nonZeroSize;
            if (nonZeroSize == 0) {
                cout << "��������ݲ��Ϸ�������������" << endl;
                continue;
            } else if(nonZeroSize>theMatrix.rows*theMatrix.columns){
                cout<<"����Ԫ�صĸ������ô��ھ����е�Ԫ������"<<endl;
            }else
                break;
        }
        for (int i = 0; i < nonZeroSize; i++) {
            int row;
            int column;
            T value;

            while (true) {
                cout << "�����" << i + 1 << "��Ԫ�ص��б꣺";
                getline(in, str);
                transformer << str;
                transformer >> row;
                transformer.clear();
                transformer.sync();

                cout << "�����" << i + 1 << "��Ԫ�ص��б꣺";
                getline(in, str);
                transformer << str;
                transformer >> column;
                transformer.clear();
                transformer.sync();

                cout << "�����" << i + 1 << "��Ԫ�ص�ֵ��";
                getline(in, str);
                transformer << str;
                transformer >> value;
                transformer.clear();
                transformer.sync();

                if (row == 0||column==0||value==0) {
                    cout << "�����������������һ���������Ϸ����Ϸ�������������" << endl;
                    continue;
                } else break;
            }
            theMatrix.terms.push_back(*(new MatrixTerm<T>(row, column, value)));
        }
        return in;
    }

public :
    SparseMatrix(int rows, int columns) : rows(rows), columns(columns) {}
//TODO ����ΪSparseMatrix��дʣ�µĴ���
    void transpose(SparseMatrix<T> &theMatrix) {

    }

    void add(SparseMatrix<T> &theMatrixA, SparseMatrix<T> &theMatrixB) {

    }

private:
    int rows;//���������
    int columns;//���������
    std::vector<MatrixTerm<T>> terms;//��0���
};