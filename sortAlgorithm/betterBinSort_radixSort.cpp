/*��������ʾ��*/
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include "D:\ClionProjects\Data_Structures_And_Algorithms\namespaces.h"

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
    //����������Ϊÿһ�����򶼲���ֱ�Ӷ�number���򣬶��Ƕ԰���ĳ�ֻ����ֽ�ɵ�digit�������������û���10������928�ֽ������digit���ֱ���9\2\8
    //��number�ֽ�Ϊdigit��Ҫ������ȡģ����������û���10���ֽ⣬�����λ�����λ�����ַֽ�ʽ��x%10 (x%100)/10 (x%1000)/100...
    //����û���100���ֽ⣬������λ�����λ�����ַֽ�ʽ��x%100 (x%10000)/100...
    //��һ��Ļ���r����Ӧ�ķֽ�ʽΪ��x%r (x%r^2)/r (x%r^3)/r^2
    //�����������ڷ�Χ[0��pow(10,dimension)-1] pow�ĵ�һ���������ݵĵ������ڶ����������ݵ�ָ��
    if (!fun(baseNumber))throw IllegalParameterValue("���û��������㷨ʱ������baseNumber����10����");
    vector<list<studentRecord>> bin;//����������ӵ�����
    bin.reserve(baseNumber);
    for (int i = 0; i < baseNumber; i++) {
        list<studentRecord> temp;
        bin.push_back(temp);
    }

    for (int i = 0; i < dimension; i++)//�����ѭ����������������ܴ���
    {
        //��������ĵ�һ��������Ԫ�ؽ�Ԫ�طŵ����������ж�Ӧ��������
        for (auto recordIterator(recordList.begin()); recordIterator != recordList.end(); recordIterator++)//�ڶ���ѭ��Ҫ��ÿһ��number��������⣬�����������������������������
        {
            int theScore = recordIterator->age;
            int pow1 = (int) pow(baseNumber, i + 1);
            int pow2 = (int) pow(baseNumber, i);
            int theDigit = theScore % pow1 / pow2;//ÿ�����ֶ�Ӧ�Ķ������digit�����밴�����digit�Ĵ�С��������������
            bin.at(theDigit).push_back(*recordIterator);
        }

        recordList.clear();
        //��������ڶ������������������ռ�����

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

    studentRecord stu1(9, "Сѧ��ϰ��ƽ");
    studentRecord stu2(45, "��ս��");
    studentRecord stu3(49, "���ɽ");
    studentRecord stu4(80, "�ݵ�");
    studentRecord stu5(32, "��³��");
    studentRecord stu6(76, "������");
    list<studentRecord> recordList;
    recordList.push_back(stu1);
    recordList.push_back(stu2);
    recordList.push_back(stu3);
    recordList.push_back(stu4);
    recordList.push_back(stu5);
    recordList.push_back(stu6);
    cout << "����֮ǰ�Ľ����" << endl;
    for (auto record: recordList) {
        cout << record.name << " " << record.age << endl;
    }
    cout << "---------------------------" << endl;
    binSort(recordList, 2, 10);
    cout << "����֮��Ľ����" << endl;
    for (auto record: recordList) {
        cout << record.name << " " << record.age << endl;
    }

    return 0;
}
