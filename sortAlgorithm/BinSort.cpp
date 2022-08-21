#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

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

void binSort(list<studentRecord> &theList, const int &beginRange, const int &endRange) {
    //初始化箱子
    int size = endRange - beginRange + 1;
    auto bin = new vector<list<studentRecord>>(size);

    int numberOfElements = theList.size();
    for (int i = 0; i < numberOfElements; i++) {
        studentRecord temp(theList.front());
        theList.pop_front();
        bin->at(temp.age - beginRange).push_back(temp);
    }

    //收集箱子中的元素
    for (int i = 0; i < bin->size(); i++) {
        while (!bin->at(i).empty()) {
            theList.push_back(bin->at(i).front());
            bin->at(i).pop_front();
        }

    }
    delete bin;

}

int main() {
    studentRecord stu1(12, "习近平");
    studentRecord stu2(10, "栗战书");
    studentRecord stu3(18, "王岐山");
    studentRecord stu4(16, "拜登");
    studentRecord stu5(15, "特鲁多");
    studentRecord stu6(14, "特朗普");
    list<studentRecord> records;
    records.push_back(stu1);
    records.push_back(stu2);
    records.push_back(stu3);
    records.push_back(stu4);
    records.push_back(stu5);
    records.push_back(stu6);
    binSort(records,10,20);
    for(auto i:records)
    {
        cout << i.name << " " << i.age << endl;
    }

    return 0;
}