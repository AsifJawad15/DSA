#include <iostream>
#include <chrono>
#include <random>

using namespace std;


void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {

                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
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
        bubbleSort(arr, size);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;


        cout << "Execution time for array size " << size << ": " << duration.count() << " seconds\n";
    }

    return 0;
}
