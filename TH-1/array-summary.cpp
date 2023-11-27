#include <iostream>
#include <chrono>
#include <random>
#include <cstdlib>
#include <pthread.h>
#include <string.h>

using namespace std;

struct sumArguments
{
    int *array;
    int start;
    int end;
};

void *sum(void *args)
{
    sumArguments *arguments = (sumArguments *)args;
    int *array = arguments->array;
    int start = arguments->start;
    int end = arguments->end;
    int *result = new int;
    *result = 0;
    for (int i = start; i < end; i++)
    {
        *result += array[i];
    }
    return result;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cout << "Usage: " << argv[0] << " <array size> <number of threads>" << endl;
        return 1;
    }

    int arraySize = stoi(argv[1]);
    int numberOfThreads = stoi(argv[2]);

    int *array = new int[arraySize];

    for (int i = 0; i < arraySize; i++)
    {
        array[i] = i + 1;
    }

    int sum = 0;

    auto start = chrono::steady_clock::now();

    for (int i = 0; i < arraySize; i++)
    {
        sum += array[i];
    }

    auto end = chrono::steady_clock::now();

    cout << "Sum: " << sum << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;

    return 0;
}