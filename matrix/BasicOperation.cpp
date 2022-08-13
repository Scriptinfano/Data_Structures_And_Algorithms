/*
 * 本程序罗列矩阵的基本操作，包括矩阵的转置，相加，相乘*/
#include <iostream>

using namespace std;

template<class T>
void transpose(T **a, int rows) {
    //原地完成矩阵的转置
    for (int i = 0; i < rows; i++)
        for (int j = i + 1; j < rows; j++)
            swap(a[i][j], a[j][i]);
}

template<class T>
void matrixAdd(T **a, T **b, T **c, int numberOfRows, int numberOfColumns) {
    for (int i = 0; i < numberOfRows; i++)
        for (int j = 0; j < numberOfColumns; j++)
            c[i][j] = a[i][j] + b[i][j];
}

template<class T>
void squareMatrixMultiply(T **a, T **b, T **c, int n) {
    //将两个n*n的方阵相乘
    /*矩阵乘法规则：
     * 执行矩阵乘法的前提条件：前一个矩阵的行数必须和后一个矩阵的列数相等，而前一个矩阵的列数和后一个矩阵的行数可以不相同
     * 若m*j的矩阵和j*n的矩阵相乘，所得矩阵必然是一个m*n的矩阵*/
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            T sum=0;
            for(int k=0;k<n;k++)
            {
                sum+=a[i][k]+b[k][j];
            }
            c[i][j]=sum;
        }
    }

}
template<class T>
void matrixMultiply(T **a,T **b,T **c,int m,int n,int p)
{
    //将两个符合矩阵乘法规则的两个矩阵相乘，即将m*n的矩阵a和n*p的矩阵b相乘
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<p;j++)
        {
            T sum=0;
            for(int k=0;k<n;k++)
            {
                sum+=a[i][k]*b[k][j];
            }
            c[i][j]=sum;
        }
    }
}