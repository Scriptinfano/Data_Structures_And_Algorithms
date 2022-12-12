/*
 * 该程序可以直接将中缀表达式计算出来，也就是将中缀表达式转后缀表达式和后缀表达式的运算结合*/
#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"

using ExceptionSpace::IllegalParameterException;
using namespace std;

//判断传入的字符串是不是操作符
bool isNumber(string element) {
    if (element == "+" || element == "-" || element == "*" || element == "/" || element == "(" || element == ")")
        return false;
    return true;
}

//判断传入的字符串是不是代表左右括号
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
        throw IllegalParameterException(
                "double operateTwoNumbers(const double &numA,const double &numB,const char &theOperator)中的第三个参数有误");
    }
}

bool priorityComparison(string operatorA, string operatorB)//比较两个运算符的优先级
{
    //operatorA代表扫描到的当前运算符，operatorB表示即将要弹出的运算符栈中的运算符
    if (operatorA == "+" || operatorA == "-") {
        return true;
    } else {
        if (operatorB == "*" || operatorB == "/")
            return true;
        else return false;
    }
}

int main() {
    stack<string> numberStack;//操作数栈
    stack<string> operatorStack;//运算符栈

    //中缀表达式集合
    vector<string> expressionVector{
            "2", "+", "3", "-", "4", "*", "3", "/", "4", "+", "7"
    };

    for (auto symbol : expressionVector) {
        //从中缀表达式集合中扫描到符号
        if (isNumber(symbol)) {
            //如果该符号是数字则直接压入操作数栈
            numberStack.push(symbol);
        } else {
            //如果该符号是运算符或界限符
            if (isBracket(symbol)) {
                //该符号是界限符的情况

                //如果该界限符是(，则直接将符号压入操作符栈
                if (symbol == "(")operatorStack.push(symbol);
                else {
                    //遇到”)“则依次弹出运算符栈内运算符，每弹出一个运算符就从操作数中弹出两个操作数，并做运算，然后将运算结果压入操作数栈
                    //直到遇到(终止运算操作，当弹出)时一定会在做一系列运算之后再次弹出(
                    while (operatorStack.top() != "(") {
                        double numA = stod(numberStack.top());
                        numberStack.pop();
                        double numB = stod(numberStack.top());
                        numberStack.pop();
                        double result = operateTwoNumbers(numB, numA, operatorStack.top());
                        operatorStack.pop();
                        numberStack.push(to_string(result));

                    }
                    operatorStack.pop();//弹出此时栈顶的”(“
                }
            } else {
                //当前扫描到的是运算符
                /*
                 * 依次弹出运算符栈中优先级高于或等于当前运算符的所有运算符，每弹出一个运算符就参与一次
                 * 运算，若遇到”(“或运算符栈为空时停止，停止后将扫描到的当前运算符压入运算符栈*/
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
                    //如果走完了while循环，说明此时operatorStack一定是空的，那么就一定会执行operatorStack.push(symbol); 将当前扫描到的运算符压栈
                    //如果在执行while循环的过程中遇到了左括号或者优先级不满足条件，那么此时operatorStack一定不为空，此时一定会进入下面的if语句
                    //一旦进入下面的if语句，无非就两种情况，一种是在执行while循环中因为遇到了左括号，另一种是在执行while循环的过程中优先级不满足条件
                    if (!operatorStack.empty()) {
                        if (operatorStack.top() == "(") {
                            //遇到左括号则应该先将左括号弹出然后再将当前运算符入栈
                            operatorStack.pop();
                            operatorStack.push(symbol);
                        } else {
                            //遇到了优先级低于当前运算符的运算符
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
        //stod函数将string类型的数字转换为double
        //to_string函数将数字转换为字符串
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


