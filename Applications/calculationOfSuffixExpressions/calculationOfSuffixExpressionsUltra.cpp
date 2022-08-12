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
                "double operateTwoNumbers(const double &numA,const double &numB,const char &theOperator)�����ĵ����������������һ��������");
    }
}

bool priorityComparison(string operatorA, string operatorB)//�Ƚ���������������ȼ�
{
    //operatorA����ɨ�赽�ĵ�ǰ�������operatorB��ʾ����Ҫ�����������ջ�е������
    if (operatorA == "+" || operatorA == "-") {
        return true;//��ʱoperatorB�����ȼ�һ�����ڻ����operatorA�����ȼ�
    } else {
        if (operatorB == "*" || operatorB == "/")
            return true;
        else return false;
    }
}

int main() {
    stack<string> numberStack;//������ջ
    stack<string> operatorStack;//�����ջ

    vector<string> expressionVector{
            "2", "+", "3", "-", "4", "*", "3", "/", "4", "+", "7"
    };//������׺���ʽ

    for (int i = 0; i < expressionVector.size(); i++) {
        string symbol = expressionVector[i];//�������׺���ʽ��ɨ�赽�ĵ�ǰ����
        if (isNumber(symbol)) {
            //��ǰɨ�赽���ǲ�������ֱ��ѹ�������ջ
            numberStack.push(symbol);
        } else {
            //��ǰɨ�赽�������������޷�
            if (isBracket(symbol)) {
                //��ǰɨ�赽���ǽ��޷�
                if (symbol == "(")operatorStack.push(symbol);
                else {
                    //������)�������ε��������ջ���������ÿ����һ��������ʹӲ������е����������������������������㣬Ȼ��������ѹ�������ջ��ֱ������"("Ϊֹ
                    while (operatorStack.top() != "(") {
                        double numA = stod(numberStack.top());
                        numberStack.pop();
                        double numB = stod(numberStack.top());
                        numberStack.pop();
                        double result = operateTwoNumbers(numB, numA, operatorStack.top());
                        operatorStack.pop();
                        numberStack.push(to_string(result));

                    }
                    operatorStack.pop();//������ʱջ����"("
                }
            } else {
                //��ǰɨ�赽���������
                //���ε��������ջ�����ȼ����ڻ���ڵ�ǰ������������������ÿ����һ��������Ͳ���һ�����㣬������"("�������ջΪ��ʱֹͣ��ֹͣ��ɨ�赽�ĵ�ǰ�����ѹ�������ջ
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
                            //���������ȼ����ڵ�ǰ����������
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
    cout << "������=" << numberStack.top() << endl;
    return 0;
}


