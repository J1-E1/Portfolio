#include <iostream>

using namespace std;
class node
{
    int key;
    int value;
    node *left, *right;

public:
    node();
    node(int);

    node *insert(node *root, int value);
    void travel(node *);
};

node::node() : key(0), left(nullptr), right(nullptr)
{
}

node::node(int value)
{
    key = value;
    value = 0;
    left = nullptr;
    right = nullptr;
}

node *node::insert(node *root, int value)
{
    if (!root)// 如果向下遍历不为空，则继续一下if操作，遇见null跳出。
    {
        return new node(value);
    }
    if (value < root->key)
    {
        root->left = insert(root->left, value);
    }

    else
    {
        root->right = insert(root->right, value);
    }

    return root;
}

void node::travel(node *root)
{
    if (!root) // ?
    {
        return;
    }
    travel(root->left);
    cout << " " << root->key;
    travel(root->right);
}

int main()
{
    node tree;
    node *root = nullptr;
    root = tree.insert(root, 50);
    tree.insert(root, 30);
    tree.insert(root, 20);
    tree.insert(root, 40);
    tree.insert(root, 70);
    tree.insert(root, 60);
    tree.insert(root, 80);

    tree.travel(root);
    return 0;
}