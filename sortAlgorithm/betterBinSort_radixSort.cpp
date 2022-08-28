/*基数排序示例*/
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\selfDefineExceptionSpace.h"

using namespace std;
using namespace ExceptionSpace;

class studentRecord {
public:
    int age;
    string name;
public:
    studentRecord(const int &theScore, const string &theName) : age(theScore), name(theName) {}

    studentRecord(const studentRecord &theRecord) {
        age = theRecord.age;
        name = theRecord.name;
    }

    int operator!=(const studentRecord &theRecord) const {
        return (age != theRecord.age);
    }

    operator int() const { return age; }
};

ostream &operator<<(ostream &out, const studentRecord &theRecord) {
    out << theRecord.age << " " << theRecord.name << endl;
    return out;
}

bool fun(const int &x) {
    int temp = x;
    while (temp > 1 && temp % 10 == 0) { temp /= 10; }
    return temp == 1;
}


void binSort(list<studentRecord> &recordList, const int &dimension, const int &baseNumber) {
    //基数排序因为每一次排序都不是直接对number排序，而是对按照某种基数分解成的digit进行排序，例如用基数10将数字928分解成三个digit，分别是9\2\8
    //将number分解为digit需要除法和取模操作，如果用基数10来分解，从最低位到最高位的数字分解式：x%10 (x%100)/10 (x%1000)/100...
    //如果用基数100来分解，则从最低位到最高位的数字分解式：x%100 (x%10000)/100...
    //对一般的基数r，相应的分解式为：x%r (x%r^2)/r (x%r^3)/r^2
    //所有数字所在范围[0，pow(10,dimension)-1] pow的第一个参数是幂的底数，第二个参数是幂的指数
    if (!fun(baseNumber))throw IllegalParameterValue("调用基数排序算法时，基数baseNumber不是10的幂");
    vector<list<studentRecord>> bin;//创建存放箱子的容器
    bin.reserve(baseNumber);
    for (int i = 0; i < baseNumber; i++) {
        list<studentRecord> temp;
        bin.push_back(temp);
    }

    for (int i = 0; i < dimension; i++)//最外层循环代表箱子排序的总次数
    {
        //箱子排序的第一步：遍历元素将元素放到箱子容器中对应的箱子中

        //第二层循环要将每一个number做基数拆解，根据这个拆解出来的数进行箱子排序
        for (auto recordIterator(recordList.begin()); recordIterator != recordList.end(); recordIterator++)
        {
            int theScore = recordIterator->age;
            int pow1 = (int) pow(baseNumber, i + 1);
            int pow2 = (int) pow(baseNumber, i);
            int theDigit = theScore % pow1 / pow2;//每个数字对应的都是这个digit，必须按照这个digit的大小来进行箱子排序
            bin.at(theDigit).push_back(*recordIterator);
        }

        recordList.clear();

        //箱子排序第二步：从箱子容器中收集箱子
        for (int j = 0; j < bin.size(); j++) {
            while (!(bin.at(j).empty())) {
                auto temp = bin.at(j).front();
                bin.at(j).pop_front();
                recordList.push_back(temp);
            }
        }

    }

}

int main() {
    setbuf(stdout, nullptr);

    studentRecord stu1(9, "某小学生");
    studentRecord stu2(45, "狗腿子安倍晋三");
    studentRecord stu3(49, "普大帝");
    studentRecord stu4(80, "拉稀登");
    studentRecord stu5(32, "小土豆特鲁多");
    studentRecord stu6(76, "懂王川普");
    list<studentRecord> recordList;
    recordList.push_back(stu1);
    recordList.push_back(stu2);
    recordList.push_back(stu3);
    recordList.push_back(stu4);
    recordList.push_back(stu5);
    recordList.push_back(stu6);
    cout << "排序之前的结果：" << endl;
    for (auto record: recordList) {
        cout << record.name << " " << record.age << endl;
    }
    cout << "---------------------------" << endl;
    binSort(recordList, 2, 10);
    cout << "排序之后的结果：" << endl;
    for (auto record: recordList) {
        cout << record.name << " " << record.age << endl;
    }

    return 0;
}
