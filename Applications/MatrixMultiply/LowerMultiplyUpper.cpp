//实现下三角矩阵和上三角矩阵的乘法
#include"D:\ClionProjects\Data_Structures_And_Algorithms\matrix\diagonalMatrix.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\matrix\MatrixMain.h"

template<class T>
BasicMatrix<T> *lowerMultiplyUpper(const lowerTriangularMatrix<T> &lower, const upperTriangularMatrix<T> &upper) {
    if (!lower.isInitialized() || !upper.isInitialized())throw MatrixUnInitializeException("两个矩阵相乘时，其中有一个矩阵处于未初始化状态");
    if (lower.getDimension() != upper.getDimension())throw matrixSizeMismatchOfMultiply();
    auto result = new BasicMatrix<T>(lower.getDimension(), upper.getDimension());
    result->initialize();
    for (int i = 0; i < lower.getDimension(); i++) {
        for (int j = 0; j < upper.getDimension(); j++) {
            T sum = 0;
            for (int k = 0; k < lower.getDimension(); k++) {
                sum += lower.get(i + 1, k + 1) * upper.get(k + 1, j + 1);
            }
            result->set(i + 1, j + 1, sum);
        }
    }
    return result;

}

int main() {
    lowerTriangularMatrix<int> lower(4);
    int element[][4] = {
            {7, 0, 0, 0},
            {8, 9, 0, 0},
            {2, 5, 6, 0},
            {5, 2, 3, 2},
    };
    lower.initialize((int *) element, 4);

    upperTriangularMatrix<int> upper(4);
    int element2[][4] = {
            {7, 2, 3, 6},
            {0, 9, 4, 5},
            {0, 0, 8, 4},
            {0, 0, 0, 2},
    };
    upper.initialize((int *) element2, 4);

    auto result = lowerMultiplyUpper(lower, upper);
    cout<<(*result);
}
