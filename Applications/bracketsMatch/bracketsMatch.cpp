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
    string out = matchSuccess ? "匹配成功" : "匹配失败";
    cout << out << endl;


    return 0;
}

bool bracketCheck(stack<char> &theStack, const vector<char> &theVector) {

    for (int i = 0; i < theVector.size(); i++) {
        //遇到左括号就入栈
        if (theVector[i] == '{' || theVector[i] == '[' || theVector[i] == '(')
            theStack.push(theVector[i]);
        else {
            //遇到了右括号但是栈里面有没有左括号，说明一定匹配失败
            if (theStack.empty())return false;
            else {
                //弹出栈顶元素，判断元素是否和当前的元素匹配
                bool match = bracketMatch(theStack.top(), theVector[i]);
                if (match) {
                    //匹配成功则弹栈
                    theStack.pop();
                    continue;
                } else {
                    //匹配失败则整个函数返回false表示匹配失败
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
        throw invalid_argument("bool bracketMatch(const char &stackElement, const char &vectorElement)的参数stackElement不符合设计需求");
    }
}