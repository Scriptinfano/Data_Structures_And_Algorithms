/*测试matrix类的主函数*/
#include "MatrixMain.h"
#include <iostream>

using namespace std;

void testMatrixMultiply() {
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

}

void testMatrixTranspose() {
    matrix<int> theMatrix(2, 2);
    matrix<int> result(2, 2);

    int element[][2] = {
            {4, 1},
            {3, 2}
    };
    theMatrix.initialize((int *) element, 2, 2);
    result.initialize();
    result = theMatrix.transpose();
    cout << result;

}

int main() {
    try {
        testMatrixTranspose();
    } catch (const matrixSizeMismatch &theException) {
        cerr << theException.what() << endl;
    } catch (const IllegalParameterValue &theException) {
        cerr << theException.what() << endl;
    } catch (const matrixIndexOutOfBounds &theException) {
        cerr << theException.what() << endl;
    } catch (const uninitializedMatrix &theException) {
        cerr << theException.what() << endl;
    } catch (const reinitializedMatrix &theException) {
        cerr << theException.what() << endl;
    }
    return 0;
}
