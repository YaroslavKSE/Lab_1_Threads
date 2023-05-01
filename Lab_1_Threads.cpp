#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
// Fill the square matrix with random numbers. on the main diagonal, place the sums of the elements that lie in the same column.

using namespace std;
const int matrixsize = 3000;
const int threadsNum = 2;

int** fillmatrix() {
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

int** rebuildmatrix(int** matrix) {
    for (int i = 0; i < matrixsize; i++) {
        int sum = 0;
        for (int j = 0; j < matrixsize; j++) {
            sum += matrix[j][i];
        }
        matrix[i][i] = sum;
    }
    return matrix;
}

void rebuildMatrixThread(int** matrix, int start, int end) {
    for (int i = start; i < end; i++) {
        int sum = 0;
        for (int j = 0; j < matrixsize; j++) {
            sum += matrix[j][i];
        }
        matrix[i][i] = sum;
    }
}

void printmatrix(int** matrix)
{
    for (int i = 0; i < matrixsize; ++i) {
        for (int j = 0; j < matrixsize; ++j) {
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

    cout << "Base matrix" << "\n";
    int** matrix = fillmatrix();
    //printmatrix(matrix);

    // rebuild without threads
    cout << "rebuilded matrix" << "\n";
    auto t1 = high_resolution_clock::now();
    int** rebuildedmatrix = rebuildmatrix(matrix);
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
    int blockSize = matrixsize / threadsNum;
    for (int i = 0; i < threadsNum; i++) {
        int start = i * blockSize;
        int end = (i + 1) * blockSize;
        if (i == threadsNum - 1) {
            end = matrixsize;
        }
        threads.emplace_back(rebuildMatrixThread, matrix, start, end);
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

//#include <iostream>
//#include <thread>
//#include <vector>
//using namespace std;
//
//const int THREAD_NUM = 1;
//const int ARRAY_SIZE = 10000;
//
//void func(const vector<int>& input, int thread_index, int thread_number, vector<int>& output)
//{
//    // Each thread calculates sum of different elemets and puts the result to an intermediate storage
//    for (size_t i = thread_index; i < input.size(); i += thread_number)
//    {
//        output[thread_index] += input[i];
//    }
//}
//
//int main()
//{
//    using std::chrono::high_resolution_clock;
//    using std::chrono::duration_cast;
//    using std::chrono::duration;
//    using std::chrono::milliseconds;
//
//    vector<int> v;
//    // Put random values inside the vector
//    for (int i = 0; i < ARRAY_SIZE; i++)
//    {
//        v.push_back(rand() % 100);
//    }
//
//    // Fill the output array with zeroes to calculate each thread's sum inside
//    vector<int> answers(THREAD_NUM, 0);
//     
//    auto t1 = high_resolution_clock::now();
//
//    // Start threads
//    thread threads[THREAD_NUM];
//    for (int i = 0; i < THREAD_NUM; i++)
//    {
//        threads[i] = thread(func, v, i, THREAD_NUM, std::ref(answers));
//    }
//
//    // Wait for threads completion
//    for (int i = 0; i < THREAD_NUM; i++)
//    {
//        threads[i].join();
//    }
//
//    // Calculate the final answer in the main thread
//    int final_answer = 0;
//    for (int i = 0; i < THREAD_NUM; i++)
//    {
//        final_answer += answers[i];
//    }
//    auto t2 = high_resolution_clock::now();
//    // mesuaring time with threads
//    auto ms_int2 = duration_cast<milliseconds>(t2 - t1);
//    duration<double, std::milli> ms_double2 = t2 - t1;
//
//    std::cout << ms_int2.count() << "ms\n";
//    std::cout << ms_double2.count() << "ms\n";
//
//    cout << "Final sum = " << final_answer << endl;
//
//    return 0;
//}