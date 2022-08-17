#include "diagonalMatrix.h"
#include <iostream>

using namespace std;

void testDiagonalInitialize() {
    diagonalMatrix<int> diagonal(3);
    int element[][3] = {
            {2, 0, 0},
            {0, 4, 0},
            {0, 0, 7}
    };
    diagonal.initialize((int *) element, 3);
    cout << diagonal;
}

void testDiagonalPlus() {
    diagonalMatrix<int> diagonal(3);
    int element[][3] = {
            {2, 0, 0},
            {0, 4, 0},
            {0, 0, 7}
    };
    diagonal.initialize((int *) element, 3);

    diagonalMatrix<int> diagonal2(3);
    int element2[][3] = {
            {4, 0, 0},
            {0, 6, 0},
            {0, 0, 9}
    };
    diagonal2.initialize((int *) element2, 3);

    diagonalMatrix<int> *result = diagonal + diagonal2;
    cout << *result;
}

void testDiagonalSub() {
    diagonalMatrix<int> diagonal(3);
    int element[][3] = {
            {2, 0, 0},
            {0, 4, 0},
            {0, 0, 7}
    };
    diagonal.initialize((int *) element, 3);

    diagonalMatrix<int> diagonal2(3);
    int element2[][3] = {
            {4, 0, 0},
            {0, 6, 0},
            {0, 0, 9}
    };
    diagonal2.initialize((int *) element2, 3);

    diagonalMatrix<int> *result = diagonal - diagonal2;
    cout << *result;

}

void testDiagonalMultiply() {
    diagonalMatrix<int> diagonal(3);
    int element[][3] = {
            {2, 0, 0},
            {0, 4, 0},
            {0, 0, 7}
    };
    diagonal.initialize((int *) element, 3);

    diagonalMatrix<int> diagonal2(3);
    int element2[][3] = {
            {4, 0, 0},
            {0, 6, 0},
            {0, 0, 9}
    };
    diagonal2.initialize((int *) element2, 3);

    diagonalMatrix<int> *result = diagonal * diagonal2;
    cout << *result;

}

void testTripleInitialize()
{
    tripleDiagonalMatrix<int> triple(4);
    int element[][4] = {
            {7, 4, 0,0},
            {8, 9, 12,0},
            {0, 5, 6,17},
            {0, 0, 3,2},

    };
    triple.initialize((int *) element, 4);
    cout << triple;

}
void testTriplePlus()
{
    tripleDiagonalMatrix<int> triple(4);
    int element[][4] = {
            {7, 4, 0,0},
            {8, 9, 12,0},
            {0, 5, 6,17},
            {0, 0, 3,2},

    };
    triple.initialize((int *) element, 4);

    tripleDiagonalMatrix<int> triple2(4);
    int element2[][4] = {
            {12, 3, 0,0},
            {22, 36, 16,0},
            {0, 13, 51,63},
            {0, 0, 67,52},
    };
    triple2.initialize((int *) element2, 4);

    tripleDiagonalMatrix<int>*result=triple+triple2;
    cout<<*result;

}
void testTripleSub()
{
    tripleDiagonalMatrix<int> triple(4);
    int element[][4] = {
            {7, 4, 0,0},
            {8, 9, 12,0},
            {0, 5, 6,17},
            {0, 0, 3,2},

    };
    triple.initialize((int *) element, 4);

    tripleDiagonalMatrix<int> triple2(4);
    int element2[][4] = {
            {12, 3, 0,0},
            {22, 36, 16,0},
            {0, 13, 51,63},
            {0, 0, 67,52},
    };
    triple2.initialize((int *) element2, 4);
    tripleDiagonalMatrix<int>*result=triple-triple2;
    cout<<*result;

}
void testTripleMultiply()
{
    tripleDiagonalMatrix<int> triple(4);
    int element[][4] = {
            {7, 4, 0,0},
            {8, 9, 12,0},
            {0, 5, 6,17},
            {0, 0, 3,2},

    };
    triple.initialize((int *) element, 4);

    tripleDiagonalMatrix<int> triple2(4);
    int element2[][4] = {
            {12, 3, 0,0},
            {22, 36, 16,0},
            {0, 13, 51,63},
            {0, 0, 67,52},
    };
    triple2.initialize((int *) element2, 4);

    tripleDiagonalMatrix<int>*result=triple*triple2;
    cout<<*result;

}

int main() {
    setbuf(stdout, nullptr);
    try {
        testTripleMultiply();
    } catch (const matrixSizeMismatch &theException) {
        cerr << theException.what() << endl;
    } catch (const IllegalParameterValue &theException) {
        cerr << theException.what() << endl;
    } catch (const matrixIndexOutOfBounds &theException) {
        cerr << theException.what() << endl;
    } catch (const uninitializedMatrix &theException) {
        cerr << theException.what() << endl;
    } catch (const reInitializedMatrix &theException) {
        cerr << theException.what() << endl;
    }catch(const invalidMatrixValueSet&theException)
    {
        cerr << theException.what() << endl;
    }
    return 0;
}