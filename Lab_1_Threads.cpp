#include <iostream>
#include <chrono>
using namespace std;
const int matrixSize = 3;

int** fillMatrix() {
    int** matrix = new int* [matrixSize];

    // Providing a seed value
    srand((unsigned)time(NULL));


    for (int i = 0; i < matrixSize; i++)
    {
        matrix[i] = new int[matrixSize];
        for (int j = 0; j < matrixSize; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

int** rebuildMatrix(int** matrix) {
    for (int i = 0; i < matrixSize; i++) {
        int sum = 0;
        for (int j = 0; j < matrixSize; j++) {
            sum += matrix[j][i];
        }
        matrix[i][i] = sum;
    }
    return matrix;
}

void printMatrix(int** matrix)
{
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    cout << "Base Matrix" << "\n";
    int** matrix = fillMatrix();
    printMatrix(matrix);
    cout << "Rebuilded Matrix" << "\n";
    int** rebuildedMatrix = rebuildMatrix(matrix);
    printMatrix(rebuildedMatrix);
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";

    return 0;
}

// Fill the square matrix with random numbers. On the main diagonal, place the sums of the elements that lie in the same column.

