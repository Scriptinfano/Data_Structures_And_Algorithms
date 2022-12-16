/*
 * �ó������ֱ�ӽ���׺���ʽ���������Ҳ���ǽ���׺���ʽת��׺���ʽ�ͺ�׺���ʽ��������*/
#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"

using ExceptionSpace::IllegalParameterException;
using namespace std;

//�жϴ�����ַ����ǲ��ǲ�����
bool isNumber(string element) {
    if (element == "+" || element == "-" || element == "*" || element == "/" || element == "(" || element == ")")
        return false;
    return true;
}

//�жϴ�����ַ����ǲ��Ǵ�����������
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
                "double operateTwoNumbers(const double &numA,const double &numB,const char &theOperator)�еĵ�������������");
    }
}

bool priorityComparison(string operatorA, string operatorB)//�Ƚ���������������ȼ�
{
    //operatorA����ɨ�赽�ĵ�ǰ�������operatorB��ʾ����Ҫ�����������ջ�е������
    if (operatorA == "+" || operatorA == "-") {
        return true;
    } else {
        if (operatorB == "*" || operatorB == "/")
            return true;
        else return false;
    }
}

int main() {
    stack<string> numberStack;//������ջ
    stack<string> operatorStack;//�����ջ

    //��׺���ʽ����
    vector<string> expressionVector{
            "2", "+", "3", "-", "4", "*", "3", "/", "4", "+", "7"
    };

    for (auto symbol : expressionVector) {
        //����׺���ʽ������ɨ�赽����
        if (isNumber(symbol)) {
            //����÷�����������ֱ��ѹ�������ջ
            numberStack.push(symbol);
        } else {
            //����÷��������������޷�
            if (isBracket(symbol)) {
                //�÷����ǽ��޷������

                //����ý��޷���(����ֱ�ӽ�����ѹ�������ջ
                if (symbol == "(")operatorStack.push(symbol);
                else {
                    //������)�������ε��������ջ���������ÿ����һ��������ʹӲ������е����������������������㣬Ȼ��������ѹ�������ջ
                    //ֱ������(��ֹ���������������)ʱһ��������һϵ������֮���ٴε���(
                    while (operatorStack.top() != "(") {
                        double numA = stod(numberStack.top());
                        numberStack.pop();
                        double numB = stod(numberStack.top());
                        numberStack.pop();
                        double result = operateTwoNumbers(numB, numA, operatorStack.top());
                        operatorStack.pop();
                        numberStack.push(to_string(result));

                    }
                    operatorStack.pop();//������ʱջ���ġ�(��
                }
            } else {
                //��ǰɨ�赽���������
                /*
                 * ���ε��������ջ�����ȼ����ڻ���ڵ�ǰ������������������ÿ����һ��������Ͳ���һ��
                 * ���㣬��������(���������ջΪ��ʱֹͣ��ֹͣ��ɨ�赽�ĵ�ǰ�����ѹ�������ջ*/
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
                    //���������whileѭ����˵����ʱoperatorStackһ���ǿյģ���ô��һ����ִ��operatorStack.push(symbol); ����ǰɨ�赽�������ѹջ
                    //�����ִ��whileѭ���Ĺ����������������Ż������ȼ���������������ô��ʱoperatorStackһ����Ϊ�գ���ʱһ������������if���
                    //һ�����������if��䣬�޷Ǿ����������һ������ִ��whileѭ������Ϊ�����������ţ���һ������ִ��whileѭ���Ĺ��������ȼ�����������
                    if (!operatorStack.empty()) {
                        if (operatorStack.top() == "(") {
                            //������������Ӧ���Ƚ������ŵ���Ȼ���ٽ���ǰ�������ջ
                            operatorStack.pop();
                            operatorStack.push(symbol);
                        } else {
                            //���������ȼ����ڵ�ǰ������������
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
        //stod������string���͵�����ת��Ϊdouble
        //to_string����������ת��Ϊ�ַ���
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


