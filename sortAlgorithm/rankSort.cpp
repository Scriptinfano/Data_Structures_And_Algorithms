#include<iostream>

using namespace std;
namespace mystd {
    template<class T>
    void rank(T a[], int n, int r[]) {
        //r[]�Ǽ�¼���ε�����
        for (int i = 0; i < n; i++)
            r[i] = 0;
        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++)
                if (a[j] <= a[i])r[i]++;
                else r[j]++;

    }

    template<class T>
    void reArrange(T a[], int n, int r[]) {
        for(int i=0;i<n;i++)
        {
            while(r[i]!=i)
            {
                int t=r[i];
                swap(a[i].a[t]);
                swap(r[i],r[t]);//������Ӧ�����Σ���Ϊ������Ԫ�ص����������������б����������λ������һһ��Ӧ�ģ��������е�Ԫ�ؽ�������ȷ��λ���Ϻ���Ӧ������ҲҪ����
            }
        }

    }
}

int main() {
    int a[] = {1, 3, 4, 9, 2, 7, 8, 6};
    int *t = new int[8];
    mystd::rank(a, 8, t);
    for (int i = 0; i < 8; i++)
        cout << t[i] << " ";

    return 0;
}