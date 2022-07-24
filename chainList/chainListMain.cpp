#include<iostream>
#include "chainListMain.h"

using namespace std;

int main() {
    chainList<int> chain;
    chain.push_back(12);
    chain.push_back(13);
    chain.push_back(1323);//
    chain.push_back(1352);//
    chain.push_back(1);//
    chain.push_back(25);
    chain.push_back(325);
    chain.push_back(1154);

    chain.removeRange(2, 4);
    //chain.setSize(3);
    //chain.set(2,43);
    cout << chain;
}