/* ��������
 * ���μ�����ʾ
 * 1��ʲô��Ԫ���������е����Σ�һ��Ԫ����һ�������е����������б���С
 * ��Ԫ�ظ�������������߳��ֵ�������ͬ��Ԫ�ظ���*/
#include<iostream>

using namespace std;
namespace rankSortSpace {
    //��a[]�и�Ԫ�ص������������Ȼ���䰴�ն�Ӧ������r[]������
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

    //�����������¶�����Ԫ�ؽ�����������������������������е�ԭ�����Ų���

    template<class T>
    void reArrange(T a[], int n, int r[]) {
        for (int i = 0; i < n; i++) {
            while (r[i] != i) //����ж�������ʾ��ǰԪ���Ƿ�����ȷ��λ���ϣ�������ȷ��λ���Ͼ�ִ�����½����㷨
            {
                int t = r[i];//t��a[i]Ӧ��ȥ����ȷ�±�
                swap(a[i], a[t]);//��Ԫ��a[i]��������ȷ��λ����
                swap(r[i], r[t]);//������Ӧ�����Σ���Ϊ������Ԫ�ص����������������б����������λ������һһ��Ӧ�ģ��������е�Ԫ�ؽ�������ȷ��λ���Ϻ���Ӧ������ҲҪ����
            }
        }
    }

    template<class T>
    void reArrange2(T a[],int n,int r[])
    {
        T *u=new T[n];

        //��a�е�Ԫ���Ƶ���ȷ��λ����
        for(int i = 0; i < n; i++)
        {
            u[r[i]]=a[i];
        }
        //��u�е�Ԫ���ƻ�ȥ
        for(int i=0;i<n;i++)
        {
            a[i]=u[i];
        }
        delete[]u;
    }
}

int main() {
    int a[] = {1, 3, 4, 9, 2, 7, 8, 6};
    int *t = new int[8];
    rankSortSpace::rank(a, 8, t);
    for (int i = 0; i < 8; i++)
        cout << t[i] << " ";

    return 0;
}