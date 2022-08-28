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
    T *element;//指向一维数组的指针，用一维数组来保存二维矩阵，属于矩阵的压缩存储
    bool initialized;//检测矩阵在被构造之后是否执行了初始化
public:
    matrix(int theRows = 0, int theColumns = 0) {
        if (theRows < 0 || theColumns < 0)throw IllegalParameterValue("行数与列数必须大于0");
        if ((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0)) {
            //判断条件的意思是两者要么都为0或者两者都不为0才能满足条件
            throw IllegalParameterValue("判断条件的意思是两者要么都为0或者两者都不为0才能满足条件");
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

    //访问私有数据接口
    int getRows() const { return rows; }

    int getColumns() const { return columns; }

    //重载运算符函数
    T &operator()(int i, int j) const;//得到索引为i,j的索引元素

    matrix<T> &operator=(const matrix<T> &theMatrix);//矩阵之间的赋值操作

    matrix<T> operator+(const matrix<T> &theMatrix) const;//矩阵加法

    matrix<T> operator-(const matrix<T> &theMatrix) const;//矩阵减法

    matrix<T> operator*(const matrix<T> &theMatrix) const;//矩阵乘法

    matrix<T> &operator+=(const T &theElement) const;//每个矩阵元素加上固定的值

    matrix<T> &operator-=(const T &theElement) const;//每个矩阵元素减去固定的值


    //其他常规接口
    void initialize(T *theElements, const int &row, const int &column);//初始化矩阵，将传入的二维数组映射到内部的一维数组中
    void initialize();//重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    int size() const {
        if (!initialized)throw uninitializedMatrix();
        return rows * columns;
    }//返回矩阵元素个数
    matrix<T> transpose();//矩阵的转置

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
    if (initialized)throw reInitializedMatrix();//如果矩阵已经初始化了就不需要再初始化了
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            element[i * columns + j] = 0;
        }
    }
    initialized = true;
}
