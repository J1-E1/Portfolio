#include <iostream>
#include <vector>
#include <math.h>

void exchange(float *a, float *b);
using namespace std;
bool test = 0;
class Beap
{
    float *arr; // point to heap arry
    int beap_size;
    int length;

public:
    Beap(int length);
    ~Beap();
    int depth(int i);
    int blockStart(int i);
    int blockEnd(int i);
    int leftParent(int index, int current_level);
    int rightParent(int index, int current_level);

    void startExchange(int index, int current_level);
    void endExchange(int index, int current_level);

    void BeapHEAPIFY();
    void insert(float key);
    void search(float key);
    void maximum();
    void minimum();
    void extract();

    void printBeap();
};

// current depth , N is elements in here
int Beap::depth(int N)
{

    return round(sqrt(2 * N)); // round more detail

    if (test)
    {
        cout << sqrt(2 * N) << endl;
        Beap a = Beap(11);
        cout << a.depth(6) << endl;  // 3
        cout << a.depth(10) << endl; // 4
        cout << a.depth(11) << endl; // 5
    }
}

int Beap::blockStart(int current_level)
{
    int i = current_level;
    return (i * (i - 1) / 2 + 1) - 1; // -1 for index

    if (test)
    {
        // root =level 1
        Beap bp = Beap(10);
        // should -1
        cout << bp.blockStart(1) << endl; // 1
        cout << bp.blockStart(2) << endl; // 2
        cout << bp.blockStart(3) << endl; // 4
    }
}

int Beap::blockEnd(int current_level)
{
    int i = current_level;
    return (i * (i + 1) / 2) - 1; // -1 for index
}

// left parent
int Beap::leftParent(int index, int current_index_level)
{
    int i = current_index_level;
    return index - i;

    if (test)
    {
        Beap bp = Beap(10);
        cout << bp.leftParent(4, 3) << endl;
        cout << bp.leftParent(7, 4) << endl;
        cout << bp.leftParent(8, 4) << endl;
    }
}

// right parent
int Beap::rightParent(int index, int current_index_level)
{
    int i = current_index_level;
    return index - i + 1;

    if (test)
    {
        Beap bp = Beap(10);
        cout << bp.rightParent(4, 3) << endl; // 2
        cout << bp.rightParent(7, 4) << endl; // 4
        cout << bp.rightParent(8, 4) << endl; // 5
    }
}

// int index, int current_level
void Beap::startExchange(int index, int current_level)
{
    int p2_index = rightParent(index, current_level);
    while (arr[index] < arr[p2_index] && index != 0)
    {
        exchange(&arr[index], &arr[p2_index]);
        index = p2_index;
        current_level--;
        p2_index = rightParent(index, current_level);
    }
}

void Beap::endExchange(int index, int current_level)
{
    int p1_index = leftParent(index, current_level);
    while (arr[index] < arr[p1_index] && index != 0)
    {
        exchange(&arr[index], &arr[p1_index]);
        index = p1_index;
        current_level--;
        p1_index = rightParent(index, current_level);
    }
}

Beap::Beap(int len)
{
    beap_size = 0;
    length = len;
    arr = new float[length];
}

Beap::~Beap()
{
    delete[] arr;
}
// concept : have a loop , compare every elements in beap
// from current_height in(depth)
// every element in each level
void Beap::BeapHEAPIFY()
{

    int index_current;
    int current_level;

    int index_left_child;
    int index_right_child;

    // depth(beap_size) - 1 , last level have no child
    for (current_level = 1; current_level <= depth(beap_size) - 1; current_level++)
    {
        int last_level = current_level + 1;
        int last_level_element_amount = beap_size - 1 - blockStart(last_level);
        int compare_end = blockStart(current_level) + last_level_element_amount;
        int last = blockEnd(current_level);
        if (current_level == depth(beap_size) - 1)
        {
            last = compare_end;
        }

        for (index_current = blockStart(current_level); index_current <= last; index_current++) //
        {

            // if last_level is not full, have child or no have child2
            // condition1 (last 2nd level) + condition2(last index is not the index in end of this level)
            if ((current_level == depth(beap_size) - 1) && index_current == compare_end) //
            {

                index_left_child = index_current + (current_level + 1) - 1;
                // just pass that next if  ( :
                index_right_child = index_left_child;
            }
            else
            {
                index_left_child = index_current + (current_level + 1) - 1;
                index_right_child = index_current + (current_level + 1);
            }

            if (arr[index_current] >= arr[index_left_child] || arr[index_current] >= arr[index_right_child])
            {
                // swap with the smaller one
                if (arr[index_left_child] >= arr[index_right_child])
                    exchange(&arr[index_current], &arr[index_right_child]);
                else
                    exchange(&arr[index_current], &arr[index_left_child]);
            }
        }
    }
}

void Beap::insert(float key)
{
    if (beap_size == length)
    {
        cout << "out of beap bound" << endl;
        exit(-1); // exit()
    }
    beap_size++;
    int index = beap_size - 1; // start from 0
    int current_level = depth(beap_size);
    arr[index] = key;

    if (index != 0 && index == blockStart(current_level)) // start
    {
        startExchange(index, current_level);
    }
    else if (index != 0 && index == blockEnd(current_level)) // end
    {
        endExchange(index, current_level);
    }
    else // middle
    {
        if (index != 0)
        {
            int p1_index = leftParent(index, current_level);
            int p2_index = rightParent(index, current_level);
            while ((arr[index] < arr[p1_index] || arr[index] < arr[p2_index]) && index != 0)
            {

                if (arr[p1_index] > arr[p2_index])
                {
                    exchange(&arr[index], &arr[p1_index]);
                    index = p1_index;
                    current_level--;
                }
                else
                {
                    exchange(&arr[index], &arr[p2_index]);
                    index = p2_index;
                    current_level--;
                }

                if (index == blockStart(current_level)) // start
                {
                    startExchange(index, current_level);
                }
                else if (index == blockEnd(current_level)) // end
                {
                    endExchange(index, current_level);
                }
                else
                {
                    p1_index = leftParent(index, current_level);
                    p2_index = rightParent(index, current_level);
                }
            }
        }
    }

    if (test)
    {
        Beap bp = Beap(10);
        bp.insert(3.1);
        bp.insert(7.8);
        bp.insert(7.2);
        bp.insert(2.1);
        bp.insert(7.3);

        bp.printBeap();
    }
}

void Beap::search(float key)
{
    int index = beap_size - 1;
    int current_level = depth(beap_size);
    string message = "Error: can not find any matched key ";

    // find the right - right point
    if (index != blockEnd(current_level))
    {
        index = blockEnd(--current_level);
    }

    //  compare and search
    // -1< current_level < max_depth
    while (current_level != 0 && current_level != (depth(beap_size) + 1))
    {
        if (key < arr[index]) // x less than element
        {
            index = leftParent(index, current_level);
            current_level--;
        }
        else if (key > arr[index])
        {
            // depth( current heap element = index +1)
            // if there have two differen dignoal in two different level
            // need to think when should move to the next line
            // last_index = beap_size -1  - blockStart(depth(beap_size)) = how many elements in last level
            // current_level_start = blockstart(current_level) +last_....
            // condition1 + condition2(when need to jump to next) + condition3 (to the left bound)

            int last_level_element_amount = beap_size - 1 - blockStart(depth(beap_size));
            int current_level_start = blockStart(current_level) + last_level_element_amount;
            // index start from 0
            if (current_level == depth(index + 1) && index != current_level_start && index != blockStart(current_level))
            {
                index--;
            }
            else
            {
                // right_parent = index -i(index_current_level)+1
                index = index + (current_level + 1) - 1;
                current_level++;
            }
        }
        else
        {
            cout << "Found : " << arr[index] << " - [" << index << "]" << endl;
            exit(0);
        }
    }
    cout << message << endl;

    if (test)
    {
        Beap bp = Beap(100);
        bp.printBeap();

        bp.search(6.9);
        bp.search(18.1);

        bp.search(3.1); // top
        bp.search(18.1);
        bp.search(19.1);
    }
}

void Beap::maximum()
{
    int index = beap_size - 1;
    int max_key = index;
    while (index != blockStart(depth(beap_size) - 1))
    {
        if (arr[max_key] < arr[index])
        {
            max_key = index;
            index--;
        }
        else
        {
            index--;
        }
    }
    cout << "Max : " << arr[max_key] << " - [" << max_key << "]" << endl;
}

void Beap::minimum()
{
    cout << "Min : " << arr[0] << " - [" << 0 << "]" << endl;
}

void Beap::extract()
{
    minimum();
    arr[0] = arr[beap_size - 1];
    beap_size--;
    BeapHEAPIFY();
    printBeap();
}

void exchange(float *a, float *b)
{
    float temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void Beap::printBeap()
{
    for (int i = 0; i < beap_size; i++)
    {
        cout << float(arr[i]) << " ";
    }
    cout << endl;
}
int main()
{
    int index = 0;
    Beap bp = Beap(100);
    bp.insert(3.1);
    bp.insert(7.8);
    bp.insert(7.2);
    bp.insert(2.1);
    bp.insert(7.3);
    bp.insert(4.1);
    bp.insert(18.1);
    bp.insert(8.1);
    bp.insert(7.7);
    bp.insert(7.6);
    bp.insert(9.1);
    bp.insert(19.1);

    bp.printBeap();
    bp.maximum();
    bp.minimum();
    // bp.extract();

    return 0;
}