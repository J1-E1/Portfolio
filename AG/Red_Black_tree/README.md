# red_black_tree
 Black red tree
## 1. Design decisions regarding median(t).
If number of nodes in tree is an odd number, middle value is fixed; if it is an even number, the median is the average of the middle two values.
### // Design decisions
1. Calculate the number of all nodes in the tree through countNodes. Because I have no clue on this topic, I went to the Internet to find ideas, so I used the Morris Inorder Traversal here which is mentioned on the Internet.
2. Use this method to calculate again whether its node is a midpoint. Or find the previous point and add them together to find the middle number.

3. Morris Traversal: Can traverse the tree without using stack and recursion. The idea is to find the rightmost value of lowest subtree first, and then exit the loop after finding this mark during the printing process.
## 2. Design decisions regarding intersection (t1, t2), and analysis of its time complexity.
Looking for the intersection of two trees, the nature of the red-black tree is a binary tree. It might be easier to understand if I regard it as 'finding the same element in two binary trees'.
Therefore, two trees are arranged in order. After querying the information available on the Internet, it is determined to use the stack data structure
I thought about the reason. If you put all the data of this tree in an array, it may be unusable when there is too much data, and the stack can be out of the stack after the comparison is completed, it will not take up space, and it is arranged in order at the same time. So, these two factors Is the key,

### // Design decisions
1. Starting from the simplest, if the data of root1 is equal to the data of root2, it will print and push out these two values at the same time, and then put the larger value into the stack.
2. If the value of root1 is greater than root2, delete the value in the stack and find the larger one in root2.
3. If the value of root2 is greater than root1, delete the value in the stack and find the larger one in root1.

### // Time complexity
O(n1+n2), n1 and n2 are number of nodes in first tree and second tree, because they need to go through two trees.

## 3. Brief instructions on how to run our program.
All the codes are done using gcc and plug-ins in vscode. The following are some instructions for use in the main function.

1. First create two arrays, and then print the arrays to represent the original data in the original data section. Then use CreateTree to create a tree, in which a for loop is applied.

2. The Search function passes in a tree root and the value to be found, and returns the tree.

3. Insert, first use newNode to create a node containing new data, and then use insert to pass in the root node and this node.

4. delete, similar to Insert, first use newNode to create a node containing data, and then use delete to pass in the root node and this node for deletion.

5. max and min, basically pass a root in these two functions and then find the leftmost and rightmost nodes. 

6. About the Intersection, pass two roots which both be created at the beginning, then function will find the same node than print it directly.
