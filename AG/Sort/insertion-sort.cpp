#include <iostream>
#include <vector>

void insertionSort(int A[], int n)
{
    int key;
    for (int j = 2; j <= n; j++)
    {
        key = A[j];
        int i = j - 1;
        while (i > 0 && key < A[i])
        {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i] = key;
    }
}