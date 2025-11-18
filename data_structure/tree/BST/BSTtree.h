struct BSTNode {
  BSTNode* left;
  BSTNode* right;
  int val;

  BSTNode() : left(nullptr), right(nullptr), val(0) {}
  BSTNode(BSTNode* l, BSTNode* r, int v) : left(l), right(r), val(v) {}
};
