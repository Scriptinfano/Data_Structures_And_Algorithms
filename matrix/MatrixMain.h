#pragma once

#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"
#include <iostream>
#include <algorithm>

using namespace std;
using namespace ExceptionSpace;

template<class T>
class matrix {

    friend ostream &operator<<(ostream &out, const matrix<T> &theMatrix) {
        for (int i = 0; i < theMatrix.size(); i++) {
            out << theMatrix.element[i] << " ";
            if ((i + 1) % theMatrix.columns == 0)out << endl;
        }
    }

private:
    int rows;
    int columns;
    T *element;//ָ��һά�����ָ�룬��һά�����������ά�������ھ����ѹ���洢
    bool initialized;//�������ڱ�����֮���Ƿ�ִ���˳�ʼ��
public:
    matrix(int theRows = 0, int theColumns = 0) {
        if (theRows < 0 || theColumns < 0)throw IllegalParameterValue("�����������������0");
        if ((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0)) {
            //�ж���������˼������Ҫô��Ϊ0�������߶���Ϊ0������������
            throw IllegalParameterValue("�ж���������˼������Ҫô��Ϊ0�������߶���Ϊ0������������");
        }
        rows = theRows;
        columns = theColumns;
        element = new T[theColumns * theRows];
        initialized = false;
    }

    matrix(const matrix<T> &theMatrix) {
        if (!initialized)throw uninitializedMatrix();
        rows = theMatrix.rows;
        columns = theMatrix.columns;
        element = new T[rows * columns];
        copy(theMatrix.element, theMatrix.element + rows * columns, element);
    }

    ~matrix() { delete[]element; }

    //����˽�����ݽӿ�
    int getRows() const { return rows; }

    int getColumns() const { return columns; }

    //�������������
    T &operator()(int i, int j) const;//�õ�����Ϊi,j������Ԫ��

    matrix<T> &operator=(const matrix<T> &theMatrix);//����֮��ĸ�ֵ����

    matrix<T> operator+(const matrix<T> &theMatrix) const;//����ӷ�

    matrix<T> operator-(const matrix<T> &theMatrix) const;//�������

    matrix<T> operator*(const matrix<T> &theMatrix) const;//����˷�

    matrix<T> &operator+=(const T &theElement) const;//ÿ������Ԫ�ؼ��Ϲ̶���ֵ

    matrix<T> &operator-=(const T &theElement) const;//ÿ������Ԫ�ؼ�ȥ�̶���ֵ


    //��������ӿ�
    void initialize(T *theElements, const int &row, const int &column);//��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������
    void initialize();//���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������
    int size() const {
        if (!initialized)throw uninitializedMatrix();
        return rows * columns;
    }//���ؾ���Ԫ�ظ���
    matrix<T> transpose();//�����ת��

};

template<class T>
T &matrix<T>::operator()(int i, int j) const {
    if (!initialized)throw uninitializedMatrix();
    if (i < 1 || i > rows || j < 1 || j > columns) {
        throw matrixIndexOutOfBounds();
    }
    return element[(i - 1) * columns + (j - 1)];
}

template<class T>
matrix<T> &matrix<T>::operator=(const matrix<T> &theMatrix) {
    if (!initialized || !theMatrix.initialized)throw uninitializedMatrix();

    if (this != &theMatrix) {
        delete[]element;
        rows = theMatrix.rows;
        columns = theMatrix.columns;
        element = new T[rows * columns];
        copy(theMatrix.element, theMatrix.element + rows * columns, element);

    }
    return *this;
}

template<class T>
matrix<T> matrix<T>::operator+(const matrix<T> &theMatrix) const {
    if (!initialized || !theMatrix.initialized)throw uninitializedMatrix();

    if (rows != theMatrix.rows || columns != theMatrix.columns)throw matrixSizeMismatchOfPlus();
    matrix<T> result(rows, columns);
    result.initialize();
    for (int i = 0; i < rows * columns; i++) {
        result.element[i] = element[i] + theMatrix.element[i];
    }
    return result;
}

template<class T>
matrix<T> matrix<T>::operator-(const matrix<T> &theMatrix) const {
    if (!initialized || !theMatrix.initialized)throw uninitializedMatrix();

    if (rows != theMatrix.rows || columns != theMatrix.columns)throw matrixSizeMismatchOfSubtraction();
    matrix<T> result(rows, columns);
    result.initialized();
    for (int i = 0; i < rows * columns; i++) {
        result.element[i] = element[i] - theMatrix.element[i];
    }
    return result;
}

template<class T>
matrix<T> matrix<T>::operator*(const matrix<T> &theMatrix) const {
    if (!initialized || !theMatrix.initialized)throw uninitializedMatrix();
    if (columns != theMatrix.rows)throw matrixSizeMismatchOfMultiply();
    matrix<T> temp(rows, theMatrix.columns);
    temp.initialize();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < theMatrix.columns; j++) {
            T sum = 0;
            for (int k = 0; k < columns; k++) {
                sum += element[i * columns + k] * theMatrix.element[k * theMatrix.columns + j];
            }
            temp(i + 1, j + 1) = sum;
        }
    }
    return temp;
}

template<class T>
matrix<T> &matrix<T>::operator+=(const T &theElement) const {
    if (!initialized)throw uninitializedMatrix();

    for (int i = 0; i < rows * columns; i++)
        element[i] += theElement;
    return *this;
}

template<class T>
void matrix<T>::initialize(T *theElements, const int &row, const int &column) {
    if (initialized)throw reInitializedMatrix();
    if (row != rows || column != columns)throw matrixSizeMismatchOfInitialize();
    int index = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            element[index] = theElements[i * column + j];
            index++;
        }
    }
    initialized = true;
}

template<class T>
matrix<T> &matrix<T>::operator-=(const T &theElement) const {
    if (!initialized)throw uninitializedMatrix();

    for (int i = 0; i < rows * columns; i++)
        element[i] -= theElement;
    return *this;

}

template<class T>
matrix<T> matrix<T>::transpose() {
    if (!initialized)throw uninitializedMatrix();
    matrix<T> temp(columns, rows);
    temp.initialize();
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            temp(j + 1, i + 1) = element[i * columns + j];
        }
    }
    return temp;
}

template<class T>
void matrix<T>::initialize() {
    if (initialized)throw reInitializedMatrix();//��������Ѿ���ʼ���˾Ͳ���Ҫ�ٳ�ʼ����
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            element[i * columns + j] = 0;
        }
    }
    initialized = true;
}
