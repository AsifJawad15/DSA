#include <iostream>
#include <chrono>
#include <random>

using namespace std;


void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
    }
}


void generateRandomArray(int arr[], int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);

    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
}

int main() {
    const int sizes[] = {1000, 5000, 10000};
    const int numSizes = sizeof(sizes) / sizeof(sizes[0]);


    for (int i = 0; i < numSizes; ++i) {
        int size = sizes[i];
        int arr[size];


        generateRandomArray(arr, size);


        auto start = chrono::high_resolution_clock::now();
        selectionSort(arr, size);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;


        cout << "Execution time for array size " << size << ": " << duration.count() << " seconds\n";
    }

    return 0;
}
