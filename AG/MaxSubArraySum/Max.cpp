#include <iostream>
#include <climits>

using namespace std;
int MaxSub(int arr[], int size)
{
    int max_ending_here = 0;
    int max_so_far = INT_MIN;

    for (int i = 0; i < size; i++)
    {
        max_ending_here = max_ending_here + arr[i];

        if (max_so_far < max_ending_here) // 如果目前的子长度已经比之前的大，替换

            max_so_far = max_ending_here;

        if (max_ending_here < 0)//累计的地方 ，+累加 ，-的话赋值
            max_ending_here = 0;
    }
    return max_so_far;
}

int main()
{
    int a[] = {-2, -1, 4, -1, -2, -1, -5, -3};
    int n = sizeof(a) / sizeof(a[0]);
    int max_sum = MaxSub(a, n);
    cout << "Maximum contiguous sum is " << max_sum;
    return 0;
}