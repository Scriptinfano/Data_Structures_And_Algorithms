#pragma once

#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"
#include <iostream>
#include <algorithm>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\matrix\VirtualBaseMatrix.h"
using namespace std;
using namespace ExceptionSpace;

//�˾�����������ľ���
template<class T>
class NormalMatrix : public NormalMatrixProperties<T>, public SpecialOperationInterface<T> {

    friend ostream &operator<<(ostream &out, const NormalMatrix <T> &theMatrix) {
        for (int i = 0; i < theMatrix.size; i++) {
            out << theMatrix.element[i] << " ";
            if ((i + 1) % theMatrix.columns == 0)out << endl;
        }
        return out;
    }
public://���еĹ��������������캯��
    NormalMatrix(const int&matrixSize) {
        if (matrixSize<4)throw IllegalParameterValue("�������ʱ�������Ԫ�ظ�������С��4");
        this->element=new T[matrixSize];
        this->initialized=false;
        //column������ʱ��ָ��������initializeʱ��ָ��
    }

    NormalMatrix(const NormalMatrix<T> &theMatrix) {
        if (!this->isInitialized())throw uninitializedMatrix();
        this->columns = theMatrix.columns;
        this->element = new T[theMatrix.size];
        this->size=theMatrix.size;
        copy(theMatrix.element, theMatrix.element + this->size, this->element);
    }

    ~NormalMatrix() { delete[]this->element; }
//˽�з���
private:
    //getter�ӿ�
    T get(int i, int j) const {
        if (!this->initialized)throw uninitializedMatrix();
        int index=(i - 1) * this->columns + (j - 1)>this->size-1;
        if (index>this->size-1) {
            throw matrixIndexOutOfBounds();
        }
        return this->element[index];
    }

    //setter�ӿ�
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



public://ʵ����������ӿ����������������������

    //�õ�����Ϊi,j������Ԫ��
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
        int rowOfMatrix=theMatrix.size/theMatrix.columns;//����������ľ��������
        int rowOfMatrix2=this->size/this->columns;//�����������
        if (this->columns!=rowOfMatrix)throw matrixSizeMismatchOfMultiply("ִ�о���˷�ʱ���������˷�������");
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

    //ÿ������Ԫ�ؼ��Ϲ̶���ֵ
   virtual void operator+=(const T &theElement) const {
        if (!this->initialized)throw uninitializedMatrix();

        for (int i = 0; i < this->size; i++)
            this->element[i] += theElement;
    }

    //ÿ������Ԫ�ؼ�ȥ�̶���ֵ
   virtual void operator-=(const T &theElement) const {
        if (!this->initialized)throw uninitializedMatrix();
        for (int i = 0; i < this->size; i++)
            this->element[i] -= theElement;

    }



    //��������ӿ�

    //��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������
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


    //���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������
    void initialize() {
        if (this->initialized)throw reInitializedMatrix();//��������Ѿ���ʼ���˾Ͳ���Ҫ�ٳ�ʼ����
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
