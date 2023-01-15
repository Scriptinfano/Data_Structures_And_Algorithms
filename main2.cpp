#include "iostream"

using namespace std;
typedef struct {
    int a{};
    string str;
} HashTab[12];

int main() {
    HashTab as;
    as[0].a = 12;
    as[1].str = "asd";
    cout << as[0].a << endl;
    return 0;
}