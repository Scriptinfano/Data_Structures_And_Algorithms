//ð������

#include<iostream>
using namespace std;
template<class T>
void mySwap(T &a, T &b) {
    T temp;
    temp = a;
    a = b;
    b = temp;
}


//һ��ð�ݹ���
template<class T>
void bubble(T a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1])swap(a[i], a[i + 1]);
    }
}

//ð�ݵ�ȫ����
template<class T>
void bubbleSort(T a[], int n) {
    for (int i = n; i > 1; i--) {
        bubble(a, i);
    }
}

//��ʱ��ֹ��ð������
template<class T>
bool betterBubble(T a[], int n) {
    bool swapped = false;
    for (int i = 0; i < n; i++) {
        if (a[i] > a[i + 1]) {
            swap(a[i], a[i + 1]);
            swapped = true;
        }
    }
    return swapped;
}

template<class T>
void betterBubbleSort(T a[], int n) {
    for (int i = n; i > 1 && betterBubble(a, i); i--);
}

//����ͨ��ð������
template<class T>
void normalBubbleSort(T &array) {
    int size = sizeof(array) / sizeof(array[0]);
    for (int i = 0; i < size; i++) {
        for(int j=0;j<size-i-1;j++)
        {
            if(array[j]<array[j+1])
                swap(array[j],array[j+1]);
        }
    }
}

int main() {
    int a[] = {12, 32, 1, 4, 16, 3, 6, 31};
    //betterBubbleSort(a, 8);
    normalBubbleSort(a);
    for (auto i: a) {
        cout << i << " ";
    }
    return 0;
}