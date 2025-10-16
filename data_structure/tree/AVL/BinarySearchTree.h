#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;

    Node(int value) : key(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(int key);
    Node* search(int key);
    void remove(int key);

    void inorderTraversal();
    void preorderTraversal();
    void postorderTraversal();

    Node* getRoot();

private:
    Node* root;

    void insertNode(Node*& node, int key, Node* parent);
    Node* searchNode(Node* node, int key);
    void removeNode(Node*& node);
    Node* findMin(Node* node);

    void inorder(Node* node);
    void preorder(Node* node);
    void postorder(Node* node);
    void destroyTree(Node* node);
};

#endif // BINARY_SEARCH_TREE_H
