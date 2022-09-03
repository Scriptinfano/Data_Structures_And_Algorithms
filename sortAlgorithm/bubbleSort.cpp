//冒泡排序

#include<iostream>
using namespace std;
template<class T>
void mySwap(T &a, T &b) {
    T temp;
    temp = a;
    a = b;
    b = temp;
}


//一次冒泡过程
template<class T>
void bubble(T a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1])swap(a[i], a[i + 1]);
    }
}

//冒泡的全过程
template<class T>
void bubbleSort(T a[], int n) {
    for (int i = n; i > 1; i--) {
        bubble(a, i);
    }
}

//及时终止的冒泡排序
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

//最普通的冒泡排序
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