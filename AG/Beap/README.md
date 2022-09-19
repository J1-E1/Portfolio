# Chapter 2 - Beap

## Some parameters

1. i = current level, i = elements in this level
2. start = (i\*(i-1)/2+1)
3. end = (i\*(i+1)/2)
4. left parent = index - i -1
5. right parent = index - i
   (When index = start or end, left or right parent +1, some parent nodes will be ignored)

## Functions

### 1 Minimum

The minimum key is first element, which is arr[0].
Here because we do min function after insert, so that we only do cout, print arr[0].

### 2 Maximum

In essay, it said" The maximum is one of the last (2N)^1/2" locations",
but When actually writing the program, I found that if there is only one parameter in the last line,
the largest parameter will also appear in the second half of the penultimate line.
The reason for the impact, I think, is because there are not enough children, it has no way to put the parameters to the bottom.

Base on that, I try to loop through two rows of parameters, and then return the largest key and index.
The time complexity should be the sum of the last two rows of elements.

### 3 Insertion

#### Base on essay:

1. condition: if this element is smaller than either of its parents, interchanged with the larger parent.
2. stop: Sifting-up process is continued until the element is in a position such that it is larger than both of its parents.

Practical application:
So according to the above conditions, we know most of basis for judgment, but the actual operation will be somewhat complicated.

    1. First of all, we need to consider that if inserted position is the beginning or end of the block,
    there will only be the left parent or the right parent, so we take it out separately,
    and use endExchange and start Exchange to complete the boundary shift exchange.

    2. Index in while! =0 can ensure that this loop is skipped at the beginning,
    and it can also be judged whether it reaches the top during the exchange process.

    3. Regarding whether there is a problem with the right and left children,
    we can make two children on the same side(same index) to pass the judgment.

How to judge whether beap conditions are met:

1. The smallest is at the top, the largest is in the last two lines.
2. The child is smaller than parent, and each layer has same elements as the number of layers.
3. Each row and each column are arranged in ascending order.

### 4 Search

We start from the top right (find a full level), top right corner of the matrix,
x is the search number and key is number in array,
function will return the key or print " no matched".

#### There are 3 different ways to compare:

1. x< key, move left one (go up one) along the row.

2. x>key, either move down one position or if on the diagonal, then move left (index -1) one position, like both graphs below, need to consider both diagonal cases. At the junction of two diagonals, it is necessary to judge whether it can go down, so it is also reflected in function.

3. if x = key, stop searching.

Repeating the above process, stop condition is to the leftmost top or bottom.

### 5 Extract

The purpose of this function is to remove the smallest value, and then modify the entire beap to meet the requirements of beap.

Here I put the last parameter in 0 position to achieve the purpose of removing smallest, and then use BeapHEAPIFY to maintain the nature of beap.

For BeapHEAPIFY, it mainly maintains characteristics of beap.
Its main content is to loop through each parameter of each layer to compare key of each (parent node-2 child nodes).
The parent node is exchanged with the smaller children until depth = the penultimate line. index = the junction of two diagonals, as shown below.

Because at this point, there is only the left child node, exchange will only end here.
If it is complete, it will reach the last point.
Here are several parameters in last line to calculate which one is the end of second-to-last line, that is, compare_end in function.
The principle is that upper and lower ones correspond to each other, so the calculation can be reversed.

# Chapter 3 - Test

The random data set in the experiment may not have a value (experiment time).
The experimental results here are all through inputting a feasible data set, and two algorithm data sets are different.
Verify time calculation of comparison time table in assignment report through preliminary comparison of two experiment time.

## 1

The following figure is the test code, which is mainly to add random values,
N is the input amount, and the speed is calculated by the time difference.

Insert
Elements Minheap Beap
100 0.000006 0.000031
1000000 0.065905 0.31
10000000 0.653032 3.1

## 2

Through the analysis of experimental data, it can be initially obtained that the running time of Beap under insert is greater than that of Minheap.
In experiment, it is about 5 times larger. Because it is not the worst case,
it can only be initially obtained that operating efficiency of beap is slightly worse than that of Minheap.

Extract
Elements Minheap Beap
100 0.000134 0.000228
10000 0.008846 0.009781-0.015319
100000 0.08846 0.38572
1000000 0.858804 1.69

Extract also got a similar situation,
so it is basically obtained through experiments. In the case of Extract,
the efficiency of Minheap is slightly higher than that of Beap. Beap in deletion is O((N)^1/2)) ,
Minheap is O(logn), still 1.7-4.7 times larger than minheap.

## Conclusion

Test experiment with random input parameters proves that Minheap is higher than Beap in operating efficiency.
Since experiment is tested by random input, it will be difficult to verify the worst results of the two algorithms.

# Chapter 4 - 3-eap

## Concept:

3 parents and 3 children.
It is a three-dimensional structure (not Beap's planar structure), so there will be more lines.
The right corner figure below is a third-level planar structure, and each node has 3 lines connected to the upper level.

The number of nodes in each layer of data is based on formula Tn = n\*(n+1)/2 , n is a layer here.
Reason for number of nodes in each layer is that a triangle can be generated for these nodes,
and the sum of the arithmetic sequence from top to bottom is the total number of nodes at each level.

## Operations:

1. complexity

2. Are there any situations where this generalization make sense?

The program structure of the main function and sub-function in the program. The structure of file management.

Arrangement structure of sub-server and main server; network structure of routers and switches.

It may also be used in the 3D model because of its design structure.

## Conclusion:

When k-eap, the number of nodes in each layer will continue to increase,
density and connecting lines will also increase, the overall shape is like a mountain
