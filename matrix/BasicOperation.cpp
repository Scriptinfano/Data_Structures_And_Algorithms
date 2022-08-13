/*
 * ���������о���Ļ������������������ת�ã���ӣ����*/
#include <iostream>

using namespace std;

template<class T>
void transpose(T **a, int rows) {
    //ԭ����ɾ����ת��
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
    //������n*n�ķ������
    /*����˷�����
     * ִ�о���˷���ǰ��������ǰһ���������������ͺ�һ�������������ȣ���ǰһ������������ͺ�һ��������������Բ���ͬ
     * ��m*j�ľ����j*n�ľ�����ˣ����þ����Ȼ��һ��m*n�ľ���*/
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
    //���������Ͼ���˷����������������ˣ�����m*n�ľ���a��n*p�ľ���b���
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