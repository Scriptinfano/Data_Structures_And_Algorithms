/*测试matrix类的主函数*/
#include "MatrixMain.h"
#include <iostream>

using namespace std;

int main() {
    try {
        matrix<int> theMatrix(2, 2);
        int element[][2] = {
                {4, 1},
                {3, 2}
        };
        matrix<int> theMatrix2(2, 2);
        int element2[][2] = {
                {7, 9},
                {8, 5}
        };
        matrix<int> theMatrix3(2, 2);

        theMatrix.initialize((int *) element, 2, 2);
        theMatrix2.initialize((int *) element2, 2, 2);

        theMatrix3 = theMatrix * theMatrix2;
        cout << theMatrix3;


    } catch (const matrixSizeMismatch &theException) {
        cerr << theException.what() << endl;
    }
    return 0;
}
