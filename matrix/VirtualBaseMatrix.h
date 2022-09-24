//��ͷ�ļ��������Զ���ṹ�ĳ��������ӿ�
#pragma once

#include <vector>

////////////////////////���������ӿ������ⷽ���ӿڿ�ʼ������////////////////////////////////////////////////
//�������������ķ����ӿ�
template<class T>
class MatrixBasicFuncInterface {
public:
    virtual ~MatrixBasicFuncInterface() = default;

    //�������������
    virtual T operator()(int i, int j) const = 0;//�õ�����Ϊi,j������Ԫ��

    //����ٶ�theMatrix��ÿһ�ж�������ͬ��Ԫ�ظ���
    virtual void initialize(const vector<vector<int>> &theMatrix) = 0;

    virtual void initialize() = 0;

    //�õ������е�ָ��Ԫ��
    virtual T get(int i, int j) const = 0;

    virtual T &get(int i, int j) = 0;

    //���þ����е�ָ��Ԫ��Ϊĳֵ
    virtual void set(int i, int j, const T &theElement) = 0;

};

//����������������ӿڣ��˽ӿڽ����������������������ת�õȣ������������������Ҫʵ��ĳЩ��������������࣬Ȼ��ѡ��ʵ�ֹ���
template<class T>
class SpecialOperationInterface {
    //����ı����麯�������дʵ�֣���ô�������ѡ��ʵ�ָù��ܣ������ʵ�֣����ø���ָ�����ʱ��Ϊ������Ȩ����protected����Ҳ�����ƻ���װ��
public :
    virtual ~SpecialOperationInterface() = default;

protected:
    //���¶�������о�����������ȫ��Ϊ����Ȩ�޵��麯��������ѡ��ʵ����Щ����
    virtual SpecialOperationInterface<T> *transpose() = 0;

    virtual SpecialOperationInterface<T> &operator=(const SpecialOperationInterface<T> &theMatrix) = 0;

    virtual SpecialOperationInterface<T> *operator+(const SpecialOperationInterface<T> &theMatrix) const = 0;

    virtual SpecialOperationInterface<T> *operator-(const SpecialOperationInterface<T> &theMatrix) const = 0;

    virtual SpecialOperationInterface<T> *operator*(const SpecialOperationInterface<T> &theMatrix) const = 0;

    virtual void operator+=(const T &theElement) const = 0;

    virtual void operator-=(const T &theElement) const = 0;

};
////////////////////////���������ӿ������ⷽ���ӿڽ���������///////////////////////////////////////////////////



///////////////////////����������Բ㿪ʼ������///////////////////////////////////////
//ע�⣺ʹ�ö�̬ʱ�������������ָ�룬������ָ��ʵ�ֲ���ľ������
template<class T>
class BaseMatrix : public MatrixBasicFuncInterface<T> {
protected://���������е�����
    T *element;
    bool initialized;

public:
    virtual ~BaseMatrix() = default;

    //����ʼ��ʱ�����뺯���ľ����Ƿ������������Ҫ�󣬸ú���Ϊ�麯�����������Ҫ������д�ú������������дҲ����ʵ����
    virtual bool checkInitialize(const vector<vector<T>> &theMatrix) {}
};
///////////////////////����������Բ����������//////////////////////////////////////


//////////////////////�������������ӿڿ�ʼ������//////////////////
//����Ļ���Խӿڽ������������䣬���˼�뼴ÿһ����������������Ʋ�ͬ�����Ը��ݲ�ͬ��������Ʋ�ͬ�ĳ�����࣬������Щ���������������������������
template<class T>
class NormalMatrixProperties : public BaseMatrix<T> {
protected:
    //��������
    int size;//��¼element������ʵ�ʵ�Ԫ�ظ���
    int columns;
};


//���ξ���ĳ�����࣬��������������ͬ
template<class T>
class SquareMatrixProperties : public BaseMatrix<T> {
protected://��������Ҫ���������п���ֱ�ӷ���
    //��������
    int size;//��¼element������ʵ�ʵ�Ԫ�ظ���
    int dimension;//���ξ��������������ʵ�ʶ��������ֵ
};
//////////////////////�������������ӿڽ���������////////////////
