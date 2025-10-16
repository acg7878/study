#include "AVLTree.h"

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    destroyTree(root);
}

void AVLTree::destroyTree(AVLNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

int AVLTree::getHeight(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

void AVLTree::updateHeight(AVLNode* node) {
    if (node != nullptr) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

int AVLTree::getBalance(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

void AVLTree::insert(int key) {
    root = insertNode(root, key);
}

AVLNode* AVLTree::insertNode(AVLNode* node, int key) {
    if (node == nullptr)
        return new AVLNode(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node; // Duplicate keys not allowed

    updateHeight(node);

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::remove(int key) {
    root = removeNode(root, key);
}

AVLNode* AVLTree::findMin(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

AVLNode* AVLTree::removeNode(AVLNode* node, int key) {
    if (node == nullptr)
        return node;

    if (key < node->key)
        node->left = removeNode(node->left, key);
    else if (key > node->key)
        node->right = removeNode(node->right, key);
    else {
        if ((node->left == nullptr) || (node->right == nullptr)) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else
                *node = *temp;
            delete temp;
        } else {
            AVLNode* temp = findMin(node->right);
            node->key = temp->key;
            node->right = removeNode(node->right, temp->key);
        }
    }

    if (node == nullptr)
        return node;

    updateHeight(node);

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLNode* AVLTree::search(int key) {
    return searchNode(root, key);
}

AVLNode* AVLTree::searchNode(AVLNode* node, int key) {
    if (node == nullptr || node->key == key) {
        return node;
    }

    if (key < node->key) {
        return searchNode(node->left, key);
    } else {
        return searchNode(node->right, key);
    }
}

void AVLTree::inorderTraversal() {
    inorder(root);
    std::cout << std::endl;
}

void AVLTree::inorder(AVLNode* node) {
    if (node != nullptr) {
        inorder(node->left);
        std::cout << node->key << " ";
        inorder(node->right);
    }
}
