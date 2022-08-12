#include<iostream>
#include <utility>
#include<vector>
#include<stack>
#include<string>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\namespaces.h"

using ExceptionSpace::IllegalParameterValue;
using namespace std;

bool isNumber(string element) {
    if (element == "+" || element == "-" || element == "*" || element == "/" || element == "(" || element == ")")
        return false;
    return true;
}

bool isBracket(string element) {
    if (element == "(" || element == ")")
        return true;
    else return false;
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

bool priorityComparison(string operatorA, string operatorB)//比较两个运算符的优先级
{
    //operatorA代表扫描到的当前运算符，operatorB表示即将要弹出的运算符栈中的运算符
    if (operatorA == "+" || operatorA == "-") {
        return true;//此时operatorB的优先级一定大于或等于operatorA的优先级
    } else {
        if (operatorB == "*" || operatorB == "/")
            return true;
        else return false;
    }
}

int main() {
    stack<string> numberStack;//操作数栈
    stack<string> operatorStack;//运算符栈

    vector<string> expressionVector{
            "2", "+", "3", "-", "4", "*", "3", "/", "4", "+", "7"
    };//代表中缀表达式

    for (int i = 0; i < expressionVector.size(); i++) {
        string symbol = expressionVector[i];//代表从中缀表达式中扫描到的当前符号
        if (isNumber(symbol)) {
            //当前扫描到的是操作数，直接压入操作数栈
            numberStack.push(symbol);
        } else {
            //当前扫描到的是运算符或界限符
            if (isBracket(symbol)) {
                //当前扫描到的是界限符
                if (symbol == "(")operatorStack.push(symbol);
                else {
                    //遇到“)”则依次弹出运算符栈内运算符，每弹出一个运算符就从操作数中弹出两个操作数与该运算符进行运算，然后将运算结果压入操作数栈，直到遇到"("为止
                    while (operatorStack.top() != "(") {
                        double numA = stod(numberStack.top());
                        numberStack.pop();
                        double numB = stod(numberStack.top());
                        numberStack.pop();
                        double result = operateTwoNumbers(numB, numA, operatorStack.top());
                        operatorStack.pop();
                        numberStack.push(to_string(result));

                    }
                    operatorStack.pop();//弹出此时栈顶的"("
                }
            } else {
                //当前扫描到的是运算符
                //依次弹出运算符栈中优先级高于或等于当前运算符的所有运算符，每弹出一个运算符就参与一次运算，若遇到"("或运算符栈为空时停止，停止后将扫描到的当前运算符压入运算符栈
                if (!operatorStack.empty()) {
                    while (!operatorStack.empty()) {
                        if (operatorStack.top() == "(" || !priorityComparison(symbol, operatorStack.top()))break;
                        string theOperator = operatorStack.top();
                        operatorStack.pop();
                        double numA = stod(numberStack.top());
                        numberStack.pop();
                        double numB = stod(numberStack.top());
                        numberStack.pop();
                        double result = operateTwoNumbers(numB, numA, theOperator);
                        numberStack.push(to_string(result));
                    }
                    if (!operatorStack.empty()) {
                        if (operatorStack.top() == "(") {
                            operatorStack.pop();
                            operatorStack.push(symbol);
                        } else {
                            //遇到了优先级低于当前运算符运算符
                            operatorStack.push(symbol);
                        }
                    } else {
                        operatorStack.push(symbol);
                    }
                } else {
                    operatorStack.push(symbol);
                }
            }
        }
    }
    while (!operatorStack.empty()) {
        double numA = stod(numberStack.top());
        numberStack.pop();
        double numB = stod(numberStack.top());
        numberStack.pop();
        double result = operateTwoNumbers(numA, numB, operatorStack.top());
        operatorStack.pop();
        numberStack.push(to_string(result));
    }
    cout << "运算结果=" << numberStack.top() << endl;
    return 0;
}


