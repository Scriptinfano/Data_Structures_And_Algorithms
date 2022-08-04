#include<iostream>

using namespace std;

class illegalParameterValue {
private:
    string message;

public:
    illegalParameterValue() : message("�Ƿ�ʵ�δ���") {}

    illegalParameterValue(string theMessage) { message = theMessage; }

    void outPutMessage() const { cout << message << endl; }
};

//�ҵ�����a�����Ԫ�ص�����,n������Ԫ�ظ���
template<class T>
int indexOfMax(T a[], int n) {
    if (n <= 0)throw illegalParameterValue("n�������0");
    int indexOfMax = 0;
    for (int i = 1; i < n; i++) {
        if (a[indexOfMax] < a[i])indexOfMax = i;
    }
    return indexOfMax;
}

template<class T>
void swap(T &a,T&b)
{
    T temp;
    temp=a;
    a=b;
    b=temp;
}

template<class T>
void selectionSort(T a[],int n)
{
    for(int size=n;size>1;size--)
    {
        int j= indexOfMax(a,size);
        swap(a[j],a[size-1]);
    }
}

template<class T>
void selectionSort2(T a[],int size)
{
    for(int i=0;i<size-1;i++)
    {
        int tempMin=i;
        for(int j=i+1;j<size;j++)
        {
            if(a[j]<a[tempMin])
                tempMin=j;
        }

        swap(a[i],a[tempMin]);
    }
}

//ԭ����ѡ�������и�ȱ����Ǽ�ʹԪ���Ѿ����򣬳�����Ȼ��������У����Ҫ���ڼ�����Ԫ��ʱ��ͬʱ��������Ƿ��Ѿ�����
template<class T>
void betterSelectionSort(T a[],int n)
{
    bool sorted=false;
    for(int size=n;!sorted&&(size>1);size--)
    {
        int indexOfMax=0;
        sorted=true;
        for(int i=1;i<size;i++)
        {
            if(a[indexOfMax]<=a[i])indexOfMax=i;
            else sorted= false;
        }
        swap(a[indexOfMax],a[size-1]);
    }
}
int main() {



    return 0;
}