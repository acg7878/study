#include <iostream>
#include "BinarySearchTree.h"
#include "AVLTree.h"

void testBST() {
    std::cout << "--- Testing Binary Search Tree ---" << std::endl;
    BinarySearchTree bst;
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    for (int key : keys) {
        bst.insert(key);
    }

    std::cout << "Inorder traversal: ";
    bst.inorderTraversal();

    std::cout << "Preorder traversal: ";
    bst.preorderTraversal();

    std::cout << "Postorder traversal: ";
    bst.postorderTraversal();

    std::cout << "Searching for 40: " << (bst.search(40) ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 90: " << (bst.search(90) ? "Found" : "Not Found") << std::endl;

    std::cout << "Removing 20" << std::endl;
    bst.remove(20);
    std::cout << "Inorder traversal after removing 20: ";
    bst.inorderTraversal();

    std::cout << "Removing 30" << std::endl;
    bst.remove(30);
    std::cout << "Inorder traversal after removing 30: ";
    bst.inorderTraversal();

    std::cout << "Removing 50" << std::endl;
    bst.remove(50);
    std::cout << "Inorder traversal after removing 50: ";
    bst.inorderTraversal();
    std::cout << std::endl;
}

void testAVL() {
    std::cout << "--- Testing AVL Tree ---" << std::endl;
    AVLTree avl;
    int keys[] = {10, 20, 30, 40, 50, 25};
    for (int key : keys) {
        avl.insert(key);
        std::cout << "Inorder traversal after inserting " << key << ": ";
        avl.inorderTraversal();
    }

    std::cout << "Searching for 40: " << (avl.search(40) ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 90: " << (avl.search(90) ? "Found" : "Not Found") << std::endl;

    std::cout << "Removing 10" << std::endl;
    avl.remove(10);
    std::cout << "Inorder traversal after removing 10: ";
    avl.inorderTraversal();

    std::cout << "Removing 40" << std::endl;
    avl.remove(40);
    std::cout << "Inorder traversal after removing 40: ";
    avl.inorderTraversal();
    std::cout << std::endl;
}

int main() {
    testBST();
    testAVL();

    return 0;
}
