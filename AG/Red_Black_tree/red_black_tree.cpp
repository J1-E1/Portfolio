#include <stdio.h>
#include <iostream>
#include <stack>

struct Node
{
    /* data
    int data
    bool color : red =0 , black =1
    */
    int data;
    bool color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} node;

class RBTree
{
public:
    Node *root;

public:
    RBTree(/* args */);
    ~RBTree();
    struct Node *newNode(int new_data);
    struct Node *CreateTree(struct Node *node, int node_data);
    struct Node copy_object(struct Node *node);

    struct Node *Search(struct Node *tree, int key);
    void Left_Rotate(struct Node *tree, struct Node *node);
    void Right_Rotate(struct Node *tree, struct Node *Node);

    void Insert_Fixup(struct Node *tree, struct Node *newnode);
    void Insert(struct Node *tree, struct Node *newnode);

    void Tansplant(struct Node *tree, struct Node *u, struct Node *v);
    void Delete(struct Node *tree, int key);
    void Delete_Fixup(struct Node *tree, struct Node *newnode);

    void Traverse(struct Node *root);
    struct Node *Min(struct Node *node);
    struct Node *Max(struct Node *node);

    int countNodes(struct Node *root);
    int Medinan(struct Node *root);
    void Intersection(struct Node *tree1, struct Node *tree2);
};

// create a new Node for root
RBTree::RBTree(/* args */) : root(nullptr) {}

RBTree::~RBTree()
{
}
struct Node *RBTree::newNode(int new_data)
{
    struct Node *temp = new Node;
    temp->data = new_data;
    temp->color = 0; // Red:0
    temp->left = temp->right = nullptr;
    temp->parent = nullptr;
    return temp;
}
struct Node *RBTree::CreateTree(struct Node *node, int node_data)
{
    if (node == nullptr)
        return newNode(node_data);
    if (node_data > node->data)
    {
        struct Node *rchild = CreateTree(node->right, node_data);
        node->right = rchild;
        rchild->parent = node;
    }
    else
    {
        struct Node *lchild = CreateTree(node->left, node_data);
        node->left = lchild;
        lchild->parent = node;
    }

    return node;
};
struct Node RBTree::copy_object(struct Node *node)
{
    struct Node temp;
    temp = *node;
    temp.color = node->color;
    temp.data = node->data;
    temp.parent = node->parent;
    temp.left = node->left;
    temp.right = node->right;

    return temp;
}

struct Node *RBTree::Search(struct Node *tree, int key)
{
    if (tree == nullptr || key == tree->data)
    {
        return tree;
    }
    if (key < tree->data)
        return Search(tree->left, key);
    return Search(tree->right, key);
}
void RBTree::Left_Rotate(struct Node *tree, struct Node *x)
{
    struct Node *y;
    y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;    // link x's parent to y
    if (x->parent == nullptr) // x  = root
        tree = y;
    else if (x == x->parent->left) // 将x的父节点替换为旋转的节点。
        x->parent->left = y;
    else // 父节点的右侧替换。
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}
void RBTree::Right_Rotate(struct Node *tree, struct Node *x)
{

    struct Node *y;
    y = x->left; // set x ;
    x->left = y->right;
    if (y->right != nullptr)  // y.right 的右边不为空。
        y->right->parent = x; //从底下反向连接。
    y->parent = x->parent;    // link
    if (x->parent == nullptr)
        tree = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}
void RBTree::Insert_Fixup(struct Node *tree, struct Node *newNode)
{
    struct Node *y = nullptr;
    struct Node *x = nullptr;
    while (newNode->parent->color == 0)
    {
        //此处的Node parent ， parent为空
        if (newNode->parent == newNode->parent->parent->left)
        {
            y = newNode->parent->parent->right;
            if (y->color == 0)
            {
                newNode->parent->color = 1;         // Black , case 1
                y->color = 1;                       // Black, case 1
                newNode->parent->parent->color = 0; // Red , case 1
                newNode = newNode->parent->parent;  // case 1
            }
            else
            {
                if (newNode == newNode->parent->right)
                {

                    newNode = newNode->parent; // case 2
                    Left_Rotate(tree, newNode);
                }
                newNode->parent->color = 1;                  // Black , case 3
                newNode->parent->parent->color = 0;          // case 3
                Right_Rotate(tree, newNode->parent->parent); // case 3
            }
        }
        else
        {
            y = newNode->parent->parent->left;
            if (y->color == 0)
            {
                newNode->parent->color = 1;         // Black , case 1
                y->color = 1;                       // Black, case 1
                newNode->parent->parent->color = 0; // Red , case 1
                newNode = newNode->parent->parent;  // case 1
            }
            else
            {
                if (newNode == newNode->parent->left)
                {
                    newNode = newNode->parent; // case 2
                    Right_Rotate(tree, newNode);
                }
                newNode->parent->color = 1;                 // Black , case 3
                newNode->parent->parent->color = 0;         // case 3
                Left_Rotate(tree, newNode->parent->parent); // case 3
            }
        }
        if (newNode == tree)
            break;
    }
    tree->color = 1; // Black;
}
void RBTree::Insert(struct Node *tree, struct Node *newNode)
{
    struct Node *Node_current = nullptr;
    struct Node *Node_next = tree;

    // tarvel whole tree and find Node_current = spercific position
    while (Node_next != nullptr)
    {
        Node_current = Node_next;
        if (newNode->data < Node_next->data)
            Node_next = Node_next->left; //
        else
            Node_next = Node_next->right; //
    }
    newNode->parent = Node_current;

    // put the newNode in Node_current position
    if (Node_current == nullptr) // if no root
        tree = newNode;
    else if (newNode->data < Node_current->data)
        Node_current->left = newNode;
    else
        Node_current->right = newNode;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->color = 0; // Red

    Insert_Fixup(tree, newNode);
}

void RBTree::Traverse(struct Node *root)
{
    using namespace std;
    if (!root)
    {
        return;
    }
    Traverse(root->left);
    cout << " || " << root->data << " " << root->color << " || ";
    Traverse(root->right);
}

void RBTree::Tansplant(struct Node *tree, struct Node *u, struct Node *v)
{
    if (u->parent == nullptr)
    {
        tree = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    if (v == nullptr)
        v->parent = nullptr;
    v->parent = u->parent; // v-parent is ？？，cannot give a number
}
void RBTree::Delete_Fixup(struct Node *tree, struct Node *x)
{
    struct Node *w;
    while (x != tree && x->color == 1)
    {
        if (x == x->parent->left)
        {
            w = x->parent->right;
            if (w->color == 0) // red
            {
                w->color = 1;
                x->parent->color = 0;
                Left_Rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 1 && w->right->color == 1)
            {
                w->color = 0;
                x = x->parent;
            }
            else
            {
                if (w->right->color == 1)
                {
                    w->left->color = 1;
                    w->color = 0;
                    Right_Rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 1;
                w->right->color = 1;
                Left_Rotate(tree, x->parent);
                x = tree;
            }
        }
        else
        {
            w = x->parent->left;
            if (w->color == 0) // red
            {
                w->color = 1;
                x->parent->color = 0;
                Right_Rotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->left->color == 1 && w->right->color == 1)
            {
                w->color = 0;
                x = x->parent;
            }
            else
            {
                if (w->left->color == 1)
                {
                    w->right->color = 1;
                    w->color = 0;
                    Left_Rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 1;
                w->left->color = 1;
                Right_Rotate(tree, x->parent);
                x = tree;
            }
        }
    }
    x->color = 1;
}

void RBTree::Delete(struct Node *tree, int key)
{
    struct Node *y = nullptr;
    struct Node *x = nullptr;
    struct Node *z = nullptr; // the node which attempt to remove
    while (tree != nullptr)
    {
        if (tree->data == key)
        {
            z = tree;
        }

        if (tree->data <= key)
        {
            tree = tree->right;
        }
        else
        {
            tree = tree->left;
        }
    }

    if (z == nullptr)
    {
        std::cout << "Couldn't find key in the tree" << std::endl;
        return;
    }

    y = z;
    bool y_original_color = y->color;
    if (z->left == nullptr)
    {
        x = z->right;
        Tansplant(tree, z, z->right);
    }
    else if (z->right == nullptr)
    {
        x = z->left;
        Tansplant(tree, z, z->left);
    }
    else
    {
        y = Min(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            Tansplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        Tansplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == 1)
    {
        Delete_Fixup(tree, x);
    }
}

struct Node *RBTree::Min(struct Node *node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}
struct Node *RBTree::Max(struct Node *node)
{
    while (node->right != nullptr)
    {
        node = node->right;
    }
    return node;
}
int RBTree::countNodes(struct Node *root)
{
    struct Node *current, *pre;
    int count = 0;

    if (root == nullptr)
        return count;

    current = root;
    while (current != nullptr)
    {
        if (current->left == nullptr)
        {
            count++;
            current = current->right;
        }
        else
        {
            pre = current->left;
            while (pre->right != nullptr &&
                   pre->right != current)
                pre = pre->right;

            if (pre->right == nullptr)
            {
                pre->right = current;
                current = current->left;
            }
            else
            {
                pre->right = nullptr;
                count++;
                current = current->right;
            }
        }
    }

    return count;
}

int RBTree::Medinan(struct Node *root)
{
    if (root == nullptr)
        return 0;

    int count = countNodes(root);
    int currCount = 0;
    struct Node *current = root, *pre = nullptr, *pre_value = nullptr;

    while (current != nullptr)
    {
        if (current->left == nullptr)
        {
            currCount++;
            // check middle - odd
            if (count % 2 != 0 && currCount == (count + 1) / 2)
                return pre_value->data;

            // check middle - even
            else if (count % 2 == 0 && currCount == (count / 2) + 1)
                return (pre_value->data + current->data) / 2;

            pre_value = current;
            current = current->right;
        }
        else
        {
            pre = current->left;
            while (pre->right != nullptr && pre->right != current)
                pre = pre->right;

            if (pre->right == nullptr)
            {
                pre->right = current;
                current = current->left;
            }
            else
            {
                pre->right = nullptr;
                pre_value = pre;
                currCount++;
                if (count % 2 != 0 && currCount == (count + 1) / 2)
                    return current->data;

                else if (count % 2 == 0 && currCount == (count / 2) + 1)
                    return (pre_value->data + current->data) / 2;
                pre_value = current;
                current = current->right;
            }
        }
    }
    return 0;
}

void RBTree::Intersection(struct Node *root1, struct Node *root2)
{
    using namespace std;
    std::stack<Node *> s1, s2;

    while (1)
    {
        // push all data of first tree to stack1
        if (root1)
        {
            s1.push(root1);
            root1 = root1->left;
        }

        // push all data of second tree to stack2
        else if (root2)
        {
            s2.push(root2);
            root2 = root2->left;
        }

        else if (!s1.empty() && !s2.empty())
        {
            root1 = s1.top();
            root2 = s2.top();

            // find one node
            if (root1->data == root2->data)
            {
                cout << root1->data << " ";
                s1.pop();
                s2.pop();

                // find the bigger node
                root1 = root1->right;
                root2 = root2->right;
            }

            else if (root1->data < root2->data)
            {
                // 1. pop the current node, to finde a bigger on
                // 2. fin a new node of root2
                s1.pop();
                root1 = root1->right;
                root2 = nullptr;
            }
            else if (root1->data > root2->data)
            {
                s2.pop();
                root2 = root2->right;
                root1 = nullptr;
            }
        }

        // Both roots and both stacks are empty
        else
            break;
    }
}
int main()
{
    using namespace std;
    int a[] = {15, 30, 10};
    int b[] = {10, 456, 78, 30, 9, 20};
    int ilen = (sizeof(a)) / (sizeof(a[0]));
    int ilen2 = (sizeof(b)) / (sizeof(b[0]));
    RBTree tree = RBTree();
    struct Node *root = nullptr;
    struct Node *root2 = nullptr;
    //========Orignial data========//
    cout << "== Orignial data : ";
    for (int i = 0; i < ilen; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    //===create a new tree ======//
    for (int j = 0; j < ilen; j++)
    {
        root = tree.CreateTree(root, a[j]);
    }
    for (int j = 0; j < ilen2; j++)
    {
        root2 = tree.CreateTree(root2, b[j]);
    }
    cout << "== New Tree : ";
    tree.Traverse(root);
    cout << endl;
    tree.Traverse(root2);
    cout << endl;
    //=========search===========//
    struct Node *search;
    search = tree.Search(root, 10);
    cout << "== Key, is in the tree, " << search->data << endl;
    //=========insert===========//
    // insert problem :
    // 1. if i try to insert more number, insertFIxup will crush. cannot sure the problem is
    //
    struct Node *newNode = tree.newNode(40);
    tree.Insert(root, newNode);
    tree.Traverse(root);

    //=========delete===========//
    // Still have problem cannot solve:
    // ERROE:x->parent = some number is not possible
    // struct Node *deleteNode = tree.newNode(10);
    // tree.Delete(root, 30);
    // tree.Traverse(root);
    //========= Max, Min ===========//
    // std::cout << "\n==the MIN in this tree is node: " << tree.Min(root)->data << std::endl;
    // std::cout << "\n==the MAX in this tree is node: " << tree.Max(root)->data << std::endl;
    //========= Medinan ===========//
    cout << "\n==Median of Tree is " << tree.Medinan(root);

    //========= intersection ===========//
    cout << "\n== Intersection ";
    // tree.Intersection(root, root2);
    return 0;
}