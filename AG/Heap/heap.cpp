#include <iostream>
#include <vector>

using namespace std;

bool test = 0;

void exchange(int *a, int *b);

class MinHeap
{
    int *arr; // point to heap arry
    int heap_size;
    int length;

public:
    MinHeap(int length);
    void MinHEAPIFY(int i);
    int PARENT(int i);
    int LEFT(int i);
    int RIGHT(int i);

    void insert(int key);
    void minimum();
    void extract();

    void printheap();

    void Build_Min_Heap();
};

// parent index
int MinHeap::PARENT(int i)
{
    return (i - 1) / 2;
}

// left index
int MinHeap::LEFT(int i)
{
    return 2 * i + 1;
}

// right index
int MinHeap::RIGHT(int i)
{
    return 2 * i + 2;
}
MinHeap::MinHeap(int len)
{
    heap_size = 0;
    length = len;
    arr = new int[length];
}
// Min-HEAPIFY(A,i)
void MinHeap::MinHEAPIFY(int i)
{
    int l = LEFT(i);
    int r = RIGHT(i);
    int smallest = i; // if node i is the smallest.

    // left or right is samllest
    if (l <= heap_size && arr[l] < arr[i])
        smallest = l;
    else
        smallest = i;
    if (r <= heap_size && arr[r] < arr[smallest])
        smallest = r;

    if (smallest != i)
    {
        exchange(&arr[i], &arr[smallest]);
        MinHEAPIFY(smallest);
    }
}

void MinHeap::insert(int key)
{

    if (heap_size == length)
    {
        cout << "out of bound" << endl;
        exit(-1); // exit()
    }
    heap_size++;
    int index = heap_size - 1;
    int parent = PARENT(index);
    arr[index] = key;
    // here parent always change until while is over
    // so original only do once
    // + parent = PARENT(index);
    while (index != 0 && arr[index] < arr[parent])
    {
        exchange(&arr[index], &arr[parent]);
        index = parent;
        parent = PARENT(index);
    }
    if (test)
    {
        MinHeap mh = MinHeap(5);
        mh.insert(10);
        mh.insert(21);
        mh.insert(20);
        mh.insert(5);
        mh.insert(3);
        mh.insert(3);
        mh.insert(24);
        mh.insert(81);
        mh.insert(21);
        // mh.insert(3); - out of bound
        mh.printheap();
    }
}

void MinHeap::minimum()
{
    cout << "first node is: " << arr[0] << endl;
}
void MinHeap::extract()
{
    minimum();
    arr[0] = arr[heap_size - 1];
    heap_size--;
    MinHEAPIFY(heap_size);
    printheap();
}
void MinHeap::printheap()
{
    for (int i = 0; i < heap_size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void MinHeap::Build_Min_Heap()
{
    heap_size = length;
    for (int i = length / 2; i >= 0; i--)
    {
        MinHEAPIFY(i);
    }
}

void exchange(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;

    if (test)
    {
        int a[] = {13, 4, 5};
        int *pt = &a[2];
        int *pt2 = &a[0];
        exchange(pt, pt2);
        cout << a[0] << " " << a[2] << endl;
    }
}
int main()
{
    MinHeap mh = MinHeap(31);
    mh.insert(10);
    mh.insert(21);
    mh.insert(20);
    mh.insert(5);
    mh.insert(3);
    mh.insert(3);
    mh.insert(24);
    mh.insert(81);
    mh.insert(21);

    mh.printheap();
    return 0;
}