#pragma once

#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"
#include <iostream>
#include <algorithm>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\matrix\VirtualBaseMatrix.h"
using namespace std;
using namespace ExceptionSpace;

//此矩阵是最基本的矩阵
template<class T>
class NormalMatrix : public NormalMatrixProperties<T>, public SpecialOperationInterface<T> {

    friend ostream &operator<<(ostream &out, const NormalMatrix <T> &theMatrix) {
        for (int i = 0; i < theMatrix.size; i++) {
            out << theMatrix.element[i] << " ";
            if ((i + 1) % theMatrix.columns == 0)out << endl;
        }
        return out;
    }
public://公有的构造析构拷贝构造函数
    NormalMatrix(const int&matrixSize) {
        if (matrixSize<4)throw IllegalParameterValue("构造矩阵时，矩阵的元素个数不得小于4");
        this->element=new T[matrixSize];
        this->initialized=false;
        //column变量暂时不指定，调用initialize时再指定
    }

    NormalMatrix(const NormalMatrix<T> &theMatrix) {
        if (!this->isInitialized())throw uninitializedMatrix();
        this->columns = theMatrix.columns;
        this->element = new T[theMatrix.size];
        this->size=theMatrix.size;
        copy(theMatrix.element, theMatrix.element + this->size, this->element);
    }

    ~NormalMatrix() { delete[]this->element; }
//私有方法
private:
    //getter接口
    T get(int i, int j) const {
        if (!this->initialized)throw uninitializedMatrix();
        int index=(i - 1) * this->columns + (j - 1)>this->size-1;
        if (index>this->size-1) {
            throw matrixIndexOutOfBounds();
        }
        return this->element[index];
    }

    //setter接口
    void set(int i, int j, const T &theElement) {
        if (!this->initialized)throw uninitializedMatrix();
        int index=(i - 1) * this->columns + (j - 1)>this->size-1;
        if (index>this->size-1) {
            throw matrixIndexOutOfBounds();
        }
        this->element[index] = theElement;
    }

    bool checkInitialize(const vector<vector<T>> &theMatrix) override {
    }



public://实现特殊操作接口中声明的重载运算符函数

    //得到索引为i,j的索引元素
    T operator()(int i, int j) const {
        return this->get(i,j);
    }

    NormalMatrix<T> &operator=(const SpecialOperationInterface<T> &theMatrix) override {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this != &theMatrix) {
            delete[]this->element;
            this->columns = theMatrix.columns;
            this->size=theMatrix.size;
            this->element = new T[this->size];
            copy(theMatrix.element, theMatrix.element + this->size, this->element);
        }
        return *this;
    }

    NormalMatrix<T> *operator+(const SpecialOperationInterface<T> &theMatrix) const override {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();

        if (this->size!=theMatrix.size||this->columns!=theMatrix.columns)throw matrixSizeMismatchOfPlus();
        auto result=new NormalMatrix<T>(this->rows, this->columns);
        result.initialize();
        for (int i = 0; i < this->size; i++) {
            result.element[i] = this->element[i] + theMatrix.element[i];
        }
        return result;
    }

    NormalMatrix<T> *operator-(const SpecialOperationInterface<T> &theMatrix) const override {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this->size!=theMatrix.size||this->columns!=theMatrix.columns)throw matrixSizeMismatchOfPlus();
        auto result=new NormalMatrix<T>(this->rows, this->columns);
        result.initialize();
        for (int i = 0; i < this->size; i++) {
            result.element[i] = this->element[i] - theMatrix.element[i];
        }
        return result;
    }

    NormalMatrix<T> *operator*(const SpecialOperationInterface<T> &theMatrix) const override {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        int rowOfMatrix=theMatrix.size/theMatrix.columns;//参数所代表的矩阵的行数
        int rowOfMatrix2=this->size/this->columns;//本矩阵的行数
        if (this->columns!=rowOfMatrix)throw matrixSizeMismatchOfMultiply("执行矩阵乘法时不满足矩阵乘法的条件");
        auto result=new NormalMatrix<T>(rowOfMatrix2*theMatrix.columns);
        result->initialize();
        for (int i = 0; i < rowOfMatrix2; i++) {
            for (int j = 0; j < theMatrix.columns; j++) {
                T sum = 0;
                for (int k = 0; k < this->columns; k++) {
                    sum += this->element[i * this->columns + k] * theMatrix.element[k * theMatrix.columns + j];
                }
                result->set(i + 1, j + 1, sum);
            }
        }
        return result;
    }

    //每个矩阵元素加上固定的值
   virtual void operator+=(const T &theElement) const {
        if (!this->initialized)throw uninitializedMatrix();

        for (int i = 0; i < this->size; i++)
            this->element[i] += theElement;
    }

    //每个矩阵元素减去固定的值
   virtual void operator-=(const T &theElement) const {
        if (!this->initialized)throw uninitializedMatrix();
        for (int i = 0; i < this->size; i++)
            this->element[i] -= theElement;

    }



    //其他常规接口

    //初始化矩阵，将传入的二维数组映射到内部的一维数组中
    void initialize(vector<vector<int>>theMatrix) {
        int column=theMatrix.at(0).size();
        int theMatrixSize=theMatrix.size()*column;
        if (this->initialized)throw reInitializedMatrix();
        if (this->columns!=column||this->size!=theMatrixSize)throw matrixSizeMismatchOfInitialize();
        int index = 0;
        for (int i = 0; i < theMatrix.size(); i++) {
            for (int j = 0; j < column; j++) {
                this->element[index] = theMatrix.at(i).at(j);
                index++;
            }
        }
        this->initialized = true;
    }


    //重载初始化函数，目的是初始化一个空的矩阵，将矩阵所有元素置零
    void initialize() {
        if (this->initialized)throw reInitializedMatrix();//如果矩阵已经初始化了就不需要再初始化了
        for (int i = 0; i < this->size/this->columns; i++) {
            for (int j = 0; j < this->columns; j++) {
                this->element[i * this->columns + j] = 0;
            }
        }
        this->initialized = true;
    }

    virtual NormalMatrix<T> *transpose() {
        if (!this->initialized)throw uninitializedMatrix();
        auto temp = new NormalMatrix<T>(this->size);
        temp->initialize();
        for (int i = 0; i < this->columns; i++) {
            for (int j = 0; j < this->size/ this->columns; j++) {
                temp(j + 1, i + 1) = this->element[i * this->columns + j];
            }
        }
        return temp;
    }

};
