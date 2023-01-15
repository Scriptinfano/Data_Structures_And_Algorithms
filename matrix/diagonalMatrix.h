/*该头文件设计了一些采用不同映射方式以及不同的内部存储结构的矩阵类，实现了矩阵以及矩阵之间的基本运算
 *在设计矩阵类时要注意矩阵的行下标和列下标都是从1开始的，和数组从0开始是不一样的 */
#pragma once

#include <iostream>
#include <cmath>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"

using namespace std;
using namespace ExceptionSpace;
using namespace MatrixExceptionSpace;

//特殊矩阵的抽象基类，该矩阵为方阵，派生自该抽象基类所定义的所有矩阵类内部皆采用一维数组来存储特殊矩阵中的非零元素
template<class T>
class virtualDiagonalMatrixAsRegularArray {
protected:
    int dimension;
    T *element;
public:
    bool initialized;
public:
    virtual T get(const int &i, const int &j) const = 0;//返回下标为i,j的矩阵元素

    virtual void set(const int &i, const int &j, const T &theElement) = 0;//将下标为i,j的矩阵元素设为另一个值

    virtual virtualDiagonalMatrixAsRegularArray<T> *operator+(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const = 0;//矩阵加法

    virtual virtualDiagonalMatrixAsRegularArray<T> *operator-(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const = 0;//矩阵减法

    virtual virtualDiagonalMatrixAsRegularArray<T> *operator*(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const = 0;//矩阵乘法

    virtual T operator()(int i, int j) const = 0;//得到索引为i,j的索引元素

    //其他常规接口
    virtual void initialize(T *theElements, const int &theDimension) = 0;//初始化矩阵，将传入的二维数组映射到内部的一维数组中

    virtual void initialize() = 0;//重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零

    virtual int size() const = 0;//返回矩阵中元素的个数

    virtual virtualDiagonalMatrixAsRegularArray<T> *transpose() = 0;//矩阵的转置

    //访问私有成员的公有接口，仅可访问维数dimension，内置数组仍不可直接访问
    int getDimension() const { return dimension; }//所有派生类可直接继承使用此接口，不再重写

    bool isInitialized() const { return initialized == true; }

};

//对角矩阵（此矩阵为方阵，只有对角线上的元素是非零元素）
template<class T>
class diagonalMatrix : public virtualDiagonalMatrixAsRegularArray<T> {
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
    diagonalMatrix(int theDimension = 10) {
        if (theDimension < 1) {
            throw IllegalParameterException("matrix的大小必须大于0");
        }
        this->dimension = theDimension;//在模板继承中要访问基类中的数据必须使用this标注
        this->element = new T[this->dimension];
        this->initialized = false;
    }

    diagonalMatrix(const diagonalMatrix<T> &theMatrix) {
        if (!theMatrix->initialized)throw MatrixUnInitializeException("使用未初始化的矩阵拷贝构造新的矩阵是不被允许的");
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
            if (theElement != 0)throw IllegalParameterException("设值失败，因为在对角矩阵中，非对角线上的元素必须是0");
        }
    }

    //矩阵的加减乘操作

    //矩阵加法
    virtual diagonalMatrix<T> *operator+(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
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
    virtual diagonalMatrix<T> *operator-(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfSubtraction();
        auto result = new diagonalMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            result->set(i + 1, i + 1, this->element[i] - theMatrix.get(i + 1, i + 1));
        }
        return result;

    }

    //矩阵乘法
    virtual diagonalMatrix<T> *operator*(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
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
        if (this->initialized)throw MatrixReinitializeException();
        if (theDimension != this->dimension)throw matrixSizeMismatchOfInitialize();
        int index = 0;
        for (int i = 0; i < theDimension; i++) {
            this->element[i] = theElements[i * (theDimension + 1)];
        }
        this->initialized = true;
    }

    //重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    virtual void initialize() {
        if (this->initialized)throw MatrixReinitializeException();
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
        return this;//对角矩阵转置之后各元素的位置不发生改变
    }


};

//按行的方式将对称矩阵的下三角区域存储在一维数组中
template<class T>
class LowerSymmetricMatrix : public virtualDiagonalMatrixAsRegularArray<T> {
    friend ostream &operator<<(ostream &out, const LowerSymmetricMatrix<T> &theMatrix) {
        int index = 0;
        int theDimension = theMatrix.dimension;
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                if (i >= j) {
                    //当i>=j时，元素在下三角区
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
    LowerSymmetricMatrix(int theDimension = 10) {
        if (theDimension < 1) {
            throw IllegalParameterException("matrix的大小必须大于0");
        }
        this->dimension = theDimension;
        this->element = new T[this->dimension * (this->dimension + 1) / 2];//上三角矩阵和下三角矩阵的元素总数都是n*(n+1)/2
        this->initialized = false;
    }

    LowerSymmetricMatrix(const LowerSymmetricMatrix<T> &theMatrix) {
        if (!theMatrix.initialized)throw MatrixUnInitializeException("使用未初始化的矩阵拷贝构造新的矩阵是不被允许的");
        this->dimension = theMatrix.getDimension();
        this->element = new T[theMatrix.getDimension() * (theMatrix.getDimension() + 1) / 2];//下三角矩阵元素数n*(n+1)/2
        copy(theMatrix.element, theMatrix.element + this->size(), this->element);
        this->initialized = true;
    }

    ~LowerSymmetricMatrix() { delete[]this->element; }


    //ADT接口
    virtual T get(const int &i, const int &j) const//返回下标为i,j的矩阵元素
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i >= j) {
            return this->element[i * (i - 1) / 2 + j - 1];//下三角矩阵的行主映射函数i*(i-1)/2+j-1
        } else {
            return this->element[j * (j - 1) / 2 + i - 1];//对称矩阵要将映射函数反着用
        }
    }

    virtual void set(const int &i, const int &j, const T &theElement)//将下标为i,j的矩阵元素设为另一个值
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        if (i >= j)//下三角区的元素i>=j
        {
            int index = i * (i - 1) / 2 + j - 1;
            this->element[index] = theElement;
        } else {
            int index = j * (j - 1) / 2 + i - 1;
            this->element[index] = theElement;
        }

    }

    virtual LowerSymmetricMatrix<T> *operator+(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const//矩阵加法
    {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new LowerSymmetricMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                int setValue = this->get(i + 1, j + 1) + theMatrix.get(i + 1, j + 1);
                result->set(i + 1, j + 1, setValue);
            }
        }
        return result;

    }

    virtual LowerSymmetricMatrix<T> *operator-(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const//矩阵减法
    {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfSubtraction();
        auto result = new LowerSymmetricMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                result->set(i + 1, j + 1, this->get(i + 1, j + 1) - theMatrix.get(i + 1, j + 1));
            }
        }
        return result;

    }

    virtual LowerSymmetricMatrix<T> *operator*(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const//矩阵乘法
    {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfMultiply();
        auto result = new LowerSymmetricMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; ++i) {
            for (int j = 0; j < this->dimension; ++j) {
                T sum = 0;
                for (int k = 0; k < this->dimension; ++k) {
                    sum += this->get(i + 1, k + 1) * theMatrix.get(k + 1, j + 1);
                }
                result->set(i + 1, j + 1, sum);
            }
        }
        return result;

    }

    virtual T operator()(int i, int j) const//得到索引为i,j的索引元素
    {
        return this->get(i, j);
    }

    //其他常规接口
    virtual void initialize(T *theElements, const int &theDimension)//初始化矩阵，将传入的二维数组映射到内部的一维数组中
    {
        if (this->initialized)throw MatrixReinitializeException();
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                this->set(i + 1, j + 1, theElements[i * theDimension + j]);
            }
        }
        this->initialized = true;

    }

    virtual void initialize()//重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    {
        if (this->initialized)throw MatrixReinitializeException();
        for (int i = 0; i < this->size(); i++) {
            this->element[i] = 0;
        }
        this->initialized = true;

    }

    virtual int size() const//返回矩阵中元素的个数
    {
        return this->dimension * (this->dimension + 1) / 2;

    }

    virtual virtualDiagonalMatrixAsRegularArray<T> *transpose()//矩阵的转置
    {
    }

};

//采用逐对角线映射的三对角矩阵，还有另外两种方法压缩存储三对角矩阵，即行主映射和列主映射
template<class T>
class tripleDiagonalMatrix : public virtualDiagonalMatrixAsRegularArray<T> {
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
    tripleDiagonalMatrix(int theDimension = 10) {
        if (theDimension < 1) {
            throw IllegalParameterException("matrix的大小必须大于0");
        }
        this->dimension = theDimension;
        this->element = new T[3 * this->dimension - 2];//三对角矩阵的非零元素的个数是3*n-2
        this->initialized = false;
    }

    tripleDiagonalMatrix(const tripleDiagonalMatrix<T> &theMatrix) {
        if (!theMatrix->initialized)throw MatrixUnInitializeException("使用未初始化的矩阵拷贝构造新的矩阵是不被允许的");
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
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
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
                if (theElement != 0)throw MatrixInvalidValueSetException();
            }
        }
    }

    //矩阵的加减乘操作
    virtual tripleDiagonalMatrix<T> *operator+(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
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

    virtual tripleDiagonalMatrix<T> *operator-(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfSubtraction();
        auto result = new tripleDiagonalMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                result->set(i + 1, j + 1, this->get(i + 1, j + 1) - theMatrix.get(i + 1, j + 1));
            }
        }
        return result;

    }

    virtual tripleDiagonalMatrix<T> *operator*(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfMultiply();
        auto result = new tripleDiagonalMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                T sum = 0;
                for (int k = 0; k < this->dimension; k++) {
                    if (abs(i - j) > 1)
                        sum += 0;
                    else {
                        sum += this->get(i + 1, k + 1) * theMatrix.get(k + 1, j + 1);
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
        if (this->initialized)throw MatrixReinitializeException();
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                this->set(i + 1, j + 1, theElements[i * theDimension + j]);
            }
        }
        this->initialized = true;
    }

    //重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    virtual void initialize() {
        if (this->initialized)throw MatrixReinitializeException();
        for (int i = 0; i < this->size(); i++) {
            this->element[i] = 0;
        }
        this->initialized = true;
    }

    //返回矩阵中元素的实际个数
    virtual int size() const {
        return 3 * this->dimension - 2;
    }

    //三对角矩阵的转置
    virtual tripleDiagonalMatrix<T> *transpose() {
        if (!this->initialized)throw MatrixUnInitializeException();
        auto temp = new tripleDiagonalMatrix<T>(this->getDimension());
        for (int i = 0; i < this->getDimension(); i++) {
            for (int j = 0; j < this->dimension; j++) {
                temp->set(i + 1, j + 1, this->get(j + 1, i + 1));
            }
        }
        return temp;

    }

private:
    void output() const//该接口仅供调试使用，输出内部element数组中的每一个元素
    {
        for (int i = 0; i < this->size(); i++) {
            cout << this->element[i] << " ";
        }
    }
};

template<class T>
class upperTriangularMatrix;//模板类的前置声明，在定义lowerTriangularMatrix类的transpose函数时会用到


//内部采用一维数组存储二维矩阵元素，映射方式采用行主映射的下三角矩阵
template<class T>
class lowerTriangularMatrix : public virtualDiagonalMatrixAsRegularArray<T> {
    friend ostream &operator<<(ostream &out, const lowerTriangularMatrix<T> &theMatrix) {
        int index = 0;
        int theDimension = theMatrix.dimension;
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                if (i >= j) {
                    //当i>=j时，元素在下三角区
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
    lowerTriangularMatrix(int theDimension = 10) {
        if (theDimension < 1) {
            throw IllegalParameterException("matrix的大小必须大于0");
        }
        this->dimension = theDimension;
        this->element = new T[this->dimension * (this->dimension + 1) / 2];//上三角矩阵和下三角矩阵的元素总数都是n*(n+1)/2
        this->initialized = false;
    }

    lowerTriangularMatrix(const lowerTriangularMatrix<T> &theMatrix) {
        if (!theMatrix.initialized)throw MatrixUnInitializeException("使用未初始化的矩阵拷贝构造新的矩阵是不被允许的");
        this->dimension = theMatrix.getDimension();
        this->element = new T[theMatrix.getDimension() * (theMatrix.getDimension() + 1) / 2];//下三角矩阵元素数n*(n+1)/2
        copy(theMatrix.element, theMatrix.element + this->size(), this->element);
        this->initialized = true;
    }

    ~lowerTriangularMatrix() { delete[]this->element; }

    virtual T operator()(int i, int j) const//获取下标为(i,j)的矩阵元素
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i >= j) {
            T result = this->element[(i * (i - 1)) / 2 + j - 1];
            return result;
        } else return 0;
    }

    //常规接口
    virtual T get(const int &i, const int &j) const//获取下标为(i,j)的矩阵元素
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i >= j) {
            T result = this->element[(i * (i - 1)) / 2 + j - 1];
            return result;
        } else return 0;
    }

    virtual void set(const int &i, const int &j, const T &theElement)//将下标为i,j的元素设为另一个值
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        if (i >= j)//下三角区的元素i>=j
        {
            int index = i * (i - 1) / 2 + j - 1;
            this->element[index] = theElement;
        } else {
            if (theElement != 0)throw MatrixInvalidValueSetException();
        }
    }

    //矩阵的加减乘操作
    //矩阵加法
    virtual lowerTriangularMatrix<T> *operator+(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new lowerTriangularMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                int setValue = this->get(i + 1, j + 1) + theMatrix.get(i + 1, j + 1);
                result->set(i + 1, j + 1, setValue);
            }
        }
        return result;

    }

    //矩阵减法
    virtual lowerTriangularMatrix<T> *operator-(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfSubtraction();
        auto result = new lowerTriangularMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                result->set(i + 1, j + 1, this->get(i + 1, j + 1) - theMatrix.get(i + 1, j + 1));
            }
        }
        return result;

    }

    //矩阵乘法
    virtual lowerTriangularMatrix<T> *operator*(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfMultiply();
        auto result = new lowerTriangularMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; ++i) {
            for (int j = 0; j < this->dimension; ++j) {
                T sum = 0;
                for (int k = 0; k < this->dimension; ++k) {
                    sum += this->get(i + 1, k + 1) * theMatrix.get(k + 1, j + 1);
                }
                result->set(i + 1, j + 1, sum);
            }
        }
        return result;
    }

    //其他常规接口
    //初始化矩阵，将传入的二维数组映射到内部的一维数组中
    virtual void initialize(T *theElements, const int &theDimension) {
        if (this->initialized)throw MatrixReinitializeException();
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                this->set(i + 1, j + 1, theElements[i * theDimension + j]);
            }
        }
        this->initialized = true;

    }

    //重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    virtual void initialize() {
        if (this->initialized)throw MatrixReinitializeException();
        for (int i = 0; i < this->size(); i++) {
            this->element[i] = 0;
        }
        this->initialized = true;
    }

    //返回矩阵中元素的个数
    virtual int size() const {
        return this->dimension * (this->dimension + 1) / 2;
    }

    //矩阵的转置
    virtual upperTriangularMatrix<T> *transpose() {
        if (!this->initialized)throw MatrixUnInitializeException();
        auto temp = new upperTriangularMatrix<T>(this->getDimension());
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                temp->set(i + 1, j + 1, this->get(j + 1, i + 1));
            }
        }
        return temp;
    }
};


//内部采用一维数组存储二维矩阵元素，映射方式采用行主映射的上三角矩阵
template<class T>
class upperTriangularMatrix : public virtualDiagonalMatrixAsRegularArray<T> {
    friend ostream &operator<<(ostream &out, const upperTriangularMatrix<T> &theMatrix) {
        int index = 0;
        int theDimension = theMatrix.dimension;
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                if (i <= j) {
                    //当i<=j时，元素在上三角区
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
    upperTriangularMatrix(int theDimension = 10) {
        if (theDimension < 1) {
            throw IllegalParameterException("matrix的大小必须大于0");
        }
        this->dimension = theDimension;
        this->element = new T[this->dimension * (this->dimension + 1) / 2];//上三角矩阵和下三角矩阵的元素总数都是n*(n+1)/2
        this->initialized = false;
    }

    upperTriangularMatrix(const upperTriangularMatrix<T> &theMatrix) {
        if (!theMatrix.initialized)throw MatrixUnInitializeException();
        this->dimension = theMatrix.getDimension();
        this->element = new T[theMatrix.getDimension() * (theMatrix.getDimension() + 1) / 2];//下三角矩阵元素数n*(n+1)/2
        copy(theMatrix.element, theMatrix.element + this->size(), this->element);
        this->initialized = true;
    }

    ~upperTriangularMatrix() { delete[]this->element; }

    virtual T operator()(int i, int j) const//获取下标为(i,j)的矩阵元素
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i <= j)return this->element[((2 * this->dimension - i + 2) * (i - 1)) / 2 + j - i];//这是上三角矩阵的行主映射函数
        else return 0;
    }

    //常规接口
    virtual T get(const int &i, const int &j) const//获取下标为(i,j)的矩阵元素
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i <= j)return this->element[((2 * this->dimension - i + 2) * (i - 1)) / 2 + j - i];//这是上三角矩阵的行主映射函数
        else return 0;
    }

    virtual void set(const int &i, const int &j, const T &theElement)//将下标为i,j的元素设为另一个值
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        if (i <= j)//下三角区的元素i>=j
        {
            int index = ((2 * this->dimension - i + 2) * (i - 1)) / 2 + j - i;
            this->element[index] = theElement;
        } else {
            if (theElement != 0)throw MatrixInvalidValueSetException();
        }
    }

    //矩阵的加减乘操作
    //矩阵加法
    virtual upperTriangularMatrix<T> *operator+(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new upperTriangularMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                int setValue = this->get(i + 1, j + 1) + theMatrix.get(i + 1, j + 1);
                result->set(i + 1, j + 1, setValue);
            }
        }
        return result;

    }

    //矩阵减法
    virtual upperTriangularMatrix<T> *operator-(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfSubtraction();
        auto result = new upperTriangularMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                result->set(i + 1, j + 1, this->get(i + 1, j + 1) - theMatrix.get(i + 1, j + 1));
            }
        }
        return result;

    }

    //矩阵乘法
    virtual upperTriangularMatrix<T> *operator*(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfMultiply();
        auto result = new upperTriangularMatrix<T>(this->dimension);
        result->initialize();
        int theDimension = result->getDimension();//测试代码
        for (int i = 0; i < this->dimension; ++i) {
            for (int j = 0; j < this->dimension; ++j) {
                T sum = 0;
                for (int k = 0; k < this->dimension; ++k) {
                    sum += this->get(i + 1, k + 1) * theMatrix.get(k + 1, j + 1);
                }
                result->set(i + 1, j + 1, sum);
            }
        }
        return result;
    }

    //其他常规接口
    //初始化矩阵，将传入的二维数组映射到内部的一维数组中
    virtual void initialize(T *theElements, const int &theDimension) {
        if (this->initialized)throw MatrixReinitializeException();
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                this->set(i + 1, j + 1, theElements[i * theDimension + j]);
            }
        }
        this->initialized = true;

    }

    //重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    virtual void initialize() {
        if (this->initialized)throw MatrixReinitializeException();
        for (int i = 0; i < this->size(); i++) {
            this->element[i] = 0;
        }
        this->initialized = true;
    }

    //返回矩阵中元素的个数
    virtual int size() const {
        return this->dimension * (this->dimension + 1) / 2;
    }

    //注意上三角矩阵转置之后是下三角矩阵
    virtual lowerTriangularMatrix<T> *transpose() {
        if (!this->initialized)throw MatrixUnInitializeException();
        auto temp = new lowerTriangularMatrix<T>(this->getDimension());
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                temp->set(i + 1, j + 1, this->get(j + 1, i + 1));
            }
        }
        return temp;
    }

};

//下面的这个抽象基类也是特殊矩阵的抽象基类，派生自该抽象基类所定义的所有矩阵类内部皆采用不规则的二维数组来存储特殊矩阵中的非零元素
template<class T>
class virtualDiagonalMatrixAsIrregularArray {
protected:
    int dimension;
    T **element;
    bool initialized;
public:
    //返回私有数据的公有接口
    int getDimension() const { return dimension; }

    bool isInitialized() const { return initialized; }

    //常规公有接口
    virtual T get(const int &i, const int &j) const = 0;//返回下标为i,j的矩阵元素

    virtual void set(const int &i, const int &j, const T &theElement) = 0;//将下标为i,j的矩阵元素设为另一个值

    virtual virtualDiagonalMatrixAsIrregularArray<T> *operator+(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const = 0;//矩阵加法

    virtual virtualDiagonalMatrixAsIrregularArray<T> *operator-(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const = 0;//矩阵减法

    virtual virtualDiagonalMatrixAsIrregularArray<T> *operator*(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const = 0;//矩阵乘法

    virtual T operator()(int i, int j) const = 0;//得到索引为i,j的索引元素

    virtual void initialize(T *theElements, const int &theDimension) = 0;//初始化矩阵，将传入的二维数组映射到内部的一维数组中

    virtual void initialize() = 0;//重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零

    virtual int size() const = 0;//返回矩阵中元素的个数

    virtual virtualDiagonalMatrixAsIrregularArray<T> *transpose() const = 0;//矩阵的转置


};

//内部采用二维数组实现的，映射方式采用行主映射方式实现的三对角矩阵
template<class T>
class tripleDiagonalMatrixAsIrregularArray : public virtualDiagonalMatrixAsIrregularArray<T> {
    friend ostream &operator<<(ostream &out, const tripleDiagonalMatrixAsIrregularArray<T> &theMatrix) {
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
    //构造，拷贝构造，析构接口
    tripleDiagonalMatrixAsIrregularArray(const int &theDimension) {
        if (theDimension < 1)
            throw IllegalParameterException("调用tripleDiagonalMatrixAsIrregularArray构造函数时，传递的参数必须大于1确保矩阵的大小符合实际");
        this->dimension = theDimension;
        this->element = new T *[theDimension];
        this->element[0] = new T[2];
        for (int i = 1; i < theDimension - 1; i++)//给二维数组中的每一个一维数组分配空间
        {
            this->element[i] = new T[3];
        }
        this->element[theDimension - 1] = new T[2];
        this->initialized = false;
    }

    tripleDiagonalMatrixAsIrregularArray(const tripleDiagonalMatrixAsIrregularArray<T> &theMatrix) {
        if (!theMatrix.isInitialized())throw MatrixUnInitializeException("使用未初始化的矩阵拷贝构造新的矩阵是不被允许的");

        this->dimension = theMatrix.getDimension();
        this->element = new T *[this->dimension];
        this->element[0] = new T[2];
        for (int i = 1; i < this->dimension - 1; i++)//给二维数组中的每一个一维数组分配空间
        {
            this->element[i] = new T[3];
        }
        this->element[this->dimension - 1] = new T[2];

        //拷贝元素的代码
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; ++j) {
                int theValue = theMatrix.get(i + 1, j + 1);
                this->set(i + 1, j + 1, theValue);
            }
        }

        this->initialized = true;


    }

    ~tripleDiagonalMatrixAsIrregularArray() {

        for (int i = 0; i < this->dimension; i++)
            delete[]this->element[i];//释放二维数组中的每一个一维数组中的每一个元素
        delete[]this->element;
    }

    //ADT方法
    virtual T get(const int &i, const int &j) const//返回下标为i,j的矩阵元素
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        if (abs(i - j) > 1)return 0;
        else {
            T temp;
            if (i == this->dimension && (j == this->dimension - 1 || j == this->dimension))//最后一行是特殊情况，特殊处理
            {
                temp = this->element[i - 1][j - 3];
                return temp;
            }
            temp = this->element[i - 1][j - 1];
            return temp;
        }
    }

    virtual void set(const int &i, const int &j, const T &theElement)//将下标为i,j的矩阵元素设为另一个值
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        if (abs(i - j) > 1) { if (theElement != 0)throw MatrixInvalidValueSetException(); }
        else {
            if (i == this->dimension && (j == this->dimension - 1 || j == this->dimension))//最后一行是特殊情况，特殊处理
            {
                this->element[i - 1][j - 3] = theElement;
                return;
            }
            this->element[i - 1][j - 1] = theElement;
        }
    }

    virtual tripleDiagonalMatrixAsIrregularArray<T> *
    operator+(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const//矩阵加法
    {
        if (!this->initialized || !theMatrix.isInitialized())throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new tripleDiagonalMatrixAsIrregularArray<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                int plusA = this->get(i + 1, j + 1);
                int plusB = theMatrix.get(i + 1, j + 1);
                result->set(i + 1, j + 1, plusA + plusB);
            }
        }
        return result;

    }

    virtual tripleDiagonalMatrixAsIrregularArray<T> *
    operator-(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const//矩阵减法
    {
        if (!this->initialized || !theMatrix.isInitialized())throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfSubtraction();
        auto result = new tripleDiagonalMatrixAsIrregularArray<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                result->set(i + 1, j + 1, this->get(i + 1, j + 1) - theMatrix.get(i + 1, j + 1));
            }
        }
        return result;

    }

    virtual tripleDiagonalMatrixAsIrregularArray<T> *
    operator*(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const//矩阵乘法
    {
        if (!this->initialized || !theMatrix.isInitialized())throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfMultiply();
        auto result = new tripleDiagonalMatrixAsIrregularArray<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                T sum = 0;
                for (int k = 0; k < this->dimension; k++) {
                    if (abs(i - j) > 1)
                        sum += 0;
                    else {
                        sum += this->get(i + 1, k + 1) * theMatrix.get(k + 1, j + 1);
                    }
                }
                result->set(i + 1, j + 1, sum);
            }
        }
        return result;

    }

    virtual T operator()(int i, int j) const//得到索引为i,j的索引元素
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        if (abs(i - j) > 1)return 0;
        else {
            T temp;
            if (i == this->dimension && (j == this->dimension - 1 || j == this->dimension))//最后一行是特殊情况，特殊处理
            {
                temp = this->element[i - 1][j - 3];
                return temp;
            }
            temp = this->element[i - 1][j - 1];
            return temp;
        }

    }

    virtual void initialize(T *theElements, const int &theDimension)//初始化矩阵，将传入的二维数组映射到内部的一维数组中
    {
        if (this->initialized)throw MatrixReinitializeException();
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                this->set(i + 1, j + 1, theElements[i * theDimension + j]);
            }
        }
        this->initialized = true;


    }

    virtual void initialize()//重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    {
        if (this->initialized)throw MatrixReinitializeException();
        for (int i = 0; i < 2; i++) {
            this->element[0][i] = 0;
        }
        for (int i = 1; i < this->dimension - 1; i++) {
            for (int j = 0; j < 3; j++) {
                this->element[i][j] = 0;
            }
        }
        for (int k = 0; k < 2; k++) {
            this->element[this->dimension - 1][k] = 0;
        }
        this->initialized = true;
    }

    virtual int size() const//返回矩阵中元素的个数
    {
        return 3 * this->dimension - 2;
    }

    virtual tripleDiagonalMatrixAsIrregularArray<T> *transpose() const//矩阵的转置
    {
        if (!this->initialized)throw MatrixUnInitializeException();
        auto temp = new tripleDiagonalMatrixAsIrregularArray<T>(this->getDimension());
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                temp->set(i + 1, j + 1, this->get(j + 1, i + 1));
            }
        }
        return temp;
    }
};

template<class T>
class upperTriangleAsIrregularArray;

//内部使用二维不规则数组实现的，按照行主映射方式实现的下三角矩阵
template<class T>
class lowerTriangleAsIrregularArray : public virtualDiagonalMatrixAsIrregularArray<T> {
    friend ostream &operator<<(ostream &out, const lowerTriangleAsIrregularArray<T> &theMatrix) {
        int index = 0;
        for (int i = 0; i < theMatrix.getDimension(); i++) {
            for (int j = 0; j < theMatrix.getDimension(); j++) {
                out << theMatrix.get(i + 1, j + 1) << " ";
                index++;
            }
            if (index % theMatrix.getDimension() == 0)out << endl;
        }
        return out;
    }

public:
    //拷贝构造，构造，析构
    lowerTriangleAsIrregularArray(const int &theDimension) {
        if (theDimension < 1)throw IllegalParameterException("调用lowerTriangleAsIrregularArray构造函数时，传递的参数必须大于1确保矩阵的大小符合实际");
        this->dimension = theDimension;
        this->element = new T *[theDimension];
        for (int i = 0; i < theDimension; i++) {
            this->element[i] = new T[i + 1];
        }
        this->initialized = false;
    }

    lowerTriangleAsIrregularArray(const lowerTriangleAsIrregularArray<T> &theMatrix) {
        if (!theMatrix.isInitialized())throw MatrixUnInitializeException("使用未初始化的矩阵拷贝构造新的矩阵是不被允许的");
        this->dimension = theMatrix.getDimension();
        this->element = new T *[this->dimension];
        for (int i = 0; i < this->dimension; i++) {
            this->element[i] = new T[i + 1];
        }
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < i + 1; ++j) {
                int theValue = theMatrix.get(i + 1, j + 1);
                this->set(i + 1, j + 1, theValue);
            }
        }
        this->initialized = true;
    }

    ~lowerTriangleAsIrregularArray() {
        for (int i = 0; i < this->dimension; i++)
            delete[]this->element[i];//释放二维数组中的每一个一维数组中的每一个元素
        delete[]this->element;
    }

    virtual T get(const int &i, const int &j) const//返回下标为i,j的矩阵元素
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i >= j) {
            int result = this->element[i - 1][j - 1];
            return result;
        } else return 0;
    }

    virtual void set(const int &i, const int &j, const T &theElement) //将下标为i,j的矩阵元素设为另一个值
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        if (i >= j)//下三角区的元素i>=j
        {
            this->element[i - 1][j - 1] = theElement;
        } else {
            if (theElement != 0)throw MatrixInvalidValueSetException();
        }

    }


    virtual lowerTriangleAsIrregularArray<T> *operator+(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const //矩阵加法
    {
        if (!this->initialized || !theMatrix.isInitialized())throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new lowerTriangleAsIrregularArray<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                int plusA = this->get(i + 1, j + 1);
                int plusB = theMatrix.get(i + 1, j + 1);
                result->set(i + 1, j + 1, plusA + plusB);
            }
        }
        return result;

    }

    virtual lowerTriangleAsIrregularArray<T> *operator-(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const //矩阵减法
    {
        if (!this->initialized || !theMatrix.isInitialized())throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfSubtraction();
        auto result = new lowerTriangleAsIrregularArray<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                int plusA = this->get(i + 1, j + 1);
                int plusB = theMatrix.get(i + 1, j + 1);
                result->set(i + 1, j + 1, plusA - plusB);
            }
        }
        return result;

    }


    virtual lowerTriangleAsIrregularArray<T> *operator*(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const //矩阵乘法
    {
        if (!this->initialized || !theMatrix.isInitialized())throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfMultiply();
        auto result = new lowerTriangleAsIrregularArray<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                T sum = 0;
                for (int k = 0; k < this->dimension; k++) {
                    if (i < j)
                        sum += 0;
                    else {
                        sum += this->get(i + 1, k + 1) * theMatrix.get(k + 1, j + 1);
                    }
                }
                result->set(i + 1, j + 1, sum);
            }
        }
        return result;

    }

    virtual T operator()(int i, int j) const //得到索引为i,j的索引元素
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i >= j) {
            int result = this->element[i - 1][j - 1];
            return result;
        } else return 0;

    }


    virtual void initialize(T *theElements, const int &theDimension)//初始化矩阵，将传入的二维数组映射到内部的一维数组中
    {
        if (this->initialized)throw MatrixReinitializeException();
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                this->set(i + 1, j + 1, theElements[i * theDimension + j]);
            }
        }
        this->initialized = true;

    }

    virtual void initialize()//重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    {
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < i + 1; j++) {
                this->element[i][j] = 0;
            }
        }
        this->initialized = true;
    }

    virtual int size() const //返回矩阵中元素的个数
    {
        return this->dimension * (this->dimension + 1) / 2;
    }

    virtual upperTriangleAsIrregularArray<T> *transpose() const //矩阵的转置，返回的是上三角矩阵
    {
        if (!this->initialized)throw MatrixUnInitializeException();
        auto temp = new upperTriangleAsIrregularArray<T>(this->getDimension());
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                temp->set(i + 1, j + 1, this->get(j + 1, i + 1));
            }
        }
        return temp;

    }

};

//内部使用二维不规则数组实现的，按照行主映射方式实现的上三角矩阵
template<class T>
class upperTriangleAsIrregularArray : public virtualDiagonalMatrixAsIrregularArray<T> {

    friend ostream &operator<<(ostream &out, const upperTriangleAsIrregularArray<T> &theMatrix) {
        int index = 0;
        for (int i = 0; i < theMatrix.getDimension(); i++) {
            for (int j = 0; j < theMatrix.getDimension(); j++) {
                out << theMatrix.get(i + 1, j + 1) << " ";
                index++;
            }
            if (index % theMatrix.getDimension() == 0)out << endl;
        }
        return out;
    }

public:
    //拷贝构造，构造，析构
    upperTriangleAsIrregularArray(const int &theDimension) {
        if (theDimension < 1)throw IllegalParameterException("调用upperTriangleAsIrregularArray构造函数时，传递的参数必须大于1确保矩阵的大小符合实际");
        this->dimension = theDimension;
        this->element = new T *[theDimension];
        for (int i = 0; i < theDimension; i++) {
            this->element[i] = new T[this->dimension - i];
        }
        this->initialized = false;
    }

    upperTriangleAsIrregularArray(const upperTriangleAsIrregularArray<T> &theMatrix) {
        if (!theMatrix.isInitialized())throw MatrixUnInitializeException("使用未初始化的矩阵拷贝构造新的矩阵是不被允许的");
        this->dimension = theMatrix.getDimension();
        this->element = new T *[this->dimension];
        for (int i = 0; i < this->dimension; i++) {
            this->element[i] = new T[this->dimension - i];
        }
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < i + 1; ++j) {
                int theValue = theMatrix.get(i + 1, j + 1);
                this->set(i + 1, j + 1, theValue);
            }
        }
        this->initialized = true;
    }

    ~upperTriangleAsIrregularArray() {
        for (int i = 0; i < this->dimension; i++)
            delete[]this->element[i];//释放二维数组中的每一个一维数组中的每一个元素
        delete[]this->element;
    }


    virtual T get(const int &i, const int &j) const//返回下标为i,j的矩阵元素
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i >= j) {
            int result = this->element[i - 1][j - 1];
            return result;
        } else return 0;

    }

    virtual void set(const int &i, const int &j, const T &theElement)//将下标为i,j的矩阵元素设为另一个值
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        if (i <= j)//上三角区的元素i<=j
        {
            this->element[i - 1][j - 1] = theElement;
        } else {
            if (theElement != 0)throw MatrixInvalidValueSetException();
        }

    }

    virtual upperTriangleAsIrregularArray<T> *operator+(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const//矩阵加法
    {
        if (!this->initialized || !theMatrix.isInitialized())throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new upperTriangleAsIrregularArray<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                int plusA = this->get(i + 1, j + 1);
                int plusB = theMatrix.get(i + 1, j + 1);
                result->set(i + 1, j + 1, plusA + plusB);
            }
        }
        return result;
    }

    virtual upperTriangleAsIrregularArray<T> *operator-(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const //矩阵减法
    {
        if (!this->initialized || !theMatrix.isInitialized())throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfSubtraction();
        auto result = new upperTriangleAsIrregularArray<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                int plusA = this->get(i + 1, j + 1);
                int plusB = theMatrix.get(i + 1, j + 1);
                result->set(i + 1, j + 1, plusA - plusB);
            }
        }
        return result;

    }

    virtual upperTriangleAsIrregularArray<T> *operator*(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const//矩阵乘法
    {
        if (!this->initialized || !theMatrix.isInitialized())throw MatrixUnInitializeException();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfMultiply();
        auto result = new upperTriangleAsIrregularArray<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                T sum = 0;
                for (int k = 0; k < this->dimension; k++) {
                    if (i > j) {
                        sum += 0;
                    } else {
                        sum += this->get(i + 1, k + 1) * theMatrix.get(k + 1, j + 1);
                    }
                }
                result->set(i + 1, j + 1, sum);
            }
        }
        return result;
    }

    virtual T operator()(int i, int j) const //得到索引为i,j的索引元素
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i >= j) {
            int result = this->element[i - 1][j - 1];
            return result;
        } else return 0;

    }

    virtual void initialize(T *theElements, const int &theDimension)//初始化矩阵，将传入的二维数组映射到内部的一维数组中
    {
        if (this->initialized)throw MatrixReinitializeException();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                this->set(i + 1, j + 1, theElements[i * theDimension + j]);
            }
        }
        this->initialized = true;
    }

    virtual void initialize() //重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    {
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension - i; j++) {
                this->element[i][j] = 0;
            }
        }
        this->initialized = true;
    }

    virtual int size() const//返回矩阵中元素的个数
    {
        return this->dimension * (this->dimension + 1) / 2;
    }

    virtual lowerTriangleAsIrregularArray<T> *transpose() const //矩阵的转置
    {
        if (!this->initialized)throw MatrixUnInitializeException();
        auto temp = new lowerTriangleAsIrregularArray<T>(this->getDimension());
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                temp->set(i + 1, j + 1, this->get(j + 1, i + 1));
            }
        }
        return temp;
    }
};