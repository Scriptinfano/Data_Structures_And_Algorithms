#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\namespaces.h"

using namespace std;
using ExceptionSpace::IllegalParameterValue;

double calculation(stack<string> &theStack, const vector<string> &theVector);

double operateTwoNumbers(const double &numA, const double &numB, const string &theOperator);

int main() {
    stack<string> numberStack;
    vector<string> expression{"15", "7", "1", "1", "+", "-", "/", "3", "*", "2", "1", "1", "+", "+",
                              "-"};//储存数字与运算符的中缀表达式
    double result = calculation(numberStack, expression);
    cout << "运算结果=" << result << endl;
    return 0;
}

double calculation(stack<string> &theStack, const vector<string> &theVector) {
    //控制整个算法的流程
    //注意使用stod()函数将代表运算数的字符串转换为可参与运算的double型数字
    //注意使用yo_string函数将数字(int,double,float等数字变量)转为string
    for (int i = 0; i < theVector.size(); i++) {
        if (theVector[i] == "+" || theVector[i] == "-" || theVector[i] == "*" || theVector[i] == "/") {
            //弹出栈中的两个元素并和当前运算符做运算
            double numA = stod(theStack.top());
            theStack.pop();
            double numB = stod(theStack.top());
            theStack.pop();
            double result = operateTwoNumbers(numA, numB, theVector[i]);
            theStack.push(to_string(result));
        } else {
            //将数字压入栈中
            theStack.push(theVector[i]);
        }
    }
    return stod(theStack.top());
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
        throw IllegalParameterValue(
                "double operateTwoNumbers(const double &numA,const double &numB,const char &theOperator)函数的第三个参数必须代表一个操作符");
    }
}
