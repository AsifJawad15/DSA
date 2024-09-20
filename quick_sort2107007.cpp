#include <iostream>
#include <chrono>
#include <random>

using namespace std;

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}


void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void generateRandomArray(int arr[], int size)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);

    for (int i = 0; i < size; ++i)
    {
        arr[i] = dis(gen);
    }
}

int main()
{
    const int sizes[] = {1000, 5000, 10000};
    const int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < numSizes; ++i)
    {
        int size = sizes[i];
        int arr[size];


        generateRandomArray(arr, size);


        auto start = chrono::high_resolution_clock::now();
        quickSort(arr, 0, size - 1);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "Execution time for array size " << size << ": " << duration.count() << " seconds\n";
    }

    return 0;
}
