//插入排序
#include <iostream>

using namespace std;

//在一个有序数组中插入一个元素，注意下面函数中的参数a[]所代表的数组一定是有序的
template<class T>
void insert(T a[],int n,const T&x)
{
    //n是元素数量，n-1是数组中最后一个元素的下标，不是数组最后一个下标，数组最后一定要留一个位置
    int i;
    for(i=n-1;i>=0&&x<a[i];i--)
    {
        a[i+1]=a[i];
    }
    a[i+1]=x;
}

template<class T>
void insertionSort(T a[],int n)
{
    for(int i=1;i<n;i++)
    {
        T t=a[i];
        insert(a,i,t);
    }
}

template<class T>
void betterInsertionSort(T a[],int n)
{
    for(int i=1;i<n;i++)
    {
        T t=a[i];
        int j;
        for(j=i-1;j>=0&&t<a[j];j--)
        {
            a[j+1]=a[j];
        }
        a[j+1]=t;
    }

}


int main()
{

    return 0;
}