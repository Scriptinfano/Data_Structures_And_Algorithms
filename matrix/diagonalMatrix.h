/*��������Ҫ��ʾ��������ѹ���洢���������Ӧ��ӳ�亯��
 *����ƾ�����ʱҪע���������±�����±궼�Ǵ�1��ʼ�ģ��������0��ʼ�ǲ�һ���� */
#pragma once

#include <iostream>
#include <cmath>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\namespaces.h"

using namespace std;
using namespace ExceptionSpace;

//�������ĳ�����࣬�þ���Ϊ���������Ըþ����Ҳ���Ƿ���
template<class T>
class virtualDiagonalMatrix {
protected:
    int dimension;
    T *element;
public:
    bool initialized;
public:
    virtual T get(const int &i, const int &j) const = 0;//�����±�Ϊi,j�ľ���Ԫ��

    virtual void set(const int &i, const int &j, const T &theElement) = 0;//���±�Ϊi,j�ľ���Ԫ����Ϊ��һ��ֵ

    virtual virtualDiagonalMatrix<T> *operator+(const virtualDiagonalMatrix<T> &theMatrix) const = 0;//����ӷ�

    virtual virtualDiagonalMatrix<T> *operator-(const virtualDiagonalMatrix<T> &theMatrix) const = 0;//�������

    virtual virtualDiagonalMatrix<T> *operator*(const virtualDiagonalMatrix<T> &theMatrix) const = 0;//����˷�

    virtual T operator()(int i, int j) const = 0;//�õ�����Ϊi,j������Ԫ��

    //��������ӿ�
    virtual void initialize(T *theElements, const int &theDimension) = 0;//��ʼ�����󣬽�����Ķ�ά����ӳ�䵽�ڲ���һά������

    virtual void initialize() = 0;//���س�ʼ��������Ŀ���ǳ�ʼ��һ���յľ��󣬽���������Ԫ������

    virtual int size() const = 0;//���ؾ�����Ԫ�صĸ���

    virtual virtualDiagonalMatrix<T> *transpose() = 0;//�����ת��

    //����˽�г�Ա�Ĺ��нӿڣ����ɷ���ά��dimension�����������Բ���ֱ�ӷ���
    int getDimension() const { return dimension; }//�����������ֱ�Ӽ̳�ʹ�ô˽ӿڣ�������д

};

//�ԽǾ��󣨴˾���Ϊ����ֻ�жԽ����ϵ�Ԫ���Ƿ���Ԫ�أ�
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
            throw IllegalParameterValue("matrix�Ĵ�С�������0");
        }
        this->dimension = theDimention;//��ģ��̳���Ҫ���ʻ����е����ݱ���ʹ��this��ע
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

    //�������
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

    //����˷�
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

//���ԽǾ��󣨴˾���Ϊ���󣩣������ԽǾ��������Խ���ӳ��ķ�ʽѹ���洢�������������ַ���ѹ���洢���ԽǾ��󣬼�����ӳ�������ӳ��
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
            throw IllegalParameterValue("matrix�Ĵ�С�������0");
        }
        this->dimension = theDimention;
        this->element = new T[3 * this->dimension - 2];//���ԽǾ���ķ���Ԫ�صĸ�����3*n-2
        this->initialized = false;
    }

    tripleDiagonalMatrix(const tripleDiagonalMatrix<T> &theMatrix) {
        if (!this->initialized)throw uninitializedMatrix();
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
                if (theElement != 0)throw invalidMatrixValueSet();
            }
        }
    }

    //����ļӼ��˲���
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


//�����Ǿ���
template<class T>
class lowerTriangularMatrix : public virtualDiagonalMatrix<T> {
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
    lowerTriangularMatrix(int theDimention = 10) {
        if (theDimention < 1) {
            throw IllegalParameterValue("matrix�Ĵ�С�������0");
        }
        this->dimension = theDimention;
        this->element = new T[this->dimension * (this->dimension + 1) / 2];//�����Ǿ���������Ǿ����Ԫ����������n*(n+1)/2
        this->initialized = false;
    }

    lowerTriangularMatrix(const lowerTriangularMatrix<T> &theMatrix) {
        if (!theMatrix.initialized)throw uninitializedMatrix();
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
    virtual lowerTriangularMatrix<T> *operator+(const virtualDiagonalMatrix<T> &theMatrix) const {
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
    virtual lowerTriangularMatrix<T> *operator-(const virtualDiagonalMatrix<T> &theMatrix) const {
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
    virtual lowerTriangularMatrix<T> *operator*(const virtualDiagonalMatrix<T> &theMatrix) const {
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


//�����Ǿ���
template<class T>
class upperDiagonalMatrix : public virtualDiagonalMatrix<T> {
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
    upperDiagonalMatrix(int theDimention = 10) {
        if (theDimention < 1) {
            throw IllegalParameterValue("matrix�Ĵ�С�������0");
        }
        this->dimension = theDimention;
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
    virtual upperDiagonalMatrix<T> *operator+(const virtualDiagonalMatrix<T> &theMatrix) const {
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
    virtual upperDiagonalMatrix<T> *operator-(const virtualDiagonalMatrix<T> &theMatrix) const {
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
    virtual upperDiagonalMatrix<T> *operator*(const virtualDiagonalMatrix<T> &theMatrix) const {
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
