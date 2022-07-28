#include<iostream>

using namespace std;

template<class T>
void swap(T &a,T&b)
{
    T temp;
    temp=a;
    a=b;
    b=temp;
}


//一次冒泡过程
template<class T>
void bubble(T a[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        if(a[i]>a[i+1])swap(a[i],a[i+1]);
    }
}

//冒泡的全过程
template<class T>
void bubbleSort(T a[],int n)
{
    for(int i=n;i>1;i--)
    {
        bubble(a,i);
    }
}

int main() {
    return 0;
}