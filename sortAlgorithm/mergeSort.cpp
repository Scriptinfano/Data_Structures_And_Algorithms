//归并排序

//FIXME 整个程序依然存在bug，暂时研究不出来
#include <iostream>
#include <vector>

using namespace std;

void output(vector<int> theArray) {
    for (auto i: theArray) {
        cout << i << " ";
    }
    cout << endl;
}

//将theArray划分为两个数组，区间分别是[left,middle)和[middle,right)，然后将这两个数组合并成一个有序数组
void myMerge(vector<int> &theArray, int left, int middle, int right) {
    vector<int> leftArray(middle - left);
    vector<int> rightArray(right - middle);
    copy(theArray.begin() + left, theArray.begin() + middle, leftArray.begin());
    copy(theArray.begin() + middle, theArray.begin() + right, rightArray.begin());
    output(leftArray);
    output(rightArray);
    auto i = leftArray.begin();
    auto j = rightArray.begin();
    auto k = theArray.begin() + left;//k != theArray.begin() + right
    while (k != theArray.begin() + right) {
        if (*i <= *j) {
            *k = *i;
            i++;
        } else {
            *k = *j;
            j++;
        }
        k++;
    }

}

//对数组a中区间为[left,right)的元素进行排序(left一般是0，right一般是数组的元素个数)
void mergeSort(vector<int> &theArray, int left, int right) {
    if (right - left <= 1)return;
    int middle = (left + right) / 2;
    mergeSort(theArray, left, middle);
    mergeSort(theArray, middle, right);
    myMerge(theArray, left, middle, right);
}


int main() {
    setbuf(stdout, nullptr);
    vector<int> array = {1, 25, 34, 56, 14, 52, 87};
    mergeSort(array, 0, array.size());
    output(array);
    cout << endl;
}
