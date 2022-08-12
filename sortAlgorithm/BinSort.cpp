#include <iostream>
#include <string>
#include <list>

using namespace std;

class studentRecord {
public:
    int score;
    string name;
public:
    studentRecord(const int &theScore, const string &theName) : score(theScore), name(theName) {}

    int operator!=(const studentRecord &theRecord) const {
        return (score != theRecord.score);
    }

    operator int() const { return score; }
};

ostream &operator<<(ostream &out, const studentRecord &theRecord) {
    out << theRecord.score << " " << theRecord.name << endl;
    return out;
}
void binSort(list<studentRecord>&theList,const int &beginRange,const int &endRange)
{
    //初始化箱子
    list<studentRecord>*bin;//箱子
    int size= endRange-beginRange+1;
    bin=new list<studentRecord>[size];

    int numberOfElements=theList.size();
    for(int i=0;i<numberOfElements;i++)
    {
        studentRecord temp=theList.front();
        theList.pop_front();
        bin[temp.score-beginRange].push_back(temp);
    }

    //收集箱子中的元素
    for(int i =0;i<bin->size();i++)
    {
        while(!bin[i].empty())
        {
            theList.push_back(bin[i].front());
            bin[i].pop_front();
        }

    }
    delete[]bin;

}
int main() {

    return 0;
}