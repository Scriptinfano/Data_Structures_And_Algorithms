/*��������Ҫ��ʾ��������ѹ���洢���������Ӧ��ӳ�亯��
 *����ƾ�����ʱҪע���������±�����±궼�Ǵ�1��ʼ�ģ��������0��ʼ�ǲ�һ���� */
#pragma once

#include <iostream>
#include <cmath>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\namespaces.h"

using namespace std;
using namespace ExceptionSpace;

//�������ĳ�����࣬�þ���Ϊ���������Ըó����������������о������ڲ��Բ���һά�������洢��������еķ���Ԫ��
template<class T>
class virtualDiagonalMatrixAsRegularArray {
protected:
    int dimension;
    T *element;
public:
    bool initialized;
public:
    virtual T get(const int &i, const int &j) const = 0;//�����±�Ϊi,j�ľ���Ԫ��

    virtual void set(const int &i, const int &j, const T &theElement) = 0;//���±�Ϊi,j�ľ���Ԫ����Ϊ��һ��ֵ

    virtual virtualDiagonalMatrixAsRegularArray<T> *operator+(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const = 0;//����ӷ�

    virtual virtualDiagonalMatrixAsRegularArray<T> *operator-(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const = 0;//�������

    virtual virtualDiagonalMatrixAsRegularArray<T> *operator*(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const = 0;//����˷�

    virtual T operator()(int i, int j) const = 0;//�õ�����Ϊi,j������Ԫ��

    //��������ӿ�
    virtual void initialize(T *theElements, const int &theDimension) = 0;//��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������

    virtual void initialize() = 0;//���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������

    virtual int size() const = 0;//���ؾ�����Ԫ�صĸ���

    virtual virtualDiagonalMatrixAsRegularArray<T> *transpose() = 0;//�����ת��

    //����˽�г�Ա�Ĺ��нӿڣ����ɷ���ά��dimension�����������Բ���ֱ�ӷ���
    int getDimension() const { return dimension; }//�����������ֱ�Ӽ̳�ʹ�ô˽ӿڣ�������д

};

//�ԽǾ��󣨴˾���Ϊ����ֻ�жԽ����ϵ�Ԫ���Ƿ���Ԫ�أ�
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
            throw IllegalParameterValue("matrix�Ĵ�С�������0");
        }
        this->dimension = theDimension;//��ģ��̳���Ҫ���ʻ����е����ݱ���ʹ��this��ע
        this->element = new T[this->dimension];
        this->initialized = false;
    }

    diagonalMatrix(const diagonalMatrix<T> &theMatrix) {
        if (!theMatrix->initialized)throw uninitializedMatrix("ʹ��δ��ʼ���ľ��󿽱������µľ����ǲ��������");
        this->dimension = theMatrix.dimension;
        this->element = new T[this->dimension];
        this->initialized = true;
        copy(theMatrix.element, theMatrix.element + this->dimension, this->element);
    }

    ~diagonalMatrix() { delete[]this->element; }

    //����ӿ�
    virtual T operator()(int i, int j) const//��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i == j)return this->element[i - 1];//�Խ����ϵ�Ԫ�ز��Ƿ���Ԫ��
        else return 0;
    }

    virtual T get(const int &i, const int &j) const//��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i == j)return this->element[i - 1];//�Խ����ϵ�Ԫ�ز��Ƿ���Ԫ��
        else return 0;
    }

    virtual void set(const int &i, const int &j, const T &theElement)//���±�Ϊi,j��Ԫ����Ϊ��һ��ֵ
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        if (i == j)this->element[i - 1] = theElement;
        else {
            if (theElement != 0)throw IllegalParameterValue("��ֵʧ�ܣ���Ϊ�ڶԽǾ����У��ǶԽ����ϵ�Ԫ�ر�����0");
        }
    }

    //����ļӼ��˲���

    //����ӷ�
    virtual diagonalMatrix<T> *operator+(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
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

    //�������
    virtual diagonalMatrix<T> *operator-(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new diagonalMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            result->set(i + 1, i + 1, this->element[i] - theMatrix.get(i + 1, i + 1));
        }
        return result;

    }

    //����˷�
    virtual diagonalMatrix<T> *operator*(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
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
                        //i==k��k==j�����
                        sum += this->element[k] * theMatrix.get(k + 1, k + 1);
                    }
                }
                result->set(i + 1, j + 1, sum);
            }
        }
        return result;

    }

    //��������ӿ�
    //��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������
    virtual void initialize(T *theElements, const int &theDimension) {
        if (this->initialized)throw reInitializedMatrix();
        if (theDimension != this->dimension)throw matrixSizeMismatchOfInitialize();
        int index = 0;
        for (int i = 0; i < theDimension; i++) {
            this->element[i] = theElements[i * (theDimension + 1)];
        }
        this->initialized = true;
    }

    //���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������
    virtual void initialize() {
        if (this->initialized)throw reInitializedMatrix();
        for (int i = 0; i < this->dimension; i++) {
            this->element[i] = 0;
        }
        this->initialized = true;
    }

    //���ؾ�����Ԫ�صĸ���
    virtual int size() const {
        return pow(this->dimension, 2);
    }

    //�����ת��
    virtual diagonalMatrix<T> *transpose() {
        return this;//�ԽǾ���ת��֮���Ԫ�ص�λ�ò������ı�
    }


};

//������Խ���ӳ������ԽǾ��󣬻����������ַ���ѹ���洢���ԽǾ��󣬼�����ӳ�������ӳ��
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
            throw IllegalParameterValue("matrix�Ĵ�С�������0");
        }
        this->dimension = theDimension;
        this->element = new T[3 * this->dimension - 2];//���ԽǾ���ķ���Ԫ�صĸ�����3*n-2
        this->initialized = false;
    }

    tripleDiagonalMatrix(const tripleDiagonalMatrix<T> &theMatrix) {
        if (!theMatrix->initialized)throw uninitializedMatrix("ʹ��δ��ʼ���ľ��󿽱������µľ����ǲ��������");
        this->dimension = theMatrix.dimension;
        this->element = new T[3 * this->dimension - 2];//���ԽǾ���Ԫ����3*n-2
        copy(theMatrix.element, theMatrix.element + this->dimension, this->element);
        this->initialized = true;
    }

    ~tripleDiagonalMatrix() { delete[]this->element; }

    virtual T operator()(int i, int j) const//��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        //ȷ��Ҫ���ص�Ԫ��
        switch (i - j) {
            case 1://i-j=1ʱΪ�¶Խ���
                return this->element[i - 2];
            case 0://i-j=0ʱΪ���Խ���
                return this->element[this->dimension + i - 2];
            case -1://i-j=-1ʱΪ�϶Խ���
                return this->element[2 * this->dimension + i - 2];
            default:
                return 0;
        }
    }

    //��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    virtual T get(const int &i, const int &j) const {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        //ȷ��Ҫ���ص�Ԫ��
        switch (i - j) {
            case 1://i-j=1ʱΪ�¶Խ���
                return this->element[i - 2];
            case 0://i-j=0ʱΪ���Խ���
                return this->element[this->dimension + i - 2];
            case -1://i-j=-1ʱΪ�϶Խ���
                return this->element[2 * this->dimension + i - 2];
            default:
                return 0;
        }
    }

    //���±�Ϊi,j��Ԫ����Ϊ��һ��ֵ
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
                if (theElement != 0)throw invalidMatrixValueSet();
            }
        }
    }

    //����ļӼ��˲���
    virtual tripleDiagonalMatrix<T> *operator+(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
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

    virtual tripleDiagonalMatrix<T> *operator-(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
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

    virtual tripleDiagonalMatrix<T> *operator*(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
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

    //��������ӿ�
    //��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������
    virtual void initialize(T *theElements, const int &theDimension) {
        if (this->initialized)throw reInitializedMatrix();
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                this->set(i + 1, j + 1, theElements[i * theDimension + j]);
            }
        }
        this->initialized = true;
    }

    //���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������
    virtual void initialize() {
        if (this->initialized)throw reInitializedMatrix();
        for (int i = 0; i < this->size(); i++) {
            this->element[i] = 0;
        }
        this->initialized = true;
    }

    //���ؾ�����Ԫ�ص�ʵ�ʸ���
    virtual int size() const {
        return 3 * this->dimension - 2;
    }

    //���ԽǾ����ת��
    virtual tripleDiagonalMatrix<T> *transpose() {
        if (!this->initialized)throw uninitializedMatrix();
        auto temp = new tripleDiagonalMatrix<T>(this->getDimension());
        for (int i = 0; i < this->getDimension(); i++) {
            for (int j = 0; j < this->dimension; j++) {
                temp->set(i + 1, j + 1, this->get(j + 1, i + 1));
            }
        }
        return temp;

    }

private:
    void output() const//�ýӿڽ�������ʹ�ã�����ڲ�element�����е�ÿһ��Ԫ��
    {
        for (int i = 0; i < this->size(); i++) {
            cout << this->element[i] << " ";
        }
    }
};

template<class T>
class upperDiagonalMatrix;//ģ�����ǰ���������ڶ���lowerTriangularMatrix���transpose����ʱ���õ�


//��������ӳ��������Ǿ���
template<class T>
class lowerTriangularMatrix : public virtualDiagonalMatrixAsRegularArray<T> {
    friend ostream &operator<<(ostream &out, const lowerTriangularMatrix<T> &theMatrix) {
        int index = 0;
        int theDimension = theMatrix.dimension;
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                if (i >= j) {
                    //��i>=jʱ��Ԫ������������
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
            throw IllegalParameterValue("matrix�Ĵ�С�������0");
        }
        this->dimension = theDimension;
        this->element = new T[this->dimension * (this->dimension + 1) / 2];//�����Ǿ���������Ǿ����Ԫ����������n*(n+1)/2
        this->initialized = false;
    }

    lowerTriangularMatrix(const lowerTriangularMatrix<T> &theMatrix) {
        if (!theMatrix.initialized)throw uninitializedMatrix("ʹ��δ��ʼ���ľ��󿽱������µľ����ǲ��������");
        this->dimension = theMatrix.getDimension();
        this->element = new T[theMatrix.getDimension() * (theMatrix.getDimension() + 1) / 2];//�����Ǿ���Ԫ����n*(n+1)/2
        copy(theMatrix.element, theMatrix.element + this->size(), this->element);
        this->initialized = true;
    }

    ~lowerTriangularMatrix() { delete[]this->element; }

    virtual T operator()(int i, int j) const//��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i >= j)return this->element[(i * (i - 1)) / 2 + j - 1];//�����Ǿ�������ӳ�亯��i*(i-1)/2+(j-1)
        else return 0;
    }

    //����ӿ�
    virtual T get(const int &i, const int &j) const//��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        int result = this->element[(i * (i - 1)) / 2 + j - 1];
        if (i >= j)return result;
        else return 0;
    }

    virtual void set(const int &i, const int &j, const T &theElement)//���±�Ϊi,j��Ԫ����Ϊ��һ��ֵ
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        if (i >= j)//����������Ԫ��i>=j
        {
            int index = i * (i - 1) / 2 + j - 1;
            this->element[index] = theElement;
        } else {
            if (theElement != 0)throw invalidMatrixValueSet();
        }
    }

    //����ļӼ��˲���
    //����ӷ�
    virtual lowerTriangularMatrix<T> *operator+(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
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

    //�������
    virtual lowerTriangularMatrix<T> *operator-(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new lowerTriangularMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                result->set(i + 1, j + 1, this->get(i + 1, j + 1) - theMatrix.get(i + 1, j + 1));
            }
        }
        return result;

    }

    //����˷�
    virtual lowerTriangularMatrix<T> *operator*(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfMultiply();
        auto result = new lowerTriangularMatrix<T>(this->dimension);
        result->initialize();
        int theDimension = result->getDimension();//���Դ���
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

    //��������ӿ�
    //��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������
    virtual void initialize(T *theElements, const int &theDimension) {
        if (this->initialized)throw reInitializedMatrix();
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                this->set(i + 1, j + 1, theElements[i * theDimension + j]);
            }
        }
        this->initialized = true;

    }

    //���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������
    virtual void initialize() {
        if (this->initialized)throw reInitializedMatrix();
        for (int i = 0; i < this->size(); i++) {
            this->element[i] = 0;
        }
        this->initialized = true;
    }

    //���ؾ�����Ԫ�صĸ���
    virtual int size() const {
        return this->dimension * (this->dimension + 1) / 2;
    }

    //�����ת��
    virtual upperDiagonalMatrix<T> *transpose() {
        if (!this->initialized)throw uninitializedMatrix();
        auto temp = new upperDiagonalMatrix<T>(this->getDimension());
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                temp->set(i + 1, j + 1, this->get(j + 1, i + 1));
            }
        }
        return temp;
    }
};


//��������ӳ��������Ǿ���
template<class T>
class upperDiagonalMatrix : public virtualDiagonalMatrixAsRegularArray<T> {
    friend ostream &operator<<(ostream &out, const upperDiagonalMatrix<T> &theMatrix) {
        int index = 0;
        int theDimension = theMatrix.dimension;
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                if (i <= j) {
                    //��i<=jʱ��Ԫ������������
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
    upperDiagonalMatrix(int theDimension = 10) {
        if (theDimension < 1) {
            throw IllegalParameterValue("matrix�Ĵ�С�������0");
        }
        this->dimension = theDimension;
        this->element = new T[this->dimension * (this->dimension + 1) / 2];//�����Ǿ���������Ǿ����Ԫ����������n*(n+1)/2
        this->initialized = false;
    }

    upperDiagonalMatrix(const upperDiagonalMatrix<T> &theMatrix) {
        if (!theMatrix.initialized)throw uninitializedMatrix();
        this->dimension = theMatrix.getDimension();
        this->element = new T[theMatrix.getDimension() * (theMatrix.getDimension() + 1) / 2];//�����Ǿ���Ԫ����n*(n+1)/2
        copy(theMatrix.element, theMatrix.element + this->size(), this->element);
        this->initialized = true;
    }

    ~upperDiagonalMatrix() { delete[]this->element; }

    virtual T operator()(int i, int j) const//��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i <= j)return this->element[((2 * this->dimension - i + 2) * (i - 1)) / 2 + j - i];//���������Ǿ��������ӳ�亯��
        else return 0;
    }

    //����ӿ�
    virtual T get(const int &i, const int &j) const//��ȡ�±�Ϊ(i,j)�ľ���Ԫ��
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension) {
            throw matrixIndexOutOfBounds();
        }
        if (i <= j)return this->element[((2 * this->dimension - i + 2) * (i - 1)) / 2 + j - i];//���������Ǿ��������ӳ�亯��
        else return 0;
    }

    virtual void set(const int &i, const int &j, const T &theElement)//���±�Ϊi,j��Ԫ����Ϊ��һ��ֵ
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        if (i <= j)//����������Ԫ��i>=j
        {
            int index = ((2 * this->dimension - i + 2) * (i - 1)) / 2 + j - i;
            this->element[index] = theElement;
        } else {
            if (theElement != 0)throw invalidMatrixValueSet();
        }
    }

    //����ļӼ��˲���
    //����ӷ�
    virtual upperDiagonalMatrix<T> *operator+(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new upperDiagonalMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                int setValue = this->get(i + 1, j + 1) + theMatrix.get(i + 1, j + 1);
                result->set(i + 1, j + 1, setValue);
            }
        }
        return result;

    }

    //�������
    virtual upperDiagonalMatrix<T> *operator-(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new upperDiagonalMatrix<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                result->set(i + 1, j + 1, this->get(i + 1, j + 1) - theMatrix.get(i + 1, j + 1));
            }
        }
        return result;

    }

    //����˷�
    virtual upperDiagonalMatrix<T> *operator*(const virtualDiagonalMatrixAsRegularArray<T> &theMatrix) const {
        if (!this->initialized || !theMatrix.initialized)throw uninitializedMatrix();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfMultiply();
        auto result = new upperDiagonalMatrix<T>(this->dimension);
        result->initialize();
        int theDimension = result->getDimension();//���Դ���
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

    //��������ӿ�
    //��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������
    virtual void initialize(T *theElements, const int &theDimension) {
        if (this->initialized)throw reInitializedMatrix();
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                this->set(i + 1, j + 1, theElements[i * theDimension + j]);
            }
        }
        this->initialized = true;

    }

    //���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������
    virtual void initialize() {
        if (this->initialized)throw reInitializedMatrix();
        for (int i = 0; i < this->size(); i++) {
            this->element[i] = 0;
        }
        this->initialized = true;
    }

    //���ؾ�����Ԫ�صĸ���
    virtual int size() const {
        return this->dimension * (this->dimension + 1) / 2;
    }

    //ע�������Ǿ���ת��֮���������Ǿ���
    virtual lowerTriangularMatrix<T> *transpose() {
        if (!this->initialized)throw uninitializedMatrix();
        auto temp = new lowerTriangularMatrix<T>(this->getDimension());
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                temp->set(i + 1, j + 1, this->get(j + 1, i + 1));
            }
        }
        return temp;
    }

};

//���������������Ҳ���������ĳ�����࣬�����Ըó����������������о������ڲ��Բ��ò�����Ķ�ά�������洢��������еķ���Ԫ��
template<class T>
class virtualDiagonalMatrixAsIrregularArray {
protected:
    int dimension;
    T **element;
    bool initialized;
public:
    //����˽�����ݵĹ��нӿ�
    int getDimension() const { return dimension; }

    bool isInitialized() const { return initialized; }

    //���湫�нӿ�
    virtual T get(const int &i, const int &j) const = 0;//�����±�Ϊi,j�ľ���Ԫ��

    virtual void set(const int &i, const int &j, const T &theElement) = 0;//���±�Ϊi,j�ľ���Ԫ����Ϊ��һ��ֵ

    virtual virtualDiagonalMatrixAsIrregularArray<T> *operator+(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const = 0;//����ӷ�

    virtual virtualDiagonalMatrixAsIrregularArray<T> *operator-(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const = 0;//�������

    virtual virtualDiagonalMatrixAsIrregularArray<T> *operator*(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const = 0;//����˷�

    virtual T operator()(int i, int j) const = 0;//�õ�����Ϊi,j������Ԫ��

    virtual void initialize(T *theElements, const int &theDimension) = 0;//��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������

    virtual void initialize() = 0;//���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������

    virtual int size() const = 0;//���ؾ�����Ԫ�صĸ���

    virtual virtualDiagonalMatrixAsIrregularArray<T> *transpose() const = 0;//�����ת��


};

//�ڲ����ö�ά����ʵ�ֵģ�ӳ�䷽ʽ��������ӳ�䷽ʽʵ�ֵ����ԽǾ���
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
    //���죬�������죬�����ӿ�
    tripleDiagonalMatrixAsIrregularArray(const int &theDimension) {
        if (theDimension < 1)throw IllegalParameterValue("����tripleDiagonalMatrixAsIrregularArray���캯��ʱ�����ݵĲ����������1ȷ������Ĵ�С����ʵ��");
        this->dimension = theDimension;
        this->element = new T *[theDimension];
        this->element[0] = new T[2];
        for (int i = 1; i < theDimension - 1; i++)//����ά�����е�ÿһ��һά�������ռ�
        {
            this->element[i] = new T[3];
        }
        this->element[theDimension - 1] = new T[2];
        this->initialized = false;
    }

    tripleDiagonalMatrixAsIrregularArray(const tripleDiagonalMatrixAsIrregularArray<T> &theMatrix) {
        if (!theMatrix.isInitialized())throw uninitializedMatrix("ʹ��δ��ʼ���ľ��󿽱������µľ����ǲ��������");

        this->dimension = theMatrix.getDimension();
        this->element = new T *[this->dimension];
        this->element[0] = new T[2];
        for (int i = 1; i < this->dimension - 1; i++)//����ά�����е�ÿһ��һά�������ռ�
        {
            this->element[i] = new T[3];
        }
        this->element[this->dimension - 1] = new T[2];

        //����Ԫ�صĴ���
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
            delete[]this->element[i];//�ͷŶ�ά�����е�ÿһ��һά�����е�ÿһ��Ԫ��
        delete[]this->element;
    }

    //ADT����
    virtual T get(const int &i, const int &j) const//�����±�Ϊi,j�ľ���Ԫ��
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        if (abs(i - j) > 1)return 0;
        else {
            T temp;
            if (i == this->dimension && (j == this->dimension - 1 || j == this->dimension))//���һ����������������⴦��
            {
                temp = this->element[i - 1][j - 3];
                return temp;
            }
            temp = this->element[i - 1][j - 1];
            return temp;
        }
    }

    virtual void set(const int &i, const int &j, const T &theElement)//���±�Ϊi,j�ľ���Ԫ����Ϊ��һ��ֵ
    {
        if (i < 1 || j < 1 || i > this->dimension || j > this->dimension)
            throw matrixIndexOutOfBounds();
        if (abs(i - j) > 1) { if (theElement != 0)throw invalidMatrixValueSet(); }
        else {
            if (i == this->dimension && (j == this->dimension - 1 || j == this->dimension))//���һ����������������⴦��
            {
                this->element[i - 1][j - 3] = theElement;
                return;
            }
            this->element[i - 1][j - 1] = theElement;
        }
    }

    virtual tripleDiagonalMatrixAsIrregularArray<T> *operator+(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const//����ӷ�
    {
        if (!this->initialized || !theMatrix.isInitialized())throw uninitializedMatrix();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new tripleDiagonalMatrixAsIrregularArray<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                result->set(i + 1, j + 1, this->get(i + 1, j + 1) + theMatrix.get(i + 1, j + 1));
            }
        }
        return result;

    }

    virtual tripleDiagonalMatrixAsIrregularArray<T> *operator-(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const//�������
    {
        if (!this->initialized || !theMatrix.isInitialized())throw uninitializedMatrix();
        if (this->dimension != theMatrix.getDimension())throw matrixSizeMismatchOfPlus();
        auto result = new tripleDiagonalMatrixAsIrregularArray<T>(this->dimension);
        result->initialize();
        for (int i = 0; i < this->dimension; i++) {
            for (int j = 0; j < this->dimension; j++) {
                result->set(i + 1, j + 1, this->get(i + 1, j + 1) - theMatrix.get(i + 1, j + 1));
            }
        }
        return result;

    }

    virtual tripleDiagonalMatrixAsIrregularArray<T> *operator*(const virtualDiagonalMatrixAsIrregularArray<T> &theMatrix) const//����˷�
    {
        if (!this->initialized || !theMatrix.isInitialized())throw uninitializedMatrix();
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

    virtual T operator()(int i, int j) const//�õ�����Ϊi,j������Ԫ��
    {

    }

    virtual void initialize(T *theElements, const int &theDimension)//��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������
    {
        if (this->initialized)throw reInitializedMatrix();
        for (int i = 0; i < theDimension; i++) {
            for (int j = 0; j < theDimension; j++) {
                this->set(i + 1, j + 1, theElements[i * theDimension + j]);
            }
        }
        this->initialized = true;


    }

    virtual void initialize()//���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������
    {
        if (this->initialized)throw reInitializedMatrix();
        for (int i = 0; i < this->size(); i++) {
            this->element[i] = 0;
        }
        this->initialized = true;
    }

    virtual int size() const//���ؾ�����Ԫ�صĸ���
    {
        return 3 * this->dimension - 2;
    }

    virtual virtualDiagonalMatrixAsIrregularArray<T> *transpose() const//�����ת��
    {

    }


};