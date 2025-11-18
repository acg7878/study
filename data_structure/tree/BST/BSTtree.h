#ifndef BSTTREE_H
#define BSTTREE_H

struct BSTNode {
  BSTNode* left;
  BSTNode* right;
  int val;

  BSTNode() : left(nullptr), right(nullptr), val(0) {}
  BSTNode(BSTNode* l, BSTNode* r, int v) : left(l), right(r), val(v) {}
  BSTNode(int v) : left(nullptr), right(nullptr), val(v) {}
};

class BST {
 private:
  BSTNode* root;

  BSTNode* _insert(BSTNode* node, int val);
  BSTNode* _remove(BSTNode* node, int val);
  bool _search(BSTNode* node, int val) const;
  void _inorder(BSTNode* node) const;
  void _preorder(BSTNode* node) const;
  void _postorder(BSTNode* node) const;
  BSTNode* _findMin(BSTNode* node) const;
  BSTNode* _findMax(BSTNode* node) const;
  void _destroyTree(BSTNode* node);

 public:
  BST() : root(nullptr) {}
  ~BST() { _destroyTree(root); }

  void insert(int val);
  void remove(int val);
  bool search(int val) const;
  void inorder() const;
  void preorder() const;
  void postorder() const;
  int findMin() const;
  int findMax() const;
  bool isEmpty() const;
};

#endif  // BSTTREE_H