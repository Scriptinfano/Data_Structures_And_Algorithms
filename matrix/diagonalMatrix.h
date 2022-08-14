/*本程序主要演示特殊矩阵的压缩存储方法及其对应的映射函数
 * */
#pragma once

#include <iostream>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\namespaces.h"

using namespace std;
using namespace ExceptionSpace;

//特殊矩阵的抽象基类，该矩阵为方阵，派生自该矩阵的也都是方阵
template<class T>
class virtualDiagonalMatrix {
protected:
    int dimension;
    T *element;
    bool initialized;
public:
    virtual T get(const int &i, const int &j) const = 0;

    virtual void set(const int &i, const int &j, const T &theElement) = 0;

    virtual virtualDiagonalMatrix<T> operator+(const virtualDiagonalMatrix<T> &theMatrix) const = 0;//矩阵加法

    virtual virtualDiagonalMatrix<T> operator-(const virtualDiagonalMatrix<T> &theMatrix) const = 0;//矩阵减法

    virtual virtualDiagonalMatrix<T> operator*(const virtualDiagonalMatrix<T> &theMatrix) const = 0;//矩阵乘法

    T operator()(int i, int j) const = 0;//得到索引为i,j的索引元素

    //其他常规接口
    void initialize(T *theElements, const int &theDimension) = 0;//初始化矩阵，将传入的二维数组映射到内部的一维数组中

    void initialize() = 0;//重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零

    int size() const = 0;//返回矩阵中元素的个数

    virtualDiagonalMatrix<T> transpose() = 0;//矩阵的转置

};

//对角矩阵（此矩阵为方阵，只有对角线上的元素是非零元素）
template<class T>
class diagonalMatrix : public virtualDiagonalMatrix<T> {
public:
    diagonalMatrix(int theDimention = 10) {
        if (theDimention < 1) {
            throw IllegalParameterValue("matrix的大小必须大于0");
        }
        this->dimension = theDimention;//在模板继承中要访问基类中的数据必须使用this标注
        this->element = new T[this->dimension];
    }

    diagonalMatrix(const diagonalMatrix<T> &theMatrix) {
        if (!this->initialized)throw uninitializedMatrix();
        this->dimension = theMatrix.dimension;
        this->element = new T[this->dimension];
        copy(theMatrix.element, theMatrix.element + this->dimension, this->element);
    }

    ~diagonalMatrix() { delete[]virtualDiagonalMatrix<T>::element; }

    //常规接口
    virtual T operator()(int i, int j) const//获取下标为(i,j)的矩阵元素
    {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i == j)return virtualDiagonalMatrix<T>::element[i - 1];//对角线上的元素才是非零元素
        else return 0;
    }

    virtual T get(const int &i, const int &j) const//获取下标为(i,j)的矩阵元素
    {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i == j)return virtualDiagonalMatrix<T>::element[i - 1];//对角线上的元素才是非零元素
        else return 0;
    }

    virtual void set(const int &i, const int &j, const T &theElement)//将下标为i,j的元素设为另一个值
    {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension)
            throw matrixIndexOutOfBounds();
        if (i == j)virtualDiagonalMatrix<T>::element[i - 1] = theElement;
        else {
            if (theElement != 0)throw IllegalParameterValue("设值失败，因为在对角矩阵中，非对角线上的元素必须是0");
        }
    }

    //矩阵的加减乘操作

    //矩阵加法
    virtual diagonalMatrix<T> operator+(const virtualDiagonalMatrix<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();

        if (this->dimension != theMatrix.dimension)throw matrixSizeMismatchOfPlus();
        diagonalMatrix<T> result(this->dimension);
        result.initialize();
        for (int i = 0; i < this->dimension; i++) {
            //result.element[i] = element[i] + theMatrix.element[i];
            result.set(i, i, this->element[i * this->dimension + i] + theMatrix.element[i * theMatrix.dimension + i]);
        }
        return result;
    }

    //矩阵减法
    virtual diagonalMatrix<T> operator-(const virtualDiagonalMatrix<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this->dimension != theMatrix.dimension)throw matrixSizeMismatchOfPlus();
        diagonalMatrix<T> result(this->dimension);
        result.initialize();
        for (int i = 0; i < this->dimension; i++) {
            //result.element[i] = element[i] + theMatrix.element[i];
            result.set(i, i, this->element[i * this->dimension + i] - theMatrix.element[i * theMatrix.dimension + i]);
        }
        return result;

    }

    //矩阵乘法
    virtual diagonalMatrix<T> operator*(const virtualDiagonalMatrix<T> &theMatrix) const {

    }

    //其他常规接口
    //初始化矩阵，将传入的二维数组映射到内部的一维数组中
    virtual void initialize(T *theElements, const int &theDimension) {
        if (this->initialized)throw reinitializedMatrix();
        if (theDimension != this->dimension)throw matrixSizeMismatchOfInitialize();
        int index = 0;
        for (int i = 0; i < theDimension; i++) {
            this->element[index++] = theElements[i * theDimension + i];
        }
        this->initialized = true;
    }

    //重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    virtual void initialize() {
        if (this->initialized)throw reinitializedMatrix();
        int index = 0;
        for (int i = 0; i < this->dimension; i++) {
            this->element[index++] = 0;
        }
        this->initialized = true;
    }

    //返回矩阵中元素的个数
    virtual int size() const {
        return pow(this->dimension, 2);
    }

    //矩阵的转置
    virtual diagonalMatrix<T> transpose() {

    }


};

//三对角矩阵（此矩阵为方阵），本三对角矩阵采用逐对角线映射的方式压缩存储，还有另外两种方法压缩存储三对角矩阵，即行主映射和列主映射
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

    tripleDiagonalMatrix(const tripleDiagonalMatrix<T> &theMatrix) {
        if (!this->initialized)throw uninitializedMatrix();
        this->dimension = theMatrix.dimension;
        this->element = new T[3 * this->dimension - 2];//三对角矩阵元素数3*n-2
        copy(theMatrix.element, theMatrix.element + this->dimension, this->element);
    }

    ~tripleDiagonalMatrix() { delete[]virtualDiagonalMatrix<T>::element; }

    virtual T operator()(int i, int j) const//获取下标为(i,j)的矩阵元素
    {
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
            default:
                return 0;
        }
    }

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
            default:
                return 0;
        }
    }

    //将下标为i,j的元素设为另一个值
    void set(const int &i, const int &j, const T &theElement) {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension)
            throw matrixIndexOutOfBounds();
        switch (i - j) {
            case 1://i-j=1时为下对角线
                this->element[i - 2] = theElement;
            case 0:
                this->element[this->dimension + i - 2] = theElement;
            case -1:
                this->element[2 * this->element + i - 2] = theElement;
        }
    }

    //矩阵的加减乘操作
    virtual tripleDiagonalMatrix<T> operator+(const virtualDiagonalMatrix<T> &theMatrix) const {
    }
//矩阵加法

    virtual tripleDiagonalMatrix<T> operator-(const virtualDiagonalMatrix<T> &theMatrix) const {
    }
//矩阵减法

    virtual tripleDiagonalMatrix<T> operator*(const virtualDiagonalMatrix<T> &theMatrix) const {
    }
//矩阵乘法


    //其他常规接口
    //初始化矩阵，将传入的二维数组映射到内部的一维数组中
    virtual void initialize(T *theElements, const int &theDimension) {
    }

    //重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    virtual void initialize() {
    }

    //返回矩阵中元素的个数
    virtual int size() const {
    }

    //矩阵的转置
    virtual tripleDiagonalMatrix<T> transpose() {
    }

};

template<class T>
class lowerTriangularMatrix : public virtualDiagonalMatrix<T> {
public:
    lowerTriangularMatrix(int theDimention = 10) {
        if (theDimention < 1) {
            throw IllegalParameterValue("matrix的大小必须大于0");
        }
        this->dimension = theDimention;
        this->element = new T[this->dimension * (this->dimension + 1) /
                              2];//上三角矩阵和下三角矩阵的元素总数都是n*(n+1)/2
    }

    lowerTriangularMatrix(const lowerTriangularMatrix<T> &theMatrix) {
        if (!this->initialized)throw uninitializedMatrix();
        this->dimension = theMatrix.dimension;
        this->element = new T[this->dimension * (this->dimension + 1) / 2];//下三角矩阵元素数n*(n+1)/2
        copy(theMatrix.element, theMatrix.element + this->dimension, this->element);
    }

    ~lowerTriangularMatrix() { delete[]virtualDiagonalMatrix<T>::element; }

    virtual T operator()(int i, int j) const//获取下标为(i,j)的矩阵元素
    {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i >= j)return this->element[(i * (i - 1)) / 2 + j - 1];//下三角矩阵行主映射函数i*(i-1)/2+(j-1)
        else return 0;
    }

    //常规接口
    T get(const int &i, const int &j) const//获取下标为(i,j)的矩阵元素
    {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i >= j)return this->element[(i * (i - 1)) / 2 + j - 1];
        else return 0;
    }

    void set(const int &i, const int &j, const T &theElement)//将下标为i,j的元素设为另一个值
    {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension)
            throw matrixIndexOutOfBounds();
        if (i >= j)//下三角区的元素i>=j
            this->element[i * (i - 1) / 2 + j - 1] = theElement;
        else if (theElement != 0)throw IllegalParameterValue("下三角矩阵中不在下三角区的元素必须为0，不得设置为其他值");
    }

    //矩阵的加减乘操作
    virtual lowerTriangularMatrix<T> operator+(const virtualDiagonalMatrix<T> &theMatrix) const {

    }
//矩阵加法

    virtual lowerTriangularMatrix<T> operator-(const virtualDiagonalMatrix<T> &theMatrix) const {
    }
//矩阵减法

    virtual lowerTriangularMatrix<T> operator*(const virtualDiagonalMatrix<T> &theMatrix) const {
    }
//矩阵乘法

    //其他常规接口
    //初始化矩阵，将传入的二维数组映射到内部的一维数组中
    virtual void initialize(T *theElements, const int &theDimension) {
    }

    //重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    virtual void initialize() {
    }

    //返回矩阵中元素的个数
    virtual int size() const {
    }

    //矩阵的转置
    virtual lowerTriangularMatrix<T> transpose() {
    }


};