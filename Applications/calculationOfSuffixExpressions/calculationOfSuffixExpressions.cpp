#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"

using namespace std;
using ExceptionSpace::IllegalParameterException;

double calculation(stack<string> &theStack, const vector<string> &theVector);

double operateTwoNumbers(const double &numA, const double &numB, const string &theOperator);

int main() {
    stack<string> numberStack;
    vector<string> expression{"15", "7", "1", "1", "+", "-", "/", "3", "*", "2", "1", "1", "+", "+","-"};//储存数字与运算符的中缀表达式
    double result = calculation(numberStack, expression);
    cout << "运算结果=" << result << endl;
    return 0;
}

double calculation(stack<string> &theStack, const vector<string> &theVector) {
    for (int i = 0; i < theVector.size(); i++) {
        if (theVector[i] == "+" || theVector[i] == "-" || theVector[i] == "*" || theVector[i] == "/") {
            //如果遇到操作符，则将操作符取出并弹出两个操作数做运算
            double numA = stod(theStack.top());//取出第一个操作数
            theStack.pop();
            double numB = stod(theStack.top());//取出第二个操作数
            theStack.pop();
            double result = operateTwoNumbers(numA, numB, theVector[i]);
            theStack.push(to_string(result));//将运算结果转换为string重新压入操作数栈
        } else {
            //若遇到数字则将数字压入操作数栈
            theStack.push(theVector[i]);
        }
    }
    return stod(theStack.top());//stod函数可将字符串转换为double值
}

double operateTwoNumbers(const double &numA, const double &numB, const string &theOperator) {
    if (theOperator == "+") {
        return numA + numB;
    } else if (theOperator == "-") {
        return numA - numB;
    } else if (theOperator == "*") {
        return numA * numB;
    } else if (theOperator == "/") {
        return numA / numB;
    } else {
        throw IllegalParameterException("double operateTwoNumbers(const double &numA,const double &numB,const char &theOperator)发生未考虑到的情况");
    }
}
