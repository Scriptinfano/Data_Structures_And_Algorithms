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
            throw IllegalParameterValue("matrix�Ĵ�С�������0");
        }
        virtualDiagonalMatrix<T>::dimension = theDimention;
        virtualDiagonalMatrix<T>::element = new T[virtualDiagonalMatrix<T>::dimension];
    }

    ~diagonalMatrix() { delete[]virtualDiagonalMatrix<T>::element; }

    //����ӿ�

    //��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    T get(const int &i, const int &j) const {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i == j)return virtualDiagonalMatrix<T>::element[i - 1];//�Խ����ϵ�Ԫ�ز��Ƿ���Ԫ��
        else return 0;
    }

    //���±�Ϊi,j��Ԫ����Ϊ��һ��ֵ
    void set(const int &i, const int &j, const T &theElement) {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension)
            throw matrixIndexOutOfBounds();
        if (i == j)virtualDiagonalMatrix<T>::element[i - 1] = theElement;
        else if (theElement != 0)throw IllegalParameterValue("�ǶԽ����ϵ�Ԫ�ر�����0");
    }
};

template<class T>
class tripleDiagonalMatrix : public virtualDiagonalMatrix<T> {
public:
    tripleDiagonalMatrix(int theDimention = 10) {
        if (theDimention < 1) {
            throw IllegalParameterValue("matrix�Ĵ�С�������0");
        }
        virtualDiagonalMatrix<T>::dimension = theDimention;
        virtualDiagonalMatrix<T>::element = new T[3 * this->dimension - 2];//��ģ��̳��У�ģ������Ҫ����ģ�����ĳ�Աֻ��ͨ�����޶�������this��ע�ķ�ʽ����

    }

    ~tripleDiagonalMatrix() { delete[]virtualDiagonalMatrix<T>::element; }

    //��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    T get(const int &i, const int &j) const {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension)
            throw matrixIndexOutOfBounds();
        //ȷ��Ҫ���ص�Ԫ��
        switch (i - j) {
            case 1://i-j=1ʱΪ�¶Խ���
                return this->element[i - 2];
            case 0://i-j=0ʱΪ���Խ���
                return this->element[this->dimension + i - 2];
            case -1:
                return this->element[2 * this->dimension + i - 2];
            default:return 0;
        }
    }

    //���±�Ϊi,j��Ԫ����Ϊ��һ��ֵ
    void set(const int &i, const int &j, const T &theElement) {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension)
            throw matrixIndexOutOfBounds();


    }

};