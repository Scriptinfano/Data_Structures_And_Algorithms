/*��������Ҫ��ʾ��������ѹ���洢���������Ӧ��ӳ�亯��
 * */
#pragma once

#include <iostream>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\namespaces.h"

using namespace std;
using namespace ExceptionSpace;

//�������ĳ�����࣬�þ���Ϊ���������Ըþ����Ҳ���Ƿ���
template<class T>
class virtualDiagonalMatrix {
protected:
    int dimension;
    T *element;
    bool initialized;
public:
    virtual T get(const int &i, const int &j) const = 0;

    virtual void set(const int &i, const int &j, const T &theElement) = 0;

    virtual virtualDiagonalMatrix<T> operator+(const virtualDiagonalMatrix<T> &theMatrix) const = 0;//����ӷ�

    virtual virtualDiagonalMatrix<T> operator-(const virtualDiagonalMatrix<T> &theMatrix) const = 0;//�������

    virtual virtualDiagonalMatrix<T> operator*(const virtualDiagonalMatrix<T> &theMatrix) const = 0;//����˷�

    T operator()(int i, int j) const = 0;//�õ�����Ϊi,j������Ԫ��

    //��������ӿ�
    void initialize(T *theElements, const int &theDimension) = 0;//��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������

    void initialize() = 0;//���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������

    int size() const = 0;//���ؾ�����Ԫ�صĸ���

    virtualDiagonalMatrix<T> transpose() = 0;//�����ת��

};

//�ԽǾ��󣨴˾���Ϊ����ֻ�жԽ����ϵ�Ԫ���Ƿ���Ԫ�أ�
template<class T>
class diagonalMatrix : public virtualDiagonalMatrix<T> {
public:
    diagonalMatrix(int theDimention = 10) {
        if (theDimention < 1) {
            throw IllegalParameterValue("matrix�Ĵ�С�������0");
        }
        this->dimension = theDimention;//��ģ��̳���Ҫ���ʻ����е����ݱ���ʹ��this��ע
        this->element = new T[this->dimension];
    }

    diagonalMatrix(const diagonalMatrix<T> &theMatrix) {
        if (!this->initialized)throw uninitializedMatrix();
        this->dimension = theMatrix.dimension;
        this->element = new T[this->dimension];
        copy(theMatrix.element, theMatrix.element + this->dimension, this->element);
    }

    ~diagonalMatrix() { delete[]virtualDiagonalMatrix<T>::element; }

    //����ӿ�
    virtual T operator()(int i, int j) const//��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i == j)return virtualDiagonalMatrix<T>::element[i - 1];//�Խ����ϵ�Ԫ�ز��Ƿ���Ԫ��
        else return 0;
    }

    virtual T get(const int &i, const int &j) const//��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i == j)return virtualDiagonalMatrix<T>::element[i - 1];//�Խ����ϵ�Ԫ�ز��Ƿ���Ԫ��
        else return 0;
    }

    virtual void set(const int &i, const int &j, const T &theElement)//���±�Ϊi,j��Ԫ����Ϊ��һ��ֵ
    {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension)
            throw matrixIndexOutOfBounds();
        if (i == j)virtualDiagonalMatrix<T>::element[i - 1] = theElement;
        else {
            if (theElement != 0)throw IllegalParameterValue("��ֵʧ�ܣ���Ϊ�ڶԽǾ����У��ǶԽ����ϵ�Ԫ�ر�����0");
        }
    }

    //����ļӼ��˲���

    //����ӷ�
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

    //�������
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

    //����˷�
    virtual diagonalMatrix<T> operator*(const virtualDiagonalMatrix<T> &theMatrix) const {

    }

    //��������ӿ�
    //��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������
    virtual void initialize(T *theElements, const int &theDimension) {
        if (this->initialized)throw reinitializedMatrix();
        if (theDimension != this->dimension)throw matrixSizeMismatchOfInitialize();
        int index = 0;
        for (int i = 0; i < theDimension; i++) {
            this->element[index++] = theElements[i * theDimension + i];
        }
        this->initialized = true;
    }

    //���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������
    virtual void initialize() {
        if (this->initialized)throw reinitializedMatrix();
        int index = 0;
        for (int i = 0; i < this->dimension; i++) {
            this->element[index++] = 0;
        }
        this->initialized = true;
    }

    //���ؾ�����Ԫ�صĸ���
    virtual int size() const {
        return pow(this->dimension, 2);
    }

    //�����ת��
    virtual diagonalMatrix<T> transpose() {

    }


};

//���ԽǾ��󣨴˾���Ϊ���󣩣������ԽǾ��������Խ���ӳ��ķ�ʽѹ���洢�������������ַ���ѹ���洢���ԽǾ��󣬼�����ӳ�������ӳ��
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

    tripleDiagonalMatrix(const tripleDiagonalMatrix<T> &theMatrix) {
        if (!this->initialized)throw uninitializedMatrix();
        this->dimension = theMatrix.dimension;
        this->element = new T[3 * this->dimension - 2];//���ԽǾ���Ԫ����3*n-2
        copy(theMatrix.element, theMatrix.element + this->dimension, this->element);
    }

    ~tripleDiagonalMatrix() { delete[]virtualDiagonalMatrix<T>::element; }

    virtual T operator()(int i, int j) const//��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    {
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
            default:
                return 0;
        }
    }

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
            default:
                return 0;
        }
    }

    //���±�Ϊi,j��Ԫ����Ϊ��һ��ֵ
    void set(const int &i, const int &j, const T &theElement) {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension)
            throw matrixIndexOutOfBounds();
        switch (i - j) {
            case 1://i-j=1ʱΪ�¶Խ���
                this->element[i - 2] = theElement;
            case 0:
                this->element[this->dimension + i - 2] = theElement;
            case -1:
                this->element[2 * this->element + i - 2] = theElement;
        }
    }

    //����ļӼ��˲���
    virtual tripleDiagonalMatrix<T> operator+(const virtualDiagonalMatrix<T> &theMatrix) const {
    }
//����ӷ�

    virtual tripleDiagonalMatrix<T> operator-(const virtualDiagonalMatrix<T> &theMatrix) const {
    }
//�������

    virtual tripleDiagonalMatrix<T> operator*(const virtualDiagonalMatrix<T> &theMatrix) const {
    }
//����˷�


    //��������ӿ�
    //��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������
    virtual void initialize(T *theElements, const int &theDimension) {
    }

    //���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������
    virtual void initialize() {
    }

    //���ؾ�����Ԫ�صĸ���
    virtual int size() const {
    }

    //�����ת��
    virtual tripleDiagonalMatrix<T> transpose() {
    }

};

template<class T>
class lowerTriangularMatrix : public virtualDiagonalMatrix<T> {
public:
    lowerTriangularMatrix(int theDimention = 10) {
        if (theDimention < 1) {
            throw IllegalParameterValue("matrix�Ĵ�С�������0");
        }
        this->dimension = theDimention;
        this->element = new T[this->dimension * (this->dimension + 1) /
                              2];//�����Ǿ���������Ǿ����Ԫ����������n*(n+1)/2
    }

    lowerTriangularMatrix(const lowerTriangularMatrix<T> &theMatrix) {
        if (!this->initialized)throw uninitializedMatrix();
        this->dimension = theMatrix.dimension;
        this->element = new T[this->dimension * (this->dimension + 1) / 2];//�����Ǿ���Ԫ����n*(n+1)/2
        copy(theMatrix.element, theMatrix.element + this->dimension, this->element);
    }

    ~lowerTriangularMatrix() { delete[]virtualDiagonalMatrix<T>::element; }

    virtual T operator()(int i, int j) const//��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i >= j)return this->element[(i * (i - 1)) / 2 + j - 1];//�����Ǿ�������ӳ�亯��i*(i-1)/2+(j-1)
        else return 0;
    }

    //����ӿ�
    T get(const int &i, const int &j) const//��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i >= j)return this->element[(i * (i - 1)) / 2 + j - 1];
        else return 0;
    }

    void set(const int &i, const int &j, const T &theElement)//���±�Ϊi,j��Ԫ����Ϊ��һ��ֵ
    {
        if (i < 1 || j < 1 || i > virtualDiagonalMatrix<T>::dimension || j > virtualDiagonalMatrix<T>::dimension)
            throw matrixIndexOutOfBounds();
        if (i >= j)//����������Ԫ��i>=j
            this->element[i * (i - 1) / 2 + j - 1] = theElement;
        else if (theElement != 0)throw IllegalParameterValue("�����Ǿ����в�������������Ԫ�ر���Ϊ0����������Ϊ����ֵ");
    }

    //����ļӼ��˲���
    virtual lowerTriangularMatrix<T> operator+(const virtualDiagonalMatrix<T> &theMatrix) const {

    }
//����ӷ�

    virtual lowerTriangularMatrix<T> operator-(const virtualDiagonalMatrix<T> &theMatrix) const {
    }
//�������

    virtual lowerTriangularMatrix<T> operator*(const virtualDiagonalMatrix<T> &theMatrix) const {
    }
//����˷�

    //��������ӿ�
    //��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������
    virtual void initialize(T *theElements, const int &theDimension) {
    }

    //���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������
    virtual void initialize() {
    }

    //���ؾ�����Ԫ�صĸ���
    virtual int size() const {
    }

    //�����ת��
    virtual lowerTriangularMatrix<T> transpose() {
    }


};