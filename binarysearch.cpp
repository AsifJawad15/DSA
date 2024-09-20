#include<bits/stdc++.h>
using namespace std;

int bin(int arr[], int key, int size)
{
    int l, mid, h;
    l = 0;
    h = size - 1;
    while (l <= h)
    {
        mid = (l + h) / 2;
        if (key == arr[mid])
            return mid;
        else if (key < arr[mid])
            h = mid - 1;
        else
            l = mid + 1;
    }
    return -1;
}

int main()
{
    int arr[] = {2, 3, 4, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]); // Calculate the size of the array
    printf("%d\n", bin(arr, 5, size));
    return 0;
}
