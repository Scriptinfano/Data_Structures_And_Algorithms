//
// Created by Mingxiang on 2022/10/13.
//
#include <iostream>
#include <vector>

using namespace std;

vector<int> test() {
    vector<int> vec = {0, 11, 54, 480};
    return vec;
}

int main() {
    vector<int> result = test();
    for (int i: result) {
        cout << i << " ";
    }
    return 0;
}