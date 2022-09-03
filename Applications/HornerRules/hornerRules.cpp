//本程序演示如何使用Horner法则进行多项式计算
#include <iostream>

using namespace std;

//coeff数组存储各多项式的系数，从常数项开始，一直到最高阶的系数
//n表示多项式的最高阶数
//x表示要计算多项式在x=几时的值
template<class T>
T horner(T coeff[], int n, const T &x) {
    T value = coeff[0];
    int step=0;
    for (int i = 1; i <= n; i++) {
        value=value*x+coeff[i];
        step++;
    }
    cout<<step<<endl;
    return value;
}

int main() {

    int theCoeff[]={5,4,1,7};
    cout<<horner<int>(theCoeff,3,3);

    return 0;
}