/*测试matrix类的主函数*/
#include "MatrixMain.h"

#include <iostream>

using namespace std;

void testMatrixMultiply() {
    vector<vector<int>> element = {
            {3, 1, 0},
            {-1, 2, 1},
            {3, 4, 2},
    };
    vector<vector<int>> element2 = {
            {1, -1, 0},
            {2, -2, 5},
            {3, 4, 1},
    };

    NormalMatrix<int> theMatrix(3, 3);
    NormalMatrix<int> theMatrix2(3, 3);
    NormalMatrix<int> *theMatrix3 = nullptr;
    NormalMatrix<int> *theMatrix4 = nullptr;
    NormalMatrix<int> *theMatrix5 = nullptr;

    theMatrix.initialize(element);
    theMatrix2.initialize(element2);

    theMatrix3 = theMatrix * theMatrix2;
    cout << *theMatrix3<<endl;

    theMatrix4=theMatrix2*theMatrix;
    cout << *theMatrix4<<endl;

    theMatrix5=(*theMatrix3)-(*theMatrix4);
    cout << *theMatrix5;

}

void testMatrixTranspose() {
    NormalMatrix<int> theMatrix(3, 1);
    NormalMatrix<int> *result = nullptr;

    vector<vector<int>> element2 = {
            {1},
            {2},
            {0}
    };

    theMatrix.initialize(element2);
    cout << theMatrix << endl;

    result = theMatrix.transpose();
    cout << *result;

}

int main() {
    try {
        setbuf(stdout, nullptr);
        testMatrixTranspose();
    } catch (const matrixSizeMismatch &theException) {
        cerr << theException.what() << endl;
    } catch (const IllegalParameterException &theException) {
        cerr << theException.what() << endl;
    } catch (const matrixIndexOutOfBounds &theException) {
        cerr << theException.what() << endl;
    } catch (const MatrixUnInitializeException &theException) {
        cerr << theException.what() << endl;
    } catch (const MatrixReinitializeException &theException) {
        cerr << theException.what() << endl;
    }
    return 0;
}
