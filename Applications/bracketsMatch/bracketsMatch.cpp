#include<iostream>
#include<vector>
#include<stack>
#include <stdexcept>
using namespace std;

bool bracketCheck(stack<char> &theStack, const vector<char> &theVector);

bool bracketMatch(const char &stackElement, const char &vectorElement);

int main() {
    stack<char> matchStack;
    vector<char> brackets;
    brackets.push_back('{');
    brackets.push_back('{');
    brackets.push_back('(');
    brackets.push_back('(');
    brackets.push_back(')');
    brackets.push_back(')');
    brackets.push_back('[');
    brackets.push_back(']');
    brackets.push_back('}');
    brackets.push_back('}');

    bool matchSuccess = bracketCheck(matchStack, brackets);
    string out = matchSuccess ? "ƥ��ɹ�" : "ƥ��ʧ��";
    cout << out << endl;


    return 0;
}

bool bracketCheck(stack<char> &theStack, const vector<char> &theVector) {

    for (int i = 0; i < theVector.size(); i++) {
        //���������ž���ջ
        if (theVector[i] == '{' || theVector[i] == '[' || theVector[i] == '(')
            theStack.push(theVector[i]);
        else {
            //�����������ŵ���ջ������û�������ţ�˵��һ��ƥ��ʧ��
            if (theStack.empty())return false;
            else {
                //����ջ��Ԫ�أ��ж�Ԫ���Ƿ�͵�ǰ��Ԫ��ƥ��
                bool match = bracketMatch(theStack.top(), theVector[i]);
                if (match) {
                    //ƥ��ɹ���ջ
                    theStack.pop();
                    continue;
                } else {
                    //ƥ��ʧ����������������false��ʾƥ��ʧ��
                    return false;
                }
            }
        }
    }
    if (theStack.empty())return true; else return false;

}

bool bracketMatch(const char &stackElement, const char &vectorElement) {
    if (stackElement == '{') {
        if (vectorElement == '}')return true;
        else return false;
    } else if (stackElement == '(') {
        if (vectorElement == ')')return true;
        else return false;

    } else if (stackElement == '[') {
        if (vectorElement == ']')return true;
        else return false;
    }else{
        throw invalid_argument("bool bracketMatch(const char &stackElement, const char &vectorElement)�Ĳ���stackElement�������������");
    }
}