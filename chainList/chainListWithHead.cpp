//
// Created by Mingxiang on 2022/9/9.
//

#include "chainListWithHead.h"
#include <iostream>

using namespace std;

int main() {
    auto linkList = new ChainListWithHead();
    linkList->push_back(7);
    linkList->push_back(6);
    linkList->push_back(9);
    linkList->push_back(8);
    linkList->eraseMaxElement();
    linkList->output();
    linkList->clear();
    linkList->output();
    throw invalid_argument("12");
}
