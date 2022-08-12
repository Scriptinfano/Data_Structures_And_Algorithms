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
                              "-"};//�������������������׺���ʽ
    double result = calculation(numberStack, expression);
    cout << "������=" << result << endl;
    return 0;
}

double calculation(stack<string> &theStack, const vector<string> &theVector) {
    //���������㷨������
    //ע��ʹ��stod()�������������������ַ���ת��Ϊ�ɲ��������double������
    //ע��ʹ��yo_string����������(int,double,float�����ֱ���)תΪstring
    for (int i = 0; i < theVector.size(); i++) {
        if (theVector[i] == "+" || theVector[i] == "-" || theVector[i] == "*" || theVector[i] == "/") {
            //����ջ�е�����Ԫ�ز��͵�ǰ�����������
            double numA = stod(theStack.top());
            theStack.pop();
            double numB = stod(theStack.top());
            theStack.pop();
            double result = operateTwoNumbers(numA, numB, theVector[i]);
            theStack.push(to_string(result));
        } else {
            //������ѹ��ջ��
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
                "double operateTwoNumbers(const double &numA,const double &numB,const char &theOperator)�����ĵ����������������һ��������");
    }
}
