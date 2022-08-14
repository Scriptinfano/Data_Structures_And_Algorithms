#pragma once

#include <iostream>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\namespaces.h"

using namespace std;
using namespace ExceptionSpace;

template<class T>
class virtualDiagonalMatrix {
protected:
    int dimension;
    T *element;
public:
    virtual T get(const int &i, const int &j) const = 0;


    virtual void set(const int &i, const int &j, const T &theElement) = 0;
};

template<class T>
class diagonalMatrix : public virtualDiagonalMatrix<T> {
public:
    diagonalMatrix(int theDimention = 10) {
        if (theDimention < 1) {
            throw IllegalParameterValue("matrix的大小必须大于0");
        }
        virtualDiagonalMatrix<T>::dimension = theDimention;
        virtualDiagonalMatrix<T>::element = new T[virtualDiagonalMatrix<T>::dimension];
    }

    ~diagonalMatrix() { delete[]virtualDiagonalMatrix<T>::element; }

    //常规接口

    //获取下标为(i,j)的矩阵元素
    T get(const int &i, const int &j) const {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i == j)return virtualDiagonalMatrix<T>::element[i - 1];//对角线上的元素才是非零元素
        else return 0;
    }

    //将下标为i,j的元素设为另一个值
    void set(const int &i, const int &j, const T &theElement) {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension)
            throw matrixIndexOutOfBounds();
        if (i == j)virtualDiagonalMatrix<T>::element[i - 1] = theElement;
        else if (theElement != 0)throw IllegalParameterValue("非对角线上的元素必须是0");
    }
};

template<class T>
class tripleDiagonalMatrix : public virtualDiagonalMatrix<T> {
public:
    tripleDiagonalMatrix(int theDimention = 10) {
        if (theDimention < 1) {
            throw IllegalParameterValue("matrix的大小必须大于0");
        }
        virtualDiagonalMatrix<T>::dimension = theDimention;
        virtualDiagonalMatrix<T>::element = new T[3 * this->dimension - 2];//在模板继承中，模板子类要访问模板基类的成员只能通过类限定符或用this标注的方式访问

    }

    ~tripleDiagonalMatrix() { delete[]virtualDiagonalMatrix<T>::element; }

    //获取下标为(i,j)的矩阵元素
    T get(const int &i, const int &j) const {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension)
            throw matrixIndexOutOfBounds();
        //确定要返回的元素
        switch (i - j) {
            case 1://i-j=1时为下对角线
                return this->element[i - 2];
            case 0://i-j=0时为主对角线
                return this->element[this->dimension + i - 2];
            case -1:
                return this->element[2 * this->dimension + i - 2];
            default:return 0;
        }
    }

    //将下标为i,j的元素设为另一个值
    void set(const int &i, const int &j, const T &theElement) {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension)
            throw matrixIndexOutOfBounds();


    }

};