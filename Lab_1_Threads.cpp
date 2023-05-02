#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cstdlib>

// Fill the square matrix with random numbers. on the main diagonal, place the sums of the elements that lie in the same column.

using namespace std;

int** fillmatrix(const int matrixsize) {
    int** matrix = new int* [matrixsize];

    // providing a seed value
    srand((unsigned)time(NULL));

    for (int i = 0; i < matrixsize; i++)
    {
        matrix[i] = new int[matrixsize];
        for (int j = 0; j < matrixsize; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

int** rebuildmatrix(int** matrix, const int matrixsize) {
    for (int i = 0; i < matrixsize; i++) {
        int sum = 0;
        for (int j = 0; j < matrixsize; j++) {
            sum += matrix[j][i];
        }
        matrix[i][i] = sum;
    }
    return matrix;
}

void rebuildMatrixThread(int** matrix, const int matrixsize, int start, int end) {
    for (int i = start; i < end; i++) {
        int sum = 0;
        for (int j = 0; j < matrixsize; j++) {
            sum += matrix[j][i];
        }
        matrix[i][i] = sum;
    }
}

void printmatrix(int** matrix, int matrixsize)
{
    for (int i = 0; i < matrixsize; ++i) {
        for (int j = 0; j < matrixsize; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "You should provide two arguments (matrix size and threads number)" << "\n";
    }
    const int matrixSize = atoi(argv[1]);
    const int threadsNum = atoi(argv[2]);
    cout << "Matrix Size: " << matrixSize << " Threads Num: " << threadsNum << "\n";

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    cout << "Base matrix" << "\n";
    int** matrix = fillmatrix(matrixSize);
    //printmatrix(matrix);

    // rebuild without threads
    cout << "rebuilded matrix" << "\n";
    auto t1 = high_resolution_clock::now();
    int** rebuildedmatrix = rebuildmatrix(matrix, matrixSize);
    auto t2 = high_resolution_clock::now();
    //printmatrix(rebuildedmatrix);

    // mesuaring time without threads
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";


    // create threads
    auto t3 = high_resolution_clock::now();
    vector<thread> threads;
    int blockSize = matrixSize / threadsNum;
    for (int i = 0; i < threadsNum; i++) {
        int start = i * blockSize;
        int end = (i + 1) * blockSize;
        if (i == threadsNum - 1) {
            end = matrixSize;
        }
        threads.emplace_back(rebuildMatrixThread, matrix, matrixSize, start, end);
    }
   
    // wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    auto t4 = high_resolution_clock::now();

    // mesuaring time with threads
    auto ms_int2 = duration_cast<milliseconds>(t4 - t3);
    duration<double, std::milli> ms_double2 = t4 - t3;

    std::cout << ms_int2.count() << "ms\n";
    std::cout << ms_double2.count() << "ms\n";

    return 0;
}
