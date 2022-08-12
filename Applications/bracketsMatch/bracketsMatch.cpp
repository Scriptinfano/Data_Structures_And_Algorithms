#include<iostream>
#include<vector>
#include<stack>

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

    bool matchSucces = bracketCheck(matchStack, brackets);
    string out = matchSucces ? "ƥ��ɹ�" : "ƥ��ʧ��";
    cout << out << endl;


    return 0;
}

bool bracketCheck(stack<char> &theStack, const vector<char> &theVector) {

    for (int i = 0; i < theVector.size(); i++) {
        if (theVector[i] == '{' || theVector[i] == '[' || theVector[i] == '(')
            theStack.push(theVector[i]);
        else {
            if (theStack.empty())return false;
            else {
                //����ջ��Ԫ�أ��ж�Ԫ���Ƿ�͵�ǰ��Ԫ��ƥ��
                bool match = bracketMatch(theStack.top(), theVector[i]);
                if (match) {
                    //ƥ��ɹ�
                    theStack.pop();
                    continue;
                } else {
                    //ƥ��ʧ��
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
    }
}