#include <iostream>
#include <chrono>
#include <random>

using namespace std;

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];


    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];


    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }


    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }


    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(int arr[], int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
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
        mergeSort(arr, 0, size - 1);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "Execution time for array size " << size << ": " << duration.count() << " seconds\n";
    }

    return 0;
}

