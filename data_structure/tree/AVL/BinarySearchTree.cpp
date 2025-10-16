#include "BinarySearchTree.h"
#include <iostream>

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

void BinarySearchTree::destroyTree(Node* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void BinarySearchTree::insert(int key) {
    insertNode(root, key, nullptr);
}

void BinarySearchTree::insertNode(Node*& node, int key, Node* parent) {
    if (node == nullptr) {
        node = new Node(key);
        node->parent = parent;
    } else if (key < node->key) {
        insertNode(node->left, key, node);
    } else if (key > node->key) {
        insertNode(node->right, key, node);
    }
}

Node* BinarySearchTree::search(int key) {
    return searchNode(root, key);
}

Node* BinarySearchTree::searchNode(Node* node, int key) {
    if (node == nullptr || node->key == key) {
        return node;
    }

    if (key < node->key) {
        return searchNode(node->left, key);
    } else {
        return searchNode(node->right, key);
    }
}

void BinarySearchTree::remove(int key) {
    Node* nodeToRemove = search(key);
    if (nodeToRemove != nullptr) {
        removeNode(nodeToRemove);
    }
}

void BinarySearchTree::removeNode(Node*& node) {
    if (node->left == nullptr) {
        // Node has no left child or no children at all
        Node* child = node->right;
        if (node->parent != nullptr) {
            if (node == node->parent->left) {
                node->parent->left = child;
            } else {
                node->parent->right = child;
            }
        } else {
            root = child;
        }
        if (child != nullptr) {
            child->parent = node->parent;
        }
        delete node;
        node = nullptr;
    } else if (node->right == nullptr) {
        // Node has only a left child
        Node* child = node->left;
        if (node->parent != nullptr) {
            if (node == node->parent->left) {
                node->parent->left = child;
            } else {
                node->parent->right = child;
            }
        } else {
            root = child;
        }
        if (child != nullptr) {
            child->parent = node->parent;
        }
        delete node;
        node = nullptr;
    } else {
        // Node has two children
        Node* successor = findMin(node->right);
        node->key = successor->key;
        removeNode(successor);
    }
}

Node* BinarySearchTree::findMin(Node* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void BinarySearchTree::inorderTraversal() {
    inorder(root);
    std::cout << std::endl;
}

void BinarySearchTree::inorder(Node* node) {
    if (node) {
        inorder(node->left);
        std::cout << node->key << " ";
        inorder(node->right);
    }
}

void BinarySearchTree::preorderTraversal() {
    preorder(root);
    std::cout << std::endl;
}

void BinarySearchTree::preorder(Node* node) {
    if (node) {
        std::cout << node->key << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

void BinarySearchTree::postorderTraversal() {
    postorder(root);
    std::cout << std::endl;
}

void BinarySearchTree::postorder(Node* node) {
    if (node) {
        postorder(node->left);
        postorder(node->right);
        std::cout << node->key << " ";
    }
}

Node* BinarySearchTree::getRoot() {
    return root;
}
