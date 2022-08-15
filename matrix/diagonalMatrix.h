/*本程序主要演示特殊矩阵的压缩存储方法及其对应的映射函数
 *在设计矩阵类时要注意矩阵的行下标和列下标都是从1开始的，和数组从0开始是不一样的 */
#pragma once

#include <iostream>
#include <cmath>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\namespaces.h"

using namespace std;
using namespace ExceptionSpace;

//特殊矩阵的抽象基类，该矩阵为方阵，派生自该矩阵的也都是方阵
template<class T>
class virtualDiagonalMatrix {
protected:
    int dimension;
    T *element;
public:
    bool initialized;
public:
    virtual T get(const int &i, const int &j) const = 0;//返回下标为i,j的矩阵元素

    virtual void set(const int &i, const int &j, const T &theElement) = 0;//将下标为i,j的矩阵元素设为另一个值

    virtual virtualDiagonalMatrix<T> *operator+(const virtualDiagonalMatrix<T> &theMatrix) const = 0;//矩阵加法

    virtual virtualDiagonalMatrix<T> *operator-(const virtualDiagonalMatrix<T> &theMatrix) const = 0;//矩阵减法

    virtual virtualDiagonalMatrix<T> *operator*(const virtualDiagonalMatrix<T> &theMatrix) const = 0;//矩阵乘法

    virtual T operator()(int i, int j) const = 0;//得到索引为i,j的索引元素

    //其他常规接口
    virtual void initialize(T *theElements, const int &theDimension) = 0;//初始化矩阵，将传入的二维数组映射到内部的一维数组中

    virtual void initialize() = 0;//重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零

    virtual int size() const = 0;//返回矩阵中元素的个数

    virtual virtualDiagonalMatrix<T> *transpose() = 0;//矩阵的转置

    //访问私有成员的公有接口，仅可访问维数dimension，内置数组仍不可直接访问
    int getDimension() const { return dimension; }//所有派生类可直接继承使用此接口，不再重写

};

//对角矩阵（此矩阵为方阵，只有对角线上的元素是非零元素）
template<class T>
class diagonalMatrix : public virtualDiagonalMatrix<T> {
    friend ostream &operator<<(ostream &out, const diagonalMatrix<T> &theMatrix) {
        int index = 0;
        for (int i = 0; i < theMatrix.getDimension(); i++) {
            for (int j = 0; j < theMatrix.getDimension(); j++) {
                if (i == j) {
                    out << theMatrix.get(i + 1, j + 1) << " ";
                    index++;
                } else {
                    out << 0 << " ";
                    index++;
                }
            }
            if (index % theMatrix.getDimension() == 0)out << endl;
        }
        return out;
    }

public:
    diagonalMatrix(int theDimention = 10) {
        if (theDimention < 1) {
            throw IllegalParameterValue("matrix的大小必须大于0");
        }
        this->dimension = theDimention;//在模板继承中要访问基类中的数据必须使用this标注
        this->element = new T[this->dimension];
        this->initialized = false;
    }

    diagonalMatrix(const diagonalMatrix<T> &theMatrix) {
        if (!this->initialized)throw uninitializedMatrix();
        this->dimension = theMatrix.dimension;
        this->element = new T[this->dimension];
        this->initialized = true;
        copy(theMatrix.element, theMatrix.element + this->dimension, this->element);
    }

    ~diagonalMatrix() { delete[]this->element; }

    //常规接口
    virtual T operator()(int i, int j) const//获取下标为(i,j)的矩阵元素
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i == j)return this->element[i - 1];//对角线上的元素才是非零元素
        else return 0;
    }

    virtual T get(const int &i, const int &j) const//获取下标为(i,j)的矩阵元素
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i == j)return this->element[i - 1];//对角线上的元素才是非零元素
        else return 0;
    }

    virtual void set(const int &i, const int &j, const T &theElement)//将下标为i,j的元素设为另一个值
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        if (i == j)this->element[i - 1] = theElement;
        else {
            if (theElement != 0)throw IllegalParameterValue("设值失败，因为在对角矩阵中，非对角线上的元素必须是0");
        }
    }

    //矩阵的加减乘操作

    //矩阵加法
    virtual diagonalMatrix<T> *operator+(const virtualDiagonalMatrix<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new diagonalMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            //result.element[i] = element[i] + theMatrix.element[i];
            result->set(i + 1, i + 1, this->element[i] + theMatrix.get(i + 1, i + 1));
        }

        return result;
    }

    //矩阵减法
    virtual diagonalMatrix<T> *operator-(const virtualDiagonalMatrix<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new diagonalMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            result->set(i + 1, i + 1, this->element[i] - theMatrix.get(i + 1, i + 1));
        }
        return result;

    }

    //矩阵乘法
    virtual diagonalMatrix<T> *operator*(const virtualDiagonalMatrix<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfMultiply();
        auto result = new diagonalMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                T sum = 0;
                for (int k = 0; k < this->dimension; k++) {
                    if (i != k || k != j) {
                        sum += 0;
                    } else {
                        //i==k且k==j的情况
                        sum += this->element[k] * theMatrix.get(k + 1, k + 1);
                    }
                }
                result->set(i + 1, j + 1, sum);
            }
        }
        return result;

    }

    //其他常规接口
    //初始化矩阵，将传入的二维数组映射到内部的一维数组中
    virtual void initialize(T *theElements, const int &theDimension) {
        if (this->initialized)throw reInitializedMatrix();
        if (theDimension != this->dimension)throw matrixSizeMismatchOfInitialize();
        int index = 0;
        for (int i = 0; i < theDimension; i++) {
            this->element[i] = theElements[i * (theDimension + 1)];
        }
        this->initialized = true;
    }

    //重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    virtual void initialize() {
        if (this->initialized)throw reInitializedMatrix();
        for (int i = 0; i < this->dimension; i++) {
            this->element[i] = 0;
        }
        this->initialized = true;
    }

    //返回矩阵中元素的个数
    virtual int size() const {
        return pow(this->dimension, 2);
    }

    //矩阵的转置
    virtual diagonalMatrix<T> *transpose() {

    }


};

//三对角矩阵（此矩阵为方阵），本三对角矩阵采用逐对角线映射的方式压缩存储，还有另外两种方法压缩存储三对角矩阵，即行主映射和列主映射
template<class T>
class tripleDiagonalMatrix : public virtualDiagonalMatrix<T> {
    friend ostream &operator<<(ostream &out, const tripleDiagonalMatrix<T> &theMatrix) {
        int index = 0;
        for (int i = 0; i < theMatrix.getDimension(); i++) {
            for (int j = 0; j < theMatrix.getDimension(); j++) {
                if (abs(i - j) <= 1) {
                    out << theMatrix.get(i + 1, j + 1) << " ";
                    index++;
                } else {
                    out << 0 << " ";
                    index++;
                }
            }
            if (index % theMatrix.getDimension() == 0)out << endl;
        }
        return out;
    }

public:
    tripleDiagonalMatrix(int theDimention = 10) {
        if (theDimention < 1) {
            throw IllegalParameterValue("matrix的大小必须大于0");
        }
        this->dimension = theDimention;
        this->element = new T[3 * this->dimension - 2];//三对角矩阵的非零元素的个数是3*n-2
        this->initialized = false;
    }

    tripleDiagonalMatrix(const tripleDiagonalMatrix<T> &theMatrix) {
        if (!this->initialized)throw uninitializedMatrix();
        this->dimension = theMatrix.dimension;
        this->element = new T[3 * this->dimension - 2];//三对角矩阵元素数3*n-2
        copy(theMatrix.element, theMatrix.element + this->dimension, this->element);
        this->initialized = true;
    }

    ~tripleDiagonalMatrix() { delete[]this->element; }

    virtual T operator()(int i, int j) const//获取下标为(i,j)的矩阵元素
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        //确定要返回的元素
        switch (i - j) {
            case 1://i-j=1时为下对角线
                return this->element[i - 2];
            case 0://i-j=0时为主对角线
                return this->element[this->dimension + i - 2];
            case -1://i-j=-1时为上对角线
                return this->element[2 * this->dimension + i - 2];
            default:
                return 0;
        }
    }

    //获取下标为(i,j)的矩阵元素
    virtual T get(const int &i, const int &j) const {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        //确定要返回的元素
        switch (i - j) {
            case 1://i-j=1时为下对角线
                return this->element[i - 2];
            case 0://i-j=0时为主对角线
                return this->element[this->dimension + i - 2];
            case -1://i-j=-1时为上对角线
                return this->element[2 * this->dimension + i - 2];
            default:
                return 0;
        }
    }

    //将下标为i,j的元素设为另一个值
    virtual void set(const int &i, const int &j, const T &theElement) {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension)
            throw matrixIndexOutOfBounds();
        switch (i - j) {
            case 1:
                this->element[i - 2] = theElement;
                break;
            case 0:
                this->element[this->dimension + i - 2] = theElement;
                break;
            case -1:
                this->element[2 * this->dimension + i - 2] = theElement;
                break;
            default: {
                if (theElement != 0)throw invalidValueSet();
            }
        }
    }

    //矩阵的加减乘操作
    virtual tripleDiagonalMatrix<T> *operator+(const virtualDiagonalMatrix<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new tripleDiagonalMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                result->set(i + 1, j + 1, this->get(i + 1, j + 1) + theMatrix.get(i + 1, j + 1));
            }
        }
        return result;
    }

    virtual tripleDiagonalMatrix<T> *operator-(const virtualDiagonalMatrix<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new tripleDiagonalMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                result->set(i + 1, j + 1, this->get(i + 1, j + 1) - theMatrix.get(i + 1, j + 1));
            }
        }
        return result;

    }

    virtual tripleDiagonalMatrix<T> *operator*(const virtualDiagonalMatrix<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfMultiply();
        auto result = new tripleDiagonalMatrix<T>(this->dimension);
        result->initialize();
        for(int i=0;i<this->dimension;i++)
        {
            for(int j=0;j<this->dimension;j++)
            {
                T sum=0;
                for(int k =0;k<this->dimension;k++)
                {
                    if(abs(i-j)>1)
                        sum+=0;
                    else{
                        sum+=this->get(i+1,k+1)*theMatrix.get(k+1,j+1);
                    }
                }
                result->set(i+1,j+1,sum);
            }
        }
        return result;
    }

    //其他常规接口
    //初始化矩阵，将传入的二维数组映射到内部的一维数组中
    virtual void initialize(T *theElements, const int &theDimension) {
        if(this->initialized)throw reInitializedMatrix();
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                this->set(i + 1, j + 1, theElements[i * theDimension + j]);
            }
        }
        this->initialized = true;
    }

    //重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    virtual void initialize() {
        if (this->initialized)throw reInitializedMatrix();
        for (int i = 0; i < this->size(); i++) {
            this->element[i] = 0;
        }
        this->initialized = true;
    }

    //返回矩阵中元素的实际个数
    virtual int size() const {
        return 3 * this->dimension - 2;
    }

    //矩阵的转置
    virtual tripleDiagonalMatrix<T> *transpose() {
    }
private:
    void output()const//该接口仅供调试使用，输出内部element数组中的每一个元素
    {
        for(int i=0;i<this->size();i++)
        {
            cout<<this->element[i]<<" ";
        }
    }
};

/*
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


};*/
