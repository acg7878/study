#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <algorithm>

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(int key);
    void remove(int key);
    AVLNode* search(int key);
    void inorderTraversal();

private:
    AVLNode* root;

    int getHeight(AVLNode* node);
    int getBalance(AVLNode* node);
    void updateHeight(AVLNode* node);

    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);

    AVLNode* insertNode(AVLNode* node, int key);
    AVLNode* removeNode(AVLNode* node, int key);
    AVLNode* findMin(AVLNode* node);

    AVLNode* searchNode(AVLNode* node, int key);
    void inorder(AVLNode* node);
    void destroyTree(AVLNode* node);
};

#endif // AVLTREE_H
