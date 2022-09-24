#pragma once

#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"
#include <iostream>
#include <algorithm>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\matrix\VirtualBaseMatrix.h"

using namespace std;
using namespace ExceptionSpace::MatrixExceptionSpace;
using namespace ExceptionSpace;

//�˾�����������ľ���
template<class T>
class NormalMatrix : public NormalMatrixProperties<T>, public SpecialOperationInterface<T> {

    friend ostream &operator<<(ostream &out, const NormalMatrix<T> &theMatrix) {
        for (int i = 0; i < theMatrix.size; i++) {
            out << theMatrix.element[i] << " ";
            if ((i + 1) % theMatrix.columns == 0)out << endl;
        }
        return out;
    }

public://���еĹ��������������캯��

    NormalMatrix(const int &row, const int &column) {
        if (row * column < 4)throw IllegalParameterException("�������ʱ�������Ԫ�ظ�������С��4");
        this->element = new T[row * column];
        this->initialized = false;
        this->columns = column;
        this->size = row * column;
    }

    NormalMatrix(const NormalMatrix<T> &theMatrix) {
        if (!this->initialized)throw MatrixUnInitializeException();
        this->columns = theMatrix.columns;
        this->element = new T[theMatrix.size];
        this->size = theMatrix.size;
        copy(theMatrix.element, theMatrix.element + this->size, this->element);
    }

    ~NormalMatrix() { delete[]this->element; }
public:    //���е�getter�ӿں�setter�ӿ�


    T get(int i, int j) const override {
        if (!this->initialized)throw MatrixUnInitializeException();
        int index = (i - 1) * this->columns + (j - 1);
        if (index > this->size - 1) {
            throw matrixIndexOutOfBounds();
        }
        return this->element[index];
    }

    void set(int i, int j, const T &theElement) override {
        if (!this->initialized)throw MatrixUnInitializeException();
        int index = (i - 1) * this->columns + (j - 1);
        if (index > this->size - 1) {
            throw matrixIndexOutOfBounds();
        }
        this->element[index] = theElement;
    }

    T &get(int i, int j) override {
        if (!this->initialized)throw MatrixUnInitializeException();
        int index = (i - 1) * this->columns + (j - 1);
        if (index > this->size - 1) {
            throw matrixIndexOutOfBounds();
        }
        return this->element[index];
    }

public://ʵ����������ӿ����������������������


    //�õ�����Ϊi,j������Ԫ��
    T operator()(int i, int j) const override {
        return this->get(i, j);
    }

    NormalMatrix<T> &operator=(const SpecialOperationInterface<T> &theMatrix) override {
        try {
            auto theMatrixCast = dynamic_cast<const NormalMatrix<T> &>(theMatrix);//�����е�theMatrix��һ��ָ�����������Ļ������ã���Ҫʹ������ת��ʵ�ֵ����������еķ���
            if (!this->initialized || !theMatrixCast.initialized)throw MatrixUnInitializeException();
            if (this != &theMatrixCast) {
                delete[]this->element;
                this->columns = theMatrixCast.columns;
                this->size = theMatrixCast.size;
                this->element = new T[this->size];
                copy(theMatrixCast.element, theMatrixCast.element + this->size, this->element);
            }
        } catch (bad_cast &exception) {
            throw MatrixDynamicCastException();
        }
        return *this;
    }

    NormalMatrix<T> *operator+(const SpecialOperationInterface<T> &theMatrix) const override {
        try {
            const NormalMatrix<T> &theMatrixCast = dynamic_cast<const NormalMatrix<T> &>(theMatrix);//�����е�theMatrix��һ��ָ�����������Ļ������ã���Ҫʹ������ת��ʵ�ֵ����������еķ���
            if (!this->initialized || !theMatrixCast.initialized)throw MatrixUnInitializeException();
            if (this->size != theMatrixCast.size || this->columns != theMatrixCast.columns)throw matrixSizeMismatchOfPlus();
            auto result = new NormalMatrix<T>(this->size / this->columns, this->columns);
            result->initialize();
            for (int i = 0; i < this->size; i++) {
                result->element[i] = this->element[i] + theMatrixCast.element[i];
            }
            return result;
        } catch (bad_cast &exception) {
            throw MatrixDynamicCastException();
        }

    }

    NormalMatrix<T> *operator-(const SpecialOperationInterface<T> &theMatrix) const override {
        try {
            const NormalMatrix<T> &theMatrixCast = dynamic_cast<const NormalMatrix<T> &>(theMatrix);//�����е�theMatrix��һ��ָ�����������Ļ������ã���Ҫʹ������ת��ʵ�ֵ����������еķ���
            if (!this->initialized || !theMatrixCast.initialized)throw MatrixUnInitializeException();
            if (this->size != theMatrixCast.size || this->columns != theMatrixCast.columns)throw matrixSizeMismatchOfPlus();
            auto result = new NormalMatrix<T>(this->size / this->columns, this->columns);
            result->initialize();
            for (int i = 0; i < this->size; i++) {
                result->element[i] = this->element[i] - theMatrixCast.element[i];
            }
            return result;

        } catch (bad_cast &exception) {
            throw MatrixDynamicCastException();
        }
    }

    NormalMatrix<T> *operator*(const SpecialOperationInterface<T> &theMatrix) const override {
        try {
            const NormalMatrix<T> &theMatrixCast = dynamic_cast<const NormalMatrix<T> &>(theMatrix);//�����е�theMatrix��һ��ָ�����������Ļ������ã���Ҫʹ������ת��ʵ�ֵ����������еķ���
            if (!this->initialized || !theMatrixCast.initialized)throw MatrixUnInitializeException();
            int rowOfMatrix = theMatrixCast.size / theMatrixCast.columns;//����������ľ��������
            int rowOfMatrix2 = this->size / this->columns;//�����������
            if (this->columns != rowOfMatrix)throw matrixSizeMismatchOfMultiply("ִ�о���˷�ʱ���������˷�������");
            auto result = new NormalMatrix<T>(rowOfMatrix2, theMatrixCast.columns);
            result->initialize();
            for (int i = 0; i < rowOfMatrix2; i++) {
                for (int j = 0; j < theMatrixCast.columns; j++) {
                    T sum = 0;
                    for (int k = 0; k < this->columns; k++) {
                        sum += this->element[i * this->columns + k] * theMatrixCast.element[k * theMatrixCast.columns + j];
                    }
                    result->set(i + 1, j + 1, sum);
                }
            }
            return result;
        } catch (bad_cast &exception) {
            throw MatrixDynamicCastException();
        }
    }

    //ÿ������Ԫ�ؼ��Ϲ̶���ֵ
    virtual void operator+=(const T &theElement) const override {
        if (!this->initialized)throw MatrixUnInitializeException();

        for (int i = 0; i < this->size; i++)
            this->element[i] += theElement;
    }

    //ÿ������Ԫ�ؼ�ȥ�̶���ֵ
    virtual void operator-=(const T &theElement) const override {
        if (!this->initialized)throw MatrixUnInitializeException();
        for (int i = 0; i < this->size; i++)
            this->element[i] -= theElement;

    }



    //��������ӿ�

    //��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������
    void initialize(const vector<vector<int>> &theMatrix) override {
        int column = theMatrix.at(0).size();
        int theMatrixSize = theMatrix.size() * column;
        if (this->initialized)throw MatrixReinitializeException();
        if (this->columns != column || this->size != theMatrixSize)throw matrixSizeMismatchOfInitialize();
        int index = 0;
        for (auto &i: theMatrix) {
            for (int j = 0; j < column; j++) {
                this->element[index] = i.at(j);
                index++;
            }
        }
        this->initialized = true;
    }


    //���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������
    void initialize() override {
        if (this->initialized)throw MatrixReinitializeException();//��������Ѿ���ʼ���˾Ͳ���Ҫ�ٳ�ʼ����
        for (int i = 0; i < this->size / this->columns; i++) {
            for (int j = 0; j < this->columns; j++) {
                this->element[i * this->columns + j] = 0;
            }
        }
        this->initialized = true;
    }

    virtual NormalMatrix<T> *transpose() override {
        if (!this->initialized)throw MatrixUnInitializeException();
        auto temp = new NormalMatrix<T>(this->size / this->columns, this->columns);
        temp->initialize();
        for (int i = 0; i < this->columns; i++) {
            for (int j = 0; j < this->size / this->columns; j++) {
                T theElement = this->element[j * this->columns + i];
                temp->set(i + 1, j + 1, theElement);
            }
        }
        return temp;
    }


};
