#include "BSTtree.h"
#include <iostream>
BSTNode* BST::_insert(BSTNode* node, int val) {
  if (node == nullptr) {
    return new BSTNode(val);
  }
  if (val < node->val) {
    node->left = _insert(node->left, val);
  } else if (val > node->val) {
    node->right = _insert(node->right, val);
  }
  return node;
}

void BST::insert(int val) {
  root = _insert(root, val);
}

BSTNode* BST::_remove(BSTNode* node, int val) {
  if (node == nullptr) {
    return nullptr;
  }
  if (val < node->val) {
    node->left = _remove(node->left, val);
  } else if (val > node->val) {
    node->right = _remove(node->right, val);
  } else {
    if (node->left == nullptr) {
      return node->right;
    }
    if (node->right == nullptr) {
      return node->left;
    }
    BSTNode* minNode = _findMin(node->right);
    node->val = minNode->val;
    node->right = _remove(node->right, minNode->val);
  }
  return node;
}

void BST::remove(int val) {
  root = _remove(root, val);
}

BSTNode* BST::_findMin(BSTNode* node) const {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->left == nullptr) {
    return node;
  }
  return _findMin(node->left);
}

int BST::findMin() const {
  BSTNode* minNode = _findMin(root);
  if (minNode == nullptr) {
    return -1;
  }
  return minNode->val;
}

BSTNode* BST::_findMax(BSTNode* node) const {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->right == nullptr) {
    return node;
  }
  return _findMax(node->right);
}

int BST::findMax() const {
  BSTNode* maxNode = _findMax(root);
  if (maxNode == nullptr) {
    return -1;
  }
  return maxNode->val;
}

bool BST::isEmpty() const {
  return root == nullptr;
}

void BST::_destroyTree(BSTNode* node) {
  if (node == nullptr) {
    return;
  }
  _destroyTree(node->left);
  _destroyTree(node->right);
  delete node;
}

void BST::inorder() const {
  _inorder(root);
}

void BST::preorder() const {
  _preorder(root);
}

void BST::postorder() const {
  _postorder(root);
}

bool BST::search(int val) const {
  return _search(root, val);
}

void BST::_inorder(BSTNode* node) const {
  if (node == nullptr) {
    return;
  }
  _inorder(node->left);
  std::cout << node->val << " ";
  _inorder(node->right);
}

void BST::_preorder(BSTNode* node) const {
  if (node == nullptr) {
    return;
  }
  std::cout << node->val << " ";
  _preorder(node->left);
  _preorder(node->right);
}

void BST::_postorder(BSTNode* node) const {
  if (node == nullptr) {
    return;
  }
  _postorder(node->left);
  _postorder(node->right);
  std::cout << node->val << " ";
}

bool BST::_search(BSTNode* node, int val) const {
  if (node == nullptr) {
    return false;
  }
  if (node->val == val) {
    return true;
  }
  if (val < node->val) {
    return _search(node->left, val);
  } else {
    return _search(node->right, val);
  }
}