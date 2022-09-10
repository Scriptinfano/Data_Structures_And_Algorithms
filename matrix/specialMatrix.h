#pragma once

#include <iostream>
#include <vector>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\globalFunctionSpace.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\matrix\VirtualBaseMatrix.h"

using namespace std;
using namespace ExceptionSpace;

//TODO 定义C型矩阵
template<class T>
class C_shapedMatrix : public SquareMatrixProperties<T> {
public:
    C_shapedMatrix() {
        this->initialized = false;
    }

    ~C_shapedMatrix() {

    }
    C_shapedMatrix(const C_shapedMatrix<T>&theMatrix){

    }

public:
    void initialize(vector<vector<int>> theMatrix) override {
/*
        int size;//记录element数组中实际的元素个数
        int dimension;//方形矩阵的行数和列数实际都等于这个值
        T *element;
        bool initialized;
*/
//首先检查传入的容器是否符合方阵的定义
        int size = GlobalSpace::getMatrixSize(theMatrix);
        this->element = new T[size];
        this->dimension=theMatrix.size();
        this->initialized= true;

        int index=0;
        for(int i=0;i<theMatrix.size();i++)
        {
            for(int j=0;j<this->dimension;j++)
            {

            }
        }


    }

    void initialize() override {

    }

    bool checkInitialize(const vector<vector<T>> &theMatrix) override {

    }

protected:
    T get(int i, int j) const override {
        return nullptr;
    }

    void set(int i, int j, const T &theElement) override {

    }

};

//TODO 定义最普通的方形矩阵
template<class T>
class SquareMatrix:public SquareMatrixProperties<T>,public SpecialOperationInterface<T>{
public:
    bool checkInitialize(const vector<vector<T>> &theMatrix) override {

    }

    MatrixBasicFuncInterface<T> &operator=(const SpecialOperationInterface<T> &theMatrix) override {

    }

    MatrixBasicFuncInterface<T> *operator+(const SpecialOperationInterface<T> &theMatrix) const override {
        return nullptr;
    }

    MatrixBasicFuncInterface<T> *operator-(const SpecialOperationInterface<T> &theMatrix) const override {
        return nullptr;
    }

    MatrixBasicFuncInterface<T> *operator*(const SpecialOperationInterface<T> &theMatrix) const override {
        return nullptr;
    }

    void operator+=(const T &theElement) const override {

    }

    void operator-=(const T &theElement) const override {

    }

    void initialize(vector<vector<int>> theMatrix) override {

    }

    void initialize() override {

    }

protected:
    T get(int i, int j) const override {
        return nullptr;
    }

    void set(int i, int j, const T &theElement) override {

    }
};