/*测试matrix类的主函数*/
#include "MatrixMain.h"

#include <iostream>

using namespace std;

void testMatrixMultiply() {
    vector<vector<int>> element = {
            {4, 1},
            {3, 2}
    };
    vector<vector<int>> element2 = {
            {7, 9},
            {8, 5}
    };

    NormalMatrix<int> theMatrix(2,2);
    NormalMatrix<int> theMatrix2(2,2);
    NormalMatrix<int> *theMatrix3 = nullptr;

    theMatrix.initialize(element);
    theMatrix2.initialize(element2);

    theMatrix3 = theMatrix * theMatrix2;
    cout << theMatrix3;

}

void testMatrixTranspose() {
    NormalMatrix<int> theMatrix(2,2);
    NormalMatrix<int> *result = nullptr;

    vector<vector<int>> element2 = {
            {4, 1},
            {3, 2}
    };

    theMatrix.initialize(element2);
    cout<<theMatrix<<endl;

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
