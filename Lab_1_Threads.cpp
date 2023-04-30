#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
const int matrixsize = 3;

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

    auto t1 = high_resolution_clock::now();
    cout << "base matrix" << "\n";
    int** matrix = fillmatrix();
    printmatrix(matrix);
    cout << "rebuilded matrix" << "\n";
    int** rebuildedmatrix = rebuildmatrix(matrix);
    printmatrix(rebuildedmatrix);
    auto t2 = high_resolution_clock::now();

    /* getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_int.count() << "ms\n";
    std::cout << ms_double.count() << "ms\n";

    return 0;
}

//void compute(const std::size_t thread_id, const std::size_t message_count)
//{
//	for (std::size_t index = 0; index < message_count; index++) {
//		std::printf("Thread with ID [%llu] started.", thread_id);
//	}
//}
//int main()
//{
//	const std::size_t thread_id = 13;
//	const std::size_t message_count = 100;
//	std::thread thread = std::thread(compute, thread_id, message_count);
//	thread.join();
//
//	return 0;
//}


// Fill the square matrix with random numbers. on the main diagonal, place the sums of the elements that lie in the same column.



