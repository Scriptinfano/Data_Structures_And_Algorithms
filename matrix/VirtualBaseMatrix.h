//此头文件包含各自定义结构的抽象基类与接口
#pragma once

#include <vector>

////////////////////////基本方法接口与特殊方法接口开始定义线////////////////////////////////////////////////
//定义矩阵最基本的方法接口
template<class T>
class MatrixBasicFuncInterface {
public:
    virtual ~MatrixBasicFuncInterface() = default;

    //重载运算符函数
    virtual T operator()(int i, int j) const = 0;//得到索引为i,j的索引元素

    //这里假定theMatrix的每一行都具有相同的元素个数
    virtual void initialize(const vector<vector<int>> &theMatrix) = 0;

    virtual void initialize() = 0;

    //得到矩阵中的指定元素
    virtual T get(int i, int j) const = 0;

    virtual T &get(int i, int j) = 0;

    //设置矩阵中的指定元素为某值
    virtual void set(int i, int j, const T &theElement) = 0;

};

//定义矩阵的特殊操作接口，此接口将定义矩阵的特殊操作，例如转置等，具体的特殊矩阵如果想要实现某些功能则派生这个类，然后选择实现功能
template<class T>
class SpecialOperationInterface {
    //基类的保护虚函数如果不写实现，那么子类可以选择实现该功能，如果不实现，则用父类指针调用时因为函数的权限是protected所以也不会破坏封装性
public :
    virtual ~SpecialOperationInterface() = default;

protected:
    //以下定义的所有矩阵的特殊操作全部为保护权限的虚函数，可以选择实现这些功能
    virtual SpecialOperationInterface<T> *transpose() = 0;

    virtual SpecialOperationInterface<T> &operator=(const SpecialOperationInterface<T> &theMatrix) = 0;

    virtual SpecialOperationInterface<T> *operator+(const SpecialOperationInterface<T> &theMatrix) const = 0;

    virtual SpecialOperationInterface<T> *operator-(const SpecialOperationInterface<T> &theMatrix) const = 0;

    virtual SpecialOperationInterface<T> *operator*(const SpecialOperationInterface<T> &theMatrix) const = 0;

    virtual void operator+=(const T &theElement) const = 0;

    virtual void operator-=(const T &theElement) const = 0;

};
////////////////////////基本方法接口与特殊方法接口结束定义线///////////////////////////////////////////////////



///////////////////////矩阵基本属性层开始定义线///////////////////////////////////////
//注意：使用多态时，请声明此类的指针，并将其指向实现层类的具体对象
template<class T>
class BaseMatrix : public MatrixBasicFuncInterface<T> {
protected://基本矩阵都有的属性
    T *element;
    bool initialized;

public:
    virtual ~BaseMatrix() = default;

    //检查初始化时，传入函数的矩阵是否符合特殊矩阵的要求，该函数为虚函数，如果有需要，请重写该函数，如果不重写也可以实例化
    virtual bool checkInitialize(const vector<vector<T>> &theMatrix) {}
};
///////////////////////矩阵基本属性层结束定义线//////////////////////////////////////


//////////////////////矩阵属性扩充层接口开始定义线//////////////////
//下面的基类对接口进行了属性扩充，设计思想即每一个特殊矩阵的属性设计不同，所以根据不同的属性设计不同的抽象基类，再由这些抽象基类派生出具体的特殊矩阵类
template<class T>
class NormalMatrixProperties : public BaseMatrix<T> {
protected:
    //保护属性
    int size;//记录element数组中实际的元素个数
    int columns;
};


//方形矩阵的抽象基类，其行数和列数相同
template<class T>
class SquareMatrixProperties : public BaseMatrix<T> {
protected://以下属性要求在子类中可以直接访问
    //保护属性
    int size;//记录element数组中实际的元素个数
    int dimension;//方形矩阵的行数和列数实际都等于这个值
};
//////////////////////矩阵属性扩充层接口结束定义线////////////////
